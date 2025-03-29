#include "infinitearithmetic.h"
#include <iostream>
#include <algorithm>

using namespace std;


namespace InfiniteArithmetic 
{  
    Integer::Integer() : value("0") {}
    Integer::Integer(const string &s) : value(s) {}
    Integer::Integer(const Integer &other) : value(other.value) {}
    Integer::~Integer() {}

    Integer Integer::parse(const string &s)
     {
        return Integer(s);
     }

    string reverse(const string &s)
    {
        string rev(s);
        reverse(rev.begin(), rev.end());
        return rev;
    }
    
    string padLeadingZeros(const string &str, int length)
    {
	if(str.size() < length)
		return string(length - str.size(), '0') + str;	
	
	return str;
    }

    int compareStrings(const string& a, const string& b)
      {
        if (a.length() > b.length()) 
		return 1;
        if (a.length() < b.length()) 
		return -1;
            
        return a.compare(b);
      }

    string addStrings(string &num1, string &num2)
    { 
        size_t maxLength = max(num1.size(), num2.size());
    	num1 = padLeadingZeros(num1,maxLength);
    	num2 = padLeadingZeros(num2,maxLength);
        
        string result;
        int carry = 0;
        
        // Perform addition
        for (int i = maxLength - 1; i >= 0; i--) 
        {     
            int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
            carry = sum/10;
            sum %= 10;
            result = char(sum + '0') + result;         
        }
        
        // Add remaining carry
        if (carry) 
            result = char(carry + '0') + result;
        
        return result;
    }
    
    string subStrings(const string &a, const string &b) 
    {
        string result;
        int borrow = 0;
        size_t maxLength = max(a.size(), b.size());

        for (size_t i = 0; i < maxLength; ++i) 
        {
            int digitA = (i < a.size()) ? (a[a.size() - 1 - i] - '0') : 0;
            int digitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;

            int diff = digitA - digitB - borrow;
            if (diff < 0) 
            {
                diff += 10;
                borrow = 1;
            } else 
            {
                borrow = 0;
            }
            result.push_back(diff + '0');
        }

        // Remove leading zeros
        while (result.size() > 1 && result.back() == '0') 
        {
            result.pop_back();
        }

        // Reverse the result to get the final difference
        reverse(result.begin(), result.end());

        return result;
    }
    
    // Addition operation
    Integer Integer::operator+(const Integer &other) const 
    { 
        string num1 = value;
        string num2 = other.value;
        string result;
        
        bool num1Negative = num1[0] == '-';
        bool num2Negative = num2[0] == '-';
        bool resultNegative = false;
        
        // Handle both positive or both negative case
        if (!num2Negative && !num1Negative)
        {
            result = addStrings(num1,num2);          
        }
           
        else if(num1Negative && num2Negative) 
        {
        	num1 = num1.substr(1);
  	        num2 = num2.substr(1);
		result = addStrings(num1,num2); 
                resultNegative = true;     
        }

        else if (!num1Negative && num2Negative)       
        {    
        	num2 = num2.substr(1);        
                if (compareStrings(num2, num1) > 0) 
                {
		        swap(num1, num2);
		        resultNegative = true;
                }
                else if(compareStrings(num1, num2) > 0)
               		resultNegative = false;             

                result = subStrings(num1,num2);           
        } 
        else if(num1Negative && !num2Negative)
        {
                num1 = num1.substr(1);
               if (compareStrings(num2, num1) > 0) 
                {
		        swap(num1, num2);
		        resultNegative = false;
                }
                else if(compareStrings(num1, num2) > 0)
               		resultNegative = true;             

                result = subStrings(num1,num2);
        }
        
        if (resultNegative) 
        	result = "-" + result;
                
  	 return Integer(result);
    }

    // Subtraction operation
    Integer Integer::operator-(const Integer &other) const 
    {
        string num1 = value;
        string num2 = other.value;
        string result;
        
        bool resultNegative = false;
         
        // Determine the signs of the numbers
        bool num1Negative = num1[0] == '-';
        bool num2Negative = num2[0] == '-';

        // If both numbers have different signs, convert subtraction to addition
        if (num2Negative && !num1Negative)
         {
            string num2Abs = num2.substr(1); 
            return *this + Integer(num2Abs);
         }
           
          else if(num1Negative && !num2Negative) 
          {
          	resultNegative = true;
          	swap(num1,num2);
       	        string num2Abs = num2.substr(1);
           	return Integer("0")-(Integer(num1) + Integer(num2Abs));
          }

        // Handle both positive or both negative cases 
        else if (num1Negative && num2Negative)    
        {
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            // Compare the absolute values to determine the result's sign
            if (compareStrings(num2, num1) > 0) 
            {
                swap(num1, num2);
               
                resultNegative = false;
            }
            else if(compareStrings(num1, num2) > 0)
            {
            	resultNegative = true; 
            }
             result = subStrings(num1,num2);
         } 
        else if(!num1Negative && !num2Negative)
        {
            if (compareStrings(num2, num1) > 0) 
            {
                swap(num1, num2);
                result = subStrings(num1,num2);
                resultNegative = true;
            }
            else if(compareStrings(num1, num2) > 0)
            {
                result = subStrings(num1,num2);
            	resultNegative = false; 
            }
            
        }
        
        if (resultNegative) 
        	result = "-" + result;
        	
    	return Integer(result);    
    }

    // Multiplication operation
    Integer Integer::operator*(const Integer &other) const 
    {
        string value1 =value;
        string value2 = other.value;
        
        // Remove negative signs from the numbers
        if (value1[0] == '-') 
        	value1 = value1.substr(1);
            
        if (value2[0] == '-') 
        	value2 = value2.substr(1);
 
        // Determine if the final product will be negative
        bool negativeResult = (value1[0] == '-' && value2[0] != '-') || (value1[0] != '-' && value2[0] == '-');
        if(value1 == "0" || value2 == "0")
        {
           return Integer("0");
        }  
        
        // Initialize a vector to store intermediate results
        vector<int> result(value1.size() + value2.size(), 0);
        
        // Perform multiplication
        for (size_t i = 0; i < value1.size(); ++i)
        {
            for (size_t j = 0; j < value2.size(); ++j) 
            {
                int digit1 = value1[value1.size() - 1 - i] - '0';
                int digit2 = value2[value2.size() - 1 - j] - '0';
                result[i + j] += digit1 * digit2;
                
                // Handle carry
                if (result[i + j] >= 10) 
                {
                    result[i + j + 1] += result[i + j] / 10;
                    result[i + j] %= 10;
                }
            }
        }
        
        // Convert result from vector to string
        string product;
        bool leadingZero = true;
        for (size_t i = result.size() - 1;i != static_cast<size_t>(-1); i--) 
        {
            if (result[i] == 0 && leadingZero) 
                continue;
         
            leadingZero = false;
            product.push_back(result[i] + '0');
        }
        
        // Handle the case when the product is zero
        if (product.empty()) 
        	product = "0";
        
        // Add negative sign if needed
        if (negativeResult) 
        	product = "-" + product;
        
        return Integer(product);
    }
    
    Integer Integer::operator/(const Integer &other) const 
    {
        // Handle division by zero
        if (other.value == "0")
        {
            cout<<"Division by zero error"<<'\n';
            exit(1);
        }

        // Determine the signs of the dividend and divisor
        bool isDividendNegative = value[0] == '-';
        bool isDivisorNegative = other.value[0] == '-';
        
        // Determine the overall result's sign
        bool isResultNegative = isDividendNegative != isDivisorNegative;
        
        // Remove negative signs from the dividend and divisor if present
        string absDividend = isDividendNegative ? value.substr(1) : value;
        string absDivisor = isDivisorNegative ? other.value.substr(1) : other.value;

        // Compare the absolute values of the dividend and divisor
        if (compareStrings(absDividend, absDivisor) < 0) 
            // Dividend is less than the divisor; return 0
            return Integer("0");

        // Perform division using long division
        string quotient;
        string current;
        size_t currentIndex = absDivisor.size();
        
        current = absDividend.substr(0, currentIndex);
        
        while (currentIndex <= absDividend.size()) 
        {
            // Find the largest integer multiple of absDivisor that fits into current
            int q = 0;
            while (compareStrings(current, absDivisor) >= 0) 
            {
                current = subStrings(current, absDivisor);
                q++;
            }
            quotient.push_back('0' + q);
            
            if(currentIndex == absDividend.size())
            {
		break;            
            }

            // Move to the next digit of absDividend
            if (currentIndex < absDividend.size()) 
            {
                current.push_back(absDividend[currentIndex]);
                currentIndex++;
            }

            // Remove leading zeros from current string
            while (current.size() > 1 && current[0] == '0') 
            {
                current = current.substr(1);
            }
            
        }

        // Remove leading zeros from the quotient
        while (quotient.size() > 1 && quotient[0] == '0') 
        {
            quotient = quotient.substr(1);
        }

        // Add negative sign to the quotient if the result is negative
        if (isResultNegative) 
        	quotient = "-" + quotient;

        return Integer(quotient);
    }

     
    
     ostream& operator<<(ostream &os, const Integer &i) 
     {
        os << i.value;
        return os;
     }
}
