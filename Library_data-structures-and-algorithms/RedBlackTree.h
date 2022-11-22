﻿#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <queue>
#include <stack>
#include <Windows.h>
using namespace std;
/* Khai báo thuộc tính color */
enum EColor { RED, BLACK };

/* Khai báo cấu trúc node */
template <class T>
struct BRTNode
{
	T Info;
	EColor Color;
	BRTNode<T>* Left, * Right, * Parent;
};

/* Khai báo cấu trúc cây Đỏ-Đen */
template <class T>
struct BRTree
{
	BRTNode<T>* Root;
};
//==================================================
//==================================================
template <class T>
BRTNode<T>* createBRTNode(T x)
{
	BRTNode<T>* p = new BRTNode<T>;
	if (p == NULL)
	{
		printf("\nKhong the cap phat nut moi!");
		_getch();
		return NULL;
	}
	p->Info = x;		// Gán dữ liệu mới cho nút
	p->Color = RED;		// Gán màu đỏ (Red) mặc định
	p->Left = NULL;		// Chưa có nút con trái
	p->Right = NULL;	// Chưa có nút con phải
	p->Parent = NULL;	// Chưa có nút cha
	return p;
}
//==================================================
void set_Color(int colorBackground, int colorText) {
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, colorBackground * 16 + colorText);
	/*	0 = Black       8 = Gray
	1 = Blue        9 = Light Blue
	2 = Green       A = Light Green
	3 = Aqua        B = Light Aqua
	4 = Red         C = Light Red
	5 = Purple      D = Light Purple
	6 = Yellow      E = Light Yellow
	7 = White       F = BRight White
	=> set_Color(X); -> X = a*16 + b, a (background) và b (character)
	*/
}
template <class T>
void showBRTNode(BRTNode<T>* p)
{
	if (p->Color == RED)
		set_Color(15, 12);	//Light Red=12 (C), BRight White=15 (F)
	else if (p->Color == BLACK)
		set_Color(15, 0);	//Black=0, BRight White=15 (F)
	_cprintf("%4d", p->Info);
	set_Color(14, 2);		//Light Yellow=14 (E), Green=2
}
//==================================================
/* Initalize BRTree */
template <class T>
void initBRTree(BRTree<T>& brt)
{
	brt.Root = NULL;
}

template <class T>
void NLR(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	show(root);
	showBRTree_InOrder(root->Left, show);
	showBRTree_InOrder(root->Right, show);
}
template <class T>
void NRL(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	show(root);
	showBRTree_InOrder(root->Right, show);
	showBRTree_InOrder(root->Left, show);
}
template <class T>
void LNR(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	showBRTree_InOrder(root->Left, show);
	show(root);
	showBRTree_InOrder(root->Right, show);
}
template <class T>
void RNL(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	showBRTree_InOrder(root->Right, show);
	show(root);
	showBRTree_InOrder(root->Left, show);
}
template <class T>
void LRN(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	showBRTree_InOrder(root->Left, show);
	showBRTree_InOrder(root->Right, show);
	show(root);
}
template <class T>
void RLN(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	showBRTree_InOrder(root->Right, show);
	showBRTree_InOrder(root->Left, show);
	show(root);
}

/* Hoán vị màu (Color) */
void swapColors(EColor& color1, EColor& color2)
{
	EColor temp = color1;
	color1 = color2;
	color2 = temp;
}

/* Hoán vị giá trị */
template <class T>
void swapInfos(T& Info1, T& Info2)
{
	T temp = Info1;
	Info1 = Info2;
	Info2 = temp;
}

/* Một hàm đệ quy để thực hiện việc duyệt thứ tự NLR - PreOrder */
template <class T>
void showBRTree_PreOrder(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	show(root); //printf("%4d", root->Info);
	showBRTree_PreOrder(root->Left, show);
	showBRTree_PreOrder(root->Right, show);
}

/* Một hàm đệ quy để thực hiện việc duyệt thứ tự LNR - InOrder */
template <class T>
void showBRTree_InOrder(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	showBRTree_InOrder(root->Left, show);
	show(root); //printf("%4d", root->Info);
	showBRTree_InOrder(root->Right, show);
}

/* Một hàm đệ quy để thực hiện việc duyệt thứ tự LRN - PostOrder */
template <class T>
void showBRTree_PostOrder(BRTNode<T>* root, void (*show)(BRTNode<T>*))
{
	if (root == NULL) return;

	showBRTree_PostOrder(root->Left, show);
	showBRTree_PostOrder(root->Right, show);
	show(root); //printf("%4d", root->Info);
}

/* Duyệt theo chiều rộng (Breadth-first search) */
template <class T>
void levelOrderL(BRTNode<T>* root, void (*show)(BRTNode<T>*)) {
	if (root == NULL) return;

	queue <BRTNode<T>*> q;
	q.push(root);

	while (!q.empty()) {
		BRTNode<T>* p;
		p = q.front();
		q.pop();
		show(p);
		if (p->Left != NULL)
			q.push(p->Left);
		if (p->Right != NULL)
			q.push(p->Right);
	}
}
template <class T>
void levelOrderR(BRTNode<T>* root, void (*show)(BRTNode<T>*)) {
	if (root == NULL) return;

	queue <BRTNode<T>*> q;
	q.push(root);

	while (!q.empty()) {
		BRTNode<T>* p;
		p = q.front();
		q.pop();
		show(p);
		if (p->Right != NULL)
			q.push(p->Right);
		if (p->Left != NULL)
			q.push(p->Left);
		
	}
}



/* insert BRTNode<T> */
template <class T>
BRTNode<T>* BRTInsert(BRTNode<T>* root, BRTNode<T>* pNew, int (*compare)(T, T))
{
	/* Nếu cây trống thì trả về một BRTNode<T> mới */
	if (root == NULL) return pNew;

	/* Nếu không thì tiếp tục duyệt xuống dưới cây */
	if (compare(pNew->Info , root->Info)<0)
	{
		root->Left = BRTInsert(root->Left, pNew,compare);
		root->Left->Parent = root;
	}
	else if (compare(pNew->Info, root->Info) > 0)
	{
		root->Right = BRTInsert(root->Right, pNew, compare);
		root->Right->Parent = root;
	}

	/* Trả về con trỏ BRTNode<T> */
	return root;
}

/* Thuật toán xoay trái */
template <class T>
void rotateLeft(BRTNode<T>*& root, BRTNode<T>*& p)
{
	BRTNode<T>* pRight = p->Right;

	p->Right = pRight->Left;

	if (p->Right != NULL)
		p->Right->Parent = p;

	pRight->Parent = p->Parent;

	if (p->Parent == NULL)
		root = pRight;

	else if (p == p->Parent->Left)
		p->Parent->Left = pRight;

	else
		p->Parent->Right = pRight;

	pRight->Left = p;
	p->Parent = pRight;
}

/* Thuật toán xoay phải */
template <class T>
void rotateRight(BRTNode<T>*& root, BRTNode<T>*& p)
{
	BRTNode<T>* pLeft = p->Left;

	p->Left = pLeft->Right;

	if (p->Left != NULL)
		p->Left->Parent = p;

	pLeft->Parent = p->Parent;

	if (p->Parent == NULL)
		root = pLeft;

	else if (p == p->Parent->Left)
		p->Parent->Left = pLeft;

	else
		p->Parent->Right = pLeft;

	pLeft->Right = p;
	p->Parent = pLeft;
}

/* Sửa lại cấu trúc khi chèn BRTNode<T> vào hoặc xóa node */
template <class T>
void fixViolation(BRTNode<T>*& root, BRTNode<T>*& pt)
{
	BRTNode<T>* pParent = NULL;
	BRTNode<T>* pGrandParent = NULL;

	while ((pt != root) && (pt->Color != BLACK) && (pt->Parent->Color == RED))
	{
		pParent = pt->Parent;
		pGrandParent = pt->Parent->Parent;

		/* Trường hợp A:
		node cha của pt là con trái của node cha của pt */
		if (pParent == pGrandParent->Left)
		{
			BRTNode<T>* pUncle = pGrandParent->Right;

			/* Trường hợp: 1
			node chú của pt là node đỏ khi này chỉ cần đổi màu cho node đó thành đen */
			if (pUncle != NULL && pUncle->Color == RED)
			{
				pGrandParent->Color = RED;
				pParent->Color = BLACK;
				pUncle->Color = BLACK;
				pt = pGrandParent;
			}

			else
			{
				/* Trường hợp: 2
				pt là node con phải của node cha nó ta thực hiện xoay trái */
				if (pt == pParent->Right)
				{
					rotateLeft(root, pParent);
					pt = pParent;
					pParent = pt->Parent;
				}

				/* Trường hợp: 3
				pt là con trái của node cha nó ta thực hiện xoay phải */
				rotateRight(root, pGrandParent);
				swapColors(pParent->Color, pGrandParent->Color);
				pt = pParent;
			}
		}

		/* Trường hợp: B
		node cha của pt là con phải của node cha của pt */
		else
		{
			BRTNode<T>* pUncle = pGrandParent->Left;

			/* Trường hợp: 1
			node chú của pt là node đỏ khi này chỉ cần đổi màu cho node đó thành đen */
			if ((pUncle != NULL) && (pUncle->Color == RED))
			{
				pGrandParent->Color = RED;
				pParent->Color = BLACK;
				pUncle->Color = BLACK;
				pt = pGrandParent;
			}
			else
			{
				/* Trường hợp: 2
				pt là con trái của node cha nó ta thực hiện xoay phải */
				if (pt == pParent->Left)
				{
					rotateRight(root, pParent);
					pt = pParent;
					pParent = pt->Parent;
				}

				/* Trường hợp: 3
				pt là node con phải của node cha nó -> nên thực hiện xoay trái */
				rotateLeft(root, pGrandParent);
				swapColors(pParent->Color, pGrandParent->Color);
				pt = pParent;
			}
		}
	}

	root->Color = BLACK;
}

/* Chèn một node mới với dữ liệu đã cho */
template <class T>
void insert(BRTNode<T>*& root, T Info,int (*compare)(T,T))
{
	BRTNode<T>* pNew = createBRTNode(Info);

	/* Thực hiện chèn như bình thường */
	root = BRTInsert(root, pNew,compare);

	/* Sửa lại lỗi của quy tắc cây đỏ đen */
	fixViolation(root, pNew);
}

/* Kiểm tra xem node hiện tại có phải là node con trái của node cha không */
template <class T>
bool isOnLeft(BRTNode<T>* p)
{
	return p == p->Parent->Left;
}

/* Trả về con trỏ tới node chú (Uncle) */
template <class T>
BRTNode<T>* findUncle(BRTNode<T>* p) {
	// Nếu không có node cha hoặc node ông, thì không có node chú
	if (p->Parent == NULL || p->Parent->Parent == NULL)
		return NULL;

	if (isOnLeft(p->Parent))
		// node chú bên phải
		return p->Parent->Parent->Right;
	else
		// node chú bên trái
		return p->Parent->Parent->Left;
}

/* Trả về con trỏ cho node anh chị em */
template <class T>
BRTNode<T>* findSibling(BRTNode<T>* p) {
	// node anh rỗng nếu không tồn tại node cha 
	if (p->Parent == NULL)
		return NULL;

	if (isOnLeft(p))
		return p->Parent->Right;
	else
		return p->Parent->Left;
}

/* Tìm nút không có nút con bên trái trong cây con của nút đã cho */
template <class T>
BRTNode<T>* findSuccessor(BRTNode<T>* p) {
	BRTNode<T>* temp = p;

	while (temp->Left != NULL)
		temp = temp->Left;

	return temp;
}

/* Kiểm tra có node hiện tại có node con là nút đỏ hay không */
template <class T>
bool hasRedChild(BRTNode<T>* p) {
	return (p->Left != NULL && p->Left->Color == RED) ||
		(p->Right != NULL && p->Right->Color == RED);
}

/* Tìm nút thay thế nút đã xóa trong BST */
template <class T>
BRTNode<T>* BSTReplace(BRTNode<T>* p) {
	// Khi nút có 2 con
	if (p->Left != NULL && p->Right != NULL)
		return findSuccessor(p->Right);

	// Khi node lá 
	if (p->Left == NULL && p->Right == NULL)
		return NULL;

	// Khi node có một con
	if (p->Left != NULL)
		return p->Left;
	else
		return p->Right;
}

/* Xóa nút đã cho */
template <class T>
void deleteNode(BRTNode<T>*& root, BRTNode<T>* pDelete) {
	BRTNode<T>* pReplace = BSTReplace(pDelete);

	// Đúng khi pReplace và pDelete đều đen
	bool flagDoubleBlack = ((pReplace == NULL || pReplace->Color == BLACK) && (pDelete->Color == BLACK));
	BRTNode<T>* pParent = pDelete->Parent;

	if (pReplace == NULL) {
		// pReplace là NULL do đó pDelete là lá 
		if (pDelete == root) {
			// pDelete là root, làm cho root là NULL 
			root = NULL;
		}
		else {
			if (flagDoubleBlack) {
				// pReplace và pDelete đều đen
				// pDelete là lá, sửa màu đen kép tại pDelete 
				fixDoubleBlack(root, pDelete);
			}
			else {
				// pReplace hoặc pDelete là đỏ
				if (findSibling(pDelete) != NULL)
					// node anh chị em không rỗng, làm cho nó màu đỏ 
					findSibling(pDelete)->Color = RED;
			}

			// Xóa pDelete khỏi cây 
			if (isOnLeft(pDelete)) {
				pParent->Left = NULL;
			}
			else {
				pParent->Right = NULL;
			}
		}
		delete pDelete;
		return;
	}

	if (pDelete->Left == NULL || pDelete->Right == NULL) {
		// pDelete có 1 node con
		if (pDelete == root) {
			// pDelete là gốc, gán giá trị của pReplace cho pDelete và xóa pReplace 
			pDelete->Info = pReplace->Info;
			pDelete->Left = pDelete->Right = NULL;
			delete pReplace;
		}
		else {
			// Tách node pDelete khỏi cây và di chuyển node pReplace lên
			if (isOnLeft(pDelete)) {
				pParent->Left = pReplace;
			}
			else {
				pParent->Right = pReplace;
			}
			delete pDelete;
			pReplace->Parent = pParent;
			if (flagDoubleBlack) {
				// pReplace và pDelete đều đen, sửa hai màu đen ở pReplace 
				fixDoubleBlack(root, pReplace);
			}
			else {
				// pReplace hoặc pDelete đỏ, màu pReplace đen 
				pReplace->Color = BLACK;
			}
		}
		return;
	}

	// pDelete có 2 con, hoán đổi giá trị với nút kế nhiệm (thế mạng) và đệ quy 
	swapInfos(pReplace->Info, pDelete->Info);
	deleteNode(root, pReplace);
}
template <class T>
void fixDoubleBlack(BRTNode<T>*& root, BRTNode<T>* p) {
	// p là node gốc thì return
	if (p == root) return;

	BRTNode<T>* pSibling = findSibling(p);
	BRTNode<T>* pParent = p->Parent;
	if (pSibling == NULL) {
		// Không có sibiling, màu đen kép được đẩy lên 
		fixDoubleBlack(root, pParent);
	}
	else {
		if (pSibling->Color == RED) {
			// Anh chị em màu đỏ 
			pParent->Color = RED;
			pSibling->Color = BLACK;
			if (isOnLeft(pSibling)) {
				// trường hợp Left 
				rotateRight(root, pParent);
			}
			else {
				// trường hợp Right 
				rotateLeft(root, pParent);
			}
			fixDoubleBlack(root, p);
		}
		else {
			// Anh chị em đen 
			if (hasRedChild(pSibling)) {
				// Ist nhất 1 trẻ em màu đỏ 
				if (pSibling->Left != NULL && pSibling->Left->Color == RED) {
					if (isOnLeft(pSibling)) {
						// Left Left 
						pSibling->Left->Color = pSibling->Color;
						pSibling->Color = pParent->Color;
						rotateRight(root, pParent);
					}
					else {
						// Right Left 
						pSibling->Left->Color = pParent->Color;
						rotateRight(root, pSibling);
						rotateLeft(root, pParent);
					}
				}
				else {
					if (isOnLeft(pSibling)) {
						// Left Right 
						pSibling->Right->Color = pParent->Color;
						rotateLeft(root, pSibling);
						rotateRight(root, pParent);
					}
					else {
						// Right Right 
						pSibling->Right->Color = pSibling->Color;
						pSibling->Color = pParent->Color;
						rotateLeft(root, pParent);
					}
				}
				pParent->Color = BLACK;
			}
			else {
				// Hai con đen 
				pSibling->Color = RED;
				if (pParent->Color == BLACK)
					fixDoubleBlack(root, pParent);
				else
					pParent->Color = BLACK;
			}
		}
	}
}

/* Tìm kiếm một giá trị trên cây */
template <class T>
BRTNode<T>* search(BRTNode<T>* root, T x) {
	BRTNode<T>* temp = root;
	while (temp != NULL) {
		if (x == temp->Info) {
			return temp;
		}
		else if (x < temp->Info) {
			temp = temp->Left;
		}
		else {
			temp = temp->Right;
		}
	}

	return NULL; //Không tìm thấy x trong cây
}

/* chức năng tiện ích xóa nút có giá trị nhất định */
template <class T>
BRTNode<T>* search(BRTNode<T>* root, T x,int(*compare)(T, T)) {
	BRTNode<T>* temp = root;
	while (temp != NULL) {
		if (compare(x,temp->Info)==0) {
			return temp;
		}
		else if (compare( temp->Info,x)>0) {
			temp = temp->Left;
		}
		else {
			temp = temp->Right;
		}
	}

	return NULL; //Không tìm thấy x trong cây
}
template <class T>
void deleteByInfo(BRTNode<T>*& root, T x,int (*compare)(T,T)) {
	// BRTree là rỗng 
	if (root == NULL) return;

	BRTNode<T>* delete_pt = search(root,x,compare);

	if (delete_pt == NULL) {
		printf("\nKhong tim thay nut nao de xoa voi gia tri");
		return;
	}
	else
	{
		printf("\nxoa thanh cong");
	}

	deleteNode(root, delete_pt);
}
//==================================================
template<class T>
BRTNode<T>* findBRTNode(BRTNode<T>* root, const T x,int(*compare)(T,T))
{
	if (root == NULL)
	{
		return NULL;
	}
	else
	{
		if (compare(root->Info , x)<0)
		{
			return findBRTNode(root->Right, x,compare);
		}
		else
		{
			if (compare(root->Info, x) > 0)
			{
				return findBRTNode(root->Left, x, compare);
			}
			else
			{
				if (compare(root->Info, x) == 0)
				{
					return root;
				}
			}
		}
	}
}