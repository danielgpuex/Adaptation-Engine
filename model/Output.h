#include <string>
#include <SmartsoftInf.h>

#ifndef OUTPUT_H
#define OUTPUT_H
using namespace std;
//This class contains information about the output objects into the .io file.
class Output {
private:
	string mzn_id;
	string type;
	string name;
	string namesp;
	string datatype;
	SmartsoftInf smartsoftInf;
public:
	//Default constructor
	Output();
	/* This constructor receives the output information from the .io file
	 * @param mzn_id 
	 * @param type 
	 * @param name
	 * @param namesp
	 * @param datatype
	 * @param smartsoftInf
	 * */	
	Output(string mzn_id,string type,string name,string namesp,string datatype, SmartsoftInf smartsoftInf);
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
	 * @param datatype mznId the value of the mzn_id
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
	/* 
	 * This method returns the smartsoftInf value
	 */		
	SmartsoftInf getSmartsoftInf();
	/* 
	 * @param smartsoftInf replace the value of the smartsoftInf
	 */		
	void setSmartsoftInf(SmartsoftInf smartsoftInf);
};

#endif

