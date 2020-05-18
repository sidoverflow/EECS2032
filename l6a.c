#include <stdio.h>

int check;
void subCheck(char sub[], char main[], int i) {
    int j = 0;
    for (int k = i; k < (i + size(sub)); k++) {
        if (main[k] != sub[j]) {
            check = 0;
        }
        else {
            check = 1;
        }
        j++;
    }
    
}

int size(char* str){
    int i = 0;
    int size = 0;
    while(str[i] != '\0') {
        size++;
        i++;
    }
    return size;
}

int main() {

    char s1[50];
    char s2[50];

    scanf("%s",s1);
    scanf("%s",s2);

    int s1size;
    int s2size;

    s1size = size(s1);
    s2size = size(s2);

    for (int k = 0; k < s2size; k++) {
        if (s2[k] == s1[0]) {
            subCheck(s1, s2, k);
        }
    }

    if (check == 1) {
        printf("YES \n");
    }
    else {
        printf("NO \n");
    }
}

