#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <any>

class ThreadGroup {
private:
	std::vector<std::thread> m_threads;
public:
	ThreadGroup(size_t number = 0);
	void join_all();
	//template <class F, class... Args>
	//void create_thread(F&& f, Args&&... args);
	void create_thread(const std::function <int ()>& f);
};