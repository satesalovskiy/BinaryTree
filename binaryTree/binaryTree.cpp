#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;
struct Node
{
	int x;
	Node *l;
	Node *r;
};
Node*startDiap;
//Очистка памяти
void delMem(Node*&Tree)
{
	if (Tree != NULL)
	{
		delMem(Tree->l);
		delMem(Tree->r);
		delete Tree;
		Tree = NULL;
	}
}
/*void show(Node *& Tree)
{

	if (Tree != NULL)
	{
		show(Tree->l);
		cout << Tree->x << "-";
		show(Tree->r);
	}

}*/
//Удаление всего
void node_clear(Node* tr) {
	if (tr != NULL) {
		node_clear(tr->l);
		node_clear(tr->r);
		delete tr;
	}
}
//Вывод на эран
void print_Tree(Node * p, int level)
{
	if (p)
	{
		print_Tree(p->l, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		cout << p->x << endl;
		print_Tree(p->r, level + 1);
	}
}
//Добавление элемента
void add_node(int x, Node*&MyTree)
{
	if (MyTree == NULL)
	{
		MyTree = new Node;
		MyTree->x = x;
		MyTree->l = MyTree->r = NULL;
	}
	if (x < MyTree->x)
	{
		if (MyTree->l != NULL)
			add_node(x, MyTree->l);
		else
		{
			MyTree->l = new Node;
			MyTree->l->l = MyTree->l->r = NULL;
			MyTree->l->x = x;
		}
	}
	if (x > MyTree->x)
	{
		if (MyTree->r != NULL)
			add_node(x, MyTree->r);
		else
		{
			MyTree->r = new Node;
			MyTree->r->l = MyTree->r->r = NULL;
			MyTree->r->x = x;
		}
	}
}
//Удаление элемента
Node* DeleteNode(Node* tree, int val) {
	if (tree == NULL)
		return tree;

	if (val == tree->x) {

		Node* tmp;
		if (tree->r == NULL)
			tmp = tree->l;
		else {

			Node* ptr = tree->r;
			if (ptr->l == NULL) {
				ptr->l = tree->l;
				tmp = ptr;
			}
			else {

				Node* pmin = ptr->l;
				while (pmin->l != NULL) {
					ptr = pmin;
					pmin = ptr->l;
				}
				ptr->l = pmin->r;
				pmin->l = tree->l;
				pmin->r = tree->r;
				tmp = pmin;
			}
		}

		delete tree;
		return tmp;
	}
	else if (val < tree->x)
		tree->l = DeleteNode(tree->l, val);
	else
		tree->r = DeleteNode(tree->r, val);
	return tree;
}
//Поиск элемента по значению
Node* find(Node *r, int d)
{
	if (r == NULL)
	{
		return NULL;  // не найден
	}
	if (r->x == d)
	{
		cout << "Элемент найден! ";
		startDiap = r;
		//cout << start << endl;
		return r; // нашли!!!
	}

	if (d <= r->x)
	{
		// left
		if (r->l != NULL)
			return find(r->l, d); // рекурсивный поиск влево
		else
		{
			return NULL; // не найден
		}
	}
	else
	{
		//right
		if (r->r)
			return find(r->r, d);// рекурсивный поиск вправо
		else
		{
			return NULL; // не найден
		}
	}
}
//Поиск в интервале
void range(int a, int b, Node*&tree)
{
	if ((a <= tree->x)&&(tree->x <= b))
	{

		cout << tree->x<<" ";

		if (tree->l != NULL)
			range(a, b, tree->l);

		if (tree->r != NULL) 
			range(a, b, tree->r);		
	}
	else
	{
		if (tree->x < a)
		{
			if (tree->r != NULL)
				range(a, b, tree->r);
		}
		else
		{
			if (tree->l != NULL)
				range(a, b, tree->l);
		}
	}
	//cout << "Ошибка" << endl;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int d;
	int n;
	int s;
	int a;
	int u;
	int j;
	int start, end;
	Node * Tree = NULL;	

	cout << "Введите количество элементов дерева" << endl;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		cin >> j;
		add_node(j, Tree);
			//add_node(rand() % 2000,Tree);
	}
	print_Tree(Tree, 0);
	//show(Tree);

	cout << "Какой элемент добавить?" << endl;
	cin >> a;
	add_node(a,Tree);
	print_Tree(Tree, 0);
	
	cout << "Какой элемент найти?" << endl;
	cin >> d;
	Tree = find(Tree, d);
	print_Tree(Tree, 0);

	cout << "Введите интервал" << endl;
	cin >> start >> end;

	cout << "Найдены значения:" << endl;
	range(start, end, Tree);
	cout << endl;

	cout << "Какой элемент удалить?" << endl;
	cin >> u;
	Tree = DeleteNode(Tree, u);
	//print_Tree(Tree, 0);

	cout << "Введите интервал" << endl;
	cin >> start >> end;

	cout << "Найдены значения:" << endl;
	range(start, end, Tree);

	delMem(Tree);
	_getwch();
	return 0;
}