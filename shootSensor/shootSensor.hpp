// =============================================================================
//
//  shootSensor.cpp
//  Airspace Application
//
//  Created by Ivan Lozano on 11/2/16.
//  Copyright © 2016 Defense Labs. All rights reserved.
//
// =============================================================================


#ifndef __SHOOTSENSOR_HPP__
#define __SHOOTSENSOR_HPP__


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include "thread.hpp"

using namespace std;

class shootSensor : public thread_c {

  private:
    enum states { 
  INIT,
  ARM,
  FIRED,
  DISARM,
  ARMED,
  NOP
};
    // int armedFromAirspaceVar = 1;
    int fd;
    int init_serial();
    char read_serial(int* n) ;
    void thread_entry();
    void thread_entry_OLD();

  protected:

  public:
    states state;
    bool armed;
    bool fired;
    bool connected;
    int arm();
    int disarm();
    shootSensor()
    {
      states state;
      state=INIT;//init_serial();
      create(); // Create Thread -> calling thread_entry()
      // armed=0;
      fired=0;
      connected=0;
    }
};



#endif // __SHOOTSENSOR_HPP__