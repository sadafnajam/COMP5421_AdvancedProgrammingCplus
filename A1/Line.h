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
        Line(const char* text); //Constructs this line
        virtual ~Line(); //Dtor
        explicit Line(const Line&); //Copy ctor
        const Line& operator=(const Line& rhs); //Assignment operator overloading
        const char* cstr( ) const; //Returns this line
        
        int length( ) const;
        bool empty() const;
        bool full() const;
        int capacity() const;
        void resize();
        void push_back(const char& ch);
        void pop_back();
        friend ostream& operator<<(ostream& out, const Line& line);
        friend istream& operator>>(istream& in, Line& line);
    };


    #endif /* Line_h */
