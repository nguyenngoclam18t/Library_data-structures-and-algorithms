#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
template <class T>
struct NODEL
{
	T data;
	NODEL<T>* next;
};
template <class T>
struct SList
{
	NODEL<T>* head;
	NODEL<T>* tail;
};
//==========================================================================================================================//

template <class T>
void init_List(SList<T>& l)
{
	l.head = NULL;
	l.tail = NULL;
}
template <class T>
bool isEmpty(SList<T>l) {
	if (l.head == NULL)return true;
	return false;
}
template <class T>
NODEL<T>* Create_Node(T x)
{
	NODEL<T>* temp = new NODEL<T>;
	temp->data = x;
	temp->next = NULL;
	return temp;
}
template <class T>
void Add_Head(SList<T>& l, T x) {
	NODEL<T>* p = Create_Node<T>(x);
	if (isEmpty(l)) //dau trong thi gan thang
	{
		l.head = p;
		l.tail = p;
	}
	else {
		//gan nhu bth
		p->next = l.head;
		l.head = p;

	}
}
template <class T>
void Add_Tail(SList<T>& l, T x) {
	NODEL<T>* p = Create_Node<T>(x);
	if (isEmpty(l)) //dau trong thi gan thang
	{
		l.head = p;
		l.tail = p;
	}
	else {
		//gan nhu bth
		l.tail->next = p;
		l.tail = p;
	}
}
//xoa
template <class T>
void Remove_Head(SList<T>& l)
{
	if (isEmpty(l)) //list trong
	{
		return;
	}
	else {
		NODEL<T>* p = l.head;
		l.head = p->next;
		delete p;
	}
}
template <class T>
void Remove_Tail(SList<T>& l)
{
	if (isEmpty(l)) //list trong
	{
		return;
	}
	else {
		NODEL<T>* p = l.head;
		//cho chay den vi tri gan cuoi cua list
		for (; p != l.tail; p = p->next);
		l.tail = p;
		delete p->next;
		p->next = NULL;
	}
}
template <class T>
void Remove_MID(SList<T>& l, NODEL<T>* p)
{
	if (isEmpty(l)) //list trong
	{
		return;
	}
	NODEL<T>* q = p->next;
	if (q == l.tail)
	{
		Remove_Tail;
		return;
	}
	p->next = q->next;
	q->next = NULL;
	delete q;
}
