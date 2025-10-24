
/*
 * This file is part of UTF8sten.
 * 
 * UTF8sten is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * UTF8sten is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with UTF8sten. If not, see <https://www.gnu.org/licenses/>.
 */


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
