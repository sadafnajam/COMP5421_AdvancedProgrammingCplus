    //
    //  Line.h
    //  A1
    //
    //  Created by Sadaf Najam on 2019-05-25.
    //  Copyright © 2019 Sadaf Najam. All rights reserved.
    //

    #ifndef Line_h
    #define Line_h

    using std::ostream;
    using std::istream;

    class Line {
        
    private:
        char* linePtr{nullptr}; //Pointer to the first character in char array
        int lineLength; //Length of this line
        int Capacity; //Storage Capacity of this line

    public:
        Line(const char* text); //Constructs this line assigning linePtr a pointer to a deep copy of the supplied C-string text
        
        explicit Line(const Line&); //Copy ctor
        
        const Line& operator=(const Line& rhs); //Assignment operator overloading
        
        virtual ~Line(); //Dtor
        
        const char* cstr( ) const; //Returns c-style version of this line
        
        int length() const; //Returns length of this line
        
        bool empty() const; //Returns whether this line is empty
        
        bool full() const; //Returns whether this line is full
        
        int capacity() const; //Returns capacity of this line
        
        void resize(); //Doubles capacity if this line is full
        
        void push_back(const char& ch); //Appends ch to the end of this line
        
        //To handle underflow
        class underflow_error : public std::runtime_error {
        public:
            explicit underflow_error (const string& what_arg);
            explicit underflow_error (const char* what_arg);
        };
        
        void pop_back(); //Removes the last character in this line
        
        friend ostream& operator<<(ostream& out, const Line& line); //Overloads operator << as a friend
        
        friend istream& operator>>(istream& in, Line& line); //Overloads operator>> as a friend
        
    };


    #endif /* Line_h */
