#pragma once
#include <chrono>
#include <iostream>
class Timer
{
public:
	Timer();
	~Timer() {}
	void DisplayClock();
	void Run();
	static inline int GetGlobalTime() { return globalTime; }
	static std::string GetRealTimeString();
	static std::string GetRealTimeString(std::time_t timeToConvert);
private:
	static inline std::time_t static_later;
	static inline std::atomic<int> globalTime;
};

