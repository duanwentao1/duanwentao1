//
// Created by 醉人饮梦 on 2023/2/25.
//

#include <stdio.h>
#include <string.h>
#include <math.h>

int top = -1;

void push(char *a,char elem)
{
    a[++top] = elem;
}
void pop(char *a)
{
    if(top==-1){
        return;
    }
    // 十六进制的处理
    if(a[top]>=10){
        printf("%c",a[top]+55);
    } else{
        printf("%d",a[top]);
    }
    top--;
}
int scaleFun(char *data,int system)
{
    int k = (int)strlen(data)-1;
    int system_10_data = 0;
    int i;
    for(i=k;i>=0;i--){
        int temp;
        // 编码数值处理
        if(data[i]>=48&&data[i]<=57){
            temp = data[i]-48;
        } else{
            temp = data[i]-97+10;
        }
        // 转换为 10 进制
        system_10_data += temp * pow(system,k-i);
    }
    return system_10_data;
}

int main()
{
    char data[100];
    printf("进制转化器，请输入原数据的进制（2，8，10，16）：");
    int system;
    scanf_s("%d",&system);
    // 消除换行符
    getchar();
    printf("请输入要转换的数据：");
    scanf_s("%s",data,100);
    getchar();
    int system_10_data = scaleFun(data,system);
    printf("请输入转换后的数据的进制：");
    int newSystem;
    scanf_s("%d",&newSystem);
    getchar();
    while(system_10_data/newSystem){
        push(data,system_10_data%newSystem);
        system_10_data/=newSystem;
    }
    // 不要忘记商为0的余数
    push(data,system_10_data%newSystem);
    printf("转换后的结果为：\n");
    while (top!=-1){
        pop(data);
    }

    return 0;
}
