#include <stdio.h>

int absoluteness(int number) {
    if (number < 0) {
        return number * -1;
    }
    else  {
        return number;
    }
}


int main(){
    float a,b,c;
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);
    int pSum;
    int nSum;

    if (a >= 0 && b >= 0 && c >= 0) {
        printf("All Positive \n");
    }
    else if (a < 0 && b < 0 && c < 0) {
        printf("All Negative \n");
    }
    else {
        if (a != absoluteness(a)) 
        {
            nSum+=absoluteness(a);
        }
        else 
        {
            pSum+=a;
        } 
        if (b != absoluteness(b)) 
        {
            nSum+=absoluteness(b);
        }
        else 
        {
            pSum+=b;
        } 
        if (c != absoluteness(c)) 
        {
            nSum+=absoluteness(c);
        }
        else 
        {
            pSum+=c;
        } 
        if (pSum >= nSum) 
        {
            printf("Positive wins \n");
        }
        else 
        {
            printf("Negative wins \n");
        }
    }
}