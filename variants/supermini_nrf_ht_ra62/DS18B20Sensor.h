#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <helpers/sensors/EnvironmentSensorManager.h>

#ifndef PIN_DS18B20
  #define PIN_DS18B20 5  // D5 / P0.24
#endif

extern OneWire ds18b20_wire;
extern DallasTemperature ds18b20_sensors;

void ds18b20_query(uint8_t channel, uint8_t sub_channel, CayenneLPP& telemetry);

class SuperMiniSensorManager : public EnvironmentSensorManager {
public:
  bool begin() override {
    EnvironmentSensorManager::begin();
    ds18b20_sensors.begin();
    if (ds18b20_sensors.getDeviceCount() > 0) {
      if (_active_sensor_count < MAX_ACTIVE_SENSORS) {
        _active_sensors[_active_sensor_count++] = { ds18b20_query, 0 };
      }
    }
    return true;
  }
};