#include <cstdio>
#include <cstring>
#include <stdio.h>

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


//structure for array with code points

struct codePoints {
  int *arr;
  int len;
  codePoints(int length){
    this->arr=new int[length];
    this->len=length;
  }
};

//structure for array of bytes

struct dataBytes {
  char *bytes;
  int len;
  dataBytes(int length){
    this->bytes=new char[length];
    this->len=length;
  }
};

//function to calculate amount of encoded data will take in bytes

int getEnLen(int len){
  int res=0;
  res=(len/3)*6;
  res+=(len%3)*3;
  return res;
}

//function to calculate amount of decoded data will take in bytes

int getStenLen(int *arr, int len){
  int res=0;
  int bits=0;

  for (int i=0;i<len;i++) {
    if (arr[i]<=0x8fff && arr[i]>=0x8000) {
      bits+=12;
    } else if (arr[i]<=0xff) {
      bits+=8;
    }

    res+=bits/8;
    bits=bits%8;
  }

  if(bits>0)
    res+=1;

  return res;
}

//functions to get value of specific bit in number

int gBit(char num, int ind){
  return (num>>ind)&1;
}

int gBit(int num, int ind){
  return (num>>ind)&1;
}

//function to encode single code point into UTF-8
//it recives unsigned code and returns structure of array of bytes

dataBytes UTF8_enc(unsigned int code){
  unsigned char len=(code<0x10000)?((code<0x0800)?((code<0x0080)?1:2):3):4;
  dataBytes bytes(len);
 
  switch (len) {
    case 1:
      bytes.bytes[0]=code;
      break;

    case 2:
      bytes.bytes[0]=PB2|((code>>6)&MASK5);
      bytes.bytes[1]=OCTPR|(code&MASK6);
      break;

    case 3:
      bytes.bytes[0]=PB3|((code>>12)&MASK4);
      bytes.bytes[1]=OCTPR|((code>>6)&MASK6);
      bytes.bytes[2]=OCTPR|(code&MASK6);
      break;

    case 4:
      bytes.bytes[0]=PB4|((code>>18)&MASK3);
      bytes.bytes[1]=OCTPR|((code>>12)&MASK6);
      bytes.bytes[2]=OCTPR|((code>>6)&MASK6);
      bytes.bytes[3]=OCTPR|(code&MASK6);
      break;
  }
  
  return bytes;
}

//function to calculate length of string not by bytes but by characters, including UTF-8 characters

int calcLen(char *str){
  int bytes=strlen(str);
  //printf("bytes: %i\n", bytes);
  int i=0;
  int res=0;
  int subI=0;
  int utf_len=0;

  while (i<bytes) {
    utf_len=0; 
    if ((str[i]&RMASK5)==PB4) {
      res++;
      utf_len=4;

    }else if ((str[i]&RMASK4)==PB3) {
      res++;
      utf_len=3;
    
    }else if ((str[i]&RMASK3)==PB2) {
      res++;
      utf_len=2;
    
    }else {
      res++;
      i++;
      continue;

    }

    subI=1;

    while (i+subI<bytes && subI<utf_len) {
      if ((str[i+subI]&RMASK2)!=OCTPR) {
        subI=1;
        break;
      }
      subI++;
    }

    i+=subI;

  }
  return res;
}

//function to deencode string that contains UTF-8 characters and returns structure with array of codepoints of characters

codePoints UTF8_den( char *bytes ){

  codePoints res=codePoints(calcLen(bytes));
  int resI=0;
  int len=strlen(bytes);
  int utf_len=0;
  int buff=0;
  bool inUTF8=false;
  int i=0;
  int subI=0;

  while(i < len) {
    buff=0;
    inUTF8=false;

    if ((bytes[i]&RMASK5)==PB4) {
      utf_len=4;
      inUTF8=true;

    }else if ((bytes[i]&RMASK4)==PB3) {
      utf_len=3;
      inUTF8=true;
    
    }else if ((bytes[i]&RMASK3)==PB2) {
      utf_len=2;
      inUTF8=true;
    
    }else {
      res.arr[resI]=bytes[i];
      resI++;
      i++;
      continue;
    }
    

    switch (utf_len) {
      case 4:
        buff|=(bytes[i]&MASK3)<<(6*(utf_len-1));
        break;

      case 3:
        buff|=(bytes[i]&MASK4)<<(6*(utf_len-1));
        break;

      case 2:
        buff|=(bytes[i]&MASK5)<<(6*(utf_len-1));
        break;   
    }

    subI=1;
    while(i+subI<len && subI<utf_len) {
      if ((bytes[i+subI]&RMASK2)==OCTPR) {
        buff|=(bytes[i+subI]&MASK6)<<(6*(utf_len-subI-1));
      }else {
        subI=1;
        inUTF8=false;
        break;
      }
      subI++;
    }

    i+=subI;

    if (inUTF8) {
      res.arr[resI]=buff;
      resI++;
      continue;
    }

    res.arr[resI]=bytes[i];
    resI++;
  }

  return res;

}

//function to encode bytes in UTF-8 characters, recives array of bytes and length of that array, and returns string with data stored in UTF-8 characters

dataBytes enSten(char* arr, int len){
  int enLen=getEnLen(len);
  dataBytes res(enLen);

  int codePoint=0x8000;
  int subB=0;
  int bits=0;
  int cary=0;
  int shift=0;
  int bitsPass=0;
  int dataI=0;
  int i=0;

  while(i < len) {
    if(bits<=0){
      bits=8;
    }
    cary=12-subB;
    shift=subB;


    if (bits<=cary){
      subB+=bits;
      codePoint|=((arr[i]>>bitsPass)&((1<<bits)-1))<<shift;
      bits=0;
      bitsPass=0;
      i++;

    } else if (bits>cary) {
      subB=12;
      codePoint|=((arr[i]>>bitsPass)&((1<<cary)-1))<<shift;
      bits-=cary;
      bitsPass=cary;

    }


    if (subB>=12||(i>=len)) {
      dataBytes utf=UTF8_enc(codePoint);
      for (int a = 0; a < utf.len; a++) {
        res.bytes[dataI+a]=utf.bytes[a];
      }
      dataI+=utf.len;
      codePoint=0x8000;
    }

    subB%=12;
  }

  return res;
}

//function to decode data from string of UTF-8 characters
//decodes result of enSten function

dataBytes deSten(int *arr, int len){
  dataBytes res(getStenLen(arr, len));

  int dataI=0;
  int bits=0;
  int bitsPass=0;
  int subB=0;
  int cary=0;
  int shift=0;
  bool proc=false;


  for (int i=0;i<len;i++) {
    proc=false;
    bitsPass=0;
    bits=0;

    if (arr[i]<=0x8fff && arr[i]>=0x8000) {
      bits=12;
      proc=true;

    } else if (arr[i]<=0x8ff && arr[i]>=0x800) {
      bits=8;
      proc=true;
      
    } else if (arr[i]<=0xff) {
      bits=8;
      proc=true;
    }
    
    //proccess data
    while(bits>0 && proc){
      cary=8-subB;
      shift=subB;

      if(bits<=cary){
        subB+=bits;
        res.bytes[dataI] |= ((arr[i]>>bitsPass)&((1<<bits)-1))<<shift;
        bits=0;

      } else if (bits>cary) {
        subB=8;
        res.bytes[dataI] |= ((arr[i]>>bitsPass)&((1<<cary)-1))<<shift;
        bits-=cary;
        bitsPass+=cary;
        
      }
      dataI+=subB/8;
      subB%=8;
    }

  }

  return res;

}

