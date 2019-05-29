    //
    //  LineList.cpp
    //  A1
    //
    //  Created by Sadaf Najam on 2019-05-25.
    //  Copyright © 2019 Sadaf Najam. All rights reserved.
    //
    #include <iostream>
    #include <string>

    #include "LineList.h"
    #include "Line.h"

    using std::cout;
    using std::endl;

    //Default constructor
    LineList::LineList(){
        cout << "Default ctor" << endl;
        head=new Node(Line{""}, nullptr, nullptr);
        tail=new Node(Line{""}, nullptr, nullptr);
        head->next=tail;
        tail->prev=head;
    }

    //Destructor
    LineList::~LineList(){
        cout << "dtor" << endl;
        while (!empty()) {
            pop_front();
        }
        delete [] head;
        head=nullptr;
        delete [] tail;
        tail=nullptr;
    }

    //Copy ctor
    LineList::LineList(const LineList& rhs){
        cout << "Copy ctor" << endl;
        head=new Node(Line{""}, nullptr, nullptr);
        tail=new Node(Line{""}, nullptr, nullptr);
        head->next=tail;
        theSize=rhs.size();
        if (rhs.empty()) {
            return;
        }
        Node* current=rhs.head->next;
        while (current != rhs.tail) {
            push_back(current->data);
            current=current->next;
        }
    }

    //Copy assignment
    const LineList& LineList:: operator=(const LineList& rhs){
        if (this==&rhs) {
            return *this;
        }
        while (empty()!=1) {
            pop_back();
        }
        LineList varname(rhs);
        return *this;
    }

    //Inserts line at front of the list
    void LineList::push_front(const Line& line){
        Node* insert=new Node(line, head, head->next);
        head->next->prev=insert;
        head->next=insert;
        theSize+=1;
    }

    //Inserts line at back of the list
    void LineList::push_back(const Line& line){
        Node* insert=new Node(line, tail->prev, tail);
        tail->prev->next=insert;
        tail->prev=insert;
        theSize+=1;
    }

    //Removes first node from the list
    void LineList::pop_front(){
        Node* removal=head->next;
        if(removal != tail){
            removal->next->prev = head;
            head->next = removal->next;
            delete [] removal;
            removal = nullptr;
            theSize-= 1;
        }
    }


    //Removes last node from the list
    void LineList::pop_back(){
        Node * removal = tail->prev;
        if(removal != head){
            removal->prev->next = tail;
            tail->prev = removal->prev;
            delete [] removal;
            removal = nullptr;
            theSize-= 1;;
        }
    }

    //Returns the size of list
    int LineList::size() const{
        return theSize;
    }

    //Returns true or false if list is empty
    bool LineList::empty() const{
        bool isEqual = 0;
        if((head->next == tail) && (tail->prev == head)){
            isEqual = 1;
        }
        return isEqual;
    }

    //Inserts a new line at position k in this list
    void LineList::insert(const Line& line, int k){
        if(head->next==tail || size()<k){
            cout<<"position out of bound"<<endl;
        }
        else{
            if(k==1){
                push_front(line);
                return;
            }
            Node * newNode = head;
            int count = 0;
            while(count != k){
                newNode = newNode->next;
                count++;
            }
            Node * n = new Node{ line , newNode->prev , newNode};
            newNode->prev->next = n;
            newNode->prev = n;
            theSize+= 1;
            
        }
    }

    //Removes node at position k in this list
    void LineList::remove(int k){
        if(head->next==tail || size()<k){
            cout<<"position out of bound"<<endl;
        }
        else{
            Node * removeNode = head;
            int count = 0;
            while(count != k){
                removeNode = removeNode->next;
                count++;
            }
            removeNode->prev->next = removeNode->next;
            removeNode->next->prev = removeNode->prev;
            theSize-= 1;
            delete [] removeNode;
            removeNode = nullptr;
        }
    }

    //Returns the line at position k in this list
    Line LineList::get (int k) const{
        Node * node = head;
        int count = 0;
        while(count != k){
            node = node->next;
            count++;
        }
        return node->data;
    }



    //Print manipulated list
    void LineList::print(){
        Node* current;
        current = first;
        while (current != null)
        {
            cout << current->data << " "; 
            current = current->next;
        }//end while
        //return expression;
    }


