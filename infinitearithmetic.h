#ifndef INFINITEARITHMETIC_H
#define INFINITEARITHMETIC_H

#include <string>

namespace InfiniteArithmetic {

    class Integer {
    private:
        std::string value;      // Holds the integer value as a string

    public:
        Integer();  			// Default constructor
        Integer(const std::string &s);  // Initialize from a string
        Integer(const Integer &other);  // Copy constructor
        ~Integer();  			// Destructor

        // Static function to parse from string
        static Integer parse(const std::string &s);

        // Operator overloads
        Integer operator+(const Integer &other) const;
        Integer operator-(const Integer &other) const;
        Integer operator*(const Integer &other) const;
        Integer operator/(const Integer &other) const;  

        // Friend function to print Integer
        friend std::ostream &operator<<(std::ostream &os, const Integer &i);
    };
    
    
   class Float {
        
    public:
        // Constructors
        
        Float();
        Float(const std::string &s);
        Float(const Float &other);
        ~Float();

        // Static function to parse from string
        static Float parse(const std::string &s);
        
        // Convert Float to string
        std::string toString() const;
        
        std::string integerPart;      // Integer part of the number
        std::string fractionalPart;   // Fractional part of the number

        // Operator overloads
        Float operator+(const Float &other) const;
        Float operator-(const Float &other) const;
        Float operator*(const Float &other) const;
        Float operator/(const Float &other) const;
        
        // Friend function to print Float
        friend std::ostream &operator<<(std::ostream &os, const Float &f);
    };
}

#endif                  // INFINITEARITHMETIC_H
