//
// Created by 醉人饮梦 on 2023/2/25.
//

#include <stdio.h>

int enQueue(int* a,int rear,int data)
{
    a[rear] = data;
    rear++;
    return rear;
}
void deQueue(int* a,int top,int rear)
{
    // top==rear，表示队列为空
    while (top!=rear){
        printf("队列元素：%d\n",a[top]);
        top++;
    }
}

int main()
{
    int a[100];
    int top,rear;
    //设置对头指针和队尾指针，当队列中没有元素，对头队尾指向同一块地址
    top = rear = 0;
    // 入队
    rear = enQueue(a,rear,1);
    rear = enQueue(a,rear,2);
    rear = enQueue(a,rear,3);
    rear = enQueue(a,rear,4);
    // 出队
    deQueue(a,top,rear);

    return 0;
}
