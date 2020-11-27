#include <string>
#ifndef SMARTSOFTINF_H
#define SMARTSOFTINF_H
using namespace std;
//This class stores the smartsoft information. The change of parameters needs this information.
class SmartsoftInf {
private:
	string parameterSetRepository;
	string parameterSet;
	string component;
	string parameter;
public:
	//Default constructor
	SmartsoftInf();
	/* This constructor receives the smartsoft parameters
	 * @param parameterSetRepository
	 * @param parameterSet 
	 * @param component
	 * @param parameter
	 * */
	SmartsoftInf(string parameterSetRepository,string parameterSet,string component,string parameter);

	/* 
	 * This method returns the parameterSetRepository value
	 */
	string getParameterSetRepository();

	/* 
	 * @param parameterSetRepository replace the value of the parameterSetRepository
	 */	
	void setParameterSetRepository(string parameterSetRepository);
	/* 
	 * This method returns the parameterSet value
	 */	
	string getParameterSet();
	void setParameterSet(string pSet);
	/* 
	 * This method returns the component value
	 */
	string getComponent();
	/* 
	 * @param component replace the value of the component
	 */		
	void setComponent(string component);
	/* 
	 * This method returns the parameter value
	 */	
	string getParameter();
	/* 
	 * @param parameter replace the value of the parameter
	 */		
	void setParameter(string parameter);
};

#endif

