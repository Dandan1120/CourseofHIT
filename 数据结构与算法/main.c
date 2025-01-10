#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#define MAX 100000
void read_input( int *n, int *arr) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
 
    fscanf(file, "%d", n);
    for (int i = 0; i < *n; ++i) {
        fscanf(file, "%d", &arr[i]);
        // printf("%d",i);
    }
 
    fclose(file);
}
void print_array(int arr[], int size) 
{
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void write(FILE *fp,int *a,int n)
{
    int i;
    // printf("start\n");
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%d ",a[i]);
    }
    fclose(fp);
}
int Partition(int *a,int low,int high)
{
    int key = a[low];
    while(low<high)
    {
         while(low<high&&a[high]>=key)
    {
        high--;
    }
    a[low]= a[high];
    while(low<high&&a[low]<=key)
    {
        low++;
    }
    a[high] = a[low];
    }
    a[low] = key;
    return low;
}
void Quick_sort(int *a,int low,int high)
{
    if(low<high)
    {
        int pivo = Partition(a,low,high);
        Quick_sort(a,low,pivo-1);
        Quick_sort(a,pivo+1,high);

    }
}
void merge(int a[], int low, int middle, int high)
{
    int L_num= middle-low+1;
    int R_num = high-middle;
    int *L = (int*)malloc((middle-low+1)*sizeof(int));
    int *R = (int*)malloc(sizeof(int)*(high-middle));
    int i=low;
    int j = 0;
    int k = low;
    for(;i<=middle&&j<L_num;i++,j++)
    {
        L[j] = a[i];
    }
    for(i=middle+1,j = 0;i<=high&&j<R_num;i++,j++)
    {
        R[j] = a[i];
    }
    for(k=low,i=0,j=0;i<L_num&&j<R_num;k++)
    {
            if(L[i]<=R[j])
            {
                a[k] = L[i];
                i++;
            }
            else
            {
                a[k] = R[j];
                j++;
            }
    }
    while(i<L_num)
    {
        a[k] = L[i];
        i++;
        k++;
    }
    while(j<R_num)
    {
        a[k] = R[j];
        j++;
        k++;
    }
    
}
void MergeSort(int *a,int low,int high)
{
    if(low<high)
    {
        int mid = (low+high)/2;
        MergeSort(a,low,mid);
        MergeSort(a,mid+1,high);
        merge(a,low,mid,high);
    }

}
void SelectSort(int *a,int num)
{
    int min;
    int i,min_idex,j,temp;
    
    for(i=0;i<num-1;i++)
    {   min=a[i];
        min_idex=i;
        for(j=i+1;j<num;j++)
        {
            if(a[j]<min)
            {
                min_idex = j;
                min = a[j];
            }
        }
        temp = a[i];
        a[i] = a[min_idex];
        a[min_idex] = temp;
    }

}

void time_test_base(int *a,int num,BOOL print,BOOL Write)
{
     int merge_sorted_arr[MAX];
    for (int i = 0; i < num; i++) {
        merge_sorted_arr[i] = a[i];
    }
    int quick_sorted_arr[MAX];
    for (int i = 0; i < num; i++) 
    {
        quick_sorted_arr[i] = a[i];
    }
     int select_sorted_arr[MAX];
    for (int i = 0; i < num; i++) 
    {
        select_sorted_arr[i] = a[i];
    }
    // 归并排序
    LARGE_INTEGER start, end, freq;
    double elapsed;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);  
    MergeSort(merge_sorted_arr,0,num-1);
    QueryPerformanceCounter(&end);
    if(Write)
    {
        FILE *fp_1 = fopen("merge_result.txt","w");
         write(fp_1,merge_sorted_arr,num);
    }
    double merge_sort_time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    if(print)
    { 
        printf("Merge Sorted Array: ");
        print_array(merge_sorted_arr, num);
    } 
    printf("Merge Sort Time: %.6f seconds\n", merge_sort_time);
   
    // 快速排序
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);  
    Quick_sort(quick_sorted_arr,0,num-1);
    QueryPerformanceCounter(&end);
     if(Write)
     {
         FILE *fp_2 = fopen("quick_result.txt","w");
         write(fp_2,quick_sorted_arr,num);
     }
    
    double quick_sort_time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    if(print)
    { 
    printf("Quick Sorted Array: ");
    print_array(quick_sorted_arr, num);
    } 
    printf("Quick Sort Time: %.6f seconds\n", quick_sort_time);

    //选择排序
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);  
    SelectSort(select_sorted_arr,num);
    QueryPerformanceCounter(&end);
     if(Write)
     {
        FILE *fp_3 = fopen("select_result.txt","w");
        write(fp_3,select_sorted_arr,num);
     }
   
    double select_sort_time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    if(print)
    { 
     printf("Select Sorted Array: ");
    print_array(select_sorted_arr, num);
    }
    printf("Select Sort Time: %.6f seconds\n", select_sort_time);
}
void time_test_random(int size)
{
    int *a = (int*)malloc(size*sizeof(int));
    int i = 0;
    if (a == NULL) {
        fprintf(stderr, "内存分配失败\n");
        exit(1);
    }
    srand(time(0));
    for(i=0;i<size;i++)
    {
        a[i] = rand()%size;
    }
    time_test_base(a,size,FALSE,FALSE);
}

int main()
{
    int num;
    int i;
    FILE *fp = fopen("intput.txt","r");
    fscanf(fp,"%d",&num);
    fclose(fp);
    int a[MAX];
    read_input(&num,a);
    
    //排序功能展示
    time_test_base(a,num,TRUE,TRUE);
    
    //三种排序性能测试
    int size[10] = {5,10,50,100,500,1000,5000,10000,50000,99000};
    for(i=0;i<10;i++)
    {
        printf("Size of test data is %d\n",size[i]);
        time_test_random(size[i]);
        printf("\n");
    } 
}