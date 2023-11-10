//用快速排序找出第k小的元素
#include<iostream>
using namespace std;

void quicksort(int* A, int p, int r);//快速排序函数
int partition(int* A, int p, int r);//快速排序划分过程，并返回A的首元素在排好序的数组中的位置
void swap(int* a, int* b);//交换值

int main() {
	int n, k;//n表示数组个数，k表示找出低k个小的元素
	cin >> n >> k;
	int A[100] = {0};
	//给数组A输入数据
	for (int i = 0; i <= n - 1; i++) {
		cin >> A[i];
	}
	quicksort(A, 0, n - 1);//进行快速排序
	cout << "第" << k << "小的元素是" << A[k-1] << endl;//返回第k小的值
	return 0;
}

void quicksort(int *A,int p,int r) {
	if (p < r) {
		int q = partition(A, p, r);//返回A的首元素在排好序的数组中的位置
		swap(&A[p], &A[q]);//交换p和q位置上的值
		//进行递归调用
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}

}

int partition(int* A, int p, int r) {
	int x = A[p];//返回首元素值
	int i = p + 1;
	int j = r;
	while (i < j) {
		if (A[j] <= x) {
			if (A[i] > x) {
				swap(&A[i], &A[j]);
				j--;
			}
			else {
				i++;
			}
			
		}
		else {
			j--;
		}
	}

	return j;
}

void swap(int *a,int *b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
