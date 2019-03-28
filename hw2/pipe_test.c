#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){

  int filedes;
  filedes = open("james_sucks.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  int returnValue;
  returnValue = fork();
  if (returnValue == 0){
    char msg[] = "Process 1\n";
    printf("I'm the child. PID: %d\n", getpid());
    write(filedes, msg, sizeof(msg));
  }
  else {
    char msg[] = "Process 2\n";
    printf("I'm the parent. PID: %d\n", getpid());
    write(filedes, msg, sizeof(msg));
  }

  close(filedes);

}
