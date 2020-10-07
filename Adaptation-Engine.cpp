#include "adaptation/minizinc.hpp"
#include "adaptation/minizinc.cc"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string mzn_path_ = "/home/miron/MIRON-Project/ModelosDeEjemplo/Generated/test2.miron.mzn";
const string dzn_path_ = "/home/miron/MIRON-Project/ModelosDeEjemplo/Generated/test2.miron.dzn";
const string json_path_ = "/home/miron/MIRON-Project/ModelosDeEjemplo/Generated/test2.miron.inputs";

int main(int argc, char *argv[])
{
	miron::Minizinc minizinc(mzn_path_,dzn_path_);

	miron::Minizinc::Solution* solution ;
	std::vector<miron::Minizinc::DataPair> parameters;

	miron::Minizinc::DataPair dp;
	dp.id="metric_intralogScenario_Performance";
	dp.value="1";
	parameters.push_back(dp);

	dp.id="vp1_input";
	dp.value="false";
	parameters.push_back(dp);

	dp.id="vp1_input_value";
	dp.value="0";
	parameters.push_back(dp);

	dp.id="vp2_input";
	dp.value="false";
	parameters.push_back(dp);

	dp.id="vp2_input_value";
	dp.value="0";
	parameters.push_back(dp);

	dp.id="vp3_input";
	dp.value="false";
	parameters.push_back(dp);

	dp.id="vp3_input_value";
	dp.value="0";
	parameters.push_back(dp);

	minizinc.Run(parameters,solution, true);

}
