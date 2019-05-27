    //
    //  LineList.h
    //  A1
    //
    //  Created by Sadaf Najam on 2019-05-25.
    //  Copyright © 2019 Sadaf Najam. All rights reserved.
    //

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
            Node(const Line& In, Node* prv, Node* nxt);
        };
        
        Node* head; //Pointer to the first node in this list
        Node* tail; //Pointer to the last node in this list
        
    public:
        LineList(); //Default ctor
        virtual ~LineList(); //Dtor
        explicit LineList(const LineList& rhs); //Copy ctor
        const LineList& operator=(const LineList& rhs); //Copy assignment
        
        void push_front(const Line& line);
        void push_back(const Line& line);
        void pop_front();
        void pop_back();
        int size() const;
        bool empty() const;
        void insert(const Line& line, int k);
        void remove(int k);
        Line get(int k) const;
        void print();
        
    };


    #endif /* LineList_h */
