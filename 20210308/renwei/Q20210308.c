
/*
函数名:wiggleMaxLength()
函数类型：int
函数功能：寻找最长摆动序列长度；
输入参数：nums:数组指针；numsSize:数组大小
返回参数：求解值
*/
int wiggleMaxLength(int* nums, int numsSize){
    int result=0;
    if (numsSize<2)
    {
            result =numsSize;
            return result;
    }
    int initDifference =nums[1]-nums[0];
    if(initDifference)
    {
        result =2;
    }
    else
    {
        result =1;
    }
    for (int i=2;i<numsSize;i++)
    {
        int temp=nums[i]-nums[i-1];
        if((temp>0&&initDifference<=0)||(temp<0&&initDifference>=0))
        {   result+=1;
            initDifference=temp;
        }
    }
    return result;
}
