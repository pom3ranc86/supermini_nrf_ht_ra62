#pragma once
#define RADIOLIB_STATIC_ONLY 1
#include <RadioLib.h>
#include <helpers/radiolib/RadioLibWrappers.h>
#include <PromicroBoard.h>
#include <helpers/radiolib/CustomSX1262Wrapper.h>
#include <helpers/AutoDiscoverRTCClock.h>
#include <helpers/ui/NullDisplayDriver.h>
#include <helpers/ui/MomentaryButton.h>
#include "DS18B20Sensor.h"

extern PromicroBoard board;
extern WRAPPER_CLASS radio_driver;
extern AutoDiscoverRTCClock rtc_clock;
extern SuperMiniSensorManager sensors;
extern NullDisplayDriver display;
extern MomentaryButton user_btn;

bool radio_init();
mesh::LocalIdentity radio_new_identity();