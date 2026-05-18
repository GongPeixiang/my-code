#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int val): data(val), next(nullptr) {}
};

using List = Node*;

int node2idx(const List &head, Node *node) {
    Node *cur = head;
    int idx = 0;
    while(cur != nullptr) {
        if (cur == node) 
            return idx;
        idx++;
        cur = cur->next;
    }
    return -1;
}

Node *idx2node(const List &head, int idx) {
    if (idx < 0) 
        return nullptr;
    Node *cur = head;
    for (int i = 0; i < idx && cur != nullptr; i++) {
        cur = cur->next;
    }
    return cur;
}

bool insertnext(Node *node, int data) {
    if (node == nullptr) 
        return false;
    Node *newnode = new Node(data);
    newnode->next = node->next;
    node->next = newnode;
    return true;
}

bool insertbefore(List &head, Node *node, int data) {
    if (node == nullptr) 
        return false;
    if (node == head) {
        Node *newnode = new Node(data);
        newnode->next = head;
        head = newnode;
        return true;
    }
    Node *cur = head;
    while (cur != nullptr && cur->next != node) {
        cur = cur->next;
    }
    if (cur != nullptr) {
        Node *newnode = new Node(data);
        cur->next = newnode;
        newnode->next = node;
        return true;
    }
    return false;
}

bool deletenext(Node *node) {
    if (node == nullptr || node->next == nullptr) 
        return false;
    Node *next = node->next;
    node->next = next->next;
    delete next;
    return true;
}

bool deletecurrent(List &head, Node *node) {
    if (head == nullptr || node == nullptr) 
        return false;
    if (head == node) {
        head = head->next;
        delete node;
        return true;
    }
    Node *cur = head;
    while (cur != nullptr && cur->next != node) {
        cur = cur->next;
    }
    if (cur != nullptr) {
        cur->next = node->next;
        delete node;
        return true;
    }
    return false;
}

void clearlist(List &head) {
    Node *cur = head;
    while (cur != nullptr) {
        Node *temp = cur;
        cur = cur->next;
        delete temp;
    }
    head = nullptr;
}

List reverse(List head) {
    List newlist = nullptr;
    List cur = head;
    while (cur != nullptr) {
       Node *newnode = new Node(cur->data);
       newnode->next = newlist;
       newlist = newnode;
       cur = cur->next;
    }
    return newlist;
}

/*
List merge(List &a, List &b) {
    Node* cur = a;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = b;
    return a;
}
但这样是浅拷贝,会影响a,下面用深拷贝写一个
*/

List deepcopy(const List &a) {
    List newlist = new Node(a->data);
    Node *node = newlist;
    Node *cur = a->next;
    while (cur != nullptr) {
        node->next = new Node(cur->data);
        node = node->next;
        cur = cur->next;
    }
    return newlist;
}

List merge(List &a, List &b) {
    List temp_a = deepcopy(a);
    List temp_b = deepcopy(b);
    Node *cur = temp_a;
    while (cur->next != nullptr) 
        cur = cur->next;
    cur->next = temp_b;
    return temp_a;
}

bool hasCycle(const List &head) {
    if (head == nullptr || head->next == nullptr) 
        return false;
    Node *slow = head;
    Node *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) 
            return true;
    }
    return false;
}

int cyclepos(const List &head) {
    if (head == nullptr || head->next == nullptr) 
        return -1;
    Node *slow = head;
    Node *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            Node *ptr = head;
            int cnt = 0;
            while (slow != ptr) {
                cnt++;
                slow = slow->next;
                ptr = ptr->next;
            }
            return cnt;
        }
    }
    return -1;
}

Node *getIntersection (List head_a, List head_b) {
    if (head_a == nullptr || head_b == nullptr) 
        return nullptr;
    Node *a = head_a, *b = head_b;
    while (a != b) {
        a = (a == nullptr) ? head_b : a->next;
        b = (b == nullptr) ? head_a : b->next;
    }
    return a;
}
