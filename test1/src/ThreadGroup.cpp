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

void ThreadGroup::create_thread(const std::function<int()>& f)
{
	m_threads.push_back(std::thread(f));
}