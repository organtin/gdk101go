/***************************************************************************
    gdk101go - an example program for the gdk101go library
    Copyright (C) 2022 giovanni.organtini@uniroma1.it

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/

#include <gdk101go.h>

#define _VERBOSE

gdk101 sensor;

/* pin 8 is used to power on the sensor */

void setup() {
  Serial.begin(9600);
#ifdef _VERBOSE
  Serial.println("\n\n\n\n\n\n\n");
  Serial.println("****** GDK101 Copyright (C) 2022 by giovanni.organtini@uniroma1.it ***");
#endif
  // power on and initialise the sensor
  sensor.poweron();
  int ret = sensor.begin();
#ifdef _VERBOSE
  if (ret) {
    Serial.print("       Sensor firmware version: ");
    Serial.println(sensor.firmware());
    Serial.println();
  } else {
    Serial.print("       Sensor not found...");
  }
  // power off it, wait for two seconds, then power on it
  sensor.poweroff();
  delay(2000);
  sensor.poweron();
  Serial.println("       Sensor activated!");
#endif
}

void checkStatus() {
  int i = 0;
  unsigned long T0 = millis() / 1000;
  unsigned long T = 0;
  do {
      Serial.print("       t (s): ");
      T = millis() / 1000 - T0;
      Serial.print(T, 1);
      Serial.print(" status: ");
      Serial.print(sensor.status());
      Serial.print(" vibrtn: ");
      Serial.print(sensor.vibration());
      Serial.print(" onsince: ");
      Serial.print(sensor.onSince());
      Serial.print(" s uptime: ");
      Serial.print(sensor.uptime());
      Serial.print(" s");
      Serial.print(" rate: ");
      Serial.print(sensor.reading1min());
      Serial.print(" uSv/h [");
      Serial.print(sensor.reading10min());
      Serial.print(" uSv/h]");
      Serial.println();
      if (T < 10) {
        delay(1000);
      } else {
       delay(10000);
      }
  } while (T < 1000);
}

void loop() {
  checkStatus();
}
