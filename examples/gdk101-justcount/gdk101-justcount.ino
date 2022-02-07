/***************************************************************************
    gdk101-justcount - an example program for the gdk101go library
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

gdk101 sensor;

/* pin 8 is used to power on the sensor */

int count;

void setup() {
  Serial.begin(9600);
  // power on and initialise the sensor
  sensor.poweron();
  int ret = sensor.begin();
  while (sensor.status() == 0) {
    // wait until ready
  }
  count = 0;
}

void loop() {
  // reset the counter
  sensor.reset();
  // wait for completion
  delay(60000);
  while (sensor.uptime() < 60) {
    // do nothing: wait until ready
  }
  // print 1 min counts CSV style
  Serial.print(sensor.reading1min());
  Serial.print(", ");
  count++;
  // newline every 10 measurements
  if (count > 10) {  
    Serial.println();
    count = 0;
  }
}
