#ifndef POINTLIST_HPP
#define POINTLIST_HPP 

#include "node.hpp"
#include <utility> // std::pair
#include <memory> // std::make_shared
#include <iostream>
#include <vector>


class Iterator {
	public:
		typedef Iterator self_type;
		typedef Node value_type;
		typedef Node& reference;
		typedef Node* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

		Iterator(pointer ptr) : ptr_(ptr) { } 
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


class Const_iterator {
	public:
		typedef Const_iterator self_type;
		typedef Node value_type;
		typedef Node& reference;
		typedef Node* pointer;

		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;
		Const_iterator(pointer ptr) : ptr_(ptr) { }
		self_type operator++() { self_type i = *this; ptr_ = ptr_->next; return i; }
		self_type operator++(int junk) { ptr_ = ptr_->next; return *this; }
		const reference operator*() { return *ptr_; }
		const pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

	private:
		pointer ptr_;
};



/**
 * @brief Stores and processes list of points (x, y) in ascending order
 */
class Pointlist {
	public:
		Pointlist();
		~Pointlist() { free(); }
		void insert(double x, double y);
		/**
		 * @brief Finds the first stored node with x smaller than the x in the query
		 *
		 * @param x A double
		 *
		 * @return A Node pointer whose ``prev'' member points to the first node
		 * with x smaller than the x in the query and its ``next'' member points
		 * to the first node with x larger than the x in the query.
		 */
		std::shared_ptr<Node> query(double x) const;
		/**
		 * @brief Delete all nodes from the list
		 */
		void free();
		// check whether points have been added - true if none added
		inline bool empty() const { return tail_->next == head_; };
		// get the length of the Pointlist object
		int size() const { return size_; }
		// iterator functionality - see iterator, Const_iterator classes above
		Iterator begin() { return Iterator(tail_->next); }
		Iterator end() { return Iterator(head_); }
		Const_iterator begin() const { return Const_iterator(tail_->next); }
		Const_iterator end() const { return Const_iterator(head_); }

	protected:
		Node* head_;
		Node* tail_;

	private:
		friend class Iterator; // has access to all (incl. private) members
		friend class Const_iterator;
		int size_ = 0;
};

#endif /* POINTLIST_HPP */
