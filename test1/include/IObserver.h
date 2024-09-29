#pragma once
#include "Observable.h"

class Observable;

class IObserver {
public:
	virtual void update(Observable*) = 0;
	virtual ~IObserver() = default;
};