#include "DS18B20Sensor.h"
#include <helpers/sensors/EnvironmentSensorManager.h>

OneWire ds18b20_wire(PIN_DS18B20);
DallasTemperature ds18b20_sensors(&ds18b20_wire);

bool ds18b20_init() {
  ds18b20_sensors.begin();
  return ds18b20_sensors.getDeviceCount() > 0;
}

void ds18b20_query(uint8_t channel, uint8_t sub_channel, CayenneLPP& telemetry) {
  ds18b20_sensors.requestTemperatures();
  float temp = ds18b20_sensors.getTempCByIndex(0);
  if (temp != DEVICE_DISCONNECTED_C) {
    telemetry.addTemperature(channel, temp);
  }
}