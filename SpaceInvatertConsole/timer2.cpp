#include "timer2.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Timer();
	}
	return sInstance;
}

void Timer::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Timer::Timer() {
	reset();
	mtimeScale = 1.0f;
	mdeltaTime = std::chrono::duration<float>(0.0f);
}

Timer::~Timer() {

}

void Timer::reset() {
	startTime = std::chrono::system_clock::now();
}

float Timer::DeltaTime() {
	return mdeltaTime.count();
}

void Timer::TimeScale(float t) {
	mtimeScale = t;
}

float Timer::TimeScale() {
	return mtimeScale;
}

void Timer::Tick() {
	mdeltaTime = std::chrono::system_clock::now() - startTime;
}