#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned short binAddition(unsigned short a, unsigned short b) 
{
    unsigned short c = 0; //carry

    while (b != 0) {
              //find carry and shift left
              c = (a & b) << 1;
              //find sum
              a=a^b;
              b=c;
    }

    
    return a; 
}

int main(){
    FILE *fp;
    FILE *fpw;

    char c;

    fp = fopen("dat.txt","r");

    int count = 0;
    if(fp == NULL)
    {
        puts("Not able to open this file");
        fclose(fp);
        exit(0);
    }
    while(fgetc(fp) != EOF) 
    {
        count++;
    }

    unsigned short bufferList[count/2];


    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < count/2; i++) {
        fread(&bufferList[i],2,count/2,fp);
    }

    unsigned short result = 0;

    for (int j = 0 ; j < count/2; j++ ) {
        result = binAddition(result, bufferList[j]);
    }

    result |= 1;

    int number_of_bits = floor(log2(result))+1; 
  
    result = ((1 << number_of_bits) - 1) ^ result;


    fpw = fopen("result.txt","w+");

    if (fpw == NULL) {
        puts("Not able to open this file");
        fclose(fpw);
        exit(0);
    }

    while ((c = fgetc(fp)) != EOF)
      fputc(c, fpw);

    fwrite(&result , 4 , 1 , fpw);
    fclose(fpw);
    fclose(fp);

    return 0;
}

