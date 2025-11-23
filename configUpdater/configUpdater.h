#pragma once
#ifndef CONFIG_UPDATER_H
#define CONFIG_UPDATER_H

#include<vector>
#include<iostream>
#include<string>
#include<algorithm> //for std::remove

class Observer {
public:
	virtual void update(const std::vector<int>& vals) = 0;
	virtual ~Observer() {};
};

class Subject {
public:
	virtual void subscribeObserver(Observer* newObserver) = 0;
	virtual void unsubscribeObserver(Observer* observer) = 0;
	virtual void notifyObservers(void) = 0;
	virtual ~Subject() {};
};

class Configuration : public Subject {
protected:
	std::vector<Observer*> observers;
	std::vector<int> configVals;

public:
	void subscribeObserver(Observer* newObserver) override {
		observers.push_back(newObserver);
	}
	void unsubscribeObserver(Observer* observer) override {
		observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
	}
	
	void notifyObservers(void) override {
		for (Observer* observer : observers) {
			observer->update(configVals);
		}
	}

	void setNewIntsConfig(const std::vector<int>& newInts) {
		configVals = newInts;
		notifyObservers();
	}

	virtual ~Configuration() {};
};

class TrackTemperatures : public Configuration {
private:
	bool isUpper;
public:
	void setNewIntsConfig(const std::vector<int>& newInts, int threshold) {
		isUpper = false;
		for (int temp : newInts) {
			if (temp > threshold) {
				isUpper = true;
				configVals.push_back(temp);
			}
		}
		if(isUpper) notifyObservers();
	}
};

class IntVals : public Observer {
private:
	std::vector<int> configVals;
	inline void showUpdate() {
		std::cout << "Updated configuration values" << std::endl;
		for (int val : configVals) {
			std::cout << "config val=" << val << std::endl;
		}
	}
public:
	void update(const std::vector<int>& vals) override {
		for (int val : vals) {
			configVals.push_back(val);
		}
		showUpdate();
	}
};

#endif // !CONFIG_UPDATER_H

