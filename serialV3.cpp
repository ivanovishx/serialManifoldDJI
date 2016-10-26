#include <stdio.h>      
#include <unistd.h>     
#include <fcntl.h>      
#include <errno.h>      
#include <termios.h>    
#include <iostream>

using namespace std;

int main()
{
	int  serial_port = open( "/dev/ttyTHS1", O_RDWR| O_NOCTTY );
	// int  serial_port = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );
	// fcntl(serial_port, F_SETFL, 0);

	/*Define the POSIX structure*/
	struct termios serial_options;

	/*Read the attribute structure*/
	tcgetattr(serial_port, &serial_options);

	/*Set the baud rate of the port  to 9600*/
	cfsetispeed(&serial_options, B115200);
	cfsetospeed(&serial_options, B115200);
        	serial_options.c_cflag |= (CLOCAL | CREAD);

	/*Define other parameters in order to  realize the 8N1 standard*/
	serial_options.c_cflag &= ~PARENB;
	serial_options.c_cflag &= ~CSTOPB;
	serial_options.c_cflag &= ~CSIZE;
	serial_options.c_cflag |= CS8;
	
	/*Apply the new attributes */
	tcsetattr(serial_port, TCSANOW, &serial_options);


	/*Now, we read the first 100 line from the data stream, then we close the port */



int n=0;
bool toggle=1;


while(toggle){
std::cout << "writing: Hello: " << endl;

  n = write(serial_port,"Hello",6);
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
		read( serial_port, &buf , VEOL);
		std::cout << "Read: " << buf << endl;
	}

	close(serial_port);
	return 0;
	}
}