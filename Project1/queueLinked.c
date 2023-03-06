//
// Created by �������� on 2023/2/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct QNode{
    int data;
    struct QNode* next;
}QNode;

// ����
QNode *initQueue()
{
    // ͷ���
    QNode *queue = malloc(sizeof(QNode));
    queue->next = NULL;
    return queue;
}

// ���
QNode *enQueue(QNode* rear,int data)
{
    QNode *enElem = malloc(sizeof(QNode));
    enElem->data = data;
    enElem->next = NULL;
    // βָ�� ��ָ���� ָ�� �½��
    rear->next = enElem;
    // βָ�� ָ�� �½�㣻
    rear = enElem;
    // �����µ� βָ��
    return rear;
}

// ���ӣ�����ָ�룬�ں����и���ָ���ָ����ֱ�Ӹ��ģ�Ҫʹ��ָ��ָ���ָ�룩
void deQueue(QNode* top,QNode** rear)
{
    QNode *p = NULL;
    // ͨ���ж�ͷ��� �� ָ���� �Ƿ�Ϊ�� ���ж������Ƿ�Ϊ��
    if(top->next == NULL){
        printf("����Ϊ�� ");
        return;
    }
    p = top->next;
    printf("%d ",p->data);
    // ɾ�����
    top->next = p->next;
    // �ж�ɾ���� �Ƿ� �����һ����㣬����ǵĻ���rearָ��ͷ��㣬���� rear ��ΪҰָ��
    if(*rear == p){
        *rear = top;
    }
    free(p);
}

int main()
{
    QNode *top = NULL, *rear = NULL;
    // ��ͷָ�� �� ��βָ�� ָ��ͷ���
    top  = rear = initQueue();
    // ��ջ
    rear = enQueue(rear,1);
    rear = enQueue(rear,2);

    // ��ջ
    deQueue(top, &rear); // 1
    deQueue(top, &rear); // 2
    // û��Ԫ�أ�������ʾʲô
    deQueue(top, &rear);

    // ��ջ
    rear = enQueue(rear,4);
    rear = enQueue(rear,5);
    rear = enQueue(rear,6);
    // ��ջ
    deQueue(top, &rear); // 4
    deQueue(top, &rear); // 5

    return 0;
}
