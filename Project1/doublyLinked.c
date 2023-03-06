//
// Created by �������� on 2023/2/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct link{
    struct link* prior;
    int data;
    struct link* next;
}link;

// ��ʼ��
link* initLink(link* head)
{
    // ��Ԫ���
    link* temp = malloc(sizeof(link));
    temp->prior = NULL;
    temp->next = NULL;
    temp->data = 1;
    // ͷָ��ָ����Ԫ���
    head = temp;

    for (int i = 2; i < 5; ++i) {
        // �����µĽ��
        link* new = malloc(sizeof(link));
        // prior ָ�� ֱ��ǰ�����
        new->prior = temp;
        // next �ÿ�
        new->next = NULL;
        new->data = i;
        // ֱ��ǰ����� ָ�� �½��
        temp->next = new;
        // ��һ�����ָ�� �½�㣨����һ����㣬��Ȼһֱ����ָ����Ԫ��㣬û���壩
        temp = temp->next;
    }
    return head;
}

// ���Ԫ��
link* insertLink(link* head, int add, int data)
{
    link* new = malloc(sizeof(link));
    // ��ʼ����㣨Ҳ����ʼ����ֱ���ã�
    new->next = NULL;
    new->prior = NULL;
    new->data = data;
    // �жϲ������
    if(add == 1){
        new->next = head;
        head->prior = new;
        head = new;
    }else{
        int i = 0;
        link* temp = head;
        // i=1��temp����if���֮ǰ��add-1������λ�õ� ǰһ����� ��Ҫͣ��
        for (i = 1; i < add-1; ++i) {
            temp = temp->next;
            if(temp == NULL){
                printf("����λ������\n");
                break;
            }
        }
        // �жϲ���Ԫ���Ƿ����
        if(temp){
            // �жϲ���Ԫ���Ƿ��� ��β
            if(temp->next == NULL){
                new->prior = temp;
                temp->next = new;
            }else{
                // ���м�Ĳ���
                new->next = temp->next;
                temp->next->prior = new;
                temp->next = new;
                new->prior = temp;
            }
        }
    }
    return head;
}

// ɾ��Ԫ��
link* delLink(link* head,int data)
{
    link* temp = head;
    while(temp){
        if(temp->data == data){
            // ͷ��ɾ��
            if(temp->prior == NULL){
                // ��һ��
//                head = head->next;
//                head->prior->next = NULL;
//                head->prior = NULL;
//                free(temp);
//                return head;
                // �ڶ��ַ���
                link* del = temp;
                temp = temp->next;
                temp->prior = NULL;
                // �ṹ���ָ�����ÿ�
                del->next = NULL;
                // �ͷ���Ԫ����ڴ�
                free(del);
                // ͷָ���ÿ�
                head = NULL;
                // ��Ԫ����Ѿ�û�У����� ֱ�Ӻ��Ԫ��
                return temp;
            }
            // β��ɾ��
            if(temp->next == NULL){
                // �Ƚ����߼���ϵ��ָ�� �ÿ����ͷ��ڴ棬�������Ұָ��
                temp->prior->next = NULL;
                temp->prior = NULL;
                free(temp);
                return head;
            }
            temp->prior->next = temp->next;
            temp->next->prior = temp->prior;
            free(temp);
            return head;
        }
        temp = temp->next;
    }
    printf("�������޸�Ԫ��\n");
    return head;
}

// ����Ԫ��
int selectElem(link* head,int elem)
{
    link* temp = head;
    int i = 1;
    while (temp){
        if(temp->data == elem){
            return i;
        }
        i++;
        temp = temp->next;
    }
    return -1;
}

// ����
void amendElem(link* head,int oldElem,int newElem)
{
    while (head){
        if(head->data==oldElem){
            head->data = newElem;
            return;
        }
        head = head->next;
    }
    if(head == NULL){
        printf("û���ҵ�Ҫ ���� ��Ԫ��\n");
    }
}

// ��ӡ
void display(link* head)
{
    while(head){
        printf("%d ",head->data);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    link* head = NULL;
    head = initLink(head);
    printf("��������Ϊ��\n");
    display(head);
    printf("��λ�� 2 ���� 7 ��\n");
    head = insertLink(head, 2, 7);
    display(head);
    printf("ɾ��Ԫ�� 2��\n");
    head = delLink(head, 1);
    display(head);
    printf("����Ԫ�� 3��%d\n",selectElem(head, 3));
    printf("���� Ԫ�� 7 Ϊ 9��\n");
    amendElem(head, 7, 9);
    display(head);

    return 0;
}
