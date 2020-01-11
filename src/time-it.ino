/*
 * Project time-it
 * Description:
 * Author:
 * Date:
 */
#include "../lib/SparkTime/src/SparkTime.h"
#include "../lib/LiquidCrystal/src/LiquidCrystal.h"

UDP UDPClient;
SparkTime rtc;

unsigned long lastTime = 0UL;

LiquidCrystal lcd(5, 4, 3, 2, 1, 0);

void setup() {
  lcd.begin(16, 2);

  rtc.begin(&UDPClient, "north-america.pool.ntp.org");
  rtc.setTimeZone(1); // gmt offset
  
  Particle.publish("Time at startup: " + getTime());

}

void loop() {
  setText(getTime(), 0);
    
}

int setText(String text, int line) {
  lcd.setCursor(0, line);
  lcd.print(text);
}

String getTime() {
  unsigned long currentTime;
  currentTime = rtc.now();
  uint8_t currentSecond = rtc.second(currentTime);
  String timeStr;
  if (currentTime != lastTime) {
    timeStr = "";
    timeStr += rtc.hourString(currentTime);
    timeStr += getSeparator(currentSecond);
    timeStr += rtc.minuteString(currentTime);
    timeStr += getSeparator(currentSecond);
    timeStr += rtc.secondString(currentTime);	
    lastTime = currentTime;
    }
  return "    " + timeStr;
}

String getSeparator(uint8_t second) {
  if (second % 2 == 1) {
    return ":";
  }
  return " ";
}
