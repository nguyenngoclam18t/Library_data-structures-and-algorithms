#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
template<class T>
struct HashNode
{
	T data;
	HashNode* next;
};
//
template<class T>
HashNode<T>* CreateHashNode(T data) {
	HashNode<T>* New = new HashNode<T>;
	if (New == NULL)
		return NULL;
	New->data = data;
	New->next = NULL;
	return New;
}
int Max;
void InputMax(int max) {
	Max = max;	
}
#define MaxSize Max
template<class T>
void InitHashTable(HashNode<T>* Array[]) {
	for (int i = 0; i < MaxSize; i++)
	{
		Array[i] = NULL;
	}
}
int HashFunction(int key) {
	return key % MaxSize;
}
template<class T>
void Insert(HashNode<T>* Array[],  T data,int(*ConvertToInt)(T),int(*compare)(T,T)) {
	int key = HashFunction(ConvertToInt(data));
	HashNode<T>* temp = Array[key];
	if (temp == NULL)
		Array[key] = CreateHashNode(data);
	else
	{
		int flag = false;
		while (temp->next != NULL)
		{
			if (compare(temp->data, data) == 0) {
				flag = true;
				break;
			}
			temp = temp->next;
		}
		if (flag||compare(temp->data,data)==0)
			return;
		else temp->next = CreateHashNode(data);
	}
}
template<class T>
void Tranverse(HashNode<T>* Array[],void (*show)(T)) {
	for (int i = 0; i < MaxSize; i++)
	{
		if (Array[i] != NULL) {
			HashNode<T>* temp = Array[i];
			while (temp!=NULL)
			{
				show(temp->data);
				temp = temp->next;
			}
		}
	}
}
template<class T>
bool Remove(HashNode<T>* Array[], T data, int(*ConvertToInt)(T), int(*compare)(T, T)) {
	int key = HashFunction(ConvertToInt(data));
	HashNode<T>* child = Array[key];
	if (child == NULL) {
		return false;
	}
	else
	{
		HashNode<T>* Parent = child;
		bool flag = false;
		while (child!=NULL)
		{
			if (compare(child->data, data) == 0) {
				flag = true;
				break;
			}
			Parent = child;
			child = child->next;
		}
		if (flag) {
			if (child == Array[key]) {
				Array[key] = Array[key]->next;
			}
			else
			{
				Parent->next = child->next;
			}
			delete child;
			return true;
		}
		else
		{
			return false;
		}
	}
}
template<class T>
HashNode<T>* Find(HashNode<T>* Array[], T data, int(*ConvertToInt)(T), int(*compare)(T, T)) {
	int key = HashFunction(ConvertToInt(data));
	HashNode<T>* child = Array[key];
	if (child == NULL) {
		return NULL;
	}
	else
	{
		while (child != NULL)
		{
			if (compare(child->data, data) == 0) {
				return child;
			}
			child = child->next;
		}
		return NULL;
	}
}
template<class T>
void DeleteHash(HashNode<T>* Array[]) {
	for (int i = 0; i < MaxSize; i++)
	{
		if (Array[i] != NULL) {
			HashNode<T>* child = Array[i];
			while (child !=NULL)
			{
				HashNode<T>* Parent = child;
				child = child->next;
				delete Parent;
			}
			Array[i] = NULL;
		}
	}
}