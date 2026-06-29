#include<bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int val): data(val), next(nullptr) {}
};
using List = Node*;

// 删除倒数第n个节点
List remove_Nth_end(List &head, int n) {
    if (!head) return nullptr;
    
    // 使用虚拟头节点简化边界处理
    Node *dummy = new Node(0);
    dummy->next = head;
    Node *fast = dummy, *slow = dummy;
    for (int i = 0; i < n; i++) {
        if (fast->next == nullptr) {
            delete dummy;
            return head;
        }
        fast = fast->next;
    }
    
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    
    Node *temp = slow->next;
    slow->next = temp->next;
    delete temp;
    List newHead = dummy->next;
    delete dummy;
    return newHead;
}