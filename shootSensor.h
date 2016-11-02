// =============================================================================
//
//  schedule_task.cpp
//  Airspace Application
//
//  Created by Ivan Lozano on 10/11/16.
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

class MatriceControl : public thread_c{

    private:
    int armedFromAirspaceVar = 1;
    int fd;

    protected:
    

    int init_serial() {
  unsigned char read_serial(int* n) 

int main()
{
  init_serial();
  std::cout << "::::Running serial reader to Fire/Sensor module:" << std::endl;
  // write_serial((void*)"v");//ask version
  write(fd, "v", 1);
  write(fd, "TEST-", 5);
  int fired = 0;
  int n=0;
  char read_char;  
  char buf[10];
  /*READ WORKING:
  while(1){
     read_char= read_serial(&n);
     if(n>0){std::cout<<"-Pointer n:"<<n<<" Char read:"<<read_char<<std::endl;  }
  }*/


  while (1) { //

    //////////////////////////////////////////////////////////////////
    read_char= read_serial(&n);
    if (read_char == 'f')
    {
      fired = 1;
      cout << "********** Net fired!" << endl;
    }
    else
    {
      fired = 0;//TODO
      if (armedFromAirspaceVar && !fired)
      {
        // write_serial((void*)"a");//send arm to aislan device
        write(fd, "a", 1);
        // read_char=read_serial();
        // read_serial(read_char);
        while (armedFromAirspaceVar)
        {
          cout << "********** in the while..." << endl;
          read_char= read_serial(&n);
          cout << "********** serial read stop...:" << read_char << endl;
          // read_serial(read_char);
          if (read_char == 'f') {
            //repeate while
          }
          else {
            fired = 1;
            cout << "**********fired received, must to go out of the while..." << endl;
            // exit(1);//TODO
            // usleep(2000000);
          }
        }
      }
      // write_serial((void*)"d");//send disarm to aislan device
      write(fd, "d", 1);
      //TODO: goto home/main after here
    }

  }




  // Don't forget to clean up
  close(fd);
  return 0;
}


};



#endif // __SHOOTSENSOR_HPP__