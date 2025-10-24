#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "UTF8.h"

void bytes2out(dataBytes&& bytes){
  std::cout.write(bytes.bytes, bytes.len);
}

int main (int argc, char *argv[]) {

  if (argc>1){
    codePoints codp=UTF8_den(argv[1]);
    
    bytes2out(deSten(codp.arr, codp.len));
    std::cout << std::endl;

  } else {

    const ssize_t bs=510;
    char buffer[bs+1];
    codePoints codp(1);

    std::cin.tie(nullptr);

    while (std::cin.read(buffer, bs)) {
      codp=UTF8_den(buffer);

      bytes2out(deSten(codp.arr, codp.len));

    }

    //ssize_t tail_size = std::cin.gcount();
    buffer[std::cin.gcount()]=0;

    codp=UTF8_den(buffer);
    bytes2out(deSten(codp.arr, codp.len));
    std::cout << std::endl;

  }
  //encoder
  /*dataBytes ut_bytes=enSten(argv[1], strlen(argv[1]));

  for (int i = 0; i < ut_bytes.len; i++) {
    printf("%c", ut_bytes.bytes[i]);
  }
  printf("\n");*/

  return 0;
}
