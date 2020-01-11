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
  if (text.length() > 0) {
    lcd.setCursor(0, line);
    lcd.print(text);
  }
}

String getTime() {
  unsigned long currentTime = rtc.now();
  String timeStr;
  if (currentTime != lastTime) {
    timeStr = rtc.dayString(currentTime)
            + "/"
            + rtc.monthString(currentTime)
            + "   "
            + rtc.hourString(currentTime) 
            + ":"
            + rtc.minuteString(currentTime)
            + ":"
            + rtc.secondString(currentTime);
    lastTime = currentTime;
  }
  return timeStr;
}
