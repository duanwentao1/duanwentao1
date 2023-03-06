//
// Created by dream on 2023/3/6.
//

#include <stdio.h>
#define NUMBER 3
typedef struct {
    int i,j; // 行，列
    int data; // 元素值
}triple;

typedef struct {
    triple data[NUMBER];
    int n,m,num; // 总行数，总列数，元素值
}TSMatrix;

void display(TSMatrix M);

int main()
{
    TSMatrix M;
    M.m = 3;
    M.n = 3;
    M.num = 3;
    M.data[0].i = 1;
    M.data[0].j = 1;
    M.data[0].data = 1;
    M.data[1].i = 2;
    M.data[1].j = 3;
    M.data[1].data = 5;
    M.data[2].i = 3;
    M.data[2].j = 1;
    M.data[2].data = 3;

    display(M);

    return 0;
}

void display(TSMatrix M)
{
    for(int i = 1;i<=M.n;i++){
        for(int j = 1;j<=M.m;j++){
            int value = 0;
            for(int k = 0;k<M.num;k++){
                // 循环 data结构 的数据，如果同时 满足 (i,j) 条件 则打印 data结构 对应的值
                if(i == M.data[k].i && j == M.data[k].j){
                    printf("%d ",M.data[k].data);
                    value = 1;
                    break;
                }
            }
            if(value==0)
                printf("0 ");
        }
        printf("\n");
    }
}