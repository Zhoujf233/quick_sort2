//
//  main.cpp
//  quick_sort2
//
//  Created by JF Zhou on 2019/8/26.
//  Copyright © 2019 JF Zhou. All rights reserved.
//

#include <iostream>
#include "QKSort.hpp"
using namespace std;

int main(int argc, const char * argv[])
{
    int arr[] = {89,22,-3,32,82,55,22,50,37,5,64,35,9,70};
    int size = (int) sizeof(arr)/sizeof(*arr);
    int i;
    cout<<"初始顺序为: ";
    for(i = 0;i < size;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    
    introSort(arr, size);
    
    cout << "快速排序后顺序为：";
    for(i = 0;i < size;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
