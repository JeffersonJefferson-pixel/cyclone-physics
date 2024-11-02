#ifndef CYCLONE_DEMO_TIMING_H
#define CYCLE_DEMO_TIMING_H

struct TimingData
{
  unsigned lastFrameTimestamp;

  unsigned lastFrameDuration;

  static TimingData& get();

  static void update();

  static void init();

  static void deinit();
};

#endif