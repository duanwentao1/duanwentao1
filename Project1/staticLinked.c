//
// Created by �������� on 2023/2/19.
//

#include <stdio.h>

// ���徲̬����Ĵ�С
#define maxSize 6

// �ṹ��������
typedef struct{
    int data; // ����
    int cur; // �α�
}component;

//������������
void reserveArr(component *array)
{
    for(int i=0;i<maxSize;i++){
        array[i].cur = i+1;//��ÿ������������ӵ�һ��
        array[i].data = 0;
    }
    array[maxSize-1].cur = 0;//�������һ�������α�ֵΪ 0
}

//��ȡ����ռ�
int mallocArr(component *array)
{
    //����������ǿգ��򷵻ط���Ľ���±꣬���򷵻� 0(���������һ�����ʱ���ý����α�ֵΪ 0)
    int i = array[0].cur;
    if(array[0].cur){
        array[0].cur = array[i].cur;//�������ص㣬��һ���α�ģ����ݣ�һֱ�ڱ䣬���·���ֵ i Ҳһֱ�ڱ�
    }
    return i;
}

//��ʼ����̬����
int initArr(component *array)
{
    int tempBody = 0, body = 0;
    reserveArr(array);//������ӵ�� 6 ���սṹ�����飬�α�Ϊ1,2,3,4,5,0
    body = mallocArr(array);//����һ���α꣬�õ�ֱ�Ӻ��Ԫ�ص�λ��
    //������Ԫ���
    array[body].data = 1;
    array[body].cur = 0;
    //����һ��������������ָ��ʹ��ָ����������һ����㣬��ǰ����Ԫ����غ�
    tempBody = body;
    for(int i=2;i<4;i++){
        int j = mallocArr(array);//�ӱ��������з�����һ��ֱ�Ӻ��Ԫ�ص�λ��
        array[j].data = i;//��ʼ���µõ��Ŀռ���
        array[tempBody].cur = j;//���µõ��Ľ�����ӵ����������β��
        tempBody = i;//��ָ���������һ������ָ�����
    }
    array[tempBody].cur = 0;//�µ��������һ�������α�����Ϊ 0
    return body;
}

void displayArr(component *array,int body)
{
    int tempBody = body;//tempBody׼��������ʹ��
    while(array[tempBody].cur){
        printf("%d,%d\n",array[tempBody].data,array[tempBody].cur);
        tempBody = array[tempBody].cur;
    }
    printf("%d,%d\n",array[tempBody].data,array[tempBody].cur);
}

//body��ʾ�����ͷ����������е�λ�ã�add��ʾ����Ԫ�ص�λ�ã�num��ʾҪ���������
void insertArr(component *array,int body,int add,int num)
{
    int tempBody = body;//��¼ֱ�Ӻ�̵��α�
    int endBody = 0;//��¼ֱ��ǰ�����α�
    //�ҵ�Ҫ����λ�õ���һ������������е�λ��
    for(int i=1;i<add;i++){
        // ��tempBodyֵ�ı�֮ǰ����ס����ֵ
        endBody = tempBody;
        tempBody = array[tempBody].cur;
    }
    int insert = mallocArr(array);//����ռ䣬׼������
    array[insert].data = num;
    // ��ӽ����α� �ĳ� ֱ��ǰ�����α�
    array[insert].cur = tempBody;
    // ֱ��ǰ�����α� ָ�� ��ӽ���λ��
    array[endBody].cur = insert;
}

//����������տռ�ĺ���������arrayΪ�洢���ݵ����飬k��ʾδʹ�ýڵ�����������±�
void freeArr(component* array, int k) {
    array[k].cur = array[0].cur;
    array[0].cur = k;
}

//ɾ����㺯����num��ʾɾ��������������ŵ����ݣ�������������������ı�ͷλ��
int deleteArr(component *array,int body,int num)
{
    int tempBody = body;
    // ɾ������λ��
    int del = 0;
    // �µ����������ͷλ��
    int newBody = 0;
    //�ҵ���ɾ������λ��
    while(array[tempBody].data != num){
        tempBody = array[tempBody].cur;
        //��tempBodyΪ0ʱ����ʾ�������������˵��������û�д洢�����ݵĽ��
        if(tempBody==0){
            printf("������û�д�����");
            return -1;
        }
    }
    //���е��⣬˵���ý�����
    del = tempBody;
    tempBody = body;
    //ɾ����Ԫ��㣬��Ҫ���⿼��
    if(del==body){
        newBody = array[del].cur;
        freeArr(array,del);
        return newBody;
    } else {
        //�ҵ��ý�����һ�����ͣ���ɾ������
        while(array[tempBody].cur != del){
            tempBody = array[tempBody].cur;
        }
        //����ɾ�������α�ֱ�Ӹ���ɾ��������һ�����
        array[tempBody].cur = array[del].cur;
        //���ձ�ժ�����Ŀռ�
        freeArr(array,del);
        return body;
    }
}

//����body��Ϊͷ���������в���������Ϊelem�Ľ���������е�λ��
int selectNum(component* array, int body, int num) {
    //���α�ֵΪ0ʱ����ʾ�������
    while (array[body].cur != 0) {
        if (array[body].data == num) {
            return body;
        }
        body = array[body].cur;
    }
    //�ж����һ������Ƿ����Ҫ��
    if (array[body].data == num) {
        return body;
    }
    return -1;//����-1����ʾ��������û���ҵ���Ԫ��
}

//����body��Ϊͷ���������н�������ΪoldElem�Ľ�㣬�������ΪnewElem
void amendElem(component* array, int body, int oldElem, int newElem) {
    int add = selectNum(array, body, oldElem);
    if (add == -1) {
        printf("�޸���Ԫ��\n");
        return;
    }
    array[add].data = newElem;
}


int main()
{
    component array[maxSize];
    int body = initArr(array); //��ʼ��̬����
    printf("��̬����Ϊ��\n");
    displayArr(array,body);
    printf("��λ��3����4��\n");
    insertArr(array,body,3,4);
    displayArr(array,body);
    printf("ɾ��Ԫ��2��\n");
    body = deleteArr(array,body,2);
    displayArr(array,body);
    printf("����Ԫ��4��λ�ã�%d\n",selectNum(array, body, 4));
    printf("����Ԫ��1Ϊ8��\n");
    amendElem(array,body,1,8);
    displayArr(array,body);

    return 0;
}
