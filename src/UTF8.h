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

#ifndef UTF8
#define UTF8

#include <algorithm>
#include <iostream>
#include <utility>
#define OCTPR  0b10000000
#define PB2    0b11000000
#define PB3    0b11100000
#define PB4    0b11110000
#define MASK3  0b00000111
#define MASK4  0b00001111
#define MASK5  0b00011111
#define MASK6  0b00111111
#define MASK8  0b11111111
#define RMASK2 0b11000000
#define RMASK3 0b11100000
#define RMASK4 0b11110000
#define RMASK5 0b11111000

struct codePoints {
  int *arr=nullptr;
  int len;
  codePoints(int length){
    this->arr=new int[length]();
    this->len=length;
  }
  
  ~codePoints(){
    delete[] this->arr;
  }

  codePoints(const codePoints& other){
    this->arr = new int[other.len];
    std::copy(other.arr, other.arr+other.len, this->arr);
    this->len=other.len;
  }

  codePoints(codePoints&& other) noexcept {
    std::swap(this->arr, other.arr);
    this->len=other.len;
  }

  codePoints& operator=(const codePoints& other){

    return *this = codePoints(other);
  }

  codePoints& operator=(codePoints&& other) noexcept {
    std::swap(this->arr, other.arr);
    this->len=other.len;

    return *this;
  }
  

};

struct dataBytes {
  char *bytes=nullptr;
  int len;
  dataBytes(int length){
    this->bytes=new char[length]();
    this->len=length;
  }


  ~dataBytes(){
    delete[] this->bytes;
  }

  dataBytes(const dataBytes& other){
    this->bytes = new char[other.len];
    std::copy(other.bytes, other.bytes+other.len, this->bytes);
    this->len=other.len;
  }

  dataBytes(dataBytes&& other) noexcept {
    std::swap(this->bytes, other.bytes);
    this->len=other.len;
  }

  dataBytes& operator=(const dataBytes& other){

    return *this = dataBytes(other);
  }

  dataBytes& operator=(dataBytes&& other) noexcept {
    std::swap(this->bytes, other.bytes);
    this->len=other.len;

    return *this;
  }
};

int getStenLen(int *arr, int len);

dataBytes enSten(char* arr, int len);

dataBytes deSten(int *arr, int len);

int gBit(char num, int ind);

int gBit(int num, int ind);

int calcLen(char *str);

dataBytes UTF8_enc(unsigned int code);

codePoints UTF8_den( char *bytes );

#endif
