//System Headers


#include <cstring>



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
/////////////
using namespace std;
int armedFromAirspaceVar = 1;
int fd;

int init_serial() {
  //fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY); 
  //fd = open("/dev/tty0", O_RDWR| O_NOCTTY );
  //fd = open("/dev/ttyS0", O_RDWR| O_NOCTTY );
  //fd = open("/dev/ttyTHS0", O_RDWR| O_NOCTTY );
  //fd = open("/dev/ttyTHS1", O_RDWR| O_NOCTTY );
  fd = open("/dev/ttyTHS2", O_RDWR| O_NOCTTY );
  //fd = open("/dev/ttyTHS3", O_RDWR| O_NOCTTY );
  if (fd == -1) {
    perror("open_port: Unable to open /dev/ttyYOURPORT - ");
    return (-1);
  }

  else {
    // perror("open_port: OK ");
    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetispeed(&tty, B230400);cfsetospeed(&tty, B230400);
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

int main(int argc, char *argv[])
{
init_serial();

  while(1){
    cout<<"writing:u "<<endl;
    write(fd, "f", 1);//send disarm to Aislan sensor
    usleep(1000000);
	
 }


  return 0;
}
