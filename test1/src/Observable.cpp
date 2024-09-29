#include "Observable.h"

void Observable::notify()
{
	for (const auto& x : observers) {
		x->update(this);
	}
}

void Observable::attach(IObserver* observer)
{
		observers.push_front(observer);
}

void Observable::detach(IObserver* observer)
{
	observers.remove(observer);
}