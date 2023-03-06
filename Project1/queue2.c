//
// Created by �������� on 2023/2/26.
//

#include <stdio.h>

#define MAX 5

// ���
int enQueue(int* a, int top, int rear, int data)
{
    // ��β�� ��һ��λ�� ���� ��ͷ��λ�� ��ռ�����
    if((rear+1)%MAX == top){
        printf("�ռ����� ");
        return rear;
    }
    // ��������֤�� �ռ�δ�����������һ���±�� ���� ��β��λ��
    a[rear%MAX]=data;
    rear++;
    // ʱ�̼�ס��β��λ��
    return rear;
}

// ����
int deQueue(int* a, int top, int rear)
{
    // ��ͷ��λ�� ���� ��β��λ�� �� ֤���ռ���Ϊ�գ�û��������
    if(top == rear % MAX){
        printf("����Ϊ�� ");
        return top;
    }
    printf("%d ", a[top]);
    // ������ ˵���������ݣ��� ��ͷ �������һ���±�ʱ ���� ��ͷ��λ��
    top = (top + 1) % MAX;
    // ʱ�̼�ס��ͷ��λ��
    return top;
}

int main()
{
    int a[MAX];
    int top,rear;
    // ���ö�ͷ ��βָ�룬��������û��Ԫ��ʱ����ͷ��βָ��ͬһ����ַ
    top = rear = 0;
    // ���
    rear = enQueue(a, top, rear, 1);
    rear = enQueue(a, top, rear, 2);
    rear = enQueue(a, top, rear, 3);
    rear = enQueue(a, top, rear, 4);
    // ����
    top = deQueue(a, top, rear); // 1
    // ���
    rear = enQueue(a, top, rear, 5);
    // ����
    top = deQueue(a, top, rear); // 2
    // ���
    rear = enQueue(a, top, rear, 6);
    // �����������ٲ���һ������
    rear = enQueue(a, top, rear, 7);
    // ����
    top = deQueue(a, top, rear); // 3
    top = deQueue(a, top, rear); // 4
    top = deQueue(a, top, rear); // 5
    // ���һ��Ԫ�س�ջ
    top = deQueue(a, top, rear); // 6
    // û��Ԫ����
    top = deQueue(a, top, rear);

    return 0;
}
