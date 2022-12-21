#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int Max=0;
int ValueHash;
template<class T>
struct HashNode
{
	T data;
};
template<class T>
struct HashTable
{
	HashNode<T>** Hash;
};
//
void InputHashKey(int hashkey) {
	ValueHash = hashkey;
	Max = ValueHash;
}
bool* check;
#define MaxSize Max
template<class T>
void InitHashTable(HashTable<T>& Hash) {
	check = new bool[Max];
	for (int i = 0; i < Max; i++)
	{
		Hash.Hash[i] = NULL;
		check[i] = 0;
	}
}
template<class T>
void CreateHashTable(HashTable<T>& Hashtable) {
	Hashtable.Hash = new HashNode<T>*[Max];
	InitHashTable(Hashtable);
} 
template<class T>
HashNode<T>* CreateHashNode(T data) {
	HashNode<T>* New = new HashNode<T>;
	if (New == NULL)
		return NULL;
	New->data = data;
	return New;
}


int HashFunction(int key) {
	return key % ValueHash;
}
template<class T>
void upArray(HashTable<T>& Hash, int(*ConvertToInt)(T), int(*compare)(T, T), int(*P)(T)) {
	HashTable<T> temp;
	CreateHashTable(temp);
	for (int i = 0; i < Max; i++)
	{
		temp.Hash[i] = Hash.Hash[i];
	}
	int maxTemp = Max;
	Max *= 2;
	ValueHash = Max;
	CreateHashTable(Hash);
	for (int i = 0; i < maxTemp; i++)
	{
		if (temp.Hash[i] != NULL) {
			Insert(Hash, temp.Hash[i]->data, ConvertToInt, compare, P);
		}
	}
	
}
template<class T>
void Insert(HashTable<T>& Hash,  T data,int(*ConvertToInt)(T),int(*compare)(T,T),int(*P)(T)) {
	int key = HashFunction(ConvertToInt(data));
	HashNode<T>* temp =Hash.Hash[key];
	bool flag = true;
	int i = 1;
	int index = key;
	while (temp!=NULL)
	{
		if (compare(temp->data, data) == 0) {
			flag = false;
			break;
		}
		if (i >= Max / 2) {
			upArray(Hash,ConvertToInt,compare,P);
			i = 0;
		}
		index = HashFunction( HashFunction(ConvertToInt(data)) + P(i));
		temp = Hash.Hash[index];
		i++;
	}
	if (flag) {
		Hash.Hash[index] = CreateHashNode(data);
	}
		
}
template<class T>
void Tranverse(HashTable<T>& Hash,void (*show)(T)) {
	for (int i = 0; i < Max; i++)
	{
		printf("Bucket[%d]: ", i);
		if (Hash.Hash[i] != NULL) {
			
			HashNode<T>* temp = Hash.Hash[i];
			show(temp->data);
		}
		printf("\n");
	}
}
template<class T>
bool Remove(HashTable<T>& Hash, T data, int(*ConvertToInt)(T), int(*compare)(T, T), int(*P)(T)) {
	int key = HashFunction(ConvertToInt(data));
	HashNode<T>* temp = Hash.Hash[key];
	bool flag=false;
	if (temp == NULL) {
		return false;
	}
	int i = 1;
	int index = key;
	while (temp != NULL)
	{
		if (compare(temp->data, data) == 0) {
			flag = true;
			break;
		}
		index = HashFunction(key + P(i));
		temp = Hash.Hash[index];
		i++;
	}
	if (flag) {
		delete temp;
		Hash.Hash[index] = NULL;
		check[index] = 1;
		return true;
	}
	return false;
	
}
template<class T>
HashNode<T>* Find(HashTable<T> Hash, T data, int(*ConvertToInt)(T), int(*compare)(T, T), int(*P)(T)) {
	int key = HashFunction(ConvertToInt(data));
	HashNode<T>* temp = Hash.Hash[key];
	bool flag=false;
	if (temp == NULL&&check[key]==0) {
		return NULL;
	}
	int i = 1;
	int index = key;
	while (temp != NULL|| check[key] == 1)
	{
		if (check[index] != 1) {
			if (compare(temp->data, data) == 0) {
				flag = true;
				break;
			}
		}
		index = HashFunction(key + P(i));
		temp = Hash.Hash[index];
		i++;
	}
	if (flag)
		return temp;
	return NULL;
}
template<class T>
void DeleteHash(HashTable<T>& Hash) {
	for (int i = 0; i < MaxSize; i++)
	{
		if (Hash.Hash[i] != NULL) {
			HashNode<T>* child = Hash.Hash[i];
			delete child;
			Hash.Hash[i] = NULL;
		}
	}
}