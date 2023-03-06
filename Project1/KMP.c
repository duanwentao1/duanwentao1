//
// Created by 醉人饮梦 on 2022/10/10.
//

#include <stdio.h>
#include <string.h>

//只有特定的值对比
void Next(char *T, int *next){
    int i = 0,j = -1;
    next[0] = -1;
    while (i< strlen(T)){
        if(j==-1||T[i]==T[j]){
            i++;
            j++;
            next[i] = j;
        } else{
            j = next[j];
        }
    }
}

int KMP(char *S, char *T){
    int next[10];
    Next(T,next);
    int i = 1,j = 1;
    while (i<= strlen(S)&&j<= strlen(T)){
        if(j==0||S[i-1]==T[j-1]){
            i++;
            j++;
        } else{
            j = next[j];
        }
    }
    if(j > strlen(T)){
        return i-(int) strlen(T);
    }
    return -1;
}

int main() {
    int i = KMP("ababcabcacbab","abcac");
    printf("%d\n",i);
    return 0;
}
