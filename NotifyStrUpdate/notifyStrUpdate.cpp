#include "notifyStrUpdate.h"

int main() {
	
	Notifier strNotifier;
	StrUpdate strObserve1;
	StrUpdate strObserve2;
	StrUpdate strObserve3;

	strNotifier.subscribe(&strObserve1);
	strNotifier.subscribe(&strObserve2);
	strNotifier.subscribe(&strObserve3);

	strNotifier.setNewItem("hello world");

	strNotifier.setNewItem("hello hello world");

	return 0;
}