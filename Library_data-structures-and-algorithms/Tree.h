#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
template<class T>
struct NODET
{
	T Data;
	NODET<T>* Left;
	NODET<T>* Right;
};
template<class T>
struct Tree
{
	NODET<T>* Root;
};
template<class T>
void InitTree(Tree<T>& Root) {
	Root.Root = NULL;
}
template<class T>
NODET<T>* CreateNodeT(T data) {
	NODET<T>* P = new NODET<T>;
	P->Data = data;
	P->Left = NULL;
	P->Right = NULL;
	return P;
}
template<class T>
void AddNodeT(NODET<T>*& root, NODET<T>* P)
{
	if (P == NULL)return;
	if (root == NULL) {
		root = P;
		return;
	}
	if (root->Left == NULL) {
		AddNodeT(root->Left, P);
	}
	else if (root->Right == NULL) {
		AddNodeT(root->Right, P);
	}
	else
	{
		srand(time(0));
		int d = rand() % 2;
		if (d) {
			AddNodeT(root->Left, P);
		}
		else
		{
			AddNodeT(root->Right, P);
		}
	}
}
//con trỏ hàm
template<class T>
void TraverseNLR(NODET<T>* root, void(*show)(NODET<T>*)) {
	if (root == NULL)return;
	show(root);
	TraverseNLR(root->Left, show);
	TraverseNLR(root->Right, show);
}
template<class T>
void traverseNRL(NODET<T>* root, void(*show)(NODET<T>*)) {
	if (root == NULL)return;
	show(root);
	traverseNRL(root->Right, show);
	traverseNRL(root->Left, show);
}
template<class T>
void traverseLNR(NODET<T>* root, void(*show)(NODET<T>*)) {
	if (root == NULL)return;
	traverseLNR(root->Left, show);
	show(root);
	traverseLNR(root->Right, show);

}
template<class T>
void traverseRNL(NODET<T>* root, void(*show)(NODET<T>*)) {
	if (root == NULL)return;
	traverseRLN(root->Right, show);
	show(root);
	traverseRLN(root->Left, show);
}
template<class T>
void traverseLRN(NODET<T>* root, void(*show)(NODET<T>*)) {
	if (root == NULL)return;
	traverseLRN(root->Left, show);
	traverseLRN(root->Right, show);
	show(root);

}
template<class T>
void traverseRLN(NODET<T>* root, void(*show)(NODET<T>*)) {
	if (root == NULL)return;
	traverseRLN(root->Right, show);
	traverseRLN(root->Left, show);
	show(root);
}
template<class T>
int CountLeaf(NODET<T>* root) {
	if (root == NULL)return 0;
	int s = CountLeaf(root->Left) + CountLeaf(root->Right);
	return (root->Left == NULL && root->Right == NULL) ? 1 + s : s;
}
template<class T>
NODET<T>* FindX(NODET<T>* root, T X) {
	if (root == NULL)return NULL;
	if (root->Data == X)return root;
	NODET<T>* P = FindX(root->Left, X);
	if (P)return P;
	FindX(root->Right, X);
}
template<class T>
void DeleteTree(NODET<T>*& root) {
	if (!root)return;
	DeleteTree(root->Left);
	DeleteTree(root->Right);
	delete root;
}
template<class T>
int CountNODE(NODET<T>* root) {
	if (root == NULL)return 0;
	return 1 + CountNODE(root->Left) + CountNODE(root->Right);
}
template<class T>
int Count1Child(NODET<T>* root) {
	if (root == NULL)return 0;
	int count = Count1Child(root->Left) + Count1Child(root->Right);
	return ((root->Left == NULL && root->Right != NULL) || ((root->Left != NULL && root->Right == NULL))) ? 1 + count : count;
}
template<class T>
int Count2Child(NODET<T>* root) {
	if (root == NULL)return 0;
	int count = Count2Child(root->Left) + Count2Child(root->Right);
	return (root->Left != NULL && root->Right != NULL) ? 1 + count : count;
}
template<class T>
double SumNodeLeaf(NODET<T>* root) {
	if (root == NULL)return 0;
	T sum = SumNodeLeaf(root->Left) + SumNodeLeaf(root->Right);
	return (root->Left == NULL && root->Right == NULL) ? sum + root->Data : sum;
}
template<class T>
double Sum1Child(NODET<T>* root) {
	if (root == NULL)return 0;
	T sum = Sum1Child(root->Left) + Sum1Child(root->Right);
	return (root->Left == NULL || root->Right == NULL) ? sum + root->Data : sum;
}
template<class T>
double Sum2Child(NODET<T>* root) {
	if (root == NULL)return 0;
	int sum = Sum2Child(root->Left) + Sum2Child(root->Right);
	return (root->Left != NULL && root->Right != NULL) ? root->Data + sum : sum;
}
template<class T>
int HighTree(NODET<T>* root) {
	if (root == NULL)return 0;
	int left = HighTree(root->Left);
	int right = HighTree(root->Right);
	return left > right ? 1 + left : 1 + right;
}
template<class T>
double SumNODE(NODET<T>* root) {
	if (root == NULL)return 0;
	return root->Data + CountNODE(root->Left) + CountNODE(root->Right);
}