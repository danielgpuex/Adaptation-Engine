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
	std::list<RoqmeDDSTopics::RoqmeIntContext> buffer;

public:
	void dataAvailable(const RoqmeDDSTopics::RoqmeIntContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::list<RoqmeDDSTopics::RoqmeIntContext> aux;
		bool exists = false;
		bool change = false;

		for (auto elem : data.value()) {
			cout << "\t " << elem << endl;
		}

		for (RoqmeDDSTopics::RoqmeIntContext val : buffer) {
			if (val.name() == data.name()) {
				exists = true;
				if (val.value() != data.value()) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;

					change = true;
				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				aux.push_back(data);
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		if (!exists) {
			cout << "Store inside of the list" << endl;
			cout << "Send to Skill Server using ZMQ" << endl;
			aux.push_back(data);
		}
		exists = false;
		buffer = aux;
	}
};

class UIntContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeUIntContext> {
private:
	std::list<RoqmeDDSTopics::RoqmeUIntContext> buffer;
public:
	void dataAvailable(const RoqmeDDSTopics::RoqmeUIntContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::list<RoqmeDDSTopics::RoqmeUIntContext> aux;
		bool exists = false;
		bool change = false;

		for (auto elem : data.value()) {
			cout << "\t " << elem << endl;
		}

		for (RoqmeDDSTopics::RoqmeUIntContext val : buffer) {
			if (val.name() == data.name()) {
				exists = true;
				if (val.value() != data.value()) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				aux.push_back(data);
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		if (!exists) {
			cout << "Store inside of the list" << endl;
			cout << "Send to Skill Server using ZMQ" << endl;
			aux.push_back(data);
		}
		exists = false;
		buffer = aux;
	}
};

class BoolContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeBoolContext> {
private:
	std::list<RoqmeDDSTopics::RoqmeBoolContext> buffer;
public:
	void dataAvailable(const RoqmeDDSTopics::RoqmeBoolContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::list<RoqmeDDSTopics::RoqmeBoolContext> aux;
		bool exists = false;
		bool change = false;

		for (auto elem : data.value()) {
			cout << "\t " << elem << endl;
		}

		for (RoqmeDDSTopics::RoqmeBoolContext val : buffer) {
			if (val.name() == data.name()) {
				exists = true;
				if (val.value() != data.value()) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				aux.push_back(data);
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		if (!exists) {
			cout << "Store inside of the list" << endl;
			cout << "Send to Skill Server using ZMQ" << endl;
			aux.push_back(data);
		}
		exists = false;
		buffer = aux;
	}
};

class EnumContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeEnumContext> {
private:
	std::list<RoqmeDDSTopics::RoqmeEnumContext> buffer;
public:
	void dataAvailable(const RoqmeDDSTopics::RoqmeEnumContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::list<RoqmeDDSTopics::RoqmeEnumContext> aux;
		bool exists = false;
		bool change = false;

		for (auto elem : data.value()) {
			cout << "\t " << elem << endl;
		}

		for (RoqmeDDSTopics::RoqmeEnumContext val : buffer) {
			if (val.name() == data.name()) {
				exists = true;
				if (val.value() != data.value()) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				aux.push_back(data);
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		if (!exists) {
			cout << "Store inside of the list" << endl;
			cout << "Send to Skill Server using ZMQ" << endl;
			aux.push_back(data);
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
		RoqmeDDSTopics::RoqmeEventContext> {
private:
	std::list<RoqmeDDSTopics::RoqmeEventContext> buffer;
public:

	void dataAvailable(const RoqmeDDSTopics::RoqmeEventContext &data,
			const dds::sub::SampleInfo &sampleInfo) {
		cout << "\t name: " << data.name() << endl;
		std::list<RoqmeDDSTopics::RoqmeEventContext> aux;
		bool exists = false;
		bool change = false;

		for (auto elem : data.value()) {
			cout << "\t " << elem << endl;
		}

		for (RoqmeDDSTopics::RoqmeEventContext val : buffer) {
			if (val.name() == data.name()) {
				exists = true;
				if (val.value() != data.value()) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				aux.push_back(data);
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		if (!exists) {
			cout << "Store inside of the list" << endl;
			cout << "Send to Skill Server using ZMQ" << endl;
			aux.push_back(data);
		}
		exists = false;
		buffer = aux;
	}
};

class DoubleContextListener: public RoqmeDDSListener<
		RoqmeDDSTopics::RoqmeDoubleContext> {
private:
	std::list<RoqmeDDSTopics::RoqmeDoubleContext> buffer;
public:

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
		std::list<RoqmeDDSTopics::RoqmeDoubleContext> aux;
		bool exists = false;
		bool change = false;

		for (auto elem : data.value()) {
			cout << "\t " << elem << endl;
		}

		for (RoqmeDDSTopics::RoqmeDoubleContext val : buffer) {
			if (val.name() == data.name()) {
				exists = true;
				if (val.value() != data.value()) {
					cout << "Differents values, update in the buffer" << endl;
					cout << "Send to Skill Server using ZMQ" << endl;
					change = true;
				} else {
					cout << "Not change" << endl;
				}
			}
			if (change) {
				aux.push_back(data);
				change = false;
			} else {
				aux.push_back(val);
			}
		}
		if (!exists) {
			cout << "Store inside of the list" << endl;
			cout << "Send to Skill Server using ZMQ" << endl;
			aux.push_back(data);
		}
		exists = false;
		buffer = aux;
		for (RoqmeDDSTopics::RoqmeDoubleContext val : buffer) {
			for (auto elem : val.value()) {
				cout << "\t value: " << elem << endl;
			}
		}
	}
};

class EstimateListener: public RoqmeDDSListener<RoqmeDDSTopics::RoqmeEstimate> {
private:
	std::vector<TopicVar> buffer;

	Minizinc minizinc;
public:
	EstimateListener(vector<TopicVar> properties, Minizinc _minizinc) {
		RoqmeDDSTopics::RoqmeEstimate estimate;
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

					//Ejecutar Minizinc, produce salida, si hay actualización manda por zmq los vp que sean.

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
		/*if (!exists) {

		}*/
		exists = false;
		buffer = aux;
	}
};
