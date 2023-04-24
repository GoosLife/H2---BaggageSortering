#include "Timer.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>
#include <windows.h>

void Timer::DisplayClock()
{

	std::chrono::time_point currTime = std::chrono::system_clock::now();

	std::time_t printableCurrTime = std::chrono::system_clock::to_time_t(currTime);

	char s_now[26];
	ctime_s(s_now, sizeof(s_now), &printableCurrTime);

	// std::cout << std::setfill('0') << std::setw(2) << hours << ':' << std::setfill('0') << std::setw(2) << minutes << ':' << std::setfill('0') << std::setw(2) << seconds << '\n';
	std::cout << s_now << '\n';

	std::cout << "Global time: " << globalTime << '\n';
}

void Timer::Run()
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));

		globalTime++;

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

std::string Timer::GetRealTimeString()
{
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << (now.tm_hour) << ':' << std::setw(2) << std::setfill('0') << (now.tm_min);
	std::setw(0); // Reset the width to 0 so it doesn't affect other streams
	std::setfill(' '); // Reset the fill character

	return ss.str();
}

std::string Timer::GetRealTimeString(std::time_t timeToConvert) {
	struct tm now;
	localtime_s(&now, &timeToConvert);

	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << (now.tm_hour) << ':' << std::setw(2) << std::setfill('0') << (now.tm_min);
	std::setw(0); // Reset the width to 0 so it doesn't affect other streams
	std::setfill(' '); // Reset the fill character

	return ss.str();
}
