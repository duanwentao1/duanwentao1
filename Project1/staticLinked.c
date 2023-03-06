//
// Created by 醉人饮梦 on 2023/2/19.
//

#include <stdio.h>

// 定义静态链表的大小
#define maxSize 6

// 结构体重命名
typedef struct{
    int data; // 数据
    int cur; // 游标
}component;

//创建备用链表
void reserveArr(component *array)
{
    for(int i=0;i<maxSize;i++){
        array[i].cur = i+1;//将每个数组分量链接到一起
        array[i].data = 0;
    }
    array[maxSize-1].cur = 0;//链表最后一个结点的游标值为 0
}

//提取分配空间
int mallocArr(component *array)
{
    //若备用链表非空，则返回分配的结点下标，否则返回 0(当分配最后一个结点时，该结点的游标值为 0)
    int i = array[0].cur;
    if(array[0].cur){
        array[0].cur = array[i].cur;//这里是重点，第一个游标的（数据）一直在变，导致返回值 i 也一直在变
    }
    return i;
}

//初始化静态链表
int initArr(component *array)
{
    int tempBody = 0, body = 0;
    reserveArr(array);//创建了拥有 6 个空结构的数组，游标为1,2,3,4,5,0
    body = mallocArr(array);//返回一个游标，得到直接后继元素的位置
    //建立首元结点
    array[body].data = 1;
    array[body].cur = 0;
    //声明一个变量，把它当指针使，指向链表的最后一个结点，当前和首元结点重合
    tempBody = body;
    for(int i=2;i<4;i++){
        int j = mallocArr(array);//从备用链表中返回下一个直接后继元素的位置
        array[j].data = i;//初始化新得到的空间结点
        array[tempBody].cur = j;//将新得到的结点链接到数据链表的尾部
        tempBody = i;//将指向链表最后一个结点的指针后移
    }
    array[tempBody].cur = 0;//新的链表最后一个结点的游标设置为 0
    return body;
}

void displayArr(component *array,int body)
{
    int tempBody = body;//tempBody准备做遍历使用
    while(array[tempBody].cur){
        printf("%d,%d\n",array[tempBody].data,array[tempBody].cur);
        tempBody = array[tempBody].cur;
    }
    printf("%d,%d\n",array[tempBody].data,array[tempBody].cur);
}

//body表示链表的头结点在数组中的位置，add表示插入元素的位置，num表示要插入的数据
void insertArr(component *array,int body,int add,int num)
{
    int tempBody = body;//记录直接后继的游标
    int endBody = 0;//记录直接前驱的游标
    //找到要插入位置的上一个结点在数组中的位置
    for(int i=1;i<add;i++){
        // 在tempBody值改变之前保存住它的值
        endBody = tempBody;
        tempBody = array[tempBody].cur;
    }
    int insert = mallocArr(array);//申请空间，准备插入
    array[insert].data = num;
    // 添加结点的游标 改成 直接前驱的游标
    array[insert].cur = tempBody;
    // 直接前驱的游标 指向 添加结点的位置
    array[endBody].cur = insert;
}

//备用链表回收空间的函数，其中array为存储数据的数组，k表示未使用节点所在数组的下标
void freeArr(component* array, int k) {
    array[k].cur = array[0].cur;
    array[0].cur = k;
}

//删除结点函数，num表示删除结点中数据域存放的数据，函数返回新数据链表的表头位置
int deleteArr(component *array,int body,int num)
{
    int tempBody = body;
    // 删除结点的位置
    int del = 0;
    // 新的数据链表表头位置
    int newBody = 0;
    //找到被删除结点的位置
    while(array[tempBody].data != num){
        tempBody = array[tempBody].cur;
        //当tempBody为0时，表示链表遍历结束，说明链表中没有存储该数据的结点
        if(tempBody==0){
            printf("链表中没有此数据");
            return -1;
        }
    }
    //运行到这，说明该结点存在
    del = tempBody;
    tempBody = body;
    //删除首元结点，需要特殊考虑
    if(del==body){
        newBody = array[del].cur;
        freeArr(array,del);
        return newBody;
    } else {
        //找到该结点的上一个结点就，做删除操作
        while(array[tempBody].cur != del){
            tempBody = array[tempBody].cur;
        }
        //将被删除结点的游标直接给被删除结点的上一个结点
        array[tempBody].cur = array[del].cur;
        //回收被摘除结点的空间
        freeArr(array,del);
        return body;
    }
}

//在以body作为头结点的链表中查找数据域为elem的结点在数组中的位置
int selectNum(component* array, int body, int num) {
    //当游标值为0时，表示链表结束
    while (array[body].cur != 0) {
        if (array[body].data == num) {
            return body;
        }
        body = array[body].cur;
    }
    //判断最后一个结点是否符合要求
    if (array[body].data == num) {
        return body;
    }
    return -1;//返回-1，表示在链表中没有找到该元素
}

//在以body作为头结点的链表中将数据域为oldElem的结点，数据域改为newElem
void amendElem(component* array, int body, int oldElem, int newElem) {
    int add = selectNum(array, body, oldElem);
    if (add == -1) {
        printf("无更改元素\n");
        return;
    }
    array[add].data = newElem;
}


int main()
{
    component array[maxSize];
    int body = initArr(array); //初始静态链表
    printf("静态链表为：\n");
    displayArr(array,body);
    printf("在位置3插入4：\n");
    insertArr(array,body,3,4);
    displayArr(array,body);
    printf("删除元素2：\n");
    body = deleteArr(array,body,2);
    displayArr(array,body);
    printf("查找元素4的位置：%d\n",selectNum(array, body, 4));
    printf("更改元素1为8：\n");
    amendElem(array,body,1,8);
    displayArr(array,body);

    return 0;
}
