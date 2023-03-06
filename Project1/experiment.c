//
// Created by 醉人饮梦 on 2023/2/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define Size 5

void func(int* p, int dim, ...)
{
    va_list ap;
    va_start(ap, dim);
    for (int i = 0; i < dim; ++i) {
        p[i] = va_arg(ap, int);
        printf("%d ",p[i]);
    }
    va_end(ap);
}

int main()
{
//    int arr[3];
//    int *p= arr;
//    func(arr,3,2,3,4,5);
    printf("\n%llu", sizeof(__builtin_va_list));

    return 0;
}
