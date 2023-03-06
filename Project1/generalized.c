//
// Created by 醉人饮梦 on 2023/2/28.
//

#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW 3
#define UNDERFLOW 4
// 假定数组维度的最大值
#define MAX_ARRAY_DIM 8

typedef int Status; // 函数的类型，函数结果状态代码，如：ok
typedef int ElemType;

typedef struct {
    ElemType *base;
    int dim; // 数组维度
    int* bounds; // 数组维界基址（每个维度数组的地址）
    int* constants; //
} Array;

Status initArray(Array* A,int dim, ...)
{
    // 元素 总个数
    int elemTotal = 1, i;
    // 定义可变参数列表
    va_list ap;
    // 判断数组 维度 是否正常
    if(dim < 1 || dim > MAX_ARRAY_DIM)
        return ERROR;
    A->dim = dim;
    A->bounds = malloc(dim * sizeof(int));
    // 判读地址是否分配成功
    if(!A->bounds)
        exit(OVERFLOW);
    // 获取函数可变参数列表
    va_start(ap, dim);

    // 根据 dim 依次取出 可变形参中的各个参数
    for (i = 0; i < dim; ++i) {
        // va_arg循环处理可变参数列表中的各个可变参数
        A->bounds[i] = va_arg(ap,int);
        if(A->bounds[i]<0)
            return UNDERFLOW;
        elemTotal *= A->bounds[i];
    }
    // 参数列表访问完以后，参数列表指针与其他指针一样，必须收回，否则出现野指针。
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

// 得到地址的偏移量
Status Locate(Array A,va_list ap,int *off)
{
    int i,ind;
    *off = 0;
    for (i = 0;i<A.dim; ++i){
        ind = va_arg(ap,int);
        // 判断传入参数是否与原定参数一致
        if(ind < 0 || ind >= A.bounds[i])
            return OVERFLOW;
        *off += A.constants[i] * ind;
    }
    return OK;
}

// 将 特定 地址 的值赋值给 变量
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

// 为 特定 地址 赋值
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
    printf("\n%d 页%d 行%d 列矩阵元素如下：\n",bound1, bound2, bound3);
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
