#include <stdio.h>

#define MAX(a, b) ((a) >= (b) ? (a): (b))

int wiggleMaxLength(const int* nums, int numsSize) {
    /* 向上摆动与向下摆动*/
    int up[numsSize], down[numsSize];

    if (numsSize < 2) {
        return numsSize;
    }

    up[0] = down[0] = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < nums[i - 1]) {
            up[i] = up[i - 1];
            down[i] = MAX(up[i - 1] + 1, down[i - 1]);
        } else if (nums[i] > nums[i - 1]) {
            up[i] = MAX(up[i - 1], down[i - 1] + 1);
            down[i] = down[i - 1];
        } else {
            up[i] = up[i - 1];
            down[i] = down[i - 1];
        }
    }
    return MAX(up[numsSize - 1], down[numsSize - 1]);
}


int main() {
    int nums[10] = {1,17,5,10,13,15,10,5,16,8};
    printf("Result: %d", wiggleMaxLength((int*)nums, 10));
    return 0;
}
