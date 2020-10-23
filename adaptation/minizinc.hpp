#include <string>
#include <vector>
#ifndef MINZINC_H
#define MINZINC_H
namespace miron {

class Minizinc {

public:

typedef struct DataPair
{
	std::string id;
	std::string value;
};

typedef struct Solution
{
	std::vector<DataPair> output;
	std::string msg;
};

private:
	std::string mzn_path_;
	std::string dzn_path_;
	std::vector<DataPair> buffer;
	std::vector<DataPair> inputs;
	Solution *solutions;
	//std::string json_path_;
protected:

    /**
     * This method parses the output string resulted from a Minizinc solver
     * 
     * @param outputs parsing results
     */
	void ParseSolution(Solution* outputs);

public:


	Minizinc(const std::string mzn_path, const std::string dzn_path,const std::vector<std::string> varPoints);
    
    /**
     * @brief Destroy the Reasoner object
     */
	virtual ~Minizinc();

    /**
     * It runs the solver for a given input
     * 
     * @param outputs Gives the configuration for variation points
     * @return int 0 when the execution is successful, otherwise -1
     */
	int Run();

    /**
     * It runs the solver for a given input
     * 
     * @param outputs Gives the configuration for variation points
     * @param display_msgs The results are display in the console when true
     * @return int 0 when the execution is successful, otherwise -1
     */
	int Run(bool display_msgs);

	void updateParameter(std::string param,std::string value);

	void checkSolutions(std::vector<DataPair> newSolutions);


	std::string removeSpaces(std::string str);

};

}
#endif

