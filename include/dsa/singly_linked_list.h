// Singly Linked List.

#pragma once

struct ListNode {
    int       val;
    ListNode* next;

    ListNode()
        : val(0)
        , next(nullptr) {}

    ListNode(int x)
        : val(x)
        , next(nullptr) {}

    ListNode(int x, ListNode* ptr)
        : val(x)
        , next(ptr) {}
};
