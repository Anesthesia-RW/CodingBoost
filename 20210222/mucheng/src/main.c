#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_MAX_SIZE (10000)
#define NODE_MIN_SIZE (4)
#define MIN_SIZE (4)

/*
 * 这里的数据结构是，有一个哈希数组，数组的下标是乘积对MAX_SIZE取余
 * 每个哈希节点下，size代表当前节点大小，capacity代表容量，key则是真正的乘积，value是此乘积的pair个数
 */

typedef struct tagHashNode{
    int  size;      // cur size
    int  capacity;  // max size
    int* key;
    int* value;
}HashNode;

typedef struct{
    HashNode* hash[TABLE_MAX_SIZE];
}HashTable;

HashNode* create()
{
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    memset(node, 0 ,sizeof(HashNode));
    node->capacity = NODE_MIN_SIZE;
    node->key = (int*)malloc(node->capacity * sizeof(int));
    memset(node->key, 0, node->capacity * sizeof(int));
    node->value = (int*)malloc(node->capacity * sizeof(int));
    memset(node->value, 0, node->capacity * sizeof(int));

    return node;
}

void insert(HashTable* hashTable, int val){
    int index = val % TABLE_MAX_SIZE; // 防止溢出
    int i;

    // 如果是第一次有这个值
    if (hashTable->hash[index] == NULL) {
        hashTable->hash[index] = create();
        hashTable->hash[index]->key[0] = val;
        hashTable->hash[index]->value[0] = 1;
        hashTable->hash[index]->size = 1;
        return;
    }

    // 以后每次有这个值，都将value++
    for(i = 0; i < hashTable->hash[index]->size; i++){
        if(hashTable->hash[index]->key[i] == val){
            hashTable->hash[index]->value[i]++;
            return;
        }
    }

    // 扩容
    if (hashTable->hash[index]->size == hashTable->hash[index]->capacity) {
        hashTable->hash[index]->capacity += NODE_MIN_SIZE;
        hashTable->hash[index]->key = (int*)realloc(hashTable->hash[index]->key, hashTable->hash[index]->capacity * sizeof(int));
        hashTable->hash[index]->value = (int*)realloc(hashTable->hash[index]->value, hashTable->hash[index]->capacity * sizeof(int));
    }

    // 如果是新值
    hashTable->hash[index]->key[hashTable->hash[index]->size] = val;
    hashTable->hash[index]->value[hashTable->hash[index]->size] = 1;
    hashTable->hash[index]->size++;
}

int tupleSameProduct(const int* nums, int numsSize)
{
    HashTable* hashTable;
    int val;
    int result = 0;
    int i, j;

    if (numsSize < MIN_SIZE) {
        return 0;
    }

    hashTable = (HashTable*)malloc(sizeof(HashTable));
    memset(hashTable, 0, sizeof(HashTable));
    for (i = 0; i < numsSize; i++){
        for(j = i + 1; j < numsSize;j++){
            val = nums[i] * nums[j];
            insert(hashTable, val);
        }
    }

    // 遍历每个有可能的乘积
    for(i = 0; i < TABLE_MAX_SIZE; i++){
        if(hashTable->hash[i] == NULL){
            continue;
        }
        for(j = 0; j < hashTable->hash[i]->size; j++){
            if(hashTable->hash[i]->value[j] > 1){
                // 从n个组合中挑出两个二元祖组成四元祖（排列组合），对于一个四元组，有8个解法
                result += 8 * ((hashTable->hash[i]->value[j]) * (hashTable->hash[i]->value[j]-1) / 2);
            }
        }
    }

    // free
    return result;
}


int main()
{
    uint32_t numSize = 5;
    uint32_t nums[5] = {1, 2, 4, 5, 10};

    printf("%d", tupleSameProduct((int*)nums, numSize));
}