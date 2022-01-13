#ifndef POINTLIST_HPP
#define POINTLIST_HPP 

#include "node.hpp"
#include <utility> // std::pair
#include <memory> // std::make_shared
#include <iostream>
#include <vector>

class iterator {
	public:
		typedef iterator self_type;
		typedef Node value_type;
		typedef Node& reference;
		typedef Node* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

		iterator(pointer ptr) : ptr_(ptr) { } 
		self_type operator++() {
			self_type i = *this; ptr_ = ptr_->next; return i;
		}
		self_type operator++(int junk) { ptr_ = ptr_->next; return *this; }
		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

	private:
		pointer ptr_;
};


class const_iterator {
	public:
		typedef const_iterator self_type;
		typedef Node value_type;
		typedef Node& reference;
		typedef Node* pointer;

		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;
		const_iterator(pointer ptr) : ptr_(ptr) { }
		self_type operator++() { self_type i = *this; ptr_ = ptr_->next; return i; }
		self_type operator++(int junk) { ptr_ = ptr_->next; return *this; }
		const reference operator*() { return *ptr_; }
		const pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

	private:
		pointer ptr_;
};



class Pointlist {
	public:
		Pointlist();
		void insert(double x, double y);
		std::shared_ptr<Node> query(double x) const;
		void free();
		void print();
		inline bool empty() const { return tail_->next == head_; };
		int size() const { return size_; }
		// iterator functionality - see iterator, const_iterator classes above
		iterator begin() { return iterator(tail_->next); }
		iterator end() { return iterator(head_); }
		const_iterator begin() const { return const_iterator(tail_->next); }
		const_iterator end() const { return const_iterator(head_); }

	protected:
		Node* head_;
		Node* tail_;

	private:
		friend class iterator;
		friend class const_iterator;
		int size_ = 0;
};

#endif /* POINTLIST_HPP */
