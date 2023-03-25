// HELGA: High Efficiency Generic dAta structure library
// Helga Chain v.2.4.2
// (Singly Linked List)
// Copyright 2023 (c) Acutis Data Structure Corporation.

#pragma once //Not supported by all compilers

#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <iostream>
#include <string>
#include <iomanip>

namespace helga{

    template <typename T>
    class chain{

        private:
            //Chain Node
            template <typename U>
            class node{
                private:
                    U node_data;
                    node<U>* node_next;
                public:
                    //Constructors
                    node(U data){
                        this->node_data = data;
                        this->node_next = nullptr;
                    }
                    node(U data, node<U>* next){
                        this->node_data = data;
                        this->node_next = next;
                    }

                    //Methods
                    U data(){
                        return this->node_data;
                    }
                    node<U>* next(){
                        return this->node_next;
                    }
                    void set_data(U data){
                        this->node_data = data;
                    }
                    void set_next(node<U>* next){
                        this->node_next = next;
                    }
            };
            size_t chain_size;
            node<T>* head;
        public:
            //Constructors

            // Default constructor
            chain() : head {nullptr}, chain_size {0} {};

            // Copy constructor
            chain(const chain& other) : head{nullptr}, chain_size {0}{
                node<T>* traversal = other.head;
                while(traversal != nullptr){
                    add_last(traversal->data());
                    traversal = traversal->next();
                }
            }

            //Destructor
            ~chain(){
                node<T>* traversal {head};
                while(traversal != nullptr){
                    head = head->next();
                    delete traversal;
                    chain_size--;
                    traversal = head;
                }
            }

            //Data Structure Manipulation and Accessing
            void add_first(T data){
                head = new node<T>(data, head);
                chain_size++;
            }

            void add_last(T data){
                if(chain_size == 0 && head == nullptr){
                    //add_first(data);
                    head = new node<T>(data, head);
                    chain_size++;
                    return;
                }
                node<T>* traversal = head;
                while(traversal->next()!=nullptr){
                    traversal = traversal->next();
                }
                traversal->set_next(new node<T> (data, nullptr));
                chain_size++;
            }

            void add_at(size_t pos, T data){
                if (pos > chain_size) {
                    throw std::out_of_range("Given position out of range");
                }

                if(chain_size == 0 && head == nullptr){
                    //add_first(data);
                    head = new node<T>(data, head);
                    chain_size++;
                }else if(pos == chain_size){
                    add_last(data);
                }else{
                    node<T>* traversal = head;
                    for(size_t i {0}; i<pos-2; i++){
                        traversal = traversal->next();
                    }
                    //std::cout << traversal->data() << '\n';
                    traversal->set_next(new node<T>(data, traversal->next()));
                    chain_size++;
                }
            }

            void delete_first(){   
                if(chain_size!=0 && head != nullptr){
                    node<T>* temp = head;
                    head = head->next();
                    delete temp;
                    chain_size--;
                }
            }

            void delete_last(){
                if(chain_size == 0 && head == nullptr){
                    return;
                }
                else if(chain_size==1){
                    delete_first();
                }else{
                    node<T>* traversal = head;
                    while(traversal->next()->next()!=nullptr){
                        traversal = traversal->next();
                    }
                    delete traversal->next();
                    chain_size--;
                    traversal->set_next(nullptr);
                }
            }

            void del_at(size_t pos){
                if (pos > chain_size) {
                    throw std::out_of_range("Given position out of range");
                }

                if(pos == 0){
                    return;
                }else if(pos == 1){
                    delete_first();
                }else if(pos == chain_size){
                    delete_last();
                }else{
                    node<T>* traversal = head;
                    for(size_t i{0}; i<pos-2; i++){
                        traversal = traversal->next();
                    }
                    node<T>* temp = traversal->next();
                    traversal->set_next(traversal->next()->next());
                    delete temp;
                    chain_size--;
                }
            }

            void deallocate(){
                this->~chain();
            }

            void obliberate(){
                this->~chain();
                ::operator delete (this);
            }

            void update(size_t pos, T data){
                if (pos > chain_size) {
                    throw std::out_of_range("Given position out of range");
                }
                node<T>* traversal {head};
                for(size_t i{0}; i<pos-1; i++){
                    traversal = traversal->next();
                }
                traversal->set_data(data);
            }

            void swap(size_t pos, size_t pos2){
                node<T>* traversal {head}, *traversal2 {head};
                for(size_t i{0}; i<pos-1; i++){
                    traversal = traversal->next();
                }

                for(size_t i{0}; i<pos2-1; i++){
                    traversal2 = traversal2->next();
                }

                T temp = traversal->data();
                traversal->set_data(traversal2->data());
                traversal2->set_data(temp);
            }

            void reverse(){
                node<T>* traversal {head}, * prev {nullptr}, * next {nullptr};
                while(traversal!=nullptr){
                    next = traversal->next();
                    traversal->set_next(prev);
                    prev = traversal;
                    traversal = next;
                }
                head = prev;
            }
            
            //Revisar, falta implementar negativos y cuando se mayor que la lista
            void shift(int n){
                node<T>* traversal{head}, *next {nullptr}, *new_head{nullptr};
                for(size_t i{1}; i<n; i++){
                    traversal = traversal->next();
                }
                next = traversal->next();
                new_head = next;
                traversal->set_next(nullptr);
                while(next->next()!=nullptr){
                    next = next->next();
                }
                next->set_next(head);
                head = new_head;
            }

            void operator+=(const chain& other){
                node<T>* traversal {head};
                while(traversal->next()!=nullptr){
                    traversal = traversal->next();
                }
                traversal->set_next(other.head);
                chain_size += other.chain_size;
            }

            void operator=(const chain& other){
                this->~chain();
                node<T>* traversal = other.head;
                while(traversal!=nullptr){
                    add_last(traversal->data());
                    traversal = traversal->next();
                }
                chain_size = other.chain_size;
            }

            //Nonmodifying Methods
            size_t size(){
                return this->chain_size;
            }

            bool empty(){
                return (chain_size==0) ? true : false;
            }

            T retrieve(size_t pos){
                node<T>* traversal {head};
                for(size_t i{0}; i<pos-1; i++){
                    traversal = traversal->next();
                }
                return traversal->data();
            }

            bool operator==(const chain& other) const{

                if(chain_size!=other.chain_size){
                    return false;
                }else{
                    node<T>* traversal {head}, *traversal2{other.head};
                    while(traversal!=nullptr){
                        if(traversal->data() != traversal2->data()){
                            return false;
                        }
                        traversal = traversal->next();
                        traversal2 = traversal2->next();
                    }
                    return true;
                }
            }

            /*
                size_t find(const T& data)

                Return the position of the first occurrence of data in the chain or 0 if data is not in the list.
            */
            size_t find(const T& data){
                if(head == nullptr && chain_size == 0){
                    return 0;
                }
                
                size_t pos = 0;
                node<T>* traversal = head;
                for(size_t i{0}; i<chain_size; i++){
                    if(traversal->data() == data ){
                        return pos+=1;
                    }traversal = traversal->next();
                    pos++;
                }

                return 0;
            }
            //I/O
            void pretty_print() {
                int max_len = 2;
                node<T>* traversal = head;
                //Determine the longest node data by num of chars
                while (traversal != nullptr) {
                    int len = std::to_string(traversal->data()).length();
                    if (len > max_len) {
                        max_len = len;
                    }
                    traversal = traversal->next();
                }

                // Reset
                traversal = head;
                std::cout << "\n        ";
                for (int i = 0; i < chain_size; i++) {
                    std::cout << "+" << std::string(max_len + 2, '-') << "+    ";
                }
                std::cout << "\nhead -> ";
                while (traversal != nullptr) {
                    std::cout << "| " << std::setw(max_len) << traversal->data() << " | -> ";
                    traversal = traversal->next();
                }
                std::cout << "null\n        ";
                for (int i = 0; i < chain_size; i++) {
                    std::cout << "+" << std::string(max_len + 2, '-') << "+    ";
                }
                std::cout << '\n';
            }

            void print(){
                
                node<T>* traversal = head;
                while(traversal!=nullptr){
                    std::cout << traversal->data() << ' ';
                    traversal = traversal->next();
                }
            }
    };

}//namespace helga

#endif/*CHAIN_HPP*/

/*
    remove(const T& data): removes the first occurrence of data in the linked list.
    remove_all(const T& data): removes all occurrences of data in the linked list.
    splice(size_t pos, const chain& other): inserts the elements of the other linked list into this linked list starting at position pos.
    splice(size_t pos, const chain& other, size_t first, size_t last): inserts a range of elements from the other linked list into this linked list starting at position pos.
    merge(chain& other): merges the other linked list into this linked list, assuming both linked lists are sorted in ascending order.
    sort(): sorts the linked list in ascending order.
    unique(): removes consecutive duplicate elements from the linked list.


    split(size_t pos): splits the linked list into two separate linked lists, with the first list containing elements up to position pos and the second list containing the remaining elements.
    partition(const T& data): rearranges the linked list such that all elements less than data come before elements greater than or equal to data.
    swap_pairs(): swaps the positions of adjacent pairs of elements in the linked list.
    unique_sorted(): removes consecutive duplicate elements from the linked list, assuming that the list is already sorted in ascending order.
    minmax(): returns a pair of iterators pointing to the minimum and maximum elements in the linked list, respectively.


    insert_sorted(const T& data): inserts data into the linked list in its sorted position, assuming that the list is already sorted in ascending order.
    is_sorted(): returns true if the linked list is sorted in ascending order, and false otherwise.
    to_vector(): returns a std::vector containing the elements of the linked list in the order they appear in the list.
    to_forward_list(): returns a std::forward_list containing the elements of the linked list in the order they appear in the list.
    replace_all(const T& old_data, const T& new_data): replaces all occurrences of old_data with new_data in the linked list.

*/