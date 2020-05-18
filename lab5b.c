#include <stdio.h>
#include <string.h>


void lower(char s[]) {
   int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] += 32;
      }
      c++;
   }
}

int main()
{
    int n;
    char input[100];

    scanf("%s", &input);
    scanf("%d", &n);
    char baseString[26] = "abcdefghijklmnopqrstuvwxyz";
    char sub[20];
    char subInput[20];
    int i;
    int j;
    int flag = 0;
    lower(input);

    for (i = 0; i < (26 - n + 1); i++)
    {
        strncpy(sub, baseString + i, n);
        for (j = 0; j < (strlen(input) - n + 1); j++)
        {
            strncpy(subInput, input + j, n);
            if (strcmp(sub, subInput) == 0)
            {
                flag = 1;
            }
        }
    }
    if (flag == 1)
    {
        printf("%s", "YES \n");
    }
    else
    {
        printf("%s", "NO \n");
    }
    
}