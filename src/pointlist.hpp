#ifndef POINTLIST_HPP
#define POINTLIST_HPP 

#include "node.hpp"
#include <utility> // std::pair
#include <memory> // std::make_shared
#include <iostream>
#include <vector>


class Pointlist
{
    public:
        Pointlist();
        void insert(double x, double y);
        std::shared_ptr<Node> query(double x) const;
        void free();
        void print();
        inline bool empty() const { return tail_->next == head_; };
        int size() const { return size_; }
        std::vector<Point> data() const;
    protected:
        Node* head_;
        Node* tail_;
    private:
        int size_ = 0;
};


#endif /* POINTLIST_HPP */
