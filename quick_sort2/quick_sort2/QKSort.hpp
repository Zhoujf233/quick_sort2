//
//  QKSort.hpp
//  quick_sort2
//
//  Created by JF Zhou on 2019/8/26.
//  Copyright © 2019 JF Zhou. All rights reserved.
//

#ifndef QKSort_h
#define QKSort_h
#include "iostream"
using namespace std;

//introsort 算法实现
//数据量的分界线,决定了使用quick sort/heap sort 还是insertion sort
const int threshold = 16;

//堆排序用到的辅助函数
int parent(int i)
{
    return (int)((i - 1)/2);
}
int left(int i)
{
    return 2 * i+1;
}
int right(int i)
{
    return (2 * i + 2);
}
void heapShiftDown(int heap[], int i, int begin, int end)
{
    int l = left(i - begin) + begin;
    int r = right(i-begin)+begin;
    int largest=i;
    //找出左右字节点与父节点中的最大者
    if(l < end && heap[l] > heap[largest])
        largest = l;
    if(r < end && heap[r] > heap[largest])
        largest = r;
    //若最大者不为父节点，则需交换数据，并持续向下滚动至满足最大堆特性
    if(largest != i)
    {
        swap(heap[largest],heap[i]);
        heapShiftDown(heap, largest, begin,end);
    }
}
//自底向上的开始建堆，即从堆的倒数第二层开始
void buildHeap(int heap[],int begin,int end)
{
    for(int i = (begin+end)/2; i >= begin; i--)
    {
        heapShiftDown(heap, i, begin,end);
    }
}

//堆排序
void heapSort(int heap[], int begin,int end)
{
    buildHeap(heap,begin,end);
    for(int i = end; i >begin; i--)
    {
        swap(heap[begin],heap[i]);
        heapShiftDown(heap,begin,begin, i);
    }
}


//插入排序
void insertionSort(int array[],int len)
{
    int i,j,temp;
    for(i=1;i<len;i++)
    {
        temp = array[i];//store the original sorted array in temp
        for(j=i;j>0 && temp < array[j-1];j--)//compare the new array with temp(maybe -1?)
        {
            array[j]=array[j-1];//all larger elements are moved one pot to the right
        }
        array[j]=temp;
    }
}


//三点中值
int median3(int array[],int first,int median,int end)
{
    if(array[first]<array[median])
    {
        if(array[median]<array[end])
            return median;
        else if(array[first]<array[end])
            return end;
        else
            return first;
    }
    else if(array[first]<array[end])
        return first;
    else if(array[median]<array[end])
        return end;
    else
        return median;
}

//对数组分割
int partition(int array[],int left,int right,int p)
{
    //选择最右侧的元素作为分割标准
    int index = left;
    swap(array[p],array[right]);
    int pivot = array[right];
    //将所有小于标准的点移动到index的左侧
    for (int i=left; i<right; i++)
    {
        if (array[i] < pivot)
            swap(array[index++],array[i]);
    }
    //将标准与index指向的元素交换，返回index，即分割位置
    swap(array[right],array[index]);
    return index;
}

//递归的对数组进行分割排序
void introSortLoop(int array[],int begin,int end,int depthLimit)
{
    while((end-begin+1)>threshold) //子数组数据量大小，则交给后面的插入排序进行处理
    {
        if(depthLimit==0)      //递归深度过大，则由堆排序代替
        {
            heapSort(array,begin,end);
            return ;
        }
        --depthLimit;
        //使用quick sort进行排序
        int cut=partition(array,begin,end,
                          median3(array,begin,begin+(end-begin)/2,end));
        introSortLoop(array,cut,end,depthLimit);
        end=cut;    //对左半段进行递归的sort
    }
}

//计算最大容忍的递归深度
int lg(int n)
{
    int k;
    for(k=0;n>1;n>>=1) ++k;
    return k;
}


//霸气的introsort
void introSort(int array[],int len)
{
    if(len!=1)
    {
        introSortLoop(array,0,len-1,lg(len)*2);
        insertionSort(array,len);
    }
}

#endif /* QKSort_h */
