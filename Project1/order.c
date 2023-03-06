//
// Created by 醉人饮梦 on 2023/2/18.
//

#include <stdio.h>
#include <stdlib.h>
#define Size 5

// 对结构体重命名
typedef struct Table{
    int* head; //声明一个动态数组 head
    int length; //记录当前顺序表的长度
    int size; //记录顺序表分配的存储容量
}table;

// 初始化结构体
table initTable(){
    table t;
    // 分配一个新的存储空间并将地址返回，malloc返回一个通用指针(void *)，没必要强转
    t.head = malloc(Size*sizeof(int));
    // 如果分配失败会返回一个空指针
    if(!t.head){
        printf("初始化失败");
        exit(0);
    }
    t.length = 0; // 空表的长度初始化为0
    t.size = Size; // 空表能存储多少个数据
    return t;
}

// 打印结构体
void displayTable(table t){
    int i;
    for(i=0;i<t.length;i++){
        printf("%d ",t.head[i]);
    }
    printf("\n");
}

//添加
table addTable(table t, int elem, int add)
{
    int i;
    //判断插入位置是否有问题
    if(add>t.length+1||add<1){
        printf("插入位置有问题");
        return t;
    }
    if(t.length==t.size){
        //重新分配内存一块内存
        t.head = realloc(t.head,(t.size+1)*sizeof(int));
        if(!t.head){
            printf("内存分配失败");
            return t;
        }
        t.size+=1;
    }
    //将从插入位置开始的元素逐个往后移
    for(i=t.length-1;i>=add-1;i--){
        t.head[i+1] = t.head[i];
    }
    //将元素放入插入位置
    t.head[add-1]=elem;
    t.length++;

    return t;
}

//删除
table delTable(table t, int add)
{
    int i;
    //判断删除位置是否有问题
    if(add>t.length||add<1){
        printf("被删除位置有误\n");
        return t;
    }
    //找到删除位置，逐个前移
    for(i=add;i<t.length;i++){
        t.head[i-1] = t.head[i];
    }
    t.length--;

    return t;
}

//查询
int selectTable(table t,int elem)
{
    int i;
    for(i=0;i<t.length;i++){
        if(t.head[i]==elem){
            return i+1;
        }
    }
    return -1;//查找失败返回 -1
}

//替换
table amendTable(table t, int elem, int newElem)
{
    int add = selectTable(t, elem);
    t.head[add-1] = newElem;
    return t;
}

int main()
{
    int i;
    table t = initTable();
    for(i=1;i<=Size;i++){
        // 这里的指针和数组是等价的
        t.head[i-1]=i;
        t.length++;
    }
    printf("顺序表中存储的元素分别是：\n");
    displayTable(t);
    printf("插入一个元素后为：\n");
    t = addTable(t,23,2);
    displayTable(t);
    printf("删除一个元素为：\n");
    t = delTable(t,3);
    displayTable(t);
    printf("查找 23 元素的位置：%d\n",selectTable(t, 23));
    printf("更改 4 为37后的数据: \n");
    t = amendTable(t, 4, 37);
    displayTable(t);

    // 释放内存
    free(t.head);
    // 内存释放以后，要将指针置空（NULL）
    t.head = NULL;

    return 0;
}
