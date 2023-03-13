#include <iostream>
#include <thread>
#include <mutex>

class ThreadCounter {
public:
	void output(int thread_num, int min, int max)
	{
		std::cout << "Start Thread " << thread_num << std::endl;

		// Used to determain the min/max each thread counts to
		switch (thread_num) {
		case 1: min = 1; max = 50; break;
		case 2: min = 101; max = 150; break;
		case 3: min = 1001; max = 1050; break;
		case 4: min = 10001; max = 10050; break;
		}

		// Prints current number
		while (min <= max) {
			std::cout << min << std::endl;
			min++;
		}

		std::cout << "Finish Thread " << thread_num << std::endl << std::endl;
	}

	void create_thread(int thread_count)
	{
		for (int i = 0; i < 4; i++) {
			std::thread thread(&ThreadCounter::output, this, thread_number, minimum, maximum);
			thread.join();
			thread_number++;
		}
	}
private:
	int thread_number = 1, minimum = 0, maximum = 0;
};