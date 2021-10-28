#include <Arduino.h>
#include <M5Stack.h>
#include <HTTPClient.h>
#include <wifi.h>
#include <timer.h>
#include <sendJson.h>

#include <driver/i2s.h>
#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2
#define I2S_PORT I2S_NUM_0


void i2s_install(){
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0, // default interrupt priority
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin(){
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  M5.begin();
  M5.Power.begin();
  Serial.begin(115200);

  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
  delay(500);

  //connectWifi();
  //setTime();

}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t sample = 0;
  int bytes = i2s_pop_sample(I2S_PORT, (char*)&sample, portMAX_DELAY);
  if(bytes > 0){
    Serial.println(sample);
  }
  if (WiFi.status() == WL_CONNECTED){
    sendJson();
    delay(20000);
  };
  delay(1000);

}