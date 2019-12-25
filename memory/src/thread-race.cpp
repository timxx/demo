#include <pthread.h>
#include <map>
#include <string>
#include <iostream>
#include <unistd.h>
#include <atomic>

int g_value = 0;

static void* test_thread1(void *param)
{
	for (int i = 0; i < 2000; ++i)
	{
		g_value++;
		usleep(100);
	}

	return nullptr;
}

static void* test_thread2(void *param)
{
	for (int i = 0; i < 1000; ++i)
	{
		g_value--;
		usleep(170);
	}

	return nullptr;
}

int main()
{
	pthread_t t1 = 0;
	pthread_t t2 = 0;

	pthread_create(&t1, nullptr, test_thread1, nullptr);
	pthread_create(&t2, nullptr, test_thread2, nullptr);

	pthread_join(t1, nullptr);
	pthread_join(t2, nullptr);

	std::cout << g_value << std::endl;

	return 0;
}
