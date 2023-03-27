#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add or remove methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * Although, it may be more difficult to do so. Your choice!
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom !
 */
namespace CPSC131
{
	/**
	 * Namespace to hold all things related to our DLL
	 */
	namespace DoublyLinkedList
	{
		/**
		 * Node class, which our DLL will use
		 * 
		 * The Professor realizes he could have made this an inline class (like the Iterator),
		 * but he is lazy.
		 */
		template <class T>
		class Node
		{
			public:
				
				/// CTORS
				Node() : prev_(nullptr), next_(nullptr) {}
				Node(T element) {}
				Node(T element, Node* prev, Node* next) {}
				
				/// Set the pointer to the previous element
				void setPrevious(Node* prev) { this->prev_ = prev; }
				
				/// Set the pointer to the previous element
				void setPrev(Node* prev) {}
				
				/// Get a pointer to the previous element
				Node* getPrevious() { return nullptr; }
				
				/// Get a pointer to the previous element
				Node* getPrev() { return nullptr; }
				
				/// Set the pointer to the next node
				void setNext(Node* next) {}
				
				/// Get a pointer to the next node
				Node* getNext() { return nullptr; }
				
				/// Set the element this node holds
				void setElement(T element) {}
				
				/// Get the element this node holds
				T& getElement() {}
				
				/// Return a reference to the element
				T& operator*() {}
				
			private:
				T element_;
				Node* prev_;
				Node* next_;
		};
		
		/**
		 * Implement our DoublyLinkedList class !
		 */
		template <class T>
		class DoublyLinkedList
		{
			public:
				
				/**
				 * Nested Iterator class.
				 * This allows user code to refer to the Iterator's type as:
				 * 
				 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
				 * 
				 * (as opposed to specifying the template argument two times)
				 */
				class Iterator
				{
					public:
						
						///	Constructor taking a head and tail pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail) : head_(head), tail_(tail)
						{
							this->cursor_ = this->end();
						}
						
						///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail, Node<T>* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
						
						///	Get a pointer to the head node, or end() if this list is empty
						Node<T>* begin()
						{
							if (head_ == nullptr){
								return this->end();
							}
							return this->head_;
						}
						
						///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
						Node<T>* end()
						{
							return nullptr;
						}
						
						///	Get the node to which this iterator is currently pointing
						Node<T>* getCursor()
						{
							return this->cursor_;
						}
						
						/**
						 * Assignment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator=(const Iterator& other)
						{
							this->head_ = other.head_;
							this->cursor_ = other.cursor_;
							this->tail_ = other.tail_;
							return *this;
						}
						
						///	Comparison operator
						bool operator==(const Iterator& other)
						{
							if (
								this->head_ == other.head_ &&
								this->cursor_ == other.cursor_ &&
								this->tail_ == other.tail_
							)
							{
								return true;
							}
							return false;
						}
						///	Inequality comparison operator
						bool operator!=(const Iterator& other)
						{
							
							return !(*this == other);
						}
						
						/**
						 * Prefix increment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator++()
						{
							cursor_ = cursor_->getNext();
							return *this;
						}
						
						/**
						 * Postfix increment
						 * Return a copy of this Iterator, BEFORE it was modified
						 */
						Iterator operator++(int)
						{
							Iterator temp = *this;
							cursor_ = cursor_->getNext();
							return temp;
						}
						
						/**
						 * Prefix decrement operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator--()
						{
							cursor_ = cursor_->getPrev();
							return *this;
						}
						
						/**
						 * Postfix decrement operator
						 * Return a copy of this Iterator BEFORE it was modified
						 */
						Iterator operator--(int)
						{
							Iterator temp = *this;
							this->cursor_ = cursor_->getPrev();
							return temp;
						}
						
						/**
						 * AdditionAssignment operator
						 * Return a copy of the current iterator, after modification
						*/
						Iterator operator +=(size_t add)
						{
							for (size_t i = 0; i != add; i++){
								if (cursor_->getNext() == nullptr){
									return *this;
								}
								cursor_ = cursor_->getNext();
							}
							return *this;
						}
						/**
						 * SubtractionAssignment operator
						 * Return a copy of the current iterator, after modification
						 */
						Iterator operator -=(size_t add)
						{
							for (size_t i = 0; i < add; i++){
								this->cursor_ = cursor_->getPrev();
							}
							return *this;
						}
						
						/**
						 * AdditionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator +=(int add)
						{
							while (add != 0) {
								if (cursor_ == nullptr) { return *this; }
								cursor_ = cursor_->getNext();
								--add;
							}
							return *this;
						}
						
						/**
						 * SubtractionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator -=(int subtract)
						{
							for (int i = 0; i < subtract; i++){
								this->cursor_ = cursor_->getPrev();
							}
							return *this;	
						}
						
						/**
						 * Dereference operator returns a reference to the ELEMENT contained with the current node
						 */
						T& operator*()
						{
							return cursor_->getElement();
						}
					
					private:
						
						/// Pointer to the head node
						Node<T>* head_ = nullptr;
						
						/// Pointer to the tail node
						Node<T>* tail_ = nullptr;
						
						/**
						 * Pointer to the cursor node.
						 * This is only one way of letting the iterator traverse the linked list.
						 * You can change to a different method if you wish (and can still pass unit tests)
						 */
						Node<T>* cursor_ = nullptr;
						
					
					friend class DoublyLinkedList;
				};
				
				/// Your welcome
				DoublyLinkedList()
				{
					this->head_ = nullptr;
					this->tail_ = nullptr;
					this->size_ = 0;
				}
				
				///	Copy Constructor
				DoublyLinkedList(DoublyLinkedList& other)
				{
					this->head_ = other.head();
					this->tail_ = other.tail();
					this->size_ = other.size();
				}
				
				/// DTOR: Your welcome
				~DoublyLinkedList()
				{
					this->clear();
				}
				
				/**
				 * Clear the list and assign the same value, count times.
				 * If count was 5, T was int, and value was 3,
				 * 	we'd end up with a list like {3, 3, 3, 3, 3}
				 */
				void assign(size_t count, const T& value)
				{
					this->clear();
					for (size_t i = 0; i < count; i++){
						this->push_back(value);
					}
				}
				
				/**
				 * Clear the list and assign values from another list.
				 * The 'first' iterator points to the first item copied from the other list.
				 * The 'last' iterator points to the last item copied from the other list.
				 * 
				 * Example:
				 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
				 * 	Suppose first points to the 4
				 *	Suppose last points to the 7
				 * 	We should end up with our list becoming: {4, 3, 2, 7}
				 *
				 * If the user code sends out-of-order iterators,
				 * 	just copy from 'first' to the end of the source list
				 * Example: first=7, last=4 from the list above would give us:
				 * 	{7, 1}
				 */
				void assign(Iterator first, Iterator last)
				{
					this->clear();
					for (Iterator itr = first; itr != last++ || itr != first.end(); ++itr){
						this->push_back(*itr);
					}
				}
				
				/// Return a pointer to the head node, if any
				Node<T>* head() {return this->head_;}
				
				/// Return a pointer to the tail node, if any
				Node<T>* tail() {return this->tail_;}
				
				/*Intializes the first element in a list*/
				void firstElementInit (const T& value){
					head_ = new Node<T>(value);
					tail_ = head_;
					++size_;
				}

				/**
				 * Return an iterator that points to the head of our list
				 */
				Iterator begin()
				{
					return Iterator(head_, tail_, head_);
				}
				
				/**
				 * Return an iterator that points to the last element (tail) of our list
				 */
				Iterator last()
				{
					return Iterator(head_, tail_, tail_);
				}
				
				/**
				 * Should return an iterator that represents being past the end of our nodes,
				 * or just that we are finished.
				 * You can make this a nullptr or use some other scheme of your choosing,
				 * 	as long as it works with the logic of the rest of your implementations.
				 */
				Iterator end()
				{
					return Iterator(head_, tail_);
				}
				
				/**
				 * Returns true if our list is empty
				 */
				bool empty() const
				{
					return size_ == 0;
				}
				
				/**
				 * Returns the current size of the list
				 * Should finish in constant time!
				 * (keep track of the size elsewhere)
				 */
				size_t size() const
				{
					return size_;
				}
				
				/**
				 * Clears our entire list, making it empty
				 * Remember: All removal operations should be memory-leak free.
				 */
				void clear()
				{
					while (this->empty() == false)
					{
						this->pop_back();
					}
				}
				
				/**
				 * Insert an element after the node pointed to by the pos Iterator
				 * 
				 * If the list is currently empty,
				 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
				 * 
				 * If the incoming iterator is this->end(), insert the element at the tail
				 * 
				 * Should return an iterator that points to the newly added node
				 * 
				 * To avoid repeated code, it might be a good idea to have other methods
				 * 	rely on this one.
				 */
				Iterator insert_after(Iterator pos, const T& value)
				{
					if (this->empty()){
						this->firstElementInit(value);
						return this->begin();
					} else if (pos == this->end()){
						pos = this->begin();
						pos += size_-1;
						pos.getCursor()->setNext(new Node<T>(value, pos.getCursor(), nullptr));
						tail_ = pos.getCursor()->getNext();
						++size_;
						return ++pos;
					} else{
						if (pos.getCursor()->getNext() != nullptr) { 
							pos.getCursor()->getNext()->setPrev(new Node<T>(value, pos.getCursor(), pos.getCursor()->getNext()));
						}
						pos.getCursor()->setNext(pos.getCursor()->getNext()->getPrev());
						++size_;
						return ++pos;
					}
				}
				
				/**
				 * Insert a new element after the index pos.
				 * Should work with an empty list.
				 * 
				 * Should return an iterator pointing to the newly created node
				 * 
				 * To reduce repeated code, you may want to simply find
				 * 	an iterator to the node at the pos index, then
				 * 	send it to the other overload of this method.
				*/
				Iterator insert_after(size_t pos, const T& value)
				{
					Iterator itr = this->begin();
					itr += pos;
					return insert_after(itr, value);
				}
				
				/**
				 * Erase the node pointed to by the Iterator's cursor.
				 * 
				 * If the 'pos' iterator does not point to a valid node,
				 * 	throw an std::range_error
				 * 
				 * Return an iterator to the node AFTER the one we erased,
				 * 	or this->end() if we just erased the tail
				 */
				Iterator erase(Iterator pos)
				{
					//Node<T>* cursor = pos.getCursor();
					if (pos == this->end()){
						throw std::range_error("This is an invalid node.");
					}
					if (pos == this->last()){
						tail_ = pos.getCursor()->getPrev();
						delete pos.getCursor();
						--size_;
						return this->end();
					} else{
						pos.getCursor()->getPrev()->setNext(pos.getCursor()->getNext());
						++pos;
						Node<T>* prev = pos.getCursor()->getPrev();
						pos.getCursor()->setPrev(prev->getPrev());
						delete prev;
						prev = nullptr;
						--size_;
						return pos;
					}
				}
				
				/**
				 * Add an element just after the one pointed to by the 'pos' iterator
				 * 
				 * Should return an iterator pointing to the newly created node
				 */
				Iterator push_after(Iterator pos, const T& value)
				{
					return insert_after(pos, value);
				}
				
				/**
				 * Add a new element to the front of our list.
				 */
				void push_front(const T& value)
				{
					if (this->empty()){
						this->firstElementInit(value);
					} else{
						Iterator itr = this->begin();
						itr.getCursor()->setPrev(new Node<T>(value, nullptr, head_));
						head_ = head_->getPrev();
						++size_;
					}
					
					
				}
				
				/**
				 * Add an element to the end of this list.
				 * 
				 * Should return an iterator pointing to the newly created node.
				 */
				Iterator push_back(const T& value)
				{
					return insert_after(this->end(), value);
				}
				
				/**
				 * Remove the node at the front of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_front()
				{
					if (this->empty()){
						throw std::range_error("Cannot remove from empty list.");
					}
					Iterator itr = this->begin();
					if (itr == this->last()){
						head_ = nullptr;
						tail_ = nullptr;
					} else{
						++itr;
						delete head_;
						head_ = itr.getCursor();
					}
					--size_;
				}
				
				/**
				 * Remove the node at the end of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_back()
				{
					if (this->empty()){
						throw std::range_error("Cannot remove from empty list.");
					}
					Iterator itr = this->last();
					if (itr == this->begin()){
						head_ = nullptr;
						tail_ = nullptr;
					} else{
						--itr;
						tail_ = itr.getCursor();
					}
					if (size_ > 0) { --size_; }
				}
				
				/**
				 * Return a reference to the element at the front.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& front()
				{
					if (this->empty()) {throw std::out_of_range("Can't access element from empty list.");}
					return *(this->begin());
				}
				
				/**
				 * Return a reference to the element at the back.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& back()
				{
					if (this->empty()) {throw std::out_of_range("Can't access element from empty list."); 
					return *(this->last());
				}
				
				/**
				 * Return the element at an index
				 * 
				 * Should throw a range_error is out of bounds
				 */
				T& at(size_t index)
				{
					Iterator itr = this->begin();
					itr += index;
					if (itr == this->end()){
						throw std::range_error("Index is out of bounds.");
					}
					return *itr;
				}
				
				/**
				 * Reverse the current list
				 * 
				 * It might be easy to consider the following:
				 * - Create a temp empty list
				 * - Iterate through the current list
				 * - For each item in the current list, push to the FRONT (not back)
				 * - Assign the current list to the temp list
				 * - Discard the temp list
				 */
				void reverse()
				{
					if (size_ > 1){
						T* temp = new T[size_];
						for (size_t i = 0; i < size_; ++i){
							temp[size_-1-i] = this->at(i);
						}
						for (size_t i = 0; i < size_; i++){
							this->push_back(temp[i]);
							this->pop_front();
							temp[i].~T();
						}
						delete[] temp;
						temp = nullptr;
					}
				}
				
				/**
				 * I bet you're happy I'm not making you do this.
				 * No tests will be run against this function,
				 * 	but feel free to try it out, as a challenge!
				 * 
				 * If I were doing this and didn't care too much for efficiency,
				 * 	I would probably create an extra helper function to swap two
				 * 	positions in the current list.
				 * Then I would simply sweep through the list and perform
				 *  the bubble-sort algorithm. Perhaps selection sort.
				 * 
				 * If you want a huge challenge, try implementing quicksort.
				 * 
				 * (but again, don't worry about this method; it will not be tested)
				 */
				void sort()
				{
					
				}
				
				/**
				 * Assignment operator
				 * 
				 * Clear this list and fill it with the others' values
				 * (by value, not by reference)
				 * 
				 * Return a reference to this list
				 */
				DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
				{
					this->clear();
					for (Iterator itr = other.begin(); itr != other.end(); ++itr){
						this->push_back(*itr);
					}
					return *this;
				}
				
				/**
				 * Return true if the lists are "equal"
				 * 
				 * "Equal" here is defined as:
				 * - Same size
				 * - Elements at the same indexes would return true for their own comparison operators
				 * 
				 * In other words: "They contain all the same values"
				 * (no need to be references to each other)
				 */
				bool operator ==(DoublyLinkedList<T>& other)
				{
					if (this->size_ == other.size_){	
						for (size_t i = 0; i < size_; i++){
							if (this->at(i) != other.at(i)){
								return false;
							}
						}
						return true;
					}
					return false;
					
				}
				
				/**
				 * Return true if the lists are "not equal"
				 * 
				 * See the operator== stub for definition of "equal"
				 * 
				 * Probably want to avoid repeated code by relying on the other operator
				 */
				bool operator !=(DoublyLinkedList<T>& other)
				{
					return !(*this == other);
				}
				
			private:
				Node<T>* head_ = nullptr;
				Node<T>* tail_ = nullptr;
				size_t size_ = 0;
		};
	}
	}


#endif
