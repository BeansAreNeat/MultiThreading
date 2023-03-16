#include <iostream>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include "thread_counter.cpp"

CONDITION_VARIABLE CV;

void output_c_version(int thread_num, int max, int min)
{
	std::cout << "Start Thread - " << thread_num << std::endl << std::endl;

	// Used to determain the min/max each thread counts to
	switch (thread_num) {
	case 1: min = 1;     max = 50;    break;
	case 2: min = 101;   max = 150;   break;
	case 3: min = 1001;  max = 1050;  break;
	case 4: min = 10001; max = 10050; break;
	}

	// Prints current number
	for (int i = min; i < max; i++)
		std::cout << "Thread #" << thread_num << ": " << i << std::endl;

	std::cout << "Finish Thread - " << thread_num << std::endl << std::endl;
}

unsigned int __stdcall create_c_thread(void* arg)
{
	int thread_num = *(int*)arg;
	output_c_version(thread_num, 0, 0);
	return 0;
}

void cpp_version()
{
	std::cout << "Start Application" << std::endl;
	ThreadCounter thread;
	thread.create_cpp_thread(4);
	std::cout << "End Application" << std::endl;
	std::cout << std::endl;
}

int main()
{
	// C++ Verison of the multi-threading
	cpp_version();
	// C Verison of the multi-threading
	const int num_threads = 4;
	std::cout << "Start Application" << std::endl;

	HANDLE handles[num_threads];
	int thread_args[num_threads];

	for (int i = 0; i < num_threads; i++) {
		thread_args[i] = i + 1;
		handles[i] = (HANDLE)_beginthreadex(0, 0, &create_c_thread, &thread_args[i], 0, 0);
	}

	WaitForMultipleObjects(num_threads, handles, true, INFINITE);

	for (int i = 0; i < num_threads; i++)
		CloseHandle(handles[i]);

	getchar();
	std::cout << "End Application" << std::endl;
	std::cout << std::endl;
	return 0;
}