#include "types.h"
#include "user.h"

char* doubleSize(char* inArr, int size){
    int newSize = size * 2;
    char* outArr = malloc(newSize);
    int i;
    for (i = 0; i < size; i++)
      outArr[i] = inArr[i];
    free(inArr);
    return outArr;
}

void printArr(char* arr, int size){
  int i;
  for(i = 0; i < size; i++){
    printf(1, "%c", arr[i]);
  }
  return;
}

char* readHead(int fd, int numOflines, char* buf, int* bufSize, int* bufCap){
  char temp;
  int n;
  int l = 0;

  while((l < numOflines) && ((n = read(fd, &temp, 1)) > 0)){
    if (temp == '\n'){
      l++;
    }
    buf[*bufSize] = temp;
    (*bufSize)++;
    if (*bufSize == *bufCap){
      buf = doubleSize(buf, *bufSize);
      *bufCap *= 2;
    }
  }
  return buf;
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

  buf = readHead(fd, numOflines, buf, &bufSize, &bufCap);

  //printf(1, "start printing... \n");
  //printf(1, "bufSize: %d\n", bufSize);
  printf(1, "main(): bufSize: %d, bufCap: %d\n", bufSize, bufCap);
  printArr(buf, bufSize);
  //printf(1, "done printing... \n");

  //printf(1, "free buf\n");
  free(buf);
  exit();
}
