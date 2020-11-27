#include <string>
#include <vector>
#include <change_velocity.hpp>
#include <query_client.hpp>
#include <variant_client.hpp>
#include <SmartsoftInf.h>

#ifndef MINZINC_H
#define MINZINC_H

class Minizinc {

public:

typedef struct DataPair
{
	std::string id;
	std::string value;
	std::string type;
	SmartsoftInf smartsoftinfo;
	
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

	std::shared_ptr<QueryClient> query_client_;
	std::shared_ptr<VariantClient> variant_client_;
protected:

    /**
     * This method parses the output string resulted from a Minizinc solver
     * 
     * @param outputs parsing results
     */
	void ParseSolution();

public:
	Minizinc();

	Minizinc(std::string mzn_path,std::string dzn_path, std::vector<DataPair> parameters, std::vector<DataPair> varPoints);
    
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

    /**
     * Update value of parameter in the buffer of minizinc
     * 
     * @param param Name of parameter
     * @param value New value of parameter
     * 
     */
	void updateParameter(std::string param,std::string value);

    /**
     * Compare old and new solutions
     * 
     * @param newSolutions New solutions vector
     * 
     */
	void checkSolutions(std::vector<DataPair> newSolutions);

    /**
     * Abort current skill
     * 
     * @param value Time you will be standing (milisec)
     * 
     */
	void abortCurrentSkill(double value);
    /**
     * Clears the spaces in a string
     * 
     * @param str string to be cleared 
     * @return cleared string
     */
	std::string removeSpaces(std::string str);

    /**
     * Checks if a file is empty
     * 
     * @param pFile file
     * @return bool 
     */	
	bool is_empty(std::ifstream &pFile);

};


#endif

