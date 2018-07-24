#pragma once
#include <thread>
#include <iostream>
#include <mutex>

const int kMax = 10;

std::mutex lock;

void thread_main(int i)
{
	lock.lock();
	std::cout << "I am thread " << i << std::endl;
	lock.unlock();
}

int main()
{
	std::thread t[kMax];

	for (int i = 0; i < kMax; i++)
	{
		t[i] = std::thread(thread_main, i);
	}

	lock.lock();
	std::cout << "I am the main thread" << std::endl;
	lock.unlock();

	for (int i = 0; i < kMax; i++)
	{
		t[i].join();
	}

	system("pause");
	return 0;

}
