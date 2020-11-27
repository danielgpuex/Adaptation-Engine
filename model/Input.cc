#include "Input.h" // header in local directory
#include <iostream> // header in standard library
using namespace std;

Input::Input() {
	this->mzn_id = "";
	this->type = "";
	this->name = "";
	this->namesp = "";
	this->datatype = "";
}
Input::Input(string mzn_id, string type, string name, string namesp,
		string datatype) {
	this->mzn_id = mzn_id;
	this->type = type;
	this->name = name;
	this->namesp = namesp;
	this->datatype = datatype;
}

string Input::getMznId() {
	return this->mzn_id;
}
void Input::setMznId(string mznId) {
	this->mzn_id = mznId;
}

string Input::getDatatype() {
	return this->datatype;
}
void Input::setDatatype(string datatype) {
	this->datatype = datatype;
}

string Input::getName() {
	return this->name;
}
void Input::setName(string name) {
	this->name = name;
}
string Input::getNamesp() {
	return this->namesp;
}
void Input::setNamesp(string namesp) {
	this->namesp;
}
string Input::getType() {
	return this->type;
}
void Input::setType(string type) {
	this->type = type;
}
