#pragma once
#include "IObserver.h"

class T2Observer : public IObserver
{
private:
	Observable* _obj;
public:
	T2Observer(Observable* obj);
	void updateRead();
	void update(Observable* obj) override;
	~T2Observer();
};