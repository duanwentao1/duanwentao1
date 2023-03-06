//
// Created by �������� on 2023/2/20.
//

#include <stdio.h>
#include <stdlib.h>

// �ṹ��������
typedef struct link{
    char elem; // ������
    struct link* next; //ָ����
}link;

link* initLink()
{
    link* head = NULL;//����ͷָ��
    // ������Ԫ�ڵ�
    // �Ƶ�һ���������ݵĽ��Ϊ��Ԫ��㣬ֻ��һ����ν��û��ʵ�����壬���Բ���д�������дһ�°�
    link* temp = malloc(sizeof(link));
    //��Ԫ�ڵ��ʼ��
    temp->elem = 1;
    temp->next = NULL;
    head = temp;

    //�ӵڶ����㿪ʼ����
    for(char i=2;i<5;i++){
        //����һ���½ڵ㲢��ʼ��
        link* new = malloc(sizeof(link));
        new->elem = i;
        new->next = NULL;
        //��temp�ڵ����½�����a�ڵ㽨���߼���ϵ
        temp->next = new;
        // ָ��tempÿ�ζ�ָ������������һ���ڵ�(����һ�����)��
        // ��Ȼһֱ�����ڶ�temp��һ������ָ�������
        // ��ʵ����a�ڵ㣬����д temp = new Ҳ����
        temp = temp->next;
    }

    //ֻ����ͷָ�룬ͨ��ͷָ����ҵ���������
    return head;
}

void display(link *head)
{
    //��tempָ������ָ��ͷ�ڵ�
    link *temp = head;
    //ֻҪtempָ��ָ��Ľڵ��next����NULL����ִ��
    while(temp){
        printf("%d ",temp->elem);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    link *head;
    head = initLink();
    printf("���������Ϊ��\n");
    display(head);

    return 0;
}

