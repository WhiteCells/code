#include <iostream>

using namespace std;

typedef struct LStack {
    int data;
    LStack* next;
}*LinkStack, Node;


void InitStack(LinkStack& s) {
    s = new Node;
    s->next = nullptr;
    s->data = 0;
}

bool PushStack(LinkStack& s, int e) {
    Node* new_node = new Node;
    if (!new_node) {
        return false;
    }
    new_node->data = e;
    new_node->next = s->next;
    s->next = new_node;
    return true;
}

bool PopStack(LinkStack& s, int& e) {
    if (!s->next) {
        return false;
    }
    Node* tmp = s->next;
    e = tmp->data;
    s->next = s->next->next;
    delete tmp;
    return true;
}

int TopStack(LinkStack& s) {
    if (!s->next) {
        return -1;
    }
    return s->next->data;
}

int main() {
    LinkStack s;
    InitStack(s);
    PushStack(s, 1);
    PushStack(s, 2);
    PushStack(s, 3);
    cout << TopStack(s) << '\n';
    int e = -1;
    PopStack(s, e);
    cout << e << '\n';
    cout << TopStack(s) << '\n';
    PopStack(s, e);
    cout << e << '\n';
    cout << TopStack(s) << '\n';
    PopStack(s, e);
    cout << e << '\n';
    cout << TopStack(s) << '\n';
    return 0;
}