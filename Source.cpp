#include<iostream>
#include <vector>
#include<algorithm>
using namespace std;

struct elem
{
	int value;
	elem* right;
	elem* left;
	elem(int value) {
		this->value = value;
		this->right = NULL;
		this->left = NULL;
	}
};

void prnt(elem* cur) {
	if (cur->left != NULL) {
		prnt(cur->left);
	}
	if (cur->right != NULL) {
		prnt(cur->right);
	}
	cout << cur->value << " ";
}

void add(elem* cur, int value) {
	if (cur == NULL) {
		cur = new elem(value);
	}

	if (cur->value < value) {
		add(cur->left, value);
	}
	else {
		add(cur->right, value);
	}
}

int main() {
	elem* head = new elem(10, 5);
	elem* prev = head;
	for (int i = 0; i < 10; i++) {
		prev->next = new elem(i);
		prev = prev->next;
	}
	bool found = false;
	prev = head;
	head.push_back()
	for (elem* start = head; start != NULL && !found; prev = start, start = start->next) {
		if (start->value == 3) {
			prev->next = start->next;
			delete start;
			found = true;
		}
	}


	for (elem* start = head; start != NULL; start = start->next) {
		cout << start->value << " ";
	}

	
	
}