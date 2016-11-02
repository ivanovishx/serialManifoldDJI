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
int armedFromAirspaceVar = 1;
int fd;

int init_serial() {
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

    /////////////
    /* Setting other Port Stuff */
    // tty.c_cflag     &=  ~PARENB;            // Make 8n1
    // tty.c_cflag     &=  ~CSTOPB;
    // tty.c_cflag     &=  ~CSIZE;
    // tty.c_cflag     |=  CS8;

    // tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    // tty.c_cc[VMIN]   =  1;                  // read doesn't block
    // tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    // tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    // /* Make raw */
    // cfmakeraw(&tty);

    // /* Flush Port, then applies attributes */
    // tcflush( fd, TCIFLUSH );
    // if ( tcsetattr ( fd, TCSANOW, &tty ) != 0) {
    //    std::cout << "Error " << errno << " from tcsetattr" << std::endl;
    // }
  }
  
  // Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
  // fcntl(fd, F_SETFL, FNDELAY);
  // fcntl(fd, F_SETFL, 0);//blocking serial port flow
}



unsigned char read_serial(int* n) 
{   
   char buff[100];
    *n =read( fd, &buff , 2);
    // std::cout<<"Num of chars:"<<*n<<std::endl; 
    if((*n>0) && ((buff[0] !='\r')||(buff[0] !='\n')))
    {
      // std::cout<< " Char Read: " << buff[0] << std::endl;
      // usleep(2000000);
      return buff[0];
      }

}




std::string readLine()
{

 
}

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


while(1){


// do{
   read_char= read_serial(&n);
   // read_serial(&n);
   if(n>0){
    std::cout<<"-Pointer n:"<<n<<" Char read:"<<read_char<<std::endl;  
    // usleep(2000000); 
   }
  // }while(n>0);

// std::cout<<"waiting serial port:"<<std::endl ;
}





  while (buf[1] != '\r' && n > 0) {
    // cout << "********** in the while..." << endl;
    std::cout << "Read init: " << endl;
  for(int i=0; i<100;i++) {
    n=read( fd, &buf , 2);
    // n=read( fd, &buf , 10);
    std::cout<<"Num of chars:"<<n << " Read: " << buf[0] << endl;
    }
/*

    do {
      n = read( fd, &buf, 1 );
      cout << "********** serial charters:" << n << endl;
      // sprintf( &response[spot], "%c", buf );
      spot += n;
    } while ( buf != '\r' && n > 0);
    cout << "********** serial read" << buf << endl;

    // if(read(fd, &read_char, 1))
    // {

    // cout << "********** serial read stop1...:" << read_char << endl;
    // usleep(500000);
    // }
    // else
    // {
    // cout<<"no read "<<endl;
    // }*/
  }



  while (1) { //

    //////////////////////////////////////////////////////////////////
    read(fd, &read_char, 1);
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
          read(fd, &read_char, 1);
          cout << "********** serial read stop...:" << read_char << endl;
          // read_serial(read_char);
          if (read_char == 'f') {
            //repeate while
          }
          else {
            fired = 1;
            cout << "**********fired received, must to go out of the while..." << endl;
            // exit(1);//TODO
            usleep(2000000);
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