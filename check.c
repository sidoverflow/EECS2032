#include <stdio.h>
#include <stdlib.h>

unsigned short binAddition(unsigned short a, unsigned short b)
{
    unsigned short c = 0; //carry

    while (b != 0)
    {
        //find carry and shift left
        c = (a & b) << 1;
        //find sum
        a = a ^ b;
        b = c;
    }

    return a;
}

unsigned short areAllBitsSet(unsigned short n)
{
    // all bits are not set
    if (n == 0)
        return 0;
    // loop till n becomes 0
    while (n > 0)
    {
        // if the last bit is not set
        if ((n & 1) == 0)
            return 0;

        // right shift n by 1
        n = n >> 1;
    }
    // all bits are set
    return 1;
}

int main()
{

    FILE *fp;

    fp = fopen("result.txt", "r");

    int count = 0;
    if (fp == NULL)
    {
        puts("Not able to open this file");
        fclose(fp);
        exit(0);
    }
    while (fgetc(fp) != EOF)
    {
        count++;
    }

    unsigned short bufferList[count / 2];

    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < count / 2; i++)
    {
        fread(&bufferList[i], 2, count / 2, fp);
    }

    unsigned short result = 0;

    for (int j = 0; j < count / 2; j++)
    {
        result = binAddition(result, bufferList[j]);
    }

    result |= 1;

    if (areAllBitsSet(result) == 1)
    {
        printf("%s \n", "Valid");
    }
    else
    {
        printf("%s \n", "Invalid");
    }

    fclose(fp);
}