#pragma once
#include <iostream>

using namespace std;

template <class T>
struct node 
{
	int key;
	T data;
	int height;
	node* left;
	node* right;
	node(int _key, T _data) {
		key = _key; 
		data = _data;
		left = right = 0; 
		height = 1; 
	}
};


template <class T>
class AvlTree {
	node<T>* data;

public:
	AvlTree(int _key, T _data) {
		data = new node<T>(_key, _data);
	}

	void Insert(int _key, T _data) {
		insert(data, _key, _data);
	}

	void Remove(int _key) {
		remove(data, _key);
	}

	int Find(int _key) {
		node<T>* res = find(data, _key);
		return res? res->data : NULL;
	}

	void Print() {
		print(data);
	}

protected:
	int height(node<T>* p)
	{
		return p ? p->height : 0;
	}

	int bfactor(node<T>* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node<T>* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node<T>* rotateright(node<T>* p)
	{
		node<T>* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	node<T>* rotateleft(node<T>* q)
	{
		node<T>* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node<T>* balance(node<T>* p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	}

	node<T>* findmin(node<T>* p)
	{
		return p->left ? findmin(p->left) : p;
	}

	node<T>* removemin(node<T>* p)
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	void print(node<T>* p) {
		if (!p) return;
		print(p->left);
		cout << p->key << ": " << p->data << endl;
		print(p->right);
	}

	node<T>* insert(node<T>* p, int _key, T _data) {
		if (!p)
			return new node<T>(_key, _data);
		if (_key < p->key)
			p->left = insert(p->left, _key, _data);
		else if (_key > p->key)
			p->right = insert(p->right, _key, _data);
		else return p;
		return balance(p);
	}

	node<T>* remove(node<T>* p, int _key) {
		if (p == nullptr) return 0;
		if (_key < p->key)
			p->left = remove(p->left, _key);
		else if (_key > p->key)
			p->right = remove(p->right, _key);
		else 
		{
			node<T>* q = p->left;
			node<T>* r = p->right;
			delete p;
			if (!r) return q;
			node<T>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	node<T>* find(node<T>* p, int _key) {
		if (!p) return NULL;
		if (_key < p->key) {
			if (p->left) node<T>* q = find(p->left, _key);
			else return NULL;
		}
		else if (_key > p->key) {
			if (p->right) node<T>* q = find(p->right, _key);
			else return NULL;
		}
		else return p;
	}
};