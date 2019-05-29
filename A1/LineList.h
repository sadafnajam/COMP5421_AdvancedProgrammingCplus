    //
    //  LineList.h
    //  A1
    //
    //  Created by Sadaf Najam on 2019-05-25.
    //  Copyright © 2019 Sadaf Najam. All rights reserved.
    //

    #include "Line.h"

    #ifndef LineList_h
    #define LineList_h

    class LineList {
        
    private:
        int theSize; //Number of elements in this list
        struct Node{ //Inner Node class
        public:
            Line data;
            Node* prev;
            Node* next;
            Node(const Line& In, Node* prv, Node* nxt):data{In}, prev{prv}, next{nxt}{};
        };
        
        Node* head; //Pointer to the first node in this list
        Node* tail; //Pointer to the last node in this list
        
    public:
        LineList(); //Default ctor
        
        virtual ~LineList(); //Dtor
        
        explicit LineList(const LineList& rhs); //Copy ctor
        
        const LineList& operator=(const LineList& rhs); //Copy assignment
        
        void push_front(const Line& line); //Inserts line at the front of the this list
        
        void push_back(const Line& line); //Inserts line at the end of the this list
        
        void pop_front(); //Remove the first node in this list
        
        void pop_back(); //Remove the last node in this list
        
        int size() const; //Returns the size of this list
        
        bool empty() const; //Returns whether this list is empty
        
        void insert(const Line& line, int k); //Inserts a new line at position k in this list
        
        void remove(int k); //Removes node at position k in this list
        
        Line get(int k) const; //Returns the line at position k in this list
        
        void print(); //Prints the lineList
        
    };


    #endif /* LineList_h */
