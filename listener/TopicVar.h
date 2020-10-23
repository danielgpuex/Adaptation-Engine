#include <string>
#ifndef TOPICVAR_H
#define TOPICVAR_H
using namespace std;

class TopicVar {
private:
	string topic;
	string value;
	string minizincParam;
public:
	TopicVar();
	TopicVar(string _topic, string _value, string mParam);

	string getMinizincParam();

	void setMinizincParam(string minizincParam);

	string getTopic();

	void setTopic(string topic);

	string getValue();

	void setValue(string value);
};
#endif

