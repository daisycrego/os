#include "types.h"
#include "user.h"

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

  char temp;

  //int n = -1;
  int l = 0;

  int n = read(fd, &temp, 1);
  while(n > 0 && l < numOflines){
    //printf(1, "temp: %c\n", temp);
    if (temp == '\n'){
      l++;
      //printf(1, "incrementing l: %d\n", l);
    }
    buf[bufSize] = temp;
    bufSize++;
    if (bufSize == bufCap){
      //printf(1, "resizing buffer\n");
      char* outArr = malloc(bufSize*2);
      int j;
      for (j = 0; j < bufSize; j++)
        outArr[j] = buf[j];
      free(buf);
      buf = outArr;
      bufCap *= 2;
    }

    n = read(fd, &temp, 1);
  }

  //printf(1, "start printing... \n");
  //printf(1, "bufSize: %d\n", bufSize);
  int i;
  for(i = 0; i < bufSize; i++){
    printf(1, "%c", buf[i]);
  }
  //printf(1, "done printing... \n");

  //printf(1, "free buf\n");
  free(buf);
  exit();
}

/*

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

void readHead(int fd, int numOflines, char* buf, int bufSize, int bufCap){
  char temp;

  int n = -1;
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
  return;
}
*/
