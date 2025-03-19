#include <cstdio>
#include <stdio.h>
#include "UTF8.h"

int main (int argc, char *argv[]) {
  //if(argc<3) return 0;
  //unsigned int qtr1=((std::stoi(argv[1])&MASK4));
  //unsigned int qtr2=((std::stoi(argv[2])&MASK4));
  //printf("%s\n",UTF8_enc(0x2800|((qtr1&MASK4)<<4)|(qtr2&MASK4)));
  //printf("%s\n",UTF8_enc(0x03ab));
  //printf("chars: %i\n", calcLen(argv[1]));
  
  //printf("%i\n", UTF8_den(argv[1]).arr[1]);

  codePoints codp=UTF8_den(argv[1]);
  printf("sten bytes: %i\n", getStenLen(codp.arr, codp.len));
  for(int i=0;i<codp.len;i++){
    printf("%i ", codp.arr[i]);
  }
  printf("\n");

  return 0;
}
