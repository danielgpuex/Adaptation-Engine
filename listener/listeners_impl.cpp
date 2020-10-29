#include "RoqmeReaderImpl.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <list>

#include "change_velocity.hpp"
#include <query_client.hpp>
#include <variant_client.hpp>
#include "TopicVar.h"
#include "minizinc.hpp"

using namespace std;
using namespace Roqme;
using namespace zmqserver;


void printTimestamp(const dds::core::Time &source_timestamp) {
	cout << "\t timestamp: " << source_timestamp.sec() << "s, "
			<< source_timestamp.nanosec() << "ns" << endl;
}

class IntContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeIntContext> {
private:
	std::vector<TopicVar> buffer;
	Minizinc minizinc;
public:

	IntContextListener(vector<TopicVar> properties, Minizinc _minizinc) {
		this->buffer = properties;
		this->minizinc=_minizinc;
	}
	void dataAvailable(const RoqmeDDSTopics::RoqmeIntContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::vector<TopicVar> aux;
		bool exists = false;
		bool change = false;
		TopicVar nVar;
		for (TopicVar val : buffer) {
			if (val.getTopic() == data.name()) {
				exists = true;
				if (stoi(val.getValue()) != data.value()[0]) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
					nVar.setTopic(val.getTopic());
					nVar.setValue(to_string(data.value()[0]));
					nVar.setMinizincParam(val.getMinizincParam());
					aux.push_back(nVar);

					//Minizinc update parameter and run.
					minizinc.updateParameter(val.getMinizincParam(), to_string(data.value()[0]));
					cout << "Ejecutamos el minizinc..." << endl;
					minizinc.Run(true);

				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		exists = false;
		buffer = aux;

	}
};

class UIntContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeUIntContext> {
private:
	std::vector<TopicVar> buffer;
	Minizinc minizinc;

public:

	UIntContextListener(vector<TopicVar> properties, Minizinc _minizinc) {
		this->buffer = properties;
		this->minizinc=_minizinc;
	}

	void dataAvailable(const RoqmeDDSTopics::RoqmeUIntContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::vector<TopicVar> aux;
		bool exists = false;
		bool change = false;
		TopicVar nVar;
		for (TopicVar val : buffer) {
			if (val.getTopic() == data.name()) {
				exists = true;
				if (stoi(val.getValue()) != data.value()[0]) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
					nVar.setTopic(val.getTopic());
					nVar.setValue(to_string(data.value()[0]));
					nVar.setMinizincParam(val.getMinizincParam());
					aux.push_back(nVar);

					//Minizinc update parameter and run.
					minizinc.updateParameter(val.getMinizincParam(), to_string(data.value()[0]));
					cout << "Ejecutamos el minizinc..." << endl;
					minizinc.Run(true);

				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		exists = false;
		buffer = aux;

	}
};

class BoolContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeBoolContext> {
private:
	std::vector<TopicVar> buffer;
	Minizinc minizinc;

public:
	BoolContextListener(vector<TopicVar> properties, Minizinc _minizinc) {
		this->buffer = properties;
		this->minizinc=_minizinc;
	}
	void dataAvailable(const RoqmeDDSTopics::RoqmeBoolContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::vector<TopicVar> aux;
		bool exists = false;
		bool change = false;
		TopicVar nVar;
		for (TopicVar val : buffer) {
			if (val.getTopic() == data.name()) {
				exists = true;

				if (stoi(val.getValue()) != data.value()[0]) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
					nVar.setTopic(val.getTopic());
					nVar.setValue(to_string(data.value()[0]));
					nVar.setMinizincParam(val.getMinizincParam());
					aux.push_back(nVar);

					//Minizinc update parameter and run.
					minizinc.updateParameter(val.getMinizincParam(), to_string(data.value()[0]));
					cout << "Ejecutamos el minizinc..." << endl;
					minizinc.Run(true);

				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		exists = false;
		buffer = aux;
	}
};

class EnumContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeEnumContext> {
private:
	std::vector<TopicVar> buffer;
	Minizinc minizinc;

public:
	EnumContextListener(vector<TopicVar> properties, Minizinc _minizinc) {
		this->buffer = properties;
		this->minizinc=_minizinc;
	}
	void dataAvailable(const RoqmeDDSTopics::RoqmeEnumContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		std::vector<TopicVar> aux;
		bool exists = false;
		bool change = false;
		TopicVar nVar;
		for (TopicVar val : buffer) {
			if (val.getTopic() == data.name()) {
				exists = true;
				if (stoi(val.getValue()) != stoi(data.value()[0])) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
					nVar.setTopic(val.getTopic());
					nVar.setValue(data.value()[0]);
					nVar.setMinizincParam(val.getMinizincParam());
					aux.push_back(nVar);

					//Minizinc update parameter and run.
					minizinc.updateParameter(val.getMinizincParam(), data.value()[0]);
					cout << "Ejecutamos el minizinc..." << endl;
					minizinc.Run(true);

				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		exists = false;
		buffer = aux;
	}
};

class ObservationListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeObservation> {
private:
	std::list<RoqmeDDSTopics::RoqmeObservation> buffer;
public:

	void dataAvailable(const RoqmeDDSTopics::RoqmeObservation &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::list<RoqmeDDSTopics::RoqmeObservation> aux;
		bool exists = false;

		for (RoqmeDDSTopics::RoqmeObservation val : buffer) {
			if (val.name() == data.name()) {
				exists = true;
			}
		}
		if (!exists) {
			cout << "Store inside of the list" << endl;
			cout << "Send to Skill Server using ZMQ??????" << endl;
			buffer.push_back(data);
		}
		exists = false;
	}
};

class EventContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeEventContext> {//TODO: No me convence. Revisar
private:
	std::vector<TopicVar> buffer;
	Minizinc minizinc;
public:
	EventContextListener(vector<TopicVar> properties, Minizinc _minizinc) {
		this->buffer = properties;
		this->minizinc=_minizinc;
	}

	void dataAvailable(const RoqmeDDSTopics::RoqmeEventContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::vector<TopicVar> aux;
		bool exists = false;
		bool change = false;
		TopicVar nVar;
		for (TopicVar val : buffer) {
			if (val.getTopic() == data.name()) {
				exists = true;

					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
					nVar.setTopic(val.getTopic());
					nVar.setValue(to_string(sampleInfo.timestamp().sec()));
					nVar.setMinizincParam(val.getMinizincParam());
					aux.push_back(nVar);

					//Minizinc update parameter and run.
					minizinc.updateParameter(val.getMinizincParam(), "true");//TODO: When minizinc is executed will change a 'false' value in his buffer.
					cout << "Ejecutamos el minizinc..." << endl;
					minizinc.Run(true);

			}
			if (change) {
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		exists = false;
		buffer = aux;
	}
};

class DoubleContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeDoubleContext> {
private:
	std::vector<TopicVar> buffer;
	Minizinc minizinc;
	//std::list<RoqmeDDSTopics::RoqmeDoubleContext> buffer;
public:
	DoubleContextListener(vector<TopicVar> properties, Minizinc _minizinc) {
		this->buffer = properties;
		this->minizinc=_minizinc;
	}

	void dataAvailable(
			dds::sub::DataReader<RoqmeDDSTopics::RoqmeDoubleContext> &dr) {
		dds::sub::LoanedSamples<RoqmeDDSTopics::RoqmeDoubleContext> samples =
				dr.take();
		if (samples.length() > 0 && (*samples.begin()).info().valid()) {
			for (auto sample = samples.begin(); sample < samples.end();
					++sample) {
				dataAvailable(sample->data(), sample->info());
			}
		}
	}

	void dataAvailable(const RoqmeDDSTopics::RoqmeDoubleContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
				std::vector<TopicVar> aux;
				bool exists = false;
				bool change = false;
				TopicVar nVar;
				for (TopicVar val : buffer) {
					if (val.getTopic() == data.name()) {
						exists = true;
						if (stoi(val.getValue()) != data.value()[0]) {
							cout << "Differents values, update in the buffer" << endl;
							cout << "Send to Skill Server using ZMQ" << endl;
							change = true;
							nVar.setTopic(val.getTopic());
							nVar.setValue(to_string(data.value()[0]));
							nVar.setMinizincParam(val.getMinizincParam());
							aux.push_back(nVar);

							//Minizinc update parameter and run.
							minizinc.updateParameter(val.getMinizincParam(), to_string(data.value()[0]));
							cout << "Ejecutamos el minizinc..." << endl;
							minizinc.Run(true);

						} else {
							cout << "Not change" << endl;
						}
					}
					if (change) {
						change = false;
					} else {
						aux.push_back(val);
					}
				}
				exists = false;
				buffer = aux;

	}
};

class EstimateListener: public RoqmeDDSListener<RoqmeDDSTopics::RoqmeEstimate> {
private:
	std::vector<TopicVar> buffer;
	Minizinc minizinc;
public:
	EstimateListener(vector<TopicVar> properties, Minizinc _minizinc) {
		this->buffer = properties;
		this->minizinc=_minizinc;
		/*for (int i = 0; i < properties.size(); ++i) {
			estimate.name_=properties[i];
			estimate.value_=-1;
			buffer.push_back(estimate);
		}*/
	}

	void dataAvailable(const RoqmeDDSTopics::RoqmeEstimate &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::vector<TopicVar> aux;
		bool exists = false;
		bool change = false;
		TopicVar nVar;
		for (TopicVar val : buffer) {
			if (val.getTopic() == data.name()) {
				exists = true;
				if (stoi(val.getValue()) != data.value()) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
					nVar.setTopic(val.getTopic());
					nVar.setValue(to_string(data.value()));
					nVar.setMinizincParam(val.getMinizincParam());
					aux.push_back(nVar);

					//Minizinc update parameter and run.
					minizinc.updateParameter(val.getMinizincParam(), to_string(data.value()));
					cout << "Ejecutamos el minizinc..." << endl;
					minizinc.Run(true);

				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		exists = false;
		buffer = aux;
	}
};
