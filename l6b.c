#include <stdio.h>
#include <string.h>


int minimum(int a, int b){
    if (a < b) {
        return a;
    }
    return b;
}
int maximum(int a, int b){
    if (a > b) {
        return a;
    }
    return b;
}


int overlap(char s1[], char s2[]) { 

    int s1size = strlen(s1);
    int s2size = strlen(s2);
    int begin, end;
    char tmp1s1[50];
    char tmp2s1[50];
    int answer;
    int min;
    int check = 1;
    int result;

    end = s1size - 1;

    for (begin = 0; begin < s1size; begin++) {
        tmp1s1[begin] = s1[end];
        end--;
    }

    min = minimum(s1size, s2size);


    for (int i = 0; i < min; i++) {
        for (int j = i, k = 0; j >= 0; j--,k++) {
            tmp2s1[k] = tmp1s1[j]; 
        } 
        answer = strncmp(tmp2s1, s2, i);
        if (answer == 0) {
            result = maximum(result, i);
        }
    }

    
    return result + 1;

}

int main() {

    char s1[50];
    char s2[50];

    scanf("%s",s1);
    scanf("%s",s2);

    int r1, r2;

    r1 = overlap(s1,s2);
    r2 = overlap(s2,s1);


    if (r1 > r2) {
        printf("%d \n", r1);
    }
    else {
        printf("%d \n", r2);
    }
}