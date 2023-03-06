//
// Created by 醉人饮梦 on 2023/2/23.
//

#include <stdio.h>
#include <stdlib.h>

// 结构体重命名
typedef struct link{
    char elem; // 数据域
    struct link* next; //指针域
}link;

// 初始化
link* initLink()
{
    link* temp = malloc(sizeof(link));//创建头节点
    link* head = temp; //头指针指针头结点

    // 称第一个存有数据的结点为首元结点，只是一个称谓，没有实际意义，我就不写了，无头结点那篇代码写了

    for(char i=1;i<5;i++){
        //创建一个新节点并初始化
        link* new = malloc(sizeof(link));
        new->elem = i;
        new->next = NULL;
        //将temp节点与新建立的a节点建立逻辑关系
        temp->next = new;
        //指针temp每次都指向新链表的最后一个节点(后移一个结点)，其实就是a节点，这里写 temp = new 也可以
        temp = temp->next;
    }

    //只返回头指针，通过头指针可找到整个链表
    return head;
}

// 添加元素
link* insertElem(link* head,int add,char elem)
{
    link* temp = head;
    link* being = NULL;
    // 注意是从 1 就开始了，需要在插入位置的前一个结点就停下
    for (int i = 1; i < add; ++i) {
        if(temp==NULL){
            printf("插入位置无效\n");
            return head;
        }
        temp = temp->next;
    }
    being = malloc(sizeof(link));
    being->elem = elem;
    // 必须先将新结点的 指针域 指向 插入位置后的下一个结点
    being->next = temp->next;
    // 然后将 插入结点的前一个结点的 指针域 指向 新结点
    temp->next = being;
    return head;
}

// 删除指定的元素
link* delElem(link* head,char elem)
{
    link *temp,*del;
    // 用两个指针分别检测前一个和后一个的指针的变化 (跳过头结点)
    for (temp=head->next,del=NULL;temp!=NULL&&temp->elem!=elem;del=temp,temp=temp->next);
    // 判断是否找到指定的元素
    if(temp==NULL) return head;
    // 找到的元素是否是第一个
    if(del==NULL){
        head = head->next;
    }else{
        del->next = temp->next;
    }
    free(temp);

    return head;

//    删除指定位置的结点
//    link *temp = head, *del = NULL;
//    for (int i = 1; i < elem; ++i) {
//        if(temp==NULL){
//            printf("删除位置无效\n");
//            return head;
//        }
//        temp = temp->next;
//    }
//    // 保留删除结点
//    del = temp->next;
//    // 指向下一个结点的下一个结点
//    temp->next = temp->next->next;
//    // 释放结点内存
//    free(del);
//    return head;
}

// 查找元素
int selectElem(link* head,char elem)
{
    link* temp = head;
    int i = 1;
    while(temp){
        // 在 if 前面的原因：跳过头结点
        temp = temp->next;
        if(temp->elem == elem) return i;
        i++;
    }
    // 没有找到元素
    return -1;
}

// 更换元素
void amendElem(link* head, char oldElem, char newElem)
{
    link* temp = head;
    // 跳过头结点
    temp = temp->next;
    while(temp){
        if(temp->elem == oldElem){
            temp->elem = newElem;
            break;
        }
        temp = temp->next;
    }
}

// 打印
void display(link* head)
{
    link* temp = head;
    // 判断 temp 是否还有下一个结点，最后一个结点的指针域为 NULL
    while(temp->next){
        // 不要忘记跳过 头结点
        temp = temp->next;
        printf("%d ",temp->elem);
    }
    printf("\n");
}

int main()
{
    link* head = NULL;
    head = initLink();
    printf("链表数据依次为：\n");
    display(head);
    printf("在位置 2 插入元素 10：\n");
    insertElem(head, 2, 10);
    display(head);
    printf("删除元素 2\n");
    delElem(head, 2);
    display(head);
    printf("元素 3 的位置：%d\n", selectElem(head, 3));
    printf("将元素 10 更换成 8 \n");
    amendElem(head, 10, 8);
    display(head);

    return 0;
}
