//
// Created by 醉人饮梦 on 2023/2/20.
//

#include <stdio.h>
#include <stdlib.h>

// 结构体重命名
typedef struct link{
    char elem; // 数据域
    struct link* next; //指针域
}link;

link* initLink()
{
    link* head = NULL;//创建头指针
    // 创建首元节点
    // 称第一个存有数据的结点为首元结点，只是一个称谓，没有实际意义，可以不用写，这里就写一下吧
    link* temp = malloc(sizeof(link));
    //首元节点初始化
    temp->elem = 1;
    temp->next = NULL;
    head = temp;

    //从第二个点开始创建
    for(char i=2;i<5;i++){
        //创建一个新节点并初始化
        link* new = malloc(sizeof(link));
        new->elem = i;
        new->next = NULL;
        //将temp节点与新建立的a节点建立逻辑关系
        temp->next = new;
        // 指针temp每次都指向新链表的最后一个节点(后移一个结点)，
        // 不然一直都是在对temp这一个结点的指针域操作
        // 其实就是a节点，这里写 temp = new 也可以
        temp = temp->next;
    }

    //只返回头指针，通过头指针可找到整个链表
    return head;
}

void display(link *head)
{
    //将temp指针重新指向头节点
    link *temp = head;
    //只要temp指针指向的节点的next不是NULL，就执行
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
    printf("链表的数据为：\n");
    display(head);

    return 0;
}

