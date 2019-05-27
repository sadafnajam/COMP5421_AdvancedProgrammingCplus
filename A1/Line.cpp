    //
    //  Line.cpp
    //  A1
    //
    //  Created by Sadaf Najam on 2019-05-25.
    //  Copyright © 2019 Sadaf Najam. All rights reserved.
    //

    #include <iostream>
    #include <cstring>

    #include "Line.h"

    using std::cout;
    using std::endl;
    using std::strcpy;

    //De
    Line::Line(const char* text){
        linePtr= new char;
        text=linePtr;
    }

    //Dtor
    Line::~Line(){
        cout<<"dtor"<<endl;
        delete [] linePtr;
        linePtr=nullptr;
    }

    //Copy ctor
    Line::Line(const Line& secondList){
        linePtr= new char;
        *linePtr=*secondList.linePtr;
    }

    //Assignment operator overloading
    const Line& Line::operator=(const Line& rhs){
        if (this==&rhs) {
            return *this;
        }
        delete [] linePtr;
        Capacity=rhs.capacity();
        linePtr=new char[Capacity];
        while (empty()!=true) {
            pop_back();
        }
        (Line(rhs));
        return *this;
    }





