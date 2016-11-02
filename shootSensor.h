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

using namespace std;

class shootSensor : public thread_c {

  private:
    // int armedFromAirspaceVar = 1;
    int fd;
    int init_serial();
    unsigned char read_serial(int* n) ;
    int thread_entry();

  protected:

  public:
    bool armed;
    bool fired;
    bool connected;

    shootSensor()
    {
        init_serial();
        create(); // Create Thread -> calling thread_entry()
         armed=0;
         fired=0;
         connected=0;
    }
};



#endif // __SHOOTSENSOR_HPP__