#ifndef TIMER2_H
#define TIMER2_H

#include <chrono>

class Timer {

private:
	static Timer* sInstance;
	std::chrono::system_clock::time_point startTime;
	std::chrono::duration<float> mdeltaTime;
	float mtimeScale;

public:

	static Timer* Instance();
	static void Release();

	void reset();

	float DeltaTime();

	void TimeScale(float t = 1.0f);

	float TimeScale();

	void Tick();

private:
	Timer();
	~Timer();
};


#endif // !TIMER2_H
