#pragma once
#include "test1.h"
#include "IObserver.h"

class Observable
{
public:
	void notify();
	void attach(IObserver* observer);
	void detach(IObserver* observer);
private:
	std::list<IObserver*> observers;
};