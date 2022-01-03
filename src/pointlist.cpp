#include "node.hpp" 
#include "pointlist.hpp" 
#include <utility> // std::pair
#include <memory> // std::make_shared
#include <iostream>


Pointlist::Pointlist() {
    // allocate head_ and tail_
    head_ = new Node;
    head_->next = nullptr;
    head_->prev = new Node;
    tail_ = new Node;
    tail_->next = new Node;
    tail_->prev = nullptr;
    // init_ialise head_ and tail_
    head_->prev= tail_;
    tail_->next = head_;
}

void Pointlist::insert(double x, double y) {
    /* Create a new node with (x,y) and link it as follows:
     * Before:
     *      curr->prev   <--+     +-----> curr 
     *      +-----------+   |     |      +-----------+
     *      |Node* next |---|-----+      |Node* next |---> 
     *  <---|Node* prev |   +------------|Node* prev |
     *      |double x, y|                |double x, y|
     *      +-----------+                +-----------+
     *
     *  After:
     *                       +---->newnode      <--+
     *                       |     +-----------+   |
     *                       |     |Node* next |---|--+
     *                       |  +--|Node* prev |   |  |
     *                       |  |  |double x, y|   |  |
     *                       |  |  +-----------+   |  |
     *                       |  |                  |  |
     *                       |  |                  |  |
     *      curr->prev       |  |                  |  +--> curr 
     *      +-----------+    |  |                  |      +-----------+
     *      |Node* next |----+  |                  |      |Node* next |---> 
     *  <---|Node* prev |<------+                  +------|Node* prev |
     *      |double x, y|                                 |double x, y|
     *      +-----------+                                 +-----------+
     */
    Node* newnode = new Node;
    newnode->xy.first = x;
    newnode->xy.second = y;
    if (!init_) [[unlikely]] {
        head_->prev = newnode;
        tail_->next = newnode;
        newnode->next = head_;
        newnode->prev = tail_;
        init_ = true;
    } else [[likely]] {
        auto curr = tail_->next;
        for (;
                (x > curr->xy.first) && (curr != head_);
                curr = curr->next);
        newnode->prev = curr->prev;
        newnode->next = curr;
        curr->prev->next = newnode;
        curr->prev = newnode;
    }
};

std::shared_ptr<Node> Pointlist::query(double x) {
    auto curr = tail_->next;
    for (;
            (x > curr->xy.first) && (curr->next != nullptr);
            curr = curr->next);

    auto ret = std::make_shared<Node>();
    ret->prev = curr->prev;
    ret->next = curr;
    return ret;
}


void Pointlist::free() {
    int len = length();
    if (len == 2) [[unlikely]] {
        auto curr = tail_->next;
        tail_->next = head_;
        std::cout << "l2" << std::endl;
        head_->prev = tail_;
        delete curr;
        curr = nullptr;
    } else [[likely]] {
        auto curr = tail_->next;
        while (curr->next != head_) {
            curr = curr->next;
            delete curr->prev;
            curr->prev = nullptr;
        }
    }
    delete head_;
    delete tail_;
};

void Pointlist::print() {
    auto curr = tail_->next;
    while (curr->next != nullptr) {
        std::cout << "(" << curr->xy.first << ", " << curr->xy.second << ")" << ", ";
        curr = curr->next;
    }
    std::cout << std::endl;
}


int Pointlist::length() {
    int i = 0;
    for (auto curr = tail_->next;
            (curr != head_);
            curr = curr->next, i++);
    return i; 
}


