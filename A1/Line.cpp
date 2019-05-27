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
    using std::size_t;

    //Deep copy
    Line::Line(const char* text){
        lineLength=(int32_t)strlen(text);
        linePtr= new char[lineLength+1];
        strcpy(linePtr, text);
    }

    //Copy ctor
    Line::Line(const Line& secondList){
        lineLength=secondList.lineLength;
        linePtr= new char[lineLength+1];
        strcpy(linePtr, secondList.linePtr);
    }

    //Assignment operator overloading
    const Line& Line::operator=(const Line& rhs){
        if (this==&rhs) {
            return *this;
        }
        else{
            delete [] linePtr;
            lineLength=rhs.lineLength;
            linePtr= new char[lineLength+1];
            strcpy(linePtr, rhs.linePtr);
            
        }
        return *this;
    }

    //Dtor
    Line::~Line(){
        cout<<"dtor"<<endl;
        delete [] linePtr;
        linePtr=nullptr;
    }

    //Returns C-style line
    const char* Line:: cstr() const{
        return linePtr;
    }

    //Returns length of this line
    int Line::length() const{
        return lineLength;
    }

    //Returns true or false if this line is empty
    bool Line::empty() const{
        if (linePtr==nullptr) {
            return true;
        }
        else
            return false;
    }

    //Returns true or false if this line is full
    bool Line::full() const{
        if (lineLength==Capacity) {
            return true;
        }
        else
            return false;
    }

    //Returns capacity of this line
    int Line::capacity() const{
        return Capacity;
    }

    //resize to double if capacity if full
    void Line::resize(){
        int dCapacity{capacity()*2};
        char* tempPtr=new char[dCapacity+1];
        strcpy(tempPtr,linePtr);
        Capacity=dCapacity;
        delete [] linePtr;
        linePtr=tempPtr;
    }

    //Adds character to end of line
    void Line::push_back(const char& ch)
    {
        if (full()) {
            resize();
        }
        linePtr[lineLength]=ch;
        linePtr[lineLength+1]='\0';
        lineLength++;
    }

    //Removes last character from this line
    void Line::pop_back(){
        if (empty()) {
            // throw Line::underflow_error;
        }
        else {
            linePtr[lineLength-1]='\0';
            lineLength--;
        }
    }

    //Overloads cout operator
    ostream& operator<<(ostream& out, const Line& line){
        if (line.lineLength > 0)
            out << line.linePtr;
        return out;
    }

    //Overloads cin operator
    istream& operator>>(istream& in, Line& line){
        char c;
        while (in.get(c)) {
            if (line.full())
                line.resize();
            line.push_back(c);
        }
        return in;
    }









    









