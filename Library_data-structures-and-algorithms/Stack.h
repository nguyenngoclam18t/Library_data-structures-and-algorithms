#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
template <class T>
struct NODES
{
	T data;
	NODES<T>* next;
};
template <class T>
struct Stack
{
	NODES<T>* top;
};
template <class T>
void InitStack(Stack<T>& S) {
	S.top = NULL;
}
template <class T>
bool IsEmpty(Stack<T> S) {
	if (S.top == NULL)return true;
	return false;
}
template <class T>
NODES<T>* Create_Node(T x)
{
	NODES<T>* temp = new NODES<T>;
	temp->data = x;
	temp->next = NULL;
	return temp;
}
template <class T>
void Push(Stack<T>& S, T x) {
	NODES<T>* p = Create_Node<T>(x);
	if (IsEmpty(S)) {
		S.top = p;
	}
	else
	{
		p->next = S.top;
		S.top = p;
	}
}
template <class T>
NODES<T>* Pop(Stack<T>& S) {
	if (IsEmpty(S))return NULL;
	NODES<T>* temp = S.top;
	S.top = S.top->next;
	return temp;
}