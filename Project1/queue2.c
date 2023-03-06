//
// Created by 醉人饮梦 on 2023/2/26.
//

#include <stdio.h>

#define MAX 5

// 入队
int enQueue(int* a, int top, int rear, int data)
{
    // 队尾的 下一个位置 等于 队头的位置 则空间已满
    if((rear+1)%MAX == top){
        printf("空间已满 ");
        return rear;
    }
    // 到这里则证明 空间未满，到达最后一个下标后 重置 队尾的位置
    a[rear%MAX]=data;
    rear++;
    // 时刻记住队尾的位置
    return rear;
}

// 出队
int deQueue(int* a, int top, int rear)
{
    // 队头的位置 等于 队尾的位置 则 证明空间已为空，没有数据了
    if(top == rear % MAX){
        printf("队列为空 ");
        return top;
    }
    printf("%d ", a[top]);
    // 到这里 说明还有数据，若 队头 到达最后一个下标时 重置 对头的位置
    top = (top + 1) % MAX;
    // 时刻记住队头的位置
    return top;
}

int main()
{
    int a[MAX];
    int top,rear;
    // 设置队头 队尾指针，当队列中没有元素时，队头队尾指向同一个地址
    top = rear = 0;
    // 入队
    rear = enQueue(a, top, rear, 1);
    rear = enQueue(a, top, rear, 2);
    rear = enQueue(a, top, rear, 3);
    rear = enQueue(a, top, rear, 4);
    // 出队
    top = deQueue(a, top, rear); // 1
    // 入队
    rear = enQueue(a, top, rear, 5);
    // 出队
    top = deQueue(a, top, rear); // 2
    // 入队
    rear = enQueue(a, top, rear, 6);
    // 队列已满，再插入一个试试
    rear = enQueue(a, top, rear, 7);
    // 出队
    top = deQueue(a, top, rear); // 3
    top = deQueue(a, top, rear); // 4
    top = deQueue(a, top, rear); // 5
    // 最后一个元素出栈
    top = deQueue(a, top, rear); // 6
    // 没有元素了
    top = deQueue(a, top, rear);

    return 0;
}
