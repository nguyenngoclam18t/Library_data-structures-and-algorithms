#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
template<class T>
struct AVLNode
{
	T data;
	int balfactor;
	AVLNode<T>* left, * right;
};
template<class T>
struct AVLTree
{
	AVLNode<T>* root;
};
//
template<class T>
void InitAVLTree(AVLTree<T>& tree) {
	tree.root = NULL;
}
template<class T>
int hightree(AVLNode<T>* root) {
	if (!root)
		return 0;
	int left = hightree(root->left);
	int right = hightree(root->right);
	return  1+(left > right ? left : right);
}
template<class T>
int GetBalfactor(AVLNode<T>* root) {
	return hightree(root->right) - hightree(root->left);
}
template<class T>
AVLNode<T>* Create_AVLNode(T data) {
	AVLNode<T>* temp = new AVLNode<T>;
	if (temp == NULL)
		return NULL;
	temp->data = data;
	temp->left = temp->right = NULL;
	temp->balfactor = 0;
}
template<class T>
bool Insert_AVLNode(AVLNode<T>*& root, T data,int(*compare)(T,T)) {
	if (root == NULL) {
		root = Create_AVLNode(data);
		return true;
	}
	bool getvalue;
	if (compare(root->data, data) == 0)
		getvalue = false;
	else if (compare(root->data, data) > 0)
		getvalue = Insert_AVLNode(root->left, data, compare);
	else
		getvalue = Insert_AVLNode(root->right, data, compare);
	Balfactor(root);
	return getvalue;
}
template<class T>
void RotateRight(AVLNode<T>*& root) {
	if (root == NULL)return;
	AVLNode<T>* Left = root->left;
	root->left = Left->right;
	Left->right = root;
	root->balfactor = GetBalfactor(root);
	Left->balfactor = GetBalfactor(Left);
	root = Left;
}
template<class T>
void RotateLeft(AVLNode<T>*& root) {
	if (root == NULL)return;
	AVLNode<T>* Right = root->right;
	root->right = Right->left;
	Right->left = root;
	root->balfactor = GetBalfactor(root);
	Right->balfactor = GetBalfactor(Right);
	root = Right;
}
template<class T>
void Balfactor(AVLNode<T>*& root) {
	root->balfactor = GetBalfactor(root);
	if (root->balfactor < -1) {
		if (root->left->balfactor <= 0)
			RotateRight(root);
		else
		{
			RotateLeft(root->left);
			RotateRight(root);
		}
	}
	else if (root->balfactor > 1) {
		if (root->right->balfactor >= 0)
			RotateLeft(root);
		else
		{
			RotateRight(root->right);
			RotateLeft(root);
		}
	}
}
template<class T>
bool RemoveNode(AVLNode<T>*& root, T data, int (*compare)(T, T)) {
	if (!root)
		return false;
	bool getvalue;
	if (compare(root->data, data) > 0)
		getvalue= RemoveNode(root->left, data, compare);
	else if(compare(root->data,data)<0)
		getvalue = RemoveNode(root->right, data, compare);
	else
	{
		if (root->left == NULL && root->right == NULL)
			root = NULL;
		else if (root->left == NULL)
			root = root->right;
		else if (root->right == NULL)
			root = root->left;
		else
		{
			AVLNode<T>* p = FindNodereplace(root);
			delete p;
		}
		getvalue = true;
	}
	return getvalue;
}
template<class T>
AVLNode<T>* FindNodereplace(AVLNode<T>*& root) {
	AVLNode<T>* child = root->right, * parent = root;
	while (child->left!=NULL)
	{
		parent = child;
		child = child->left;
	}
	root->data = child->data;
	if (root == parent)
		parent->right = child->right;
	else
		parent->left = child->right;
	return child;
}
template<class T>
void NLR(AVLNode<T>* root, void(*show)(T)) {
	if (!root)
		return;
	show(root->data);
	NLR(root->left);
	NLR(root->right);
}