//锦标赛算法
#include<iostream>
#include<stdio.h>
#include<stdlib.h>//malloc头文件
using namespace std;

typedef struct LNode {
    int data;
    struct LNode* next;
}LinkNode;

void Champion(LinkNode* d, int num,bool (*p)(int,int));
void InsertListL(LinkNode* d, LinkNode* p);
int FindSecond(LinkNode* d,bool(*p)(int, int));
//判断函数
bool Max(int a, int b) {
    return a < b;
}
bool Min(int a, int b) {
    return a > b;
}
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
    Champion(max, num,Max);
    int max1 = max[0].data;
    int max2 = FindSecond(&max[0],Max);

    LinkNode* min = (LinkNode*)malloc(sizeof(LinkNode) * num);
    //给每个节点赋值
    for (int i = 0; i < num; i++) {
        min[i].data = a[i];
        min[i].next = NULL;
    }
    Champion(min, num, Min);
    int min1 = min[0].data;
    int min2 = FindSecond(&min[0],Min);

    printf("max=%d max2=%d\n", max1, max2);
    printf("min=%d min2=%d", min1, min2);

    free(a);  // 释放a指向的内存
    free(max); // 释放max指向的内存
    free(min); // 释放min指向的内存

    /**********  End  **********/
}

//锦标赛算法，查找第一大（小）和第二大（小）
void Champion(LinkNode* d, int num, bool (*p)(int, int)) {
    //多轮循环找出最大
    while (num != 1) {
        int count = 0;//记录每轮较大（小）值
        //两两比较查找较大（小）值，并将较小（大）值头插入到较大（小）值的链表中,需保证i+1不能大于等于num
        for (int i = 0; i + 1 < num; i += 2) {
            if (p(d[i].data,d[i + 1].data)) {//回调函数判断大小
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


//头插法插入
void InsertListL(LinkNode* d, LinkNode* p) {
    p->next = d->next;
    d->next = p;
}

//查找第二大值或第二小值
int FindSecond(LinkNode* d,bool(*p)(int, int)) {
    LinkNode* s = d->next;//s指向d的第二个节点
    int m2 = s->data;//m2保存第二大或第二小值
    while (s->next != NULL) {
        s = s->next;
        if (p(m2 , s->data)) {//回调函数判断大小
            m2 = s->data;
        }
    }

    return m2;
}
