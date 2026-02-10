#include <SPI.h>
#include <usbhub.h>
#include <PS3USB.h>

// USB Host (MAX3421E)
USB Usb;

PS3USB PS3(&Usb);

static const uint8_t STATUS_LED_PIN = 13;

void onPs3Init() {
  PS3.setAllOff();
  PS3.setLedOn(LED1);
  PS3.setRumbleOff();
}

void setup() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, LOW);

  // Serial.begin(115200);

  if (Usb.Init() != 0) {
    while (true) {
      digitalWrite(STATUS_LED_PIN, HIGH);
      delay(150);
      digitalWrite(STATUS_LED_PIN, LOW);
      delay(150);
    }
  }

  PS3.attachOnInit(onPs3Init);
}

void loop() {
  Usb.Task();

  if (PS3.PS3Connected) {
    digitalWrite(STATUS_LED_PIN, HIGH);
  } else {
    static uint32_t t = 0;
    if (millis() - t > 500) {
      t = millis();
      digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
    }
  }
}
