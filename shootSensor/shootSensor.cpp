// =============================================================================
//
//  shootSensor.h
//  Airspace Application
//
//  Created by Ivan Lozano on 11/2/16.
//  Copyright © 2016 Defense Labs. All rights reserved.
//
// =============================================================================


#include "shootSensor.hpp"

using namespace std;
int armedFromAirspaceVar = 1;
int fd;

int shootSensor::init_serial() {
  // fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY); 
  fd = open( "/dev/ttyS0", O_RDWR| O_NOCTTY );
  if (fd == -1) {
    perror("open_port: Unable to open /dev/ttyS0 - ");
    return (-1);
  }

  else {
    // perror("open_port: OK ");
    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetispeed(&tty, B115200);cfsetospeed(&tty, B115200);
    // cfsetispeed(&tty, B230400);cfsetospeed(&tty, B230400);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tcsetattr(fd, TCSANOW, &tty);
  // Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
  // fcntl(fd, F_SETFL, FNDELAY);
  // fcntl(fd, F_SETFL, 0);//blocking serial port flow
  }
  
}

char shootSensor::read_serial(int* n) 
{   
   char buff[100];
    *n =read( fd, &buff , 2);
    // std::cout<<"Num of chars:"<<*n<<std::endl; 
    if((*n>0) && ((buff[0] !='\r')||(buff[0] !='\n')))
    {
      // std::cout<< " Char Read: " << buff[0] << std::endl;usleep(2000000);
      return buff[0];
      }

}


void shootSensor::thread_entry_OLD()//threat or main logic
{
  // // init_serial(); working on the initialization on: shootSensor()
  // std::cout << "::::Running serial reader to Fire/Sensor module:" << std::endl;
  // // write_serial((void*)"v");//ask version
  // write(fd, "v", 1);
  // write(fd, "TEST-", 5);
  // int fired = 0;
  // int n=0;
  // char read_char;  
  // char buf[10];
  // /*READ WORKING:
  // while(1){
  //    read_char= read_serial(&n);
  //    if(n>0){std::cout<<"-Pointer n:"<<n<<" Char read:"<<read_char<<std::endl;  }
  // }*/
  // while (1) { //

  //   //////////////////////////////////////////////////////////////////
  //   read_char= read_serial(&n);
  //   if (read_char == 'f')
  //   {
  //     fired = 1;
  //     cout << "********** Net fired!" << endl;
  //   }
  //   else
  //   {
  //     // fired = 0;//TODO
  //     if (armedFromAirspaceVar && !fired)
  //     {

  //       write(fd, "a", 1);//send arm to Aislan sensor
  //       while (armedFromAirspaceVar)
  //       {
  //         cout << "********** in the while..." << endl;
  //         read_char= read_serial(&n);
  //         cout << "********** serial read stop...:" << read_char << endl;

  //         if (read_char == 'f') {
  //           fired = 1;
  //           cout << "**********fired received, must to go out of the while..." << endl;
  //           armedFromAirspaceVar=0;
  //         }
  //         // else {
  //         //   //repeate while

  //         // }
  //       }
  //     }
  //     // write_serial((void*)"d");//send disarm to aislan device
  //     write(fd, "d", 1);
  //     //TODO: goto home/main after here
  //   }

  // }

  // // Don't forget to clean up the Serialport
  // close(fd);


}


// int shootSensor::armSensor(){}
// int shootSensor::disarmSensor(){}

int shootSensor::arm(){
    state = ARM;


}
int shootSensor::disarm(){
    state = DISARM;
}

void shootSensor::thread_entry(){


  std::cout << "::::Running serial reader to Fire/Sensor module:" << std::endl;
  char read_char;  
  int n=0;
  

  while(1) {
  switch(state) {
  case INIT:
    init_serial();
    state = DISARM; 
    break;
  case ARM:
    write(fd, "a", 1);//send arm to Aislan sensor
    std::cout << "********** CAUTION: Net is armed!" << std::endl;
    state = ARMED; // LED back on on next round
    break;
  case ARMED:
     read_char= read_serial(&n);
    if (read_char == 'f')
    {
      state = FIRED;
    }
    break;
  case FIRED:
    fired = 1;
    std::cout << "********** Net fired!" << std::endl;
    state = DISARM;
    break;
  case DISARM:
    write(fd, "d", 1);//send arm to Aislan sensor
    std::cout << "********** Net is disarmed" << std::endl;
    state = NOP;
    break; 
  case NOP:
    usleep(20000);
    break;  

   }

  }

}    