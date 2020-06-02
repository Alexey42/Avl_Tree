﻿#include <iostream>
#include "AvlTree.h"

using namespace std;

void main()
{
	AvlTree<int> t(1, 7);
	t.Insert(2, 11);
	t.Insert(0, 1);
	t.Insert(7, 5);
	t.Insert(3, 6);

	t.Print();
	cout << endl;

	t.Remove(3);

	t.Print();
	cout << endl;

	cout << t.Find(7) << endl;

    system("pause");
}
