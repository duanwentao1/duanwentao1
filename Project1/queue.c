//
// Created by �������� on 2023/2/25.
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
    // top==rear����ʾ����Ϊ��
    while (top!=rear){
        printf("����Ԫ�أ�%d\n",a[top]);
        top++;
    }
}

int main()
{
    int a[100];
    int top,rear;
    //���ö�ͷָ��Ͷ�βָ�룬��������û��Ԫ�أ���ͷ��βָ��ͬһ���ַ
    top = rear = 0;
    // ���
    rear = enQueue(a,rear,1);
    rear = enQueue(a,rear,2);
    rear = enQueue(a,rear,3);
    rear = enQueue(a,rear,4);
    // ����
    deQueue(a,top,rear);

    return 0;
}
