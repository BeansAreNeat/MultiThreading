#include <iostream>
#include <thread>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <math.h>

CRITICAL_SECTION critical_section;

void thread()
{
	std::cout << "Start Thread -" << GetCurrentThreadId() << std::endl;
	std::cout << "Finish Thread -" << GetCurrentThreadId() << std::endl;
	std::cout << std::endl;
}

int main()
{
	int counter = 0;
	std::cout << "Start Application" << std::endl;
	//Loops creation of threads
	while (counter < 4) {
		EnterCriticalSection(&critical_section);
		counter++;
		thread();
	}
	
	std::cout << "End Application" << std::endl;
	return 0;
}

