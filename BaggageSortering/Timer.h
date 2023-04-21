#pragma once
#include <chrono>
class Timer
{
public:
	Timer(int hours = 10, int minutes = 0, int seconds = 0) : hours(hours), minutes(minutes), seconds(seconds) {
		std::chrono::time_point currTime = std::chrono::system_clock::now();
		std::chrono::time_point l_later = currTime + std::chrono::seconds(10);

		std::time_t printableCurrTime = std::chrono::system_clock::to_time_t(currTime);
		std::time_t printableLater = std::chrono::system_clock::to_time_t(l_later);


		char s_now[26];
		ctime_s(s_now, sizeof(s_now), &printableCurrTime);

		char s_then[26];
		ctime_s(s_then, sizeof(s_then), &printableLater);

		static_later = printableLater;
	}
	~Timer() {}
	void DisplayClock();
	void Run();
	static inline int GetGlobalTime() { return globalTime; }
private:
	int hours;
	int minutes;
	int seconds;
	static inline std::time_t static_later;
	static inline std::atomic<int> globalTime;
};

