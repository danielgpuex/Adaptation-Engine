#include <string>
#ifndef TOPICVAR_H
#define TOPICVAR_H
using namespace std;
//This class relates the data provided by DDS with the minizinc parameter. The buffer of each listener contains objects of this class.
class TopicVar {
private:
	string topic;
	string value;
	string minizincParam;
public:
	//Default constructor
	TopicVar();
	/* 
	 * @param _topic topic name of dds
	 * @param _value value
	 * @param mParam topic name in Minizinc
	 * */ 
	TopicVar(string _topic, string _value, string mParam);

	/*
	*	return minizincParam attribute value
	*/
	string getMinizincParam();

	/*
	*	@param minizincParam replace the value of the minizincParam
	*/
	void setMinizincParam(string minizincParam);

	/*
	*	return topic attribute value
	*/
	string getTopic();
	/*
	*	@param topic replace the value of the topic
	*/
	void setTopic(string topic);
	/*
	*	return attribute value
	*/
	string getValue();
	/*
	*	@param value replace the value 
	*/
	void setValue(string value);
};
#endif

