//
// Created by �������� on 2023/2/28.
//

#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW 3
#define UNDERFLOW 4
// �ٶ�����ά�ȵ����ֵ
#define MAX_ARRAY_DIM 8

typedef int Status; // ���������ͣ��������״̬���룬�磺ok
typedef int ElemType;

typedef struct {
    ElemType *base;
    int dim; // ����ά��
    int* bounds; // ����ά���ַ��ÿ��ά������ĵ�ַ��
    int* constants; //
} Array;

Status initArray(Array* A,int dim, ...)
{
    // Ԫ�� �ܸ���
    int elemTotal = 1, i;
    // ����ɱ�����б�
    va_list ap;
    // �ж����� ά�� �Ƿ�����
    if(dim < 1 || dim > MAX_ARRAY_DIM)
        return ERROR;
    A->dim = dim;
    A->bounds = malloc(dim * sizeof(int));
    // �ж���ַ�Ƿ����ɹ�
    if(!A->bounds)
        exit(OVERFLOW);
    // ��ȡ�����ɱ�����б�
    va_start(ap, dim);

    // ���� dim ����ȡ�� �ɱ��β��еĸ�������
    for (i = 0; i < dim; ++i) {
        // va_argѭ������ɱ�����б��еĸ����ɱ����
        A->bounds[i] = va_arg(ap,int);
        if(A->bounds[i]<0)
            return UNDERFLOW;
        elemTotal *= A->bounds[i];
    }
    // �����б�������Ժ󣬲����б�ָ��������ָ��һ���������ջأ��������Ұָ�롣
    va_end(ap);
    A->base = malloc(elemTotal * sizeof(ElemType));
    if(!A->base)
        exit(OVERFLOW);
    A->constants = malloc(dim * sizeof(int));
    if(!A->constants)
        exit(OVERFLOW);
    A->constants[dim - 1] = 1;
    for (i = dim - 2;i >= 0; --i)
        A->constants[i] = A->bounds[i + 1] * A->constants[i + 1];
    return OK;
}

Status destroyArray(Array *A)
{;
    if(A->base){
        free(A->base);
        A->base = NULL;
    }else{
        return ERROR;
    }
    if(A->bounds){
        free(A->bounds);
        A->bounds = NULL;
    }else{
        return ERROR;
    }
    if(A->constants){
        free(A->constants);
        A->constants = NULL;
    }else{
        return ERROR;
    }
    return OK;
}

// �õ���ַ��ƫ����
Status Locate(Array A,va_list ap,int *off)
{
    int i,ind;
    *off = 0;
    for (i = 0;i<A.dim; ++i){
        ind = va_arg(ap,int);
        // �жϴ�������Ƿ���ԭ������һ��
        if(ind < 0 || ind >= A.bounds[i])
            return OVERFLOW;
        *off += A.constants[i] * ind;
    }
    return OK;
}

// �� �ض� ��ַ ��ֵ��ֵ�� ����
Status Value(ElemType *e,Array A, ...)
{
    va_list ap;
    Status result;
    int off;
    va_start(ap, A);
    if((result = Locate(A,ap,&off)) == OVERFLOW)
        return result;
    *e = *(A.base + off);
    return OK;
}

// Ϊ �ض� ��ַ ��ֵ
Status Assign(Array *A,ElemType e, ...)
{
    va_list ap;
    Status result;
    int off;
    va_start(ap, e);
    if((result = Locate(*A, ap, &off)) == OVERFLOW)
        return result;
    *(A->base + off) = e;
    return OK;
}

int main()
{
    Array A;
    int i, j, k, *p, dim = 3, bound1 = 3, bound2 = 4, bound3 = 2;
    ElemType e, *p1;
    initArray(&A, dim, bound1, bound2, bound3);
    p = A.bounds;
    printf("A.bounds=");
    for (i = 0;i<dim;i++)
        printf("%d ",*(p + i));
    p = A.constants;
    printf("\nA.constants=");
    for (i = 0;i<dim;i++)
        printf("%d ",*(p + i));
    printf("\n%d ҳ%d ��%d �о���Ԫ�����£�\n",bound1, bound2, bound3);
    for (i = 0;i<bound1;i++){
        for(j = 0;j<bound2;j++){
            for (k = 0;k<bound3;k++){
                Assign(&A, i * 100 + j * 10 + k, i, j, k);
                Value(&e, A, i, j, k);
                printf("A[%d][%d][%d]=%2d ",i, j, k, e);
            }
            printf("\n");
        }
        printf("\n");
    }
    p1 = A.base;
    printf("A.base=\n");
    for (i = 0;i<bound1*bound2*bound3;i++){
        printf("%4d",*(p1 + i));
        if(i % (bound2 * bound3) == bound2*bound3 - 1)
            printf("\n");
    }
    destroyArray(&A);

    return 0;
}
