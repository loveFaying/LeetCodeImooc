#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/// LinkedList 测试辅助函数

// 根据n个元素的数组arr创建一个链表, 并返回链表的头
ListNode* createLinkedList(int arr[], int n){

    if(n == 0)
        return NULL;

    ListNode* head = new ListNode(arr[0]);
    ListNode* curNode = head;
    for(int i = 1 ; i < n ; i ++){
        curNode->next = new ListNode(arr[i]);
        curNode = curNode->next;
    }

    return head;
}

// 打印以head为头结点的链表信息内容
void printLinkedList(ListNode* head){

    ListNode* curNode = head;
    while(curNode != NULL){
        cout << curNode->val << " -> ";
        curNode = curNode->next;
    }

    cout << "NULL" << endl;

    return;
}

// 释放以head为头结点的链表空间
void deleteLinkedList(ListNode* head){

    ListNode* curNode = head;
    while(curNode != NULL){
        ListNode* delNode = curNode;
        curNode = curNode->next;
        delete delNode;
    }

    return;
}

// 206. Reverse Linked List
// https://leetcode.com/problems/reverse-linked-list/description/
class Solution {
public:
    // 时间复杂度: O(n)
    // 空间复杂度: O(1)
    ListNode* reverseList(ListNode* head) {

        ListNode* pre = NULL;
        ListNode* cur = head;
        while(cur != NULL){
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }

        return pre;
    }


    // 递归的方式反转链表
    // 时间复杂度: O(n)
    // 空间复杂度: O(1)
    ListNode* reverseList2(ListNode* head) {

        // 递归终止条件
        if(head == NULL || head->next == NULL)
            return head;

        ListNode* rhead = reverseList(head->next);

        // head->next此刻指向head后面的链表的尾节点
        // head->next->next = head把head节点放在了尾部
        head->next->next = head;
        head->next = NULL;

        return rhead;
    }
};

int main() {

    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(int);

    ListNode* head = createLinkedList(arr, n);
    printLinkedList(head);
    ListNode* head2 = Solution().reverseList(head);
    printLinkedList(head2);
    deleteLinkedList(head2);

    head = createLinkedList(arr, n);
    printLinkedList(head);
    head2 = Solution().reverseList2(head);
    printLinkedList(head2);
    deleteLinkedList(head2);

    return 0;
}