#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 512

/* TODO 时间不够了，先复制粘贴过来，后面补上 */

struct User {
    int id;                  //用户id
    int followee[MAX_SIZE];  //用户关注的用户id  (基于数组的散列)
};

struct Tweet {
    int userId;
    int tweetId;
    struct Tweet* next;
};

typedef struct {
    struct User* user;
    struct Tweet* tweet;
} Twitter;

/** Initialize your data structure here. */
Twitter* twitterCreate() {
    Twitter* twitter = (Twitter*)malloc(sizeof(Twitter));
    twitter->user = (struct User*)calloc(MAX_SIZE, sizeof(struct User));
    twitter->tweet = (struct Tweet*)malloc(sizeof(struct Tweet));
    twitter->tweet->next = NULL;
    return twitter;
}

/** Compose a new tweet. */
void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    struct Tweet* tweet = (struct Tweet*)malloc(sizeof(struct Tweet));
    tweet->userId = userId;
    tweet->tweetId = tweetId;
    tweet->next = obj->tweet->next;  //头插法,保证最后发布的推文在最前面
    obj->tweet->next = tweet;
}

/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
    int* ret = (int*)calloc(10, sizeof(int));
    *retSize = 0;
    struct Tweet* tweet = obj->tweet->next;
    struct User* user = obj->user;
    while (tweet && *retSize < 10) {  //用户自己及用户关注的人的推文
        if (tweet->userId == userId || (user + userId)->followee[tweet->userId] == 1)
            ret[(*retSize)++] = tweet->tweetId;
        tweet = tweet->next;
    }
    return ret;
}

/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    (obj->user + followerId)->followee[followeeId] = 1;
}

/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    (obj->user + followerId)->followee[followeeId] = 0;
}

void twitterFree(Twitter* obj) {
    if (obj && obj->user) free(obj->user);
    if (obj && obj->tweet) free(obj->tweet);
    if (obj) free(obj);
}


int main() {
    printf("Hello, World!\n");
    return 0;
}
