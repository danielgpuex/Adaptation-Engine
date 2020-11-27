#include "Output.h" // header in local directory
#include <iostream> // header in standard library
using namespace std;

Output::Output() {
	this->mzn_id = "";
	this->type = "";
	this->name = "";
	this->namesp = "";
	this->datatype = "";
}
Output::Output(string mzn_id, string type, string name, string namesp,
		string datatype, SmartsoftInf smartsoftInf) {
	this->mzn_id = mzn_id;
	this->type = type;
	this->name = name;
	this->namesp = namesp;
	this->datatype = datatype;
	this->smartsoftInf = smartsoftInf;
}

string Output::getMznId() {
	return this->mzn_id;
}
void Output::setMznId(string mznId) {
	this->mzn_id = mznId;
}

string Output::getDatatype() {
	return this->datatype;
}
void Output::setDatatype(string datatype) {
	this->datatype = datatype;
}

string Output::getName() {
	return this->name;
}
void Output::setName(string name) {
	this->name = name;
}
string Output::getNamesp() {
	return this->namesp;
}
void Output::setNamesp(string namesp) {
	this->namesp;
}
string Output::getType() {
	return this->type;
}
void Output::setType(string type) {
	this->type = type;
}

SmartsoftInf Output::getSmartsoftInf() {
	return this->smartsoftInf;
}

void Output::setSmartsoftInf(SmartsoftInf smarsoftInf) {
	this->smartsoftInf = smarsoftInf;
}
