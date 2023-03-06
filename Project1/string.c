//
// Created by 醉人饮梦 on 2023/2/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* a1 = NULL;
    char* a2 = NULL;
    a1 = malloc(10 * sizeof(char));
    strcpy_s(a1,6,"hello");
    a2 = malloc(10 * sizeof(char));
    strcpy_s(a2,7," world");
    int length1 = (int)strlen(a1);
    int length2 = (int)strlen(a2);
    // 总长
    int length = length1 + length2;
    if(length1 < length){
        // 加 1 ：给 '\0' 留一个位置
        a1 = realloc(a1, (length+1) * sizeof(char));
    }
    for (int i = length1; i < length; ++i) {
        a1[i] = a2[i - length1];
    }
    a1[length] = '\0';
    printf("%s", a1);
    free(a1);
    free(a2);

    exit(0);
}
