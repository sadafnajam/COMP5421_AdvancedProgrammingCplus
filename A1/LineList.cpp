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

    using std::cout;
    using std::endl;

    //Default constructor
    LineList::LineList(){
        cout << "default ctor" << endl;
    }

    //Destructor
    LineList::~LineList(){
        cout << "dtor" << endl;
       // delete[] msgPtr;
        //msgPtr = nullptr;
    }

    //Print manipulated list
    LineList::void print(){
        Node* current;
        current = first;
        while (current != null)
        {
            cout << current->data << " "; 
            current = current->next;
        }//end while
        //return expression;
    }

    LineList::LineList(const LineList& rhs){
        
    }
