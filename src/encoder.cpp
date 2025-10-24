
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
