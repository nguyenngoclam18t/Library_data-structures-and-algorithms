#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"Btree.h"
int compare(int a, int b);
int main() {
	BTree<int>tree;
	InitTree<int>(tree);
	int a = 5;
	AddNodeT<int>(tree.Root, CreateNodeT(a),compare);
	a = 3;
	AddNodeT<int>(tree.Root, CreateNodeT(a), compare);
	a = 2;
	AddNodeT<int>(tree.Root, CreateNodeT(a), compare);
	a = 4;
	AddNodeT<int>(tree.Root, CreateNodeT(a), compare);
	a = 7;
	AddNodeT<int>(tree.Root, CreateNodeT(a), compare);
	a = 6;
	AddNodeT<int>(tree.Root, CreateNodeT(a), compare);
	a = 8;
	AddNodeT<int>(tree.Root, CreateNodeT(a), compare);
	Remove_X<int>(tree.Root, 7);
	return 0;
}
int compare(int a, int b) {
	if (a == b)return 0;
	if (a > b)return 1;
	if (a < b)return -1;
}