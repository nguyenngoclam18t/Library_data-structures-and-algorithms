#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include "HashTable.h"
#include <Windows.h>
void show(int a) {
	printf("%d ", a);
}
int compare(int a, int b) {
	if (a == b)return 0;
	if (a > b)return 1;
	if (a < b)return -1;
}
int convert(int a) {
	return a;
}
/* Hàm main để thực hiện kiểm tra kết quả */
int main()
{
	InputMax(100);
	HashNode<int>* Array[100];
	InitHashTable(Array);
	Insert(Array, 2, convert, compare);
	Insert(Array, 3, convert, compare);
	Insert(Array, 102, convert, compare);
	Insert(Array, 2, convert, compare);
}
