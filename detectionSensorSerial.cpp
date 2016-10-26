#include <iostream>
#include <stdio.h>
#include <string.h>
// #include <string>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

using namespace std;
// int main(int argc, char * argv) {

int fd;



int init_serial() {
  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("open_port: Unable to open /dev/ttyS0 - ");
    return (-1);
  }
  else {
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

}



int write_serial(void* h_data) {
// int write_serial(std::string &h_data) {
  int n=0;
  int max_buff=10;
  n = write(fd, (void*)h_data, max_buff);
  if (n < 0)
  { perror("Write failed - ");
    return -1;
  }
 return 1;
}

int read_serial(char &read_char) {
  // TODO: we need to send aaaa to read only one a, improve this!
  // Read up to 255 characters from the port if they are there
  char buf[256];
  int n = read(fd, (void*)buf, 4);
  if (n < 0) {
    perror("Read failed - ");
    return -1;
  }
  else if (n == 0) {
    // printf("No data on port\n");
    // usleep(500000);
  }
  else {

    read_char=buf[0];
    std::cout<<"Charter read:"<<read_char<<std::endl;

    // buf[n] = '\0';
    // printf("%i bytes read : %s", n, buf);
    // usleep(500000);
  }
}




int main() {
  init_serial();
  // write_serial((void*)"test ");usleep(500000);

  std::cout<<"Starting to read->"<<std::endl;
  while(1){    
    char read_char;
    read_serial(read_char);
    std::cout<<" -Charter read in main:"<<read_char<<std::endl;
    usleep(50000);
  }



  // Don't forget to clean up
  close(fd);
  return 0;
}