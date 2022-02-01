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

#ifndef GDK101GO_H
#define GDK101GO_H

#include "Arduino.h"
#include <Wire.h>

#define GDK101_ADDR   0x18
#define GDK101_RESET  0xA0
#define GDK101_STATUS 0xB0
#define GDK101_UPTIME 0xB1
#define GDK101_10MRT  0xB2
#define GDK101_1MRT   0xB3
#define GDK101_FRMWR  0xB4

#define GDK101_POWER  8

class gdk101 {
  public:
    gdk101(int addr = GDK101_ADDR);
    gdk101(int a0, int a1);
    int   begin();
    int   reset();
    int   status();
    int   vibration();
    int   uptime();
    float onSince();
    float reading10min();
    float reading1min();
    char* firmware();
    void poweron(int pin = GDK101_POWER);
    void poweroff(int pin = GDK101_POWER);
  private:  
    int  _addr;
    char _fw[6];
    int  _msb;
    int  _lsb;
    void exec_cmd(int cmd, int retCount = 2);
    unsigned long _uptime;
};

#endif
