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
	// int  fd = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );
	// fcntl(fd, F_SETFL, 0);

	/*Define the POSIX structure*/
	struct termios tty;

	/*Read the attribute structure*/
	tcgetattr(fd, &tty);

	/*Set the baud rate of the port  to 9600*/
	// cfsetispeed(&tty, B230400);
    // cfsetospeed(&tty, B230400);
	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);
        	tty.c_cflag |= (CLOCAL | CREAD);

	/*Define other parameters in order to  realize the 8N1 standard*/
	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;
	
	/*Apply the new attributes */
	tcsetattr(fd, TCSANOW, &tty);


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

	char buf[1000];
std::cout << "Read init: " << endl;
	for(int i=0; i<100;i++) {
		std::cout<<"Block/"<<i<<"/";
		// std::cout<<"Block/"<<i<<"/"<<std::endl;
		read( fd, &buf , 10);
		std::cout << "Read: " << buf[0] << endl;
	}
}
	close(fd);
	return 0;
	}
