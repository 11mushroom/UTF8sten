#ifndef UTF8
#define UTF8

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
  int *arr;
  int len;
  codePoints(int length){
    this->arr=new int[length];
    this->len=length;
  }
};

struct dataBytes {
  char *bytes;
  int len;
  dataBytes(int length){
    this->bytes=new char[length];
    this->len=length;
  }
};

int getStenLen(int *arr, int len);

dataBytes deSten(int *arr, int len);

int gBit(char num, int ind);

int gBit(int num, int ind);

int calcLen(char *str);

char* UTF8_enc(unsigned int code);

codePoints UTF8_den( char *bytes );

#endif
