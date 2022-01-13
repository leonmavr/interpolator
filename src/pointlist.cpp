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
    // initialise head_ and tail_
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
     * After:
     *                       +---->new_node     <--+
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
    Node* new_node = new Node;
    new_node->xy.first = x;
    new_node->xy.second = y;
    if (size_ == 0) [[unlikely]] {
        head_->prev = new_node;
        tail_->next = new_node;
        new_node->next = head_;
        new_node->prev = tail_;
    } else [[likely]] {
        auto curr = tail_->next;
        for (;
                (x > curr->xy.first) && (curr != head_);
                curr = curr->next);
        new_node->prev = curr->prev;
        new_node->next = curr;
        curr->prev->next = new_node;
        curr->prev = new_node;
    }
    size_++;
};


std::shared_ptr<Node> Pointlist::query(double x) const {
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
    if (size_ == 0) [[unlikely]] {
        auto curr = tail_->next;
        tail_->next = head_;
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
        delete curr;
    }
    delete head_;
    delete tail_;
};
