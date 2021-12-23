#include <iostream>

using namespace std;

typedef struct Node
{
    int data;
    Node* next;
} Node;

int main()
{

    Node b = {-1, NULL};
    Node* root = &b;
    Node t = {1, NULL};
    root->next = &t;
    Node* cur = root->next;
    Node* c = NULL;
    for (int i = 0; i < 10; i++) {
        Node n = {i, NULL};
        if (i == 5) {
            c = &n;
        }
        else {
            cur->next = &n;
            cur = cur->next;
        }
    }
    // cur->next = c;

    Node *p, *q;
    p = root;
    q = p->next;
    while (p != q && q && q->next) {
        p = p->next;
        q = q->next->next;
    }
    if (p == q) {
        puts("have cycle!");
    } else {
        puts("no cycle!");
    }
    return 0;
}