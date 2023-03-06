@[TOC](文章目录)

---
# 一、链表
存储逻辑关系**一对一**的数据，使用链表存储的数据，其物理存储位置是**随机**的；
链表每个数据最少由两部分组成：
数据元素本身，其所在的区域称为**数据域**；
指向直接后继元素的指针，其所在的区域称为**指针域**；

代码实现：
```c
typedef struct link{
    char elem; // 数据域
    struct link* next; //指针域
}link;
```

专业术语：
头指针：一个普通的指针，特点是永远指向链表第一个结点的位置
结点：
	头结点：不存在任何数据的空结点，通常作为链表的第一个结点，对于链表不是必需的；
	首元结点：由于头结点（也就是空结点），链表中称第一个存有数据的结点为首元结点，只是一个称谓，没有实际意义；
	其他结点：剩余的结点；
![](https://img-blog.csdnimg.cn/ef8422dd050e468db8d523c51d4407b4.png#pic_center)注意：链表中有头结点时，头指针指向头结点；若没有，则头指针指向首元结点


# 二、链表的创建
## 1、初始化（无头结点）
（1）声明一个头指针（如需要，可以声明一个头结点）；
（2）创建多个存储数据的结点，注意随时与前驱元素建立逻辑关系；
```c
link* initLink()
{
    link* p = NULL;//创建头指针
    link* temp = malloc(sizeof(link));//创建首元节点
    //首元节点初始化
    temp->elem = 1;
    temp->next = NULL;
    p = temp;

    //从第二个点开始创建
    for(int i=2;i<5;i++){
        //创建一个新节点并初始化
        link* a = malloc(sizeof(link));
        a->elem = i;
        a->next = NULL;
        //将temp节点与新建立的a节点建立逻辑关系
        temp->next = a;
        //指针temp每次都指向新链表的最后一个节点(后移一个结点)，其实就是a节点，这里写 temp = a 也可以
        temp = temp->next;
    }

    //只返回头指针，通过头指针可找到整个链表
    return p;
}
```
---
## 2、打印结果
```c
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
```
## 3、初始化（有头结点）
图解：首元结点在上一个图中设置了，但上一个图又没有头结点（懒写，哈哈）
![](https://img-blog.csdnimg.cn/a167234281b0469a882a0267952cfc5a.png#pic_center)
```c
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
```
---
## 4、添加元素
可能出现三种情况：
（1）插入链表头部（头结点之后），作为首元结点；
（2）插入链表中间某个位置；
（3）插入链表的最末端，作为链表的最后一个数据；

方法：
（1）将新结点的next指针指向插入位置后的结点；
（2）将插入位置前结点的next指针指向插入结点；
必须先步骤1，在步骤2；不然会导致后续链表丢失；
![](https://img-blog.csdnimg.cn/f12f59b89baf412da9538d631bf79b04.png)
```c
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
```
---
## 5、删除元素
步骤：（删除指定位置的元素）
（1）将节点从链表中摘下来
（2）手动释放掉结点，回收被结点占用的存储空间
找到删除结点的前驱结点跳过就行了（很简单），不要忘记释放存储空间

删除指定位置的元素
![](https://img-blog.csdnimg.cn/45cc203e682d4eb18af62af03ce79a86.png#pic_center)
```c
link* delElem(link* head,char elem)
{
//    删除指定位置的结点
    link *temp = head, *del = NULL;
    for (int i = 1; i < elem; ++i) {
        if(temp==NULL){
            printf("删除位置无效\n");
            return head;
        }
        temp = temp->next;
    }
    // 保留删除结点
    del = temp->next;
    // 指向下一个结点的下一个结点
    temp->next = temp->next->next;
    // 释放结点内存
    free(del);
    return head;
}
```
删除指定的元素
第一轮：
![](https://img-blog.csdnimg.cn/9016154972e647c086aba6e5d2d0233a.png#pic_center)第二轮：
![](https://img-blog.csdnimg.cn/5a7ea4250a0246de9f64d6f95dd5b661.png#pic_center)第三轮：
![](https://img-blog.csdnimg.cn/0191ea8d450f461fac02c47938d98d2d.png#pic_center)满足条件，退出循环
释放存储空间这里可以好好看一下，可能有点绕（注意）
```c
link* delElem(link* head,char elem)
{
    link *temp,*del;
    // 用两个指针分别检测前一个和后一个的指针的变化
    for (temp=head,del=NULL;temp!=NULL&&temp->elem!=elem;del=temp,temp=temp->next);
    // 判断是否找到指定的元素
    if(temp==NULL){
        return head;
    }
    // 找到的元素是否是第一个
    if(del==NULL){
        head = head->next;
    }else{
        del->next = temp->next;
    }
    free(temp);

    return head;
}
```
---
## 6、查找元素
```c
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
```
---
## 7、更新元素
```c
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
```
---
## 8、打印结果
```c
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
```
---
## 9、全部代码
```c
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
```
---

# 结语
个人记录学习所用，如用错误之处还请指出，谢谢
