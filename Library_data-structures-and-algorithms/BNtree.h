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
struct BTree
{
	NODET<T>* Root;
};
template<class T>
void InitTree(BTree<T>& Root) {
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
int AddNodeT(NODET<T>*& root, NODET<T>* P,int (*Compare)(T,T))
{
	if (P == NULL)return 0;
	if (root == NULL) {
		root = P;
		return 1;
	}
	if (Compare(root->Data, P->Data)==0)return 0;
	if (Compare(root->Data, P->Data)>0) AddNodeT(root->Left, P,Compare);
	else if (Compare(root->Data, P->Data)<0) AddNodeT(root->Right, P,Compare);
}
template<class T>
NODET<T>* FindReplace(NODET<T>*& p) {
	NODET<T>* f = p, * rp = p->Right;
	while (rp->Left != NULL)
	{
		f = rp;
		rp = rp->Left;
	}
	p->Data = rp->Data;
	if (rp == f->Right)f->Right = rp->Right;
	else f->Left = rp->Right;
	return rp;
}
template<class T>
int Remove_X(NODET<T>*& root, T X, int (*Compare)(T, T)) {
	if (!root)return 0;
	if (Compare(root->Data, X) > 0) Remove_X(root->Left, X);
	else if (Compare(root->Data, X) < 0) Remove_X(root->Right, X);
	else
	{
		if (root->Left == NULL)root = root->Right;
		else if (root->Right == NULL)root = root->Left;
		else
		{
			NODET<T>* P = root, * rp = FindReplace(P);
			delete rp;

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
int HighTree(NODET<T>* root) {
	if (root == NULL)return 0;
	int left = HighTree(root->Left);
	int right = HighTree(root->Right);
	return left > right ? 1 + left : 1 + right;
}
