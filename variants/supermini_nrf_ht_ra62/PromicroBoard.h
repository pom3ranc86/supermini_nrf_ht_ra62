#pragma once
#include <MeshCore.h>
#include <Arduino.h>
#include <helpers/NRF52Board.h>

// LoRa SPI piny
#define P_LORA_NSS      13  // D15 / P1.13
#define P_LORA_DIO_1    11  // D16 / P0.10
#define P_LORA_RESET    10  // D10 / P0.09
#define P_LORA_BUSY     16  // D20 / P0.29
#define P_LORA_MISO     15  // D19 / P0.02
#define P_LORA_SCLK     12  // D14 / P1.11
#define P_LORA_MOSI     14  // D18 / P1.15

// HT-RA62 specifické nastavení
// SX126X_POWER_EN není na SuperMini vyveden — vynecháváme
#define SX126X_RXEN             1   // D1 / P0.06
#define SX126X_TXEN             RADIOLIB_NC
#define SX126X_DIO2_AS_RF_SWITCH  true
#define SX126X_DIO3_TCXO_VOLTAGE  (1.8f)

// Baterie — dělič 2x4k7 na pin D21 / P0.31 (BSP číslo 17)
#define PIN_VBAT_READ   17
#define ADC_MULTIPLIER  (1.758f)

class PromicroBoard : public NRF52BoardDCDC {
protected:
  uint8_t btn_prev_state;
  float adc_mult = ADC_MULTIPLIER;

public:
  PromicroBoard() : NRF52Board("SuperMini_OTA") {}
  void begin();

  #define BATTERY_SAMPLES 8
  uint16_t getBattMilliVolts() override {
    analogReadResolution(12);
    uint32_t raw = 0;
    for (int i = 0; i < BATTERY_SAMPLES; i++) {
      raw += analogRead(PIN_VBAT_READ);
    }
    raw = raw / BATTERY_SAMPLES;
    return (uint16_t)(adc_mult * raw);
  }

  bool setAdcMultiplier(float multiplier) override {
    adc_mult = (multiplier == 0.0f) ? ADC_MULTIPLIER : multiplier;
    return true;
  }

  float getAdcMultiplier() const override {
    return (adc_mult == 0.0f) ? ADC_MULTIPLIER : adc_mult;
  }

  const char* getManufacturerName() const override {
    return "SuperMini DIY";
  }

  int buttonStateChanged() {
    #ifdef BUTTON_PIN
    uint8_t v = digitalRead(BUTTON_PIN);
    if (v != btn_prev_state) {
      btn_prev_state = v;
      return (v == LOW) ? 1 : -1;
    }
    #endif
    return 0;
  }

  void powerOff() override {
    sd_power_system_off();
  }
};