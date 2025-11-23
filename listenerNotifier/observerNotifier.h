#pragma once
#ifndef OBSERVER_NOTIFIER_H
#define OBSERVER_NOTIFIER_H
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>


class Observer {
public:
	virtual void update(const std::string& weather) = 0;
};

class Subject {
public:
	virtual void addObserver(Observer* observer) = 0;
	virtual void removeObserver(Observer* observer) = 0;
	virtual void notifyObservers(void) = 0;
};

class PhoneDisplay : public Observer {
private:
	std::string weather;
	void displayWeather() {
		std::cout << "PhoneDisplay: Weather update - " << weather << std::endl;
	}
public:
	void update(const std::string& weather) override {
		this->weather = weather;
		displayWeather();
	}
};

class TvDisplay : public Observer {
private:
	std::string weather;
	void displayWeather() {
		std::cout << "TvDisplay : Weather update - " << weather << std::endl;
	}
public:
	void update(const std::string& weather) override {
		this->weather = weather;
		displayWeather();
	}
};

class WeatherStation : public Subject {
private:
	std::vector<Observer*> observers;
	std::string weather;
	
public:
	void addObserver(Observer* observer) override {
		observers.push_back(observer);
	}

	void removeObserver(Observer* observer) override {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void notifyObservers(void) override {
		for (Observer* observer : observers) {
			observer->update(weather);
		}
	}

	void setWaeather(const std::string& newWeather) {
		this->weather = newWeather;
		notifyObservers();
	}
};
#endif // !OBSERVER_NOTIFIER_H

