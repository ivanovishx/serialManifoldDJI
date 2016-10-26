// #include <rs232.h>

// #define COMPORT         16       // this is '/dev/ttyUSB0' (for arduino) or choose wherever you added '/dev/ttyAMA0' (for raspberry pi UART pins) to the list
// #define BAUDRATE      9600   // or whatever baudrate you want
// #define RECEIVE_CHARS   8      // or whatever size of buffer you want to receive
// #define SEND_CHARS      4      // or whatever size of buffer you want to send

// int main (int argc, char **argv) {
//    unsigned char receive_buffer[RECEIVE_CHARS];
//    unsigned char send_byte = 42;
//    unsigned char send_buffer[SEND_CHARS] = {'a','b','c','d'};

//    OpenComport(COMPORT, BAUDRATE);
//    while(1) {
//       // change send_byte and/or send_buffer with what you want to send. Then:
//       SendByte(COMPORT, send_byte); // or:
//       SendBuf(COMPORT, send_buffer, SEND_CHARS);
      
//       // and/or:
//       PollComport(COMPORT, receive_buffer, RECEIVE_CHARS);

//       // do something with received data in buffer
//       // maybe sleep for a while
//    }
//    CloseComport(COMPORT);
   
//    return 0;
// }  




#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

// int main(int argc, char * argv) {
int main(){
  int fd;
  // Open the Port. We want read/write, no "controlling tty" status, and open it no matter what state DCD is in
  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("open_port: Unable to open /dev/ttyS0 - ");
    return(-1);
  }

  else{
   struct termios tty;
tcgetattr(fd, &tty);
cfsetispeed(&tty, B230400);
cfsetospeed(&tty, B230400);
// cfsetispeed(&tty, B115200);
// cfsetospeed(&tty, B115200);
tcsetattr(fd, TCSANOW, &tty);
  }
  // Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
  fcntl(fd, F_SETFL, 0);
  
  // Write to the port
  // int n = 1;//TODO
  // write("Hello Peripheral");
  // write("a");
 

int n=0;
bool toggle=1;
while(toggle){

  n = write(fd,"Hello",6);
  usleep(500000);
  if (n < 0) {
    perror("Write failed - ");
    return -1; 
  }

}


while(!toggle){


  // Read up to 255 characters from the port if they are there
  char buf[256];
  n = read(fd, (void*)buf, 255);
  if (n < 0) {
    perror("Read failed - ");
    return -1;
  } 
  else if (n == 0) {
   printf("No data on port\n");
   usleep(500000);
   }
  else {
    buf[n] = '\0';
    printf("%i bytes read : %s", n, buf);
    usleep(500000);
  }
}

  // Don't forget to clean up
  close(fd);
  return 0;
}