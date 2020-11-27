#include <string>
#ifndef INPUT_H
#define INPUT_H
using namespace std;
//This class contains information about the inputs objects into the .io file.
class Input {
private:
	string mzn_id;
	string type;
	string name;
	string namesp;
	string datatype;
public:
	//Default constructor
	Input();
	/* This constructor receives the input information from the .io file
	 * @param mzn_id 
	 * @param type 
	 * @param name
	 * @param namesp
	 * @param datatype
	 * */
	Input(string mzn_id,string type,string name,string namesp,string datatype);
	/* 
	 * This method returns the datatype value
	 */	
	string getDatatype();
	/* 
	 * @param datatype replace the value of the datatype
	 */		
	void setDatatype(string datatype);
	/* 
	 * This method returns the mzn_id value
	 */
	string getMznId();
	/* 
	 * @param mznId replace the value of the mzn_id
	 */	
	void setMznId(string mznId);
	/* 
	 * This method returns the name value
	 */	
	string getName();
	/* 
	 * @param name replace the value of the name
	 */		
	void setName(string name);
	/* 
	 * This method returns the namesp value
	 */	
	string getNamesp();
	/* 
	 * @param namesp replace the value of the namesp
	 */		
	void setNamesp(string namesp);
	/* 
	 * This method returns the type value
	 */	
	string getType();
	/* 
	 * @param type replace the value of the type
	 */		
	void setType(string type);
};

#endif

