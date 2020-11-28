//#include "minizinc.hpp"
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
#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "TopicVar.h"
#include "TopicVar.cc"
#include "Input.h"
#include "Input.cc"
#include "Output.h"
#include "Output.cc"

#include <map>
#include <iterator>
#include <stdlib.h>
using namespace std;
using namespace Roqme;
using namespace rapidjson;

//Execution args?
string mzn_path_;
string dzn_path_;
string json_path_;


std::map<string, vector<string>> variantsListeners;
std::vector<Input> inputs;
std::vector<Output> outputs;
std::vector<Minizinc::DataPair> minizincParameters;
std::vector<Minizinc::DataPair> varpoints;
RoqmeEstimateReader estimateReader;
RoqmeIntReader intReader;
RoqmeUIntReader uintReader;
RoqmeDoubleReader doubleReader;
RoqmeBoolReader boolReader;
RoqmeEnumReader enumReader;
RoqmeEventReader eventReader;
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

void loadFromJSONInputs() {
	Input input;
	string json = readInputFile();
	const char *jsonC = json.c_str();
	Document d;
	d.Parse(jsonC);
	Value &s = d["inputs"];
	SmartsoftInf smartsoftInfo = SmartsoftInf();
	Output output;
	assert(s.IsArray());

	for (auto &v : s.GetArray()) {
		input.setMznId(v["mzn_id"].GetString());
		input.setName(v["name"].GetString());
		input.setType(v["class"].GetString());
		input.setNamesp(v["namespace"].GetString());
		input.setDatatype(v["datatype"].GetString());

		inputs.push_back(input);
	}

	Value &f = d["outputs"];
	
	for (auto &element : f.GetArray()) {
		output.setMznId(element["mzn_id"].GetString());
		output.setName(element["name"].GetString());
		output.setType(element["class"].GetString());
		output.setNamesp(element["namespace"].GetString());
		output.setDatatype(element["datatype"].GetString());

		Value &smartsoft = element["smartsoft"];	
		if(smartsoft.HasMember("component")){
		smartsoftInfo.setComponent(smartsoft["component"].GetString());
		}
		if(smartsoft.HasMember("parameter")){
		smartsoftInfo.setParameter(smartsoft["parameter"].GetString());
		}		
		if(smartsoft.HasMember("parameterSet")){
		smartsoftInfo.setParameterSet(smartsoft["parameterSet"].GetString());
		}		
		if(smartsoft.HasMember("parameterSetRepository")){
		smartsoftInfo.setParameterSetRepository(smartsoft["parameterSetRepository"].GetString());
		}						
		output.setSmartsoftInf(smartsoftInfo);
		outputs.push_back(output);
	}

}
constexpr unsigned int str2int(const char *str, int h = 0) {
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
void initListeners(Minizinc minizinc) {
	vector<TopicVar> props;
	vector<TopicVar> doubles;
	vector<TopicVar> ints;
	vector<TopicVar> bools;
	vector<TopicVar> enums;
	TopicVar vp;
	for (int i = 0; i < inputs.size(); ++i) {
		if (inputs[i].getType() == "Property" || inputs[i].getType() == "Context") {
			vp = TopicVar(inputs[i].getName(), "-1", inputs[i].getMznId());
			props.push_back(vp);
		}

	}
	if (props.size() > 0) {
		RoqmeEstimateReader estimateReader(new EstimateListener(props, minizinc));
		RoqmeIntReader intReader(new IntContextListener(props, minizinc));
		RoqmeUIntReader uintReader(new UIntContextListener(props, minizinc));
		RoqmeDoubleReader doubleReader(
				new DoubleContextListener(props, minizinc));
		RoqmeBoolReader boolReader(new BoolContextListener(props, minizinc));
		RoqmeEnumReader enumReader(new EnumContextListener(props, minizinc));
		RoqmeEventReader eventReader(new EventContextListener(props, minizinc));

		cout << "Press any key to finish..." << endl;
		string out;
		cin >> out;
		cout << "Finishing..." << endl;

		estimateReader.close();
		intReader.close();
		uintReader.close();
		doubleReader.close();
		boolReader.close();
		enumReader.close();
		eventReader.close();
		exit(1);

	}

}

void loadMinizinc() {
	Minizinc::DataPair dp;

	for (int i = 0; i < inputs.size(); ++i) {
		if (inputs[i].getType() == "Property") { //For contexts, properties ... (name into inputs file) and execution parameters
			dp.id = inputs[i].getMznId();
			dp.value = "0";
			dp.type = inputs[i].getType();

		}

		if(inputs[i].getType() == "VariationPoint" ){
			dp.id = inputs[i].getMznId();
			dp.value = "0";
			dp.type = inputs[i].getType();
		}

		if(inputs[i].getType() == "Context"){
			if(inputs[i].getDatatype()== "EventType" || inputs[i].getDatatype()== "BooleanType"){
				dp.value = "false";
			}else{
				if(inputs[i].getDatatype()== "EnumType"){
					dp.value = "-1";				
				}else{
					dp.value = "0";				
				}
			}
			dp.id = inputs[i].getMznId();
			dp.type = inputs[i].getType();
		}
		if (inputs[i].getDatatype() == "BooleanType") { //For vp1_input ... (name into inputs file) and execution parameters
			dp.id = inputs[i].getMznId();
			dp.value = "false";
			dp.type = inputs[i].getType();
			
		}
		minizincParameters.push_back(dp);		

	}

	for (int i = 0; i < outputs.size(); i++)
	{
		dp.id = outputs[i].getMznId();
		dp.type = outputs[i].getDatatype();
		if(dp.type == "NumericSampledType"){
			dp.value = "-1";
			dp.smartsoftinfo = outputs[i].getSmartsoftInf();
		}else{
			dp.value = "null";
		}
		varpoints.push_back(dp);
	}
	
	Minizinc minizinc(mzn_path_, dzn_path_, minizincParameters, varpoints);
	initListeners(minizinc);

}
int main(int argc, char *argv[]) {
	// Check the number of parameters
	if (argc < 3) {
		// Tell the user how to run the program
		std::cerr << "Use 3 arguments: path of .mzn file, .dzn file and .io file" << std::endl;
		return 1;
	}
	std::cout << "Args: " << argv[1] << " - " << argv[2] << " - " << argv[3]
			<< std::endl;
	mzn_path_ = argv[1];
	dzn_path_ = argv[2];
	json_path_ = argv[3];
	loadFromJSONInputs();
	loadMinizinc();

}
