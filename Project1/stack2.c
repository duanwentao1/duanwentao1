//
// Created by �������� on 2023/2/25.
//

#include <stdio.h>
#include <string.h>

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
    top--;
}
char visit(char *a)
{
    if(top!=-1){
        return a[top];
    }else{
        return ' ';
    }
}

int main()
{
    char a[30],bracket[100];
    printf("�������������У�");
    scanf_s("%s",bracket,100);
    // �������з�
    getchar();
    int length = (int) strlen(bracket);
    for (int i = 0; i < length; ++i) {
        if(bracket[i]=='('||bracket[i]=='{'||bracket[i]=='['){
            push(a,bracket[i]);
        } else{
            if(bracket[i]==')'){
                if(visit(a)=='('){
                    pop(a);
                } else{
                    printf("���Ų�����");
                    return 0;
                }
            } else if(bracket[i]=='}'){
                if(visit(a)=='{'){
                    pop(a);
                } else{
                    printf("���Ų�����");
                    return 0;
                }
            } else{
                if(visit(a)=='['){
                    pop(a);
                } else{
                    printf("���Ų�����");
                    return 0;
                }
            }
        }
    }
    if(top!=-1){
        printf("���Ų�����");
    } else{
        printf("��������");
    }

    return 0;
}
