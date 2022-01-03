#ifndef POINTLIST_HPP
#define POINTLIST_HPP 

#include "node.hpp"
#include <utility> // std::pair
#include <memory> // std::make_shared
#include <iostream>


class Pointlist
{
    public:
        Pointlist();
        void insert(double x, double y);
        std::shared_ptr<Node> query(double x);
        void free();
        void print();
        inline bool empty() { return tail_->next == head_; };
        int length();
    protected:
        Node* head_;
        Node* tail_;
    private:
        bool init_ = false;
};


#endif /* POINTLIST_HPP */
