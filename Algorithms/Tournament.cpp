//使用链表实现锦标赛算法
#include<iostream>
#include<stdio.h>
#include<stdlib.h>//malloc头文件
using namespace std;

typedef struct LNode {
    int data;
    struct LNode* next;
}LinkNode;

void ChampionMax(LinkNode* d, int num);
void ChampionMin(LinkNode* d, int num);
void InsertListL(LinkNode* d, LinkNode* p);
int FindSecondMax(LinkNode* d);
int FindSecondMin(LinkNode* d);


int main() {

    int num;
    int* a;
    scanf_s("%d", &num);
    a = (int*)malloc(sizeof(int) * num);//动态分配内存,记得free
    //输入数组
    for (int i = 0; i < num; i++)
        scanf_s("%d", &a[i]);

    /**********  Begin  **********/
    //创建一个数据类型均为链表的数组

    LinkNode* max=(LinkNode*)malloc(sizeof(LinkNode) * num);
    //给每个节点赋值
    for (int i = 0; i < num; i++) {
        max[i].data = a[i];
        max[i].next = NULL;
    }
    ChampionMax(max, num);
    int max1 = max[0].data;
    int max2 = FindSecondMax(&max[0]);

    LinkNode* min = (LinkNode*)malloc(sizeof(LinkNode) * num);
    //给每个节点赋值
    for (int i = 0; i < num; i++) {
        min[i].data = a[i];
        min[i].next = NULL;
    }
    ChampionMin(min, num);
    int min1 = min[0].data;
    int min2 = FindSecondMin(&min[0]);

    printf("max=%d max2=%d\n", max1, max2);
    printf("min=%d min2=%d", min1, min2);

    free(a);  // 释放a指向的内存
    free(max); // 释放max指向的内存
    free(min); // 释放min指向的内存

    /**********  End  **********/
}


//锦标赛算法，查找第一大和第二大,只考虑偶数个情况
void ChampionMax(LinkNode* d, int num) {
    //多轮循环找出最大
    while (num != 1) {
        int count = 0;//记录每轮较大值
        //两两比较查找较大值，并将较小值头插入到较大值的链表中,需保证i+1不能大于等于num
        for (int i = 0; i + 1 < num; i += 2) {
            if (d[i].data < d[i + 1].data) {
                LinkNode* p=(LinkNode*)malloc(sizeof(LinkNode));
                p->data = d[i].data;//必须创建一个新节点保存需要插入的节点，不然可能造成死循环
                p->next = NULL;                //例如InsertListL(&d[i + 1], &d[i]);  
                InsertListL(&d[i + 1], p);     //  d[count] = d[i + 1];*/
                d[count] = d[i + 1];
            }
            else {
                LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
                p->data = d[i+1].data;
                p->next = NULL;
                InsertListL(&d[i], p);
                d[count] = d[i];
            }
            count++;
        }
        //考虑轮空值
        if (num % 2 == 1) {
            d[count] = d[num-1];
            num = num / 2 + 1;
        }
        else {
            num /= 2; 
        }
    }
}

//锦标赛算法，查找第一小和第二小,只考虑偶数个情况
void ChampionMin(LinkNode* d, int num) {
    //多轮循环找出最小
    while (num != 1) {
        int count = 0;//记录每轮较小值
        //两两比较查找较小值，并将较大值头插入到较值的链表中
        for (int i = 0; i + 1 < num; i += 2) {
            if (d[i].data > d[i + 1].data) {
                LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
                p->data = d[i].data;
                p->next = NULL;
                InsertListL(&d[i + 1], p);
                d[count] = d[i + 1];
            }
            else {
                LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
                p->data = d[i+1].data;
                p->next = NULL;
                InsertListL(&d[i], p);
                d[count] = d[i];
            }
            count++;
        }
        //考虑轮空值
        if (num % 2 == 1) {
            d[count] = d[num-1];
            num = num / 2 + 1;
        }
        else {
            num /= 2;
        }
    }
}
//头插法插入
void InsertListL(LinkNode* d, LinkNode* p) {
    p->next = d->next;
    d->next = p;
}

//查找第二大值
int FindSecondMax(LinkNode* d) {
    LinkNode* s = d->next;//s指向d的第二个节点
    int max2 = s->data;//max2保存第二大值
    while (s->next != NULL) {
        s = s->next;
        if (max2 < s->data) {
            max2 = s->data;
        }
    }

    return max2;
}

//查找第二小值
int FindSecondMin(LinkNode* d) {
    LinkNode* s = d->next;//s指向d的第二个节点
    int min2 = s->data;//max2保存第二小
    while (s->next != NULL) {
        s = s->next;
        if (min2 > s->data) {
            min2 = s->data;
        }
    }

    return min2;
}
