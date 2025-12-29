#pragma once
#ifndef __FACTORY_PATTERN__
#define __FACTORY_PATTERN__
#include <memory>
#include <iostream>
#include <thread>
#include <mutex>



class Sensor {
public:
	virtual void build() = 0;
	virtual ~Sensor() {}
};

class sensorFacotry {
protected:
	int nSensors=0;
public:
	virtual std::unique_ptr<Sensor> createSensor() = 0;
	virtual int getSensorsCount() const = 0;
	virtual ~sensorFacotry() {}
};

class Ccd : public Sensor {
public:
	void build() override {
		std::cout << "Building CCD sensor" << std::endl;
	}
};

class ccdFacotry : public sensorFacotry {
public:
	std::unique_ptr<Sensor> createSensor() override {
		this->nSensors++;
		return std::make_unique<Ccd>();
	}
	int getSensorsCount() const {
		return this->nSensors;
	}
};

struct threadArgs {
	sensorFacotry* factPtr;
	std::mutex* mutex1;
	std::mutex* mutex2;
};

void buildSensors(void* args);
void showSensors(void* args);
#endif // !__FACTORY_PATTERN__

