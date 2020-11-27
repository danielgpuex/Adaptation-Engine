#include "SmartsoftInf.h" // header in local directory
#include <iostream> // header in standard library
using namespace std;
SmartsoftInf::SmartsoftInf() {
	this->component = "";
	this->parameter = "";
	this->parameterSet = "";
	this->parameterSetRepository = "";
}
SmartsoftInf::SmartsoftInf(string parameterSetRepository, string parameterSet,
		string component, string parameter) {
	this->component = component;
	this->parameter = parameter;
	this->parameterSet = parameterSet;
	this->parameterSetRepository = parameterSetRepository;
}
string SmartsoftInf::getParameterSetRepository() {
	return this->parameterSetRepository;
}
void SmartsoftInf::setParameterSetRepository(string parameterSetRepository) {
	this->parameterSetRepository = parameterSetRepository;
}
string SmartsoftInf::getParameterSet() {
	return this->parameterSet;
}
void SmartsoftInf::setParameterSet(string pSet) {
	this->parameterSet = pSet;
}
string SmartsoftInf::getComponent() {
	return this->component;
}
void SmartsoftInf::setComponent(string component) {
	this->component = component;
}
string SmartsoftInf::getParameter() {
	return this->parameter;
}
void SmartsoftInf::setParameter(string parameter) {
	this->parameter = parameter;
}
