//
// Created by 醉人饮梦 on 2023/2/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct QNode{
    int data;
    struct QNode* next;
}QNode;

// 创建
QNode *initQueue()
{
    // 头结点
    QNode *queue = malloc(sizeof(QNode));
    queue->next = NULL;
    return queue;
}

// 入队
QNode *enQueue(QNode* rear,int data)
{
    QNode *enElem = malloc(sizeof(QNode));
    enElem->data = data;
    enElem->next = NULL;
    // 尾指针 的指针域 指向 新结点
    rear->next = enElem;
    // 尾指针 指向 新结点；
    rear = enElem;
    // 返回新的 尾指针
    return rear;
}

// 出队（二级指针，在函数中更改指针的指向不能直接更改，要使用指向指针的指针）
void deQueue(QNode* top,QNode** rear)
{
    QNode *p = NULL;
    // 通过判断头结点 的 指针域 是否为空 来判读队列是否为空
    if(top->next == NULL){
        printf("队列为空 ");
        return;
    }
    p = top->next;
    printf("%d ",p->data);
    // 删除结点
    top->next = p->next;
    // 判断删除的 是否 是最后一个结点，如果是的话，rear指向头结点，避免 rear 成为野指针
    if(*rear == p){
        *rear = top;
    }
    free(p);
}

int main()
{
    QNode *top = NULL, *rear = NULL;
    // 队头指针 和 队尾指针 指向头结点
    top  = rear = initQueue();
    // 入栈
    rear = enQueue(rear,1);
    rear = enQueue(rear,2);

    // 出栈
    deQueue(top, &rear); // 1
    deQueue(top, &rear); // 2
    // 没有元素，看会显示什么
    deQueue(top, &rear);

    // 入栈
    rear = enQueue(rear,4);
    rear = enQueue(rear,5);
    rear = enQueue(rear,6);
    // 出栈
    deQueue(top, &rear); // 4
    deQueue(top, &rear); // 5

    return 0;
}
