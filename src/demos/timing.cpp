#include "timing.h"

#include <stdlib.h>

static TimingData *timingData = NULL;

TimingData& TimingData::get()
{
  return (TimingData&)*timingData;
}

void TimingData::update()
{

}

void TimingData::init()
{

}

void TimingData::deinit()
{
  
}