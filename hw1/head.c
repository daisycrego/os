#include "types.h"
#include "user.h"

#define DEFAULT_LINES 10

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

char* readHead(int fd, int lines, char* buf, int* bufSize, int* bufCap){
  char temp;
  int n;
  int l = 0;

  while((l < lines) && ((n = read(fd, &temp, 1)) > 0)){
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
  int lines;
	int fd;

  if (argc == 1){
    fd = 0;
    lines = DEFAULT_LINES;
  }
  else if (argc == 2){
    char* arg2 = argv[1];
    if (*arg2 == '-'){
      arg2++;
      lines = atoi(arg2);
      fd = 0;
    }
    else {
      lines = DEFAULT_LINES;
      if((fd = open(argv[1], 0)) < 0){
        printf(1, "head: cannot open %s\n", argv[1]);
        exit();
      }
    }
  }
  else if (argc == 3){
    char* arg2 = argv[1];
    if (*arg2 == '-'){
      arg2++;
      lines = atoi(arg2);
      if((fd = open(argv[2], 0)) < 0){
        printf(1, "head: cannot open %s\n", argv[2]);
        exit();
      }
    }
    else {
      printf(1, "usage: head [-number of lines] [filename]\n");
      exit();
    }
  }
  else {
    printf(1, "usage: head [-number of lines] [filename]\n");
    exit();
  }

  buf = readHead(fd, lines, buf, &bufSize, &bufCap);
  printArr(buf, bufSize);
  free(buf);

  exit();
}
