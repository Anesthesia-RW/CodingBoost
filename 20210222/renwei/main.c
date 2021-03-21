
#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b);
void sort(int* s,int start, int end);
int tupleSameProduct(int* nums,int numsSize);
/*对于同积元组问题求解：
先利用快速排序按照从小到的顺序排列，
然后利用双指针求解；
双指针思路：首先固定两端，
在中间找是否有两个数的乘积等于两端数的乘积*/

/*
函数名:sort()
函数类型：void
函数功能：实现整数数组快速排序
输入参数：s:数组指针；start：数组左边界；end:数组右边界；
返回参数：无
*/
void sort(int* s,int start, int end)
{ if(start>=end) return;
    int i=start;
    int j=end;
    int key=s[start];
    while(i<j)
    {
        while(i<j&&key<=s[j])
            j--;
        swap(&s[i],&s[j]);
        while(i<j&&s[i]<=key)
            i++;
        swap(&s[i],&s[j]);
    }
    s[i]=key;
    if(start<i)
        sort(s,start,i-1);
    if(i<end)
        sort(s,i+1,end);
}
/*
函数名:swap()
函数类型：void
函数功能：实现两个整数的交换
输入参数：a：整数指针；b:整数指针；
返回参数：无
*/
void swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
/*
函数名:tupleSameProduct()
函数类型：int
函数功能：同积元组求解
输入参数：nums:数组指针；numsSzie:数组大小
返回参数：同积元组求解答案
*/
int tupleSameProduct(int* nums,int numsSize)
{ if (numsSize<4) return 0;
    int answer=0;
    sort(nums,0,numsSize-1);

    for(int i=0;i<numsSize;i++)
        for(int j=numsSize-1;j>=i+2;j--)
    {
       int left=i+1;
       int right=j-1;
        while(left<right)
        {
            int a=nums[i]*nums[j];
            int b=nums[left]*nums[right];
            if(a==b)
            {
                answer++;
                left++;
                right--;
            }else if(a>b){
                left++;
            }else{
                right--;
            }
        }
    }
    return answer*8;
}

