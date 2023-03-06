//
// Created by �������� on 2023/2/18.
//

#include <stdio.h>
#include <stdlib.h>
#define Size 5

// �Խṹ��������
typedef struct Table{
    int* head; //����һ����̬���� head
    int length; //��¼��ǰ˳���ĳ���
    int size; //��¼˳������Ĵ洢����
}table;

// ��ʼ���ṹ��
table initTable(){
    table t;
    // ����һ���µĴ洢�ռ䲢����ַ���أ�malloc����һ��ͨ��ָ��(void *)��û��Ҫǿת
    t.head = malloc(Size*sizeof(int));
    // �������ʧ�ܻ᷵��һ����ָ��
    if(!t.head){
        printf("��ʼ��ʧ��");
        exit(0);
    }
    t.length = 0; // �ձ�ĳ��ȳ�ʼ��Ϊ0
    t.size = Size; // �ձ��ܴ洢���ٸ�����
    return t;
}

// ��ӡ�ṹ��
void displayTable(table t){
    int i;
    for(i=0;i<t.length;i++){
        printf("%d ",t.head[i]);
    }
    printf("\n");
}

//���
table addTable(table t, int elem, int add)
{
    int i;
    //�жϲ���λ���Ƿ�������
    if(add>t.length+1||add<1){
        printf("����λ��������");
        return t;
    }
    if(t.length==t.size){
        //���·����ڴ�һ���ڴ�
        t.head = realloc(t.head,(t.size+1)*sizeof(int));
        if(!t.head){
            printf("�ڴ����ʧ��");
            return t;
        }
        t.size+=1;
    }
    //���Ӳ���λ�ÿ�ʼ��Ԫ�����������
    for(i=t.length-1;i>=add-1;i--){
        t.head[i+1] = t.head[i];
    }
    //��Ԫ�ط������λ��
    t.head[add-1]=elem;
    t.length++;

    return t;
}

//ɾ��
table delTable(table t, int add)
{
    int i;
    //�ж�ɾ��λ���Ƿ�������
    if(add>t.length||add<1){
        printf("��ɾ��λ������\n");
        return t;
    }
    //�ҵ�ɾ��λ�ã����ǰ��
    for(i=add;i<t.length;i++){
        t.head[i-1] = t.head[i];
    }
    t.length--;

    return t;
}

//��ѯ
int selectTable(table t,int elem)
{
    int i;
    for(i=0;i<t.length;i++){
        if(t.head[i]==elem){
            return i+1;
        }
    }
    return -1;//����ʧ�ܷ��� -1
}

//�滻
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
        // �����ָ��������ǵȼ۵�
        t.head[i-1]=i;
        t.length++;
    }
    printf("˳����д洢��Ԫ�طֱ��ǣ�\n");
    displayTable(t);
    printf("����һ��Ԫ�غ�Ϊ��\n");
    t = addTable(t,23,2);
    displayTable(t);
    printf("ɾ��һ��Ԫ��Ϊ��\n");
    t = delTable(t,3);
    displayTable(t);
    printf("���� 23 Ԫ�ص�λ�ã�%d\n",selectTable(t, 23));
    printf("���� 4 Ϊ37�������: \n");
    t = amendTable(t, 4, 37);
    displayTable(t);

    // �ͷ��ڴ�
    free(t.head);
    // �ڴ��ͷ��Ժ�Ҫ��ָ���ÿգ�NULL��
    t.head = NULL;

    return 0;
}
