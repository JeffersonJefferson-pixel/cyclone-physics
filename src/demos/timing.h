#ifndef CYCLONE_DEMO_TIMING_H
#define CYCLE_DEMO_TIMING_H

struct TimingData
{
	unsigned frameNumber;
	
	unsigned lastFrameTimestamp;

	unsigned lastFrameDuration;

	unsigned long lastFrameClockstamp;
	
	unsigned long lastFrameClockTicks;

	bool isPaused;

	double averageFrameDuration;

	float fps;

	static TimingData& get();

	static void update();

	static void init();

	static void deinit();

	static unsigned getTime();

	static unsigned long getClock();
};

#endif