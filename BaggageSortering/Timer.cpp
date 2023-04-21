#include "Timer.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>
#include <windows.h>

void Timer::DisplayClock()
{

	std::chrono::time_point currTime = std::chrono::system_clock::now();
	std::chrono::time_point later = currTime + std::chrono::minutes(2);

	std::time_t printableCurrTime = std::chrono::system_clock::to_time_t(currTime);
	std::time_t printableLater = std::chrono::system_clock::to_time_t(later);

	char s_now[26];
	ctime_s(s_now, sizeof(s_now), &printableCurrTime);
	
	char s_then[26];
	ctime_s(s_then, sizeof(s_then), &printableLater);

	char s_static[26];
	ctime_s(s_static, sizeof(s_static), &static_later);

	if (s_now == s_static) {
		system("CLS");
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}

	std::cout << std::setfill('0') << std::setw(2) << hours << ':' << std::setfill('0') << std::setw(2) << minutes << ':' << std::setfill('0') << std::setw(2) << seconds << '\n';
	std::cout << s_now << '\n';

	if (static_later < printableLater) {
		std::cout << s_static  << '\n';
	}

}

void Timer::Run()
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));

		seconds++;

		if (seconds == 60) { 
			seconds = 0;
			
			minutes++;

			if (minutes == 60) {
				minutes = 0;
				
				hours++;

				if (hours == 24) {
					hours = 0;
				}

			}
			
		}
	}
}
