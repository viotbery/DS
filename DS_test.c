#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int* creat(int n);//随机创建一个变量
void tra(int num[],int n);//打印变量所有元素
void swap(int*, int*);//交换函数
void bubbleGeneral(int *,int n);//普通冒泡排序.O(n^2)
void bubbleTag(int*, int n);//冒泡排序标记版，若经过若干次冒泡，前部分已经有序就可以跳出排序.O(n^2)
void bubbleUpdata(int *,int, int);//冒泡排序升级版，可以跳过未排序但后端部门已经有序的情况。O(n^2)
void selectsort(int* arr, int n);//选择复杂度O(n^2)
void merge(int* arr, int* temp, int left, int mi, int right);//归并排序合并复杂度O(n)
void msort(int* arr, int* temp, int left,int right);//归并排序递归分解
void mergesort(int* arr, int n);//归并排序入口,总复杂度Θ(nlogn)
void reverse(int* arr, int lo, int hi);//二分递归，数组倒置O(n)
int binsearch(int* arr, int e, int n);//二分查找,O(logn)
int sum(int* arr, int lo, int hi);//二分递归，O(n)
long int Fibcreat(int n);//递归打印斐波那契数列,复杂度O(2^n)
long long int Fibcreat_qucik(int n, long long int*);//制表查询已经计算出的斐波那契数
void Fib();//打印斐波那契数列
int count(int* arr, int lo, int hi);//二分排序数数组中0的个数
void main()
{
    int n = 20;
    int *arr = creat(n);
    tra(arr, n);
    //bubbleTag(arr, n);
    //bubbleGeneral(arr, n);
    //bubbleUpdata(arr, 0, n);
    //selectsort(arr, n);
    //mergesort(arr, n);
    //tra(arr, n);
    //printf("%d\n", binsearch(arr, 28, n));
    //reverse(arr, 0, n-1);
    //tra(arr, n);
    printf("number of \"0\" = %d\n", count(arr,0, n-1));
    //Fib();
}

int* creat(int n)
{
    srand(time(0));
    int i;
    int *num = (int*)malloc(n * sizeof(int));
    for (i=0; i< n;i++)
    {
        num[i] = rand()%2;
    }
    return num;
}
void tra(int num[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", num[i]);
    }
    printf("\n");
}
void swap(int *num1,int *num2)
{
    int temp;
    temp = *num1;*num1 = *num2; *num2 = temp;
}
void bubbleTag(int* arr, int n)
{
    int isSord = 0;
    int i,j;
    for (i = 0; i < n && isSord == 0; i++)
    {   
        isSord = 1;
        for(j = 0; j < n-i;j++)
        {   
            if(arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
                isSord = 0;
            }
        }
    }
}
void bubbleGeneral(int* arr,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for (j=0;j<n-i;j++)
        {
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
        }
    }
}
void bubbleUpdata(int *elem, int lo, int hi)
{    
    int last = hi;
    int count = 0;
    int i,num = 0;
    while (lo < (hi = last) )
    {    
        last = lo;
        while (++lo < hi)
        {
            if (elem[lo - 1] > elem[lo]){
                last = lo;
                swap(&elem[lo - 1], &elem[lo]);     
                count++;     
            }        
        }
        lo = 0;
    }
    for(i = 0; i<20;i++)
        num+=i;
    printf("bad count = %d,but this count = %d\n",num,count);
}
void selectsort(int* arr, int n)
{    
    int i,j;
    for(i=0;i<n;i++)
    {   
         int max = 0;
         for(j = 1 ;j < n-i;j++)
         {
             if (arr[max] < arr[j])
                max = j;
         }
         swap(&arr[max], &arr[n-i-1]);
    }
}
void merge(int* arr, int* temp, int left, int mi, int right)
{
    int l_pos = left;
    int r_pos = mi + 1;
    int t_pos = left;
    while (l_pos <= mi && r_pos <= right)
    {
        if (arr[l_pos] < arr[r_pos])
            temp[t_pos++] = arr[l_pos++];
        else temp[t_pos++] = arr[r_pos++];
    }
    while (l_pos <= mi)
    {
        temp[t_pos++] = arr[l_pos++];
    }
    while (r_pos <= right)
    {
        temp[t_pos++] = arr[r_pos++];
    }
    while(left <= right)
    {
        arr[left++] = temp[left];
    }
}
void msort(int* arr, int* temp, int left,int right)
{
    if (left < right)
    {   
        int mi = (left + right) >> 1;
        msort(arr, temp, left, mi);
        msort(arr, temp, mi + 1, right);
        merge(arr, temp, left, mi, right);
    }
}
void mergesort(int* arr, int n)
{
    int* temp = (int*)malloc(n * sizeof(int));
    if (temp)
    {
        msort(arr, temp, 0, n-1);
    }
    else printf("Opps!\n");
}
void reverse(int* arr, int lo, int hi)
{
    if (lo < hi)
    {
        swap(&arr[lo], &arr[hi]);
        reverse(arr, lo+1, hi-1);
    }
}
int binsearch(int* arr, int e, int n)
{
    int lo = 0;
    int hi = n-1;
    while (lo < hi)
    {
        int mi = (lo + hi) >> 1;
        (e<arr[mi]) ? (hi = mi) : (lo = mi + 1);
    }
    return --lo;
    /*
    int lo = 0;
    int hi = n;
    while (lo < hi)
    {
        int mi = (lo + hi) >> 1;
        
        if (arr[mi] < e)
            lo = mi + 1;
        else if(e < arr[mi])
            hi = mi;
        else return mi;
    }
    return -1;
    */
}
int sum(int* arr, int lo, int hi)
{   
    int mi = (lo + hi) >> 1;
    if (lo == hi)
        return arr[lo];
    else return sum(arr, lo, mi) + sum(arr, mi+1, hi);
}
long int Fibcreat(int n)
{   
    return (n<2)? n : Fibcreat(n-1) + Fibcreat(n-2);
}
long long int Fibcreat_qucik(int n, long long int* Fib)
{   
    if (n == 0 || n == 1)
    {
        return Fib[n] = n;
    }
    else if(Fib[n] == 0)
    {
        return Fib[n] = Fibcreat_qucik(n-1, Fib) + Fibcreat_qucik(n-2, Fib);
    }
    else return Fib[n];
}
void Fib()
{
    long long int Fib[100] = {0};;
    int i = 0;
    for (i = 0;i<100; i++)
    {
        //Fib[i] = Fibcreat(i);
        Fib[i] = Fibcreat_qucik(i, Fib);
        printf("%lld ", Fib[i]);
    }
    printf("\n");
}
int count(int* arr, int lo, int hi)
{
    int mid = (lo + hi)>>1;
    return (lo < hi) ? count(arr, lo, mid)+count(arr, mid + 1, hi) : (arr[lo] == 0);
}                                                                                                                                                                                                                                         `````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````