#include "configUpdater.h"

int main() {
	/*int myInts[] = { 1,2,3 };
	std::vector<int> config(myInts, myInts+sizeof(myInts)/sizeof(int));
	Configuration conf;

	IntVals newConfig;

	conf.subscribeObserver(&newConfig);

	conf.setNewIntsConfig(config);*/

	int myTemperatures[] = { 10,22, 15, 33, 25 };

	//Configuration* tracker = new TrackTemperatures();
	TrackTemperatures tracker;
	IntVals newTempsToTrack1;
	IntVals newTempsToTrack2;
	IntVals newTempsToTrack3;

	std::vector<int> temps(myTemperatures, myTemperatures + sizeof(myTemperatures) / sizeof(int));
	int threshold = 32;
	tracker.subscribeObserver(&newTempsToTrack1);
	tracker.subscribeObserver(&newTempsToTrack2);
	tracker.subscribeObserver(&newTempsToTrack3);

	tracker.setNewIntsConfig(temps, threshold);

	return 0;
}