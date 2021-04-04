/*摆动序列求解：
    引入一个参数m，取值±1，表示前两个数差的正负；m=0,表示两个数相等
    遍历序列，若该数比前一个数大，且m=-1，则结果加1，并且m设为1；
             若该数比前一个数小，且m=1，则结果加1，并且m设为-1；

*/
#include<stdio.h>
int wiggleMaxLength(int* nums, int numsSize){
    if (numsSize < 2){
            return numsSize;
    }
    int result = 1,m = 0;
//先判断前两个数  
    if (nums[1]>nums[0]){
        result = 2;
        m = 1;
    }else if (nums[1]<nums[0]){
        result = 2;
        m = -1;
    }
    for (int i=2;i<numsSize;i++){
        if(nums[i]>nums[i-1] && m != 1){
            result ++;
            m = 1;
        }else if(nums[i]<nums[i-1] && m != -1){
            result++;
            m = -1;
        }
    }
    return result;
}
