#pragma once
#ifndef NOTIFY_STR_UPDATE
#define NOTIFY_STR_UPDATE

#include <string>
#include <vector>
#include<algorithm> //for std::remove
#include<iostream>

class Observer {
public:
	virtual void update(const std::string& newString) = 0;
	virtual ~Observer() {};
};

class Subject {
public:
	virtual void subscribe(Observer* newObserver) =0;
	virtual void unSubscribe(const Observer* observer) =0;
	virtual void notifyObservers(void) = 0;
	virtual ~Subject() {};
};

class Notifier : public Subject{
protected:
	std::string newStr;
	std::vector<Observer*> observers;
public:
	void subscribe(Observer* newObserver) {
		this->observers.push_back(newObserver);
	}
	void unSubscribe(const Observer* observer) {
		this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
	}
	void notifyObservers(void) {
		for (Observer* observer : observers) {
			observer->update(this->newStr);
		}
	}
	void setNewItem(const std::string& newStr) {
		this->newStr = newStr;
		notifyObservers();
	}

	virtual ~Notifier() {};
};

class StrUpdate : public Observer {
private:
	std::string newStr;
	void showUpdate(void) {
		std::cout << "new string: " << this->newStr << std::endl;
	}
public:
	void update(const std::string& newStr) {
		this->newStr = newStr;
		showUpdate();
	}
	virtual ~StrUpdate() {};
};
#endif // !NOTIFY_STR_UPDATE

