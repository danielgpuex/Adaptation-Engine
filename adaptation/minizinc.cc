#include "minizinc.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace miron {

Minizinc::Minizinc(const std::string mzn_path, const std::string dzn_path, std::vector<string> varPoints) {
	solutions=new Solution();
	mzn_path_ = mzn_path;
	dzn_path_ = dzn_path;
	DataPair dp;
	//Create the buffer
	for (int i = 0; i < varPoints.size(); ++i) {
		dp.id=varPoints[i];
		dp.value="-1";
		buffer.push_back(dp);
	}


	FILE *fp;
	char output[1035];
	bool error = false;
	std::string command;

	// Checking minizinc command
	command = "minizinc --version 2>&1 1>/dev/null";
	//cout << "Command: "<< command << endl;
	fp = popen(command.c_str(), "r");

	if (fp == NULL) {
		std::cerr << "[Minizinc]" << std::endl;
		std::cerr
				<< "\tAn error has been encountered while checking the minizinc command"
				<< std::endl;
		error = true;
	} else {
		while (fgets(output, sizeof(output) - 1, fp) != NULL) {
			printf("[Minizinc] \t%s", output);
			error = true;
		}
		pclose(fp);
	}
	if (error)
		exit(EXIT_FAILURE);
}

Minizinc::~Minizinc() {
}

bool is_empty(std::ifstream &pFile) {
	return pFile.good();
}

void Minizinc::ParseSolution(Solution *outputs) {
	std::string msg = outputs->msg;
	size_t pos1 = 0;
	size_t pos2 = 0;
	std::string assignment_token;
	std::string assignment_delimiter = ";";
	std::string blankspace_delimiter = " ";
	std::string param_delimiter = "=";
	DataPair varpoint;
	vector<DataPair> newSolutions;
	ofstream solutionsFile;
	ifstream sFile(
			"/home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build/solutions.txt");
	bool existsFile = false;
	if (is_empty(sFile)) {
		existsFile = true;
	}
	sFile.close();
	if (!existsFile)
		solutionsFile.open("solutions.txt");

	//Removes the spaces in the string
	//msg.erase(remove_if(msg.begin(), msg.end(), isspace), msg.end());

	// Tokinizes the string
	while ((pos1 = msg.find(assignment_delimiter)) != std::string::npos) {
		assignment_token = msg.substr(0, pos1);
		if ((pos2 = assignment_token.find(param_delimiter))
				!= std::string::npos) {
			varpoint.id = assignment_token.substr(0, pos2);
			varpoint.value = assignment_token.substr(pos2 + 1,
					assignment_token.length());
			//Check previous value
			//outputs->output.push_back(varpoint);
			newSolutions.push_back(varpoint);
			if (!existsFile)
				solutionsFile << varpoint.id << "=" << varpoint.value << "\n";
			cout << varpoint.id << "=" << varpoint.value << endl;
		}
		msg.erase(0, pos1 + assignment_delimiter.length());
	}
	if (!existsFile)
		solutionsFile.close();

	checkSolutions(newSolutions);
}
void Minizinc::checkSolutions(vector<DataPair> newSolutions){
	for (int i= 0; i < solutions->output.size(); ++i) {
		for (int j = 0; j< newSolutions.size(); ++j) {
			if(solutions->output[i].id==newSolutions[j].id){
				if(solutions->output[i].value!=newSolutions[j].value){
					solutions->output[i].value=newSolutions[j].value;

					//Call ZMQ
				}
			}
		}
	}
}


int Minizinc::Run() {
	return Run(false);
}

int Minizinc::Run(bool display_msgs) {
	FILE *fp;
	char output_str[1035];
	std::string command;
	std::string context_str;
	std::string solution_str;
	int result = 0;

	// Getting the parameters as string
	context_str = "";
	for (unsigned int i = 0; i < inputs.size(); i++) {
		context_str.append(inputs[i].id.c_str());
		context_str.append("=");
		context_str.append(inputs[i].value.c_str());
		context_str.append(";");
	}

	// Running minizinc command to execute the optimization
	if (result == 0) {
		command = "minizinc -D \"" + context_str + "\" " + mzn_path_ + " "
				+ dzn_path_;
		/*+ mzn_path_.substr(0,mzn_path_.size()-3) + "ozn --output-to-file "
		 + mzn_path_.substr(0,mzn_path_.size()-3) + "fzn\"";*/

		//Print minizinc command
		//cout << "Command new:" << command << endl;
		fp = popen(command.c_str(), "r");
		if (fp == NULL) {
			std::cerr << "[Minizinc.run]" << std::endl;
			std::cerr
					<< "\tAn error has been encountered while executing minizinc"
					<< std::endl;
			result = -1;

		} else {

			// Getting the solution
			while (fgets(output_str, sizeof(output_str) - 1, fp) != NULL) {
				solution_str.append(output_str);
				//Remove blank spaces before write into a txt file
				solution_str = removeSpaces(solution_str);
				if (display_msgs) {
					printf("[Minizinc.run] \t%s", output_str);
				}
			}

			solutions->msg = solution_str;
			ParseSolution(solutions);
			pclose(fp);
		}
	}

	return result;
}

void Minizinc::updateParameter(std::string param,std::string value){
	for (int i = 0; i < buffer.size(); ++i) {
		if(buffer[i].id==param){
			buffer[i].value=value;
		}
	}
}

string Minizinc::removeSpaces(string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

}
