//
// Created by 醉人饮梦 on 2022/10/11.
//

#include <stdio.h>
#define SIZE 10

void quicksort(int a[],int low,int high);
int qsort(int a[],int low,int high);

int main()
{
    int array[SIZE] = {78,89,12,23,6,34,45,87,29,72};
    quicksort(array, 0, SIZE-1);
    for(int i =0;i<SIZE;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

void quicksort(int a[],int low,int high)
{
    int middle;
    if(low>=high){
        return;
    }
    middle = qsort(a,low,high);
    quicksort(a,low,middle-1);
    quicksort(a,middle+1,high);
}

int qsort(int a[],int low,int high)
{
    int first = a[low];
    for(;;){
        while(low<high&&first<=a[high]){
            high--;
        }
        if(low>=high){
            break;
        }
        a[low++]=a[high];

        while (low<high&&a[low]<=first){
            low++;
        }
        if(low>=high){
            break;
        }
        a[high--]=a[low];
    }
    a[high] =first;

    return high;
}