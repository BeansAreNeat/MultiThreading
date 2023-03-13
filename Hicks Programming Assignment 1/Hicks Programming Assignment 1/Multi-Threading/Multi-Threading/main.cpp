#include <iostream>
#include <Windows.h>
#include <process.h>
#include <stdio.h>

CONDITION_VARIABLE CV;
CRITICAL_SECTION critical;
HANDLE mutex;

void output(int thread_num)
{
	std::cout << "Start Thread " << thread_num << std::endl;
	int min, max;

	// Used to determain the min/max each thread counts to
	switch (thread_num) {
	case 1: min = 1; max = 50; break;
	case 2: min = 101; max = 150; break;
	case 3: min = 1001; max = 1050; break;
	case 4: min = 10001; max = 10050; break;
	}

	// Prints current number
	for(int i = min; i < max; i++) {
		std::cout << min << std::endl;
	}

	std::cout << "Finish Thread " << thread_num << std::endl << std::endl;
}

unsigned int __stdcall create_thread(void*)
{
		EnterCriticalSection(&critical);
		WaitForSingleObject(mutex, INFINITE);

		ReleaseMutex(mutex);
		LeaveCriticalSection(&critical);
	return 0;
}

int main()
{
	std::cout << "Start Application" << std::endl;
	HANDLE handle1, handle2, handle3, handle4;

	InitializeCriticalSection(&critical);
	mutex = CreateMutex(0, 0, 0);

	handle1 = (HANDLE)_beginthreadex(0, 0, &create_thread, (void*)0, 0, 0);
	handle2 = (HANDLE)_beginthreadex(0, 0, &create_thread, (void*)0, 0, 0);
	handle3 = (HANDLE)_beginthreadex(0, 0, &create_thread, (void*)0, 0, 0);
	handle4 = (HANDLE)_beginthreadex(0, 0, &create_thread, (void*)0, 0, 0);

	WaitForSingleObject(handle1, INFINITE);
	WaitForSingleObject(handle2, INFINITE);
	WaitForSingleObject(handle3, INFINITE);
	WaitForSingleObject(handle4, INFINITE);

	CloseHandle(handle1);
	CloseHandle(handle2);
	CloseHandle(handle3);
	CloseHandle(handle4);

	getchar();
	CloseHandle(mutex);

	std::cout << "End Application" << std::endl;
	DeleteCriticalSection(&critical);
	return 0;
}