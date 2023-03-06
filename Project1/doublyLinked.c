//
// Created by 醉人饮梦 on 2023/2/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct link{
    struct link* prior;
    int data;
    struct link* next;
}link;

// 初始化
link* initLink(link* head)
{
    // 首元结点
    link* temp = malloc(sizeof(link));
    temp->prior = NULL;
    temp->next = NULL;
    temp->data = 1;
    // 头指针指向首元结点
    head = temp;

    for (int i = 2; i < 5; ++i) {
        // 创建新的结点
        link* new = malloc(sizeof(link));
        // prior 指向 直接前驱结点
        new->prior = temp;
        // next 置空
        new->next = NULL;
        new->data = i;
        // 直接前驱结点 指向 新结点
        temp->next = new;
        // 上一个结点指向 新结点（后移一个结点，不然一直都会指向首元结点，没意义）
        temp = temp->next;
    }
    return head;
}

// 添加元素
link* insertLink(link* head, int add, int data)
{
    link* new = malloc(sizeof(link));
    // 初始化结点（也不初始化，直接用）
    new->next = NULL;
    new->prior = NULL;
    new->data = data;
    // 判断插入情况
    if(add == 1){
        new->next = head;
        head->prior = new;
        head = new;
    }else{
        int i = 0;
        link* temp = head;
        // i=1：temp放在if语句之前；add-1：插入位置的 前一个结点 就要停下
        for (i = 1; i < add-1; ++i) {
            temp = temp->next;
            if(temp == NULL){
                printf("插入位置有误\n");
                break;
            }
        }
        // 判断插入元素是否存在
        if(temp){
            // 判断插入元素是否在 链尾
            if(temp->next == NULL){
                new->prior = temp;
                temp->next = new;
            }else{
                // 表中间的插入
                new->next = temp->next;
                temp->next->prior = new;
                temp->next = new;
                new->prior = temp;
            }
        }
    }
    return head;
}

// 删除元素
link* delLink(link* head,int data)
{
    link* temp = head;
    while(temp){
        if(temp->data == data){
            // 头部删除
            if(temp->prior == NULL){
                // 第一种
//                head = head->next;
//                head->prior->next = NULL;
//                head->prior = NULL;
//                free(temp);
//                return head;
                // 第二种方法
                link* del = temp;
                temp = temp->next;
                temp->prior = NULL;
                // 结构体的指针域置空
                del->next = NULL;
                // 释放首元结点内存
                free(del);
                // 头指针置空
                head = NULL;
                // 首元结点已经没有，返回 直接后继元素
                return temp;
            }
            // 尾部删除
            if(temp->next == NULL){
                // 先将有逻辑关系的指针 置空再释放内存，避免出现野指针
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
    printf("链表中无该元素\n");
    return head;
}

// 查找元素
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

// 更改
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
        printf("没有找到要 更改 的元素\n");
    }
}

// 打印
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
    printf("数据依次为：\n");
    display(head);
    printf("在位置 2 插入 7 ：\n");
    head = insertLink(head, 2, 7);
    display(head);
    printf("删除元素 2：\n");
    head = delLink(head, 1);
    display(head);
    printf("查找元素 3：%d\n",selectElem(head, 3));
    printf("更改 元素 7 为 9：\n");
    amendElem(head, 7, 9);
    display(head);

    return 0;
}
