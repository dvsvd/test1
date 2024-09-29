#include "ThreadGroup.h"

ThreadGroup::ThreadGroup(size_t number)
{
	m_threads.reserve(number);
}

void ThreadGroup::join_all()
{
	for (auto& t : m_threads)
	{
		t.join();
	}
}