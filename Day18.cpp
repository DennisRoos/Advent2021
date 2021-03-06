#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;

int A[502][502];
int D[502][502];


class node {
public:
	node* left;
	node* right;
	node* parent;
	~node();
	bool pairleft;
	bool pairright;
	int l;
	int r;
};

node::~node() {
	if (pairleft) {
		delete left;
	}
	if (pairright) {
		delete right;
	}
}

int magnitude(node* n) {
	int le;
	int ri;
	if (n->pairleft) {
		le = magnitude(n->left);
	}
	else {
		le = n->l;
	}
	if (n->pairright) {
		ri = magnitude(n->right);
	}
	else {
		ri = n->r;
	}
	return (3 * le) + (2 * ri);
}

void Explodeleft(node* n, node* src, int v) {
	if (src == n->right) {//number we seek must be to the left
		if (!n->pairleft) {
			n->l += v;
		}
		else {
			n = n->left;
			while (n->pairright) {
				n = n->right;
			}
			n->r += v;
		}
	}
	else {
		if (n->parent != NULL) {
			Explodeleft(n->parent, n, v);
		}
	}
	return;
}


void Exploderight(node* n, node* src, int v) {
	if (src == n->left) {//number we seek must be to the right
		if (!n->pairright) {
			n->r += v;
		}
		else {
			n = n->right;
			while (n->pairleft) {
				n = n->left;
			}
			n->l += v;
		}
	}
	else {
		if (n->parent != NULL) {
			Exploderight(n->parent, n, v);
		}
	}
	return;
}

bool checkExplode(node* n, int d) {
	if (d == 3) {
		if (n->pairleft) {
			Explodeleft(n, n->left, n->left->l);
			Exploderight(n, n->left, n->left->r);
			n->pairleft = false;
			n->l = 0;
			delete n->left;
			n->left = NULL;
			return true;
		}
		else if (n->pairright) {
			Explodeleft(n, n->right, n->right->l);
			Exploderight(n, n->right, n->right->r);
			n->pairright = false;
			n->r = 0;
			delete n->right;
			n->right = NULL;
			return true;
		}
		return false;
	}
	bool b = false;
	if (n->pairleft) {
		b = checkExplode(n->left, d + 1);
	}
	if (!b && n->pairright) {
		b = checkExplode(n->right, d + 1);
	}
	return b;
}

bool split(node* n) {
	bool b = false;
	if (!n->pairleft) {
		if (n->l > 9) {
			node* m = new node();
			m->parent = n;
			n->pairleft = true;
			n->left = m;
			m->pairleft = false;
			m->pairright = false;
			m->l = n->l / 2;
			m->r = (n->l + 1) / 2;
			return true;
		}
	}
	else {
		b = split(n->left);
	}
	if (!b) {
		if (!n->pairright) {
			if (n->r > 9) {
				node* m = new node();
				m->parent = n;
				n->pairright = true;
				n->right = m;
				m->pairleft = false;
				m->pairright = false;
				m->l = n->r / 2;
				m->r = (n->r + 1) / 2;
				return true;
			}
		}
		else{
			return split(n->right);
		}
	}
	return b;
}

string s;
int i;

node* parse() {
	node* n = new node();
	if (s[i] == '[') {
		i++;
		n->left = parse();
		n->left->parent = n;
		n->pairleft = true;
	}
	else {
		int v = 0;
		while (s[i] != ',') {
			v *= 10;
			v += s[i] - '0';
			i++;
		}
		n->l = v;
	}
	i++;//skip past comma

	if (s[i] == '[') {
		i++;
		n->right = parse();
		n->right->parent = n;
		n->pairright = true;
	}
	else {
		int v = 0;
		while (s[i] != ']') {
			v *= 10;
			v += s[i] - '0';
			i++;
		}
		n->r = v;
	}
	i++;
	return n;

}

node* add(node* n1, node* n2) {
	node* n = new node();
	n->left = n1;
	n->right = n2;
	n->pairleft = true;
	n->pairright = true;
	n1->parent = n;
	n2->parent = n;
	return n;
}

void print(node* n) {
	cout << '[';
	if (n->pairleft) {
		print(n->left);
	}
	else {
		cout << n->l;
	}
	cout << ',';
	if (n->pairright) {
		print(n->right);
	}
	else {
		cout << n->r;
	}
	cout << ']';
}

void reduce(node* root) {
	bool b = true;
	while (b) {//reduce the sum as much as possible
		b = checkExplode(root, 0);
		if (!b) {
			b = split(root);
		}
	}
}

node* root;

vector<string> v;

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		infile >> s;
		i = 1;
		root = parse();
		v.push_back(s);
		while (infile >> s) {
			i = 1;
			node* m = parse();
			v.push_back(s);
			root = add(root, m);
			reduce(root);
			//print(root);
			//cout << endl;
		}
		//print(root);
		cout << "The magnitude of the total sum is " << magnitude(root) << endl;
		delete root;
		int best = 0;
		for (int a = 0; a < v.size(); a++) {//root is never deleted, so leaks memory with each pair (and the original sum)
			for (int b = 0; b < v.size(); b++) {
				if (a != b) {
					s = v[a];
					i = 1;
					node* n1 = parse();
					s = v[b];
					i = 1;
					node* n2 = parse();
					root = add(n1, n2);
					reduce(root);
					int mag = magnitude(root);
					if (mag > best) {
						best = mag;
					}
					delete root;
				}
			}
		}
		cout << "The best magnitude was " << best << endl;
	}
	return 0;
}
