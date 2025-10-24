#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include "UTF8.h"

void bytes2out(dataBytes&& bytes){
  std::cout.write(bytes.bytes, bytes.len);
}

int main (int argc, char *argv[]) {

  if (argc>1){

    bytes2out(enSten(argv[1], strlen(argv[1])));
    std::cout << std::endl;

  } else {

    const ssize_t bs=510;
    char buffer[bs];

    std::cin.tie(nullptr);

    while (std::cin.read(buffer, bs)) {
      bytes2out(enSten(buffer, bs));
    }

    ssize_t tail_size = std::cin.gcount();
    bytes2out(enSten(buffer, tail_size));
    std::cout << std::endl;


  }

  return 0;
}
