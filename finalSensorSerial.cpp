#include <stdio.h>      
#include <unistd.h>     
#include <fcntl.h>      
#include <errno.h>      
#include <termios.h>    
#include <iostream>

using namespace std;

int main()
{
	int  fd = open( "/dev/ttyS0", O_RDWR| O_NOCTTY );
	  // fd = open( "/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	
	struct termios tty;
	tcgetattr(fd, &tty);
	cfsetispeed(&tty, B230400);
    cfsetospeed(&tty, B230400);
    tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;
	// tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    // tty.c_cc[VMIN]   =  1;                  // read doesn't block
    // tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	/*Apply the new attributes */
	tcsetattr(fd, TCSANOW, &tty);
// fcntl(fd, F_SETFL, FNDELAY);

	/*Now, we read the first 100 line from the data stream, then we close the port */



int n=0;
bool toggle=0;


while(toggle){
std::cout << "writing: Hello: " << endl;

  n = write(fd,"Hello",6);
  usleep(500000);
  if (n < 0) {
    perror("Write failed - ");
    return -1; 
  }

}


while(!toggle){

	char buf[10];
    std::cout << "Read init: " << endl;
	for(int i=0; i<100;i++) {
		n=read( fd, &buf , 2);
		// n=read( fd, &buf , 10);
		std::cout<<"Num of chars:"<<n << " Read: " << buf[0] << endl;
	}
}
	close(fd);
	return 0;
	}
