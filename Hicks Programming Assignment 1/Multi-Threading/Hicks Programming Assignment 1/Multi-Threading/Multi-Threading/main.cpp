#include <iostream>
#include <thread>
#include <Windows.h>

//CRITICAL_SECTION critical_section;

void my_thread(int* thread_num, int min, int max)
{
	std::cout << "Start Thread " << *thread_num << std::endl;
	std::cout << "Thread ID = " << GetCurrentThreadId() << std::endl;

	for(int curr = min; curr <= max; curr++)
		std::cout << curr << std::endl;

	std::cout << "Finish Thread " << *thread_num << std::endl << std::endl;
}

int main()
{
	std::cout << "Start Application" << std::endl;
	int thread_number = 1, minimum, maximum;


	for (int i = 0; i < 4; i++) {
		std::thread thread(my_thread, &thread_number, minimum, maximum);
		thread.join();
		thread_number++;
	}

	std::cout << "End Application" << std::endl;
	return 0;
}

