//
// Created by �������� on 2023/2/23.
//

#include <stdio.h>
#include <stdlib.h>

// �ṹ��������
typedef struct link{
    char elem; // ������
    struct link* next; //ָ����
}link;

// ��ʼ��
link* initLink()
{
    link* temp = malloc(sizeof(link));//����ͷ�ڵ�
    link* head = temp; //ͷָ��ָ��ͷ���

    // �Ƶ�һ���������ݵĽ��Ϊ��Ԫ��㣬ֻ��һ����ν��û��ʵ�����壬�ҾͲ�д�ˣ���ͷ�����ƪ����д��

    for(char i=1;i<5;i++){
        //����һ���½ڵ㲢��ʼ��
        link* new = malloc(sizeof(link));
        new->elem = i;
        new->next = NULL;
        //��temp�ڵ����½�����a�ڵ㽨���߼���ϵ
        temp->next = new;
        //ָ��tempÿ�ζ�ָ������������һ���ڵ�(����һ�����)����ʵ����a�ڵ㣬����д temp = new Ҳ����
        temp = temp->next;
    }

    //ֻ����ͷָ�룬ͨ��ͷָ����ҵ���������
    return head;
}

// ���Ԫ��
link* insertElem(link* head,int add,char elem)
{
    link* temp = head;
    link* being = NULL;
    // ע���Ǵ� 1 �Ϳ�ʼ�ˣ���Ҫ�ڲ���λ�õ�ǰһ������ͣ��
    for (int i = 1; i < add; ++i) {
        if(temp==NULL){
            printf("����λ����Ч\n");
            return head;
        }
        temp = temp->next;
    }
    being = malloc(sizeof(link));
    being->elem = elem;
    // �����Ƚ��½��� ָ���� ָ�� ����λ�ú����һ�����
    being->next = temp->next;
    // Ȼ�� �������ǰһ������ ָ���� ָ�� �½��
    temp->next = being;
    return head;
}

// ɾ��ָ����Ԫ��
link* delElem(link* head,char elem)
{
    link *temp,*del;
    // ������ָ��ֱ���ǰһ���ͺ�һ����ָ��ı仯 (����ͷ���)
    for (temp=head->next,del=NULL;temp!=NULL&&temp->elem!=elem;del=temp,temp=temp->next);
    // �ж��Ƿ��ҵ�ָ����Ԫ��
    if(temp==NULL) return head;
    // �ҵ���Ԫ���Ƿ��ǵ�һ��
    if(del==NULL){
        head = head->next;
    }else{
        del->next = temp->next;
    }
    free(temp);

    return head;

//    ɾ��ָ��λ�õĽ��
//    link *temp = head, *del = NULL;
//    for (int i = 1; i < elem; ++i) {
//        if(temp==NULL){
//            printf("ɾ��λ����Ч\n");
//            return head;
//        }
//        temp = temp->next;
//    }
//    // ����ɾ�����
//    del = temp->next;
//    // ָ����һ��������һ�����
//    temp->next = temp->next->next;
//    // �ͷŽ���ڴ�
//    free(del);
//    return head;
}

// ����Ԫ��
int selectElem(link* head,char elem)
{
    link* temp = head;
    int i = 1;
    while(temp){
        // �� if ǰ���ԭ������ͷ���
        temp = temp->next;
        if(temp->elem == elem) return i;
        i++;
    }
    // û���ҵ�Ԫ��
    return -1;
}

// ����Ԫ��
void amendElem(link* head, char oldElem, char newElem)
{
    link* temp = head;
    // ����ͷ���
    temp = temp->next;
    while(temp){
        if(temp->elem == oldElem){
            temp->elem = newElem;
            break;
        }
        temp = temp->next;
    }
}

// ��ӡ
void display(link* head)
{
    link* temp = head;
    // �ж� temp �Ƿ�����һ����㣬���һ������ָ����Ϊ NULL
    while(temp->next){
        // ��Ҫ�������� ͷ���
        temp = temp->next;
        printf("%d ",temp->elem);
    }
    printf("\n");
}

int main()
{
    link* head = NULL;
    head = initLink();
    printf("������������Ϊ��\n");
    display(head);
    printf("��λ�� 2 ����Ԫ�� 10��\n");
    insertElem(head, 2, 10);
    display(head);
    printf("ɾ��Ԫ�� 2\n");
    delElem(head, 2);
    display(head);
    printf("Ԫ�� 3 ��λ�ã�%d\n", selectElem(head, 3));
    printf("��Ԫ�� 10 ������ 8 \n");
    amendElem(head, 10, 8);
    display(head);

    return 0;
}
