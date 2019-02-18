#include "types.h"
#include "user.h"

char* resize(char* inArr, int* size){
    char* outArr = malloc(*(size)*2);
    int i;
    for (i = 0; i < *size; i++)
      outArr[i] = inArr[i];
    free(inArr);
    *size *= 2;
    return outArr;
}

void printArr(char* arr, int size){
  int i;
  for(i = 0; i < size; i++){
    printf(1, "%c", arr[i]);
  }
  return;
}

int readHead(int fd, int numOflines, char* buf, int bufSize, int bufCap){
  char temp;
  int n;
  int l = 0;

  while(((n = read(fd, &temp, 1)) > 0) && l < numOflines){
    if (temp == '\n'){
      l++;
    }
    buf[bufSize] = temp;
    bufSize++;
    if (bufSize == bufCap)
      buf = resize(buf, &bufCap);
  }
  return bufSize;
}

int main(int argc, char *argv[]){

  int bufCap = 512;
  int bufSize = 0;
  char* buf = malloc(bufCap);
  int numOflines = 10;
	int fd;

  if (argc <= 1){ //filename NOT provided
    fd = 0;
  }
  else { //filename provided
    if((fd = open(argv[1], 0)) < 0){
      printf(1, "head: cannot open %s\n", argv[1]);
      exit();
    }
  }

  bufSize = readHead(fd, numOflines, buf, bufSize, bufCap);

  //printf(1, "start printing... \n");
  //printf(1, "bufSize: %d\n", bufSize);
  printArr(buf, bufSize);
  //printf(1, "done printing... \n");

  //printf(1, "free buf\n");
  free(buf);
  exit();
}
