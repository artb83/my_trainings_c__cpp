#include "observerNotifier.h"

int main() {
	WeatherStation weatherStation;

	TvDisplay tvDisplay;
	PhoneDisplay phoneDisplay;

	weatherStation.addObserver(&tvDisplay);
	weatherStation.addObserver(&phoneDisplay);

	weatherStation.setWaeather("Rainy");
	weatherStation.setWaeather("Sunny");
	weatherStation.setWaeather("Cloudy");

	weatherStation.removeObserver(&phoneDisplay);

	weatherStation.setWaeather("Windy");
	return 0;
}