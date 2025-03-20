#include <cstdio>
#include <cstring>
#include <stdio.h>
#include "UTF8.h"

int main (int argc, char *argv[]) {

  codePoints codp=UTF8_den(argv[1]);
  //printf("sten bytes: %i\n", getStenLen(codp.arr, codp.len));
  /*for(int i=0;i<codp.len;i++){
    printf("%i ", codp.arr[i]);
  }
  printf("\n");*/

  //decoder
  /*dataBytes datB = deSten(codp.arr, codp.len);

  for (int i = 0; i < datB.len; i++) {
    printf("%c", datB.bytes[i]);
  }
  printf("\n");*/

  //encoder
  dataBytes ut_bytes=enSten(argv[1], strlen(argv[1]));

  for (int i = 0; i < ut_bytes.len; i++) {
    printf("%c", ut_bytes.bytes[i]);
  }
  printf("\n");

  return 0;
}
