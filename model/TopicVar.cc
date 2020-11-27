#include "TopicVar.h" 
#include <iostream> 
using namespace std;

TopicVar::TopicVar()
{
	topic = "";
	value = "";
	minizincParam = "";
}

TopicVar::TopicVar(string _topic, string _value, string mParam)
{
	topic = _topic;
	value = _value;
	minizincParam = mParam;
}
string TopicVar::getMinizincParam() {
	return minizincParam;
}

void TopicVar::setMinizincParam(string minizincParam) {
	this->minizincParam = minizincParam;
}

string TopicVar::getTopic() {
	return TopicVar::topic;
}

void TopicVar::setTopic(string topic) {
	this->topic = topic;
}

string TopicVar::getValue() {
	return value;
}

void TopicVar::setValue(string value) {
	this->value = value;
}

