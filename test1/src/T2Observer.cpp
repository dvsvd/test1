#include "T2Observer.h"

T2Observer::T2Observer(Observable* obj)
{
	if (obj == nullptr)
		throw std::logic_error("T2Observer null argument exception");
	_obj = obj;
	obj->attach(this);
}

void T2Observer::updateRead()
{
	SharedBuf* b = static_cast<SharedBuf*>(_obj);
	b->writingDone = false;
	b->cv.notify_one();
}

void T2Observer::update(Observable*)
{
	SharedBuf* b = static_cast<SharedBuf*>(_obj);
	b->writingDone = true;
	b->cv.notify_one();
}

T2Observer::~T2Observer()
{
	_obj->detach(this);
}