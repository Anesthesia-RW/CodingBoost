
/*
������:wiggleMaxLength()
�������ͣ�int
�������ܣ�Ѱ����ڶ����г��ȣ�
���������nums:����ָ�룻numsSize:�����С
���ز��������ֵ
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
