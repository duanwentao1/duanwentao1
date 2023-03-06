//
// Created by 醉人饮梦 on 2022/10/10.
//
#include <stdio.h>
#include <string.h>

int BF(char *B,char *A){
    int i = 0,j = 0;
    // 终止条件（j: 如果确认主子串关系 j 就会等于 strlen(A)）
    while(i< strlen(B)&&j< strlen(A)){
        // 如果相等就 一起移动一位，比较第二位
        // 如果不相等A串重置位置，B串移动到刚开始和A串比较的位置的后一位
        if(B[i]==A[j]){
            i++;
            j++;
        }else{
            i = i-j+1;
            j = 0;
        }
    }
    // 通过 j 判断 A 串 B串 是否具有 子主串 关系
    if(j == strlen(A)){
        return i- (int)strlen(A)+1;
    }
    return -1;
}

int main()
{
    int i = BF("ababcabcacbab","abcac");
    printf("%d\n",i);
    return 0;
}