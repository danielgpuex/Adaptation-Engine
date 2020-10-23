#include "adaptation/minizinc.hpp"
#include "adaptation/minizinc.cc"

//DDS
#include <RoqmeReaderImpl.h>
#include "RoqmeDDSManager.h"
#include "RoqmeConstantDefinitions.h"
#include "RoqmeDataWriter.h"
#include <RoqmeWriterImpl.h>
#include "listener/listeners_impl.cpp"
#include "RoqmeDDSListener.h"
//DDS

////ZMQ
//
//#include "zhelpers.hpp"
//#include "positions.hpp"
//#include "change_velocity.hpp"
//#include <thread>
//#include <mutex>
//#include "variant_client.hpp"
//#include "query_client.hpp"
//#include <abort_current_skill.hpp>
////ZMQ

#include <iostream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "TopicVar.h"
#include <map>
#include <iterator>
using namespace std;
using namespace Roqme;
using namespace rapidjson;

typedef struct Input {
	string id;
	string type;
	string name;
	string namesp;
};

//Execution args?
const string mzn_path_ =
		"/home/miron/MIRON-Project/ModelosDeEjemplo/Generated/test2.miron.mzn";
const string dzn_path_ =
		"/home/miron/MIRON-Project/ModelosDeEjemplo/Generated/test2.miron.dzn";
const string json_path_ =
		"/home/miron/MIRON-Project/ModelosDeEjemplo/Generated/test2.miron.inputs";
std::vector<miron::Minizinc::DataPair> buffer;

std::map<string, vector<string>> variantsListeners;
std::vector<Input> inputs;

std::vector<miron::Minizinc::DataPair> minizincParameters;

std::vector<string> varpoints;

/*
 * Check the individual solutions of the minizinc execution
 */
bool checkDataPair(miron::Minizinc::DataPair dataPair) {
	bool exists = false;
	bool change = false;
	std::vector<miron::Minizinc::DataPair> aux;

	for (miron::Minizinc::DataPair val : buffer) {
		if (val.id == dataPair.id) {
			exists = true;
			if (val.value != dataPair.value) {
				cout << "Differents values, update in the buffer" << endl;
				cout << "Send to Skill Server using ZMQ" << endl;
				change = true;
			} else {
				cout << "Not change" << endl;
			}
		}
		if (change) {
			aux.push_back(dataPair);
			change = false;
		} else {
			aux.push_back(val);
		}
	}
	buffer = aux;
	return change;
}
/*
 * Check the solutions before send data using ZMQ
 *
 * @param outputs
 */
void checkSolutions(miron::Minizinc::Solution *solutions) {
	cout << "Solutions: " << solutions->output[1].id << "="
			<< solutions->output[1].value << endl;
	std::string delimiter = "=";
	string line, name, value;
	ifstream myfile("solutions.txt");
	miron::Minizinc::DataPair dp;
	buffer.clear();
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			name = line.substr(0, line.find(delimiter));
			value = line.substr(line.find(delimiter) + 1, line.length());
			cout << "Name " << name << " Value " << value << endl;
			dp.id = name;
			dp.value = value;
			buffer.push_back(dp);
		}
		myfile.close();
	} else
		cout << "Unable to open file";

	for (miron::Minizinc::DataPair dataPair : solutions->output) {
		checkDataPair(dataPair);
	}

	//build the new solutions file
	ofstream solutionsFile;
	solutionsFile.open("solutions.txt");
	for (miron::Minizinc::DataPair val : buffer) {
		solutionsFile << val.id << "=" << val.value << "\n";
	}
	solutionsFile.close();

}
string readInputFile() {
	string jsonFile = "";
	string line;
	ifstream myfile(json_path_);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			jsonFile.append(line);
		}
		myfile.close();
	} else
		cout << "Unable to open file";

	return jsonFile;
}

bool existsInsertMap(string key, string value) {
	bool exists = false;
	std::map<std::string, vector<string>>::iterator it =
			variantsListeners.begin();
	vector<string> actualValues;
	if (variantsListeners.count(key) > 0) {
		exists = true;
		variantsListeners[key].push_back(value);
	}
	if (!exists) {
		vector<string> vals;
		vals.push_back(value);
		variantsListeners.insert(pair<string, vector<string>>(key, vals));
	}

	// Iterate over the map using Iterator till end.
	return exists;
}
void loadFromJSONInputs() {
	Input input;
	// 1. Parse a JSON string into DOM.
	string json = readInputFile();
	const char *jsonC = json.c_str();
	Document d;
	d.Parse(jsonC);
	Value &s = d["inputs"];
	assert(s.IsArray());

	for (auto &v : s.GetArray()) {
		//existsInsertMap(v["type"].GetString(), v["name"].GetString());
		input.id = v["id"].GetString();
		input.name = v["name"].GetString();
		input.type = v["type"].GetString();
		input.namesp = v["namespace"].GetString();
		inputs.push_back(input);
		//insert to input vector
	}
	/*cout << variantsListeners["Property"][0] << endl;
	 std::map<std::string, vector<string>>::iterator it = variantsListeners.begin();
	 // Iterate over the map using Iterator till end.
	 while (it != variantsListeners.end())
	 {
	 // Accessing KEY from element pointed by it.
	 std::string word = it->first;
	 // Accessing VALUE from element pointed by it.
	 vector<string> count = it->second;
	 std::cout << word << " :: " << count.size() << std::endl;
	 // Increment the Iterator to point to next entry
	 it++;
	 }*/

}
void initListeners() {
	for (int i = 0; i < inputs.size(); ++i) {

	}
	/*if (variantsListeners.count("Property") > 0) { //One if for each DDS Listener
	 RoqmeEstimateReader estimateReader(
	 new EstimateListener(variantsListeners["Property"]));
	 }

	 if (variantsListeners.count("Context") > 0) {
	 if (variantsListeners.count("Enum") > 0) { //One if for each DDS Context Listener
	 //TODO
	 }
	 }*/

}

void loadMinizincParameters() {
	vector<string> params;
	miron::Minizinc::DataPair dp;
	if (variantsListeners.count("boolean") > 0) { //One if for each DDS Listener
		params = variantsListeners["boolean"];
		for (int i = 0; i < params.size(); ++i) {
			dp.id = params[i];
			dp.value = "false";
			minizincParameters.push_back(dp);
		}
	}
	if (variantsListeners.count("VariationPoint") > 0) { //One if for each DDS Listener
		params = variantsListeners["VariationPoint"];
		for (int i = 0; i < params.size(); ++i) {
			dp.id = params[i];
			dp.value = "0";
			minizincParameters.push_back(dp);
		}
	}
}
int main(int argc, char *argv[]) {
	loadFromJSONInputs();
	initListeners();
	miron::Minizinc minizinc(mzn_path_, dzn_path_,
			variantsListeners["VariationPoint"]);
	miron::Minizinc::Solution *solution = new miron::Minizinc::Solution();
	//Start DDS Readers
	/*try {
	 RoqmeIntReader intReader(new IntContextListener);
	 RoqmeUIntReader uintReader(new UIntContextListener);
	 RoqmeDoubleReader doubleReader(new DoubleContextListener);
	 RoqmeBoolReader boolReader(new BoolContextListener);
	 RoqmeEnumReader enumReader(new EnumContextListener);
	 RoqmeEventReader eventReader(new EventContextListener);
	 RoqmeObservationReader observationReader(new ObservationListener);
	 RoqmeEstimateReader estimateReader(new EstimateListener);

	 //Test Publisher
	 Roqme::RoqmeDDSManager roqmeManager;

	 roqmeManager.createDoubleContextWriter();
	 roqmeManager.createEventContextWriter();

	 RoqmeDDSTopics::RoqmeDoubleContext int_data;
	 RoqmeDDSTopics::RoqmeEventContext event_data;

	 int_data.name("numero");
	 int_data.value() = { 1 };
	 roqmeManager.write(int_data);

	 int_data.name("numero");
	 int_data.value() = { 2 };
	 roqmeManager.write(int_data);

	 int_data.name("numero");
	 int_data.value() = { 3 };
	 roqmeManager.write(int_data);

	 int_data.name("numero");
	 int_data.value() = { 3 };
	 roqmeManager.write(int_data);
	 cout << "Pulsa para terminar ..." << endl;
	 std::cin.get();

	 intReader.close();
	 uintReader.close();
	 doubleReader.close();
	 boolReader.close();
	 enumReader.close();
	 eventReader.close();
	 observationReader.close();
	 estimateReader.close();
	 } catch (RoqmeDDSException &e) {
	 std::cerr << "Ups, algo fue mal: " << e.what() << std::endl;
	 }

	 //Start minizinc commands

	 std::vector<miron::Minizinc::DataPair> parameters;


	 //Execution args?. Contexts de DDS serán parametros.
	 miron::Minizinc::DataPair dp;
	 dp.id = "metric_intralogScenario_Performance";
	 dp.value = "1";
	 parameters.push_back(dp);

	 dp.id = "vp1_input";
	 dp.value = "false";
	 parameters.push_back(dp);

	 dp.id = "vp1_input_value";
	 dp.value = "0";
	 parameters.push_back(dp);

	 dp.id = "vp2_input";
	 dp.value = "false";
	 parameters.push_back(dp);

	 dp.id = "vp2_input_value";
	 dp.value = "0";
	 parameters.push_back(dp);

	 dp.id = "vp3_input";
	 dp.value = "false";
	 parameters.push_back(dp);

	 dp.id = "vp3_input_value";
	 dp.value = "0";
	 parameters.push_back(dp);
	 //solution->output={};
	 minizinc.Run(parameters, solution, true);
	 checkSolutions(solution);

	 delete solution;*/

	//End minizinc commands
}
