/***************************************************************************
    gdk101go - a library for the GDK101 gamma sensor 
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

#include "gdk101go.h"

gdk101::gdk101(int addr = GDK101_ADDR) {
  /* the default constructor: assign the i2c address */
  _addr = addr;
}

gdk101::gdk101(int a0, int a1) {
  /* an alternative constructor, used when assigning
     the address by means of the jumpers A0 and A1 */
  int code = a0 * 10 + a1;
  if (code == 11) {
    _addr = GDK101_ADDR;
  } else if (code == 10) {
    _addr = 0x1A;
  } else if (code == 1) {
    _addr = 0x19;
  } else if (code == 0) {
    _addr = 0x1B;
  }
}

void gdk101::poweron(int pin = GDK101_POWER) {
  /* the sensor can be powered using a digital pin 
     such that it can be powered on and off by 
     software. The default pin is 8 */
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  begin();
  while (status() == 0) {
    // do nothing, just wait...
  }
  _uptime = millis(); 
}

float gdk101::onSince() {
  /* returns the number of seconds elapsed since 
     last power on */
  return (millis() - _uptime)/1000.;
}

void gdk101::poweroff(int pin = GDK101_POWER) {
  /* power off; requires using a digital pin for
     powering it on */
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

int gdk101::begin() {
  /* initialise the sensor */
  Wire.begin(); 
  exec_cmd(GDK101_FRMWR);
  sprintf(_fw, "%d.%d", _msb, _lsb);
  return reset();
}

int gdk101::reset() {
  /* reset the sensor */
  exec_cmd(GDK101_RESET, 1);
  return _msb;
}

int gdk101::status() {
  /* get the status: 0 - not ready; 
     1 - on since less than 10 min;
     2 - on since more than 10 min */
  exec_cmd(GDK101_STATUS, 2);
  return _msb;
}

int gdk101::vibration() {
  /* check vibration status: 0 - no vibrations */
  exec_cmd(GDK101_STATUS, 2);
  return _lsb;  
}

int gdk101::uptime() {
  /* returns the actual measuring time */
  exec_cmd(GDK101_UPTIME, 2);
  return _lsb + _msb * 60;
}

float gdk101::reading10min() {
  /* returns the reading consisting in the
     measured dose averaged over 10 minutes;
     the dose is given in uSv/h */
  exec_cmd(GDK101_10MRT, 2);
  return _msb + 0.1 * _lsb;
}

float gdk101::reading1min() {
  /* returns the reading consisting in the
     measured dose averaged over 1 minute;
     the dose is given in uSv/h */  
  exec_cmd(GDK101_1MRT, 2);
  return _msb + 0.1 * _lsb;
}

char* gdk101::firmware() {
  /* returns the firmware version */
  return _fw;  
}

void gdk101::exec_cmd(int cmd, int retCount = 2) {
  /* used internally to handle the i2c protocol */
  Wire.beginTransmission(GDK101_ADDR);
  Wire.write(cmd);
  Wire.endTransmission();  
  Wire.requestFrom(GDK101_ADDR, retCount);
  while (Wire.available()) {
    _msb = Wire.read();
    _lsb = Wire.read();
  }
}

