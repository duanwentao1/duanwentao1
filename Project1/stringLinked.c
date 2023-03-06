//
// Created by 醉人饮梦 on 2023/2/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 链表中各节点存储数据的个数
#define LINKNUM 3

typedef struct link{
    char a[LINKNUM];
    struct link* next;
}link;

link* initLink(link* head,char* str)
{
    int length = (int)strlen(str);
    // 根据字符串的长度，计算链表使用结点的个数
    int num = length/LINKNUM;
    if(length%LINKNUM){
        num++;
    }
    head = malloc(sizeof(link));
    head->next = NULL;
    link* temp = head;
    for (int i = 0; i < num; ++i) {
        int j = 0;
        for (; j < LINKNUM; j++) {
            if(i * LINKNUM + j < length){
                temp->a[j] = str[i * LINKNUM + j];
            }else{
                temp->a[j] = '#';
            }
        }
        // 判断是否还有下一节点
        if(i * LINKNUM + j < length){
            link* newLink = malloc(sizeof(link));
            newLink->next = NULL;
            temp->next = newLink;
            temp = newLink;
        }
    }
    return head;
}

void display(link* head)
{
    link* temp = head;
    while (temp){
        for (int i = 0; i < LINKNUM; ++i) {
            printf("%c",temp->a[i]);
        }
        temp = temp->next;
    }
}

int main()
{
    link* head = NULL;
    head = initLink(head, "hello world");
    display(head);

    return 0;
}
