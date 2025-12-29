#include "factoryPattern.h"


void buildSensors(void* args) {
	struct threadArgs* thrArgs = (struct threadArgs*)args;
	thrArgs->mutex1->lock();
	thrArgs->factPtr->createSensor();
	thrArgs->mutex2->unlock();
}

void showSensors(void* args) {
	struct threadArgs* thrArgs = (struct threadArgs*)args;
	thrArgs->mutex2->lock();
	std::cout << "built " << thrArgs->factPtr->getSensorsCount() << " sensors\n";
	thrArgs->mutex1->unlock();
}
