#include "infinitearithmetic.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>

using namespace std;


namespace InfiniteArithmetic
{
     // Define the operator<< function to print Float objects
    ostream& operator<<(ostream& os, const Float& f)
    {
        os << f.toString(); 
        return os;
     }
     
    // Default constructor
    Float::Float() : integerPart("0"), fractionalPart("0") {}
    
    // Function to remove leading zeros from a string
    string removeLeadingZeros(string &s)
    {
        size_t i = 0;
        while (i < s.size() && s[i] == '0')
        {
            i++;
        }
        s.erase(0, i);
        if (s.empty())
            s = "0";
            
            return s;
    }

    // Function to remove trailing zeros from a string
    string removeTrailingZeros(string &s)
    {
        size_t i = s.size();
        while (i > 0 && s[i - 1] == '0')
        {
            i--;
        }
        s.erase(i);
        if (s.empty())
            s = "0";
            return s;
    }

    // Constructor from string
    Float::Float(const string &s)
    {
        size_t dotPos = s.find('.');
        if (dotPos == string::npos)
        {
            // No decimal point, entire number is an integer
            integerPart = s;
            fractionalPart = "0";
        }
        else
        {
            // Split integer and fractional parts
            integerPart = s.substr(0, dotPos);
            fractionalPart = s.substr(dotPos + 1);
        }
        removeLeadingZeros(integerPart);
        removeTrailingZeros(fractionalPart);
    }

    // Copy constructor
    Float::Float(const Float &other) : integerPart(other.integerPart), fractionalPart(other.fractionalPart) {}

    // Destructor
    Float::~Float() {}

    // Parse the input string
    Float Float::parse(const string &s)
    {
        return Float(s);
    }
    
    // Convert Float to string
    string Float::toString() const
    {
        if (fractionalPart == "0")
            return integerPart;

        return integerPart + "." + fractionalPart;
    }
    
    // Function to pad the shorter string with zeros at the end
    string padTrailingZeros(const string &str, size_t length)
    {
        if (str.size() < length)
        {
            return str + string(length - str.size(), '0');
        }
        return str;
    }
    
   // Function to pad the shorter string with zeros at the beginning
    string padLeadingZeros(const string &str, size_t length)
    {
        if (str.size() < length)
            return string(length - str.size(), '0') + str;
            
        return str;
    }
    
    // Function to compare two numbers represented as strings
    int compare_Strings(const string &num1, const string &num2)
    {
        // Compare integer parts
        if (num1.size() > num2.size())
            return 1;          // num1 is larger
        
        else if (num1.size() < num2.size())
            return -1;         // num2 is larger

        else
        {
         	 // Compare character by character
          	for (size_t i = 0; i < num1.size(); i++)
          	{
            		if (num1[i] > num2[i])
           	 		return 1;
            
           		 else if (num1[i] < num2[i])
   			        return -1;
           	}
         }
        // Both numbers are equal
        return 0;
    }
    
     string subtractNumericStrings(const string &num1, const string &num2, bool &borrowOut)
	{
    		string result;
    		borrowOut = false;    // Initialize borrow to false
    		bool resultIsNegative = false;
    
    
    		int borrow = 0;
    		int len1 = num1.length();
    		int len2 = num2.length();
    
                for (int i = 0; i < max(len1, len2); ++i)
         	 {
            		int digit1 = (i < len1) ? num1[len1 - i - 1] - '0' : 0;
            		int digit2 = (i < len2) ? num2[len2 - i - 1] - '0' : 0;
            		
        		// Subtract with borrow
        		int diff = digit1 - digit2 - borrow;
        		if (diff < 0)
       			{
       				diff += 10; 	 // Perform borrow
            			borrow = 1;
        		}
       			 else
       				borrow = 0;

 			 // Convert the digit back to a character and add to the result
       			 result = char(diff + '0') + result;
    		}

   			 // After the loop, check if there's a final borrow
   			 borrowOut = (borrow != 0);

    			// Remove leading zeros from the result
    			while (result.length() > 1 && result[0] == '0')
    			{
       				 result = result.substr(1);
    			}

    		       if(resultIsNegative)
    				result = "-" + result;
    	
		return result;
	}
	
     // Function to add two numeric strings
    string addNumericStrings(const string &num1, const string &num2, bool &carryOut)
    {
    
   	 string result;
         carryOut = false;                
         bool resultIsNegative = false;
        
       	 int carry = 0;
       	 int len1 = num1.length();
       	 int len2 = num2.length(); 

        // Perform addition from right to left
        for (int i = 0; i < max(len1, len2); ++i)
        {
            int digit1 = (i < len1) ? num1[len1 - i - 1] - '0' : 0;
            int digit2 = (i < len2) ? num2[len2 - i - 1] - '0' : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            sum %= 10;           
            result = char(sum + '0') + result;
     
        }
         // If there is any remaining carry, add it to the beginning of the result
        if (carry > 0) 
            result = char(carry + '0') + result;
        
        // After the loop, check if there's a final carry
    	carryOut = (carry > 0);
        
        // Return the final result and update the carry out
        carryOut = carry;
        return result;
        
    }
    
     // Implementation of subtractStrings function that handles integer and fractional parts
    Float subtractStrings(string &int1, string &int2, string &frac1, string &frac2)
    {
        // Determine the maximum length of the fractional parts
        size_t maxLengthFractional = max(frac1.size(), frac2.size());

        // Pad fractional parts to the same length
        frac1 = padTrailingZeros(frac1, maxLengthFractional);
        frac2 = padTrailingZeros(frac2, maxLengthFractional);

        // Perform subtraction on fractional parts
        bool borrowFromFractional = false;
        string resultFractional = subtractNumericStrings(frac1, frac2, borrowFromFractional);

        // Determine the maximum length of the integer parts
        size_t maxLengthInteger = max(int1.size(), int2.size());

        // Pad integer parts to the same length
        int1 = padLeadingZeros(int1, maxLengthInteger);
        int2 = padLeadingZeros(int2, maxLengthInteger);

        // Perform subtraction on integer parts
        bool borrowFromInteger = false;
        string resultInteger = subtractNumericStrings(int1, int2, borrowFromInteger);
	      

        // Handle borrow from fractional subtraction
        if (borrowFromFractional) 
                    resultInteger = subtractNumericStrings(resultInteger, "1", borrowFromInteger);  // Subtract 1 from integer part

        resultFractional = (resultFractional[0] == '-') ? resultFractional.substr(1) : resultFractional;

        // Clean up leading and trailing zeros in the result
        resultInteger = removeLeadingZeros(resultInteger);
        resultFractional = removeTrailingZeros(resultFractional);

        // Create the final result as a Float
        InfiniteArithmetic::Float result;
        result.integerPart = resultInteger;
        result.fractionalPart = resultFractional;

        return result;
    }
    
    // Addition function for strings
     Float addStrings( string &int1, string &int2, string &frac1, string &frac2)
    {
         // Determine the maximum length of the fractional parts
        size_t maxLengthFractional = max(frac1.size(), frac2.size());
        
        // Pad fractional parts to the same length
        frac1 = padTrailingZeros(frac1, maxLengthFractional);
        frac2 = padTrailingZeros(frac2, maxLengthFractional);
        
        // Perform addition on fractional parts
        bool carryFromFractional = false;
        string resultFractional = addNumericStrings(frac1, frac2, carryFromFractional);

        // Determine the maximum length of the integer parts
        size_t maxLengthInteger = max(int1.size(), int2.size());

        // Perform subtraction on integer parts
        bool carryFromInteger = false;
        string resultInteger = addNumericStrings(int1, int2, carryFromInteger);
        
         // Handle carry from fractional subtraction
        if (carryFromFractional)
        {
            // add 1 to integer part 
            resultInteger = addNumericStrings(resultInteger, "1", carryFromInteger);
        }

        InfiniteArithmetic::Float result;
        
        if(resultFractional.size() > maxLengthFractional)
        {
        	resultFractional = resultFractional.substr(1);
        }
        
         // Clean up leading and trailing zeros in the result
        removeLeadingZeros(resultInteger);
        removeTrailingZeros(resultFractional);
        
        // Create the final result as a Float      
        result.integerPart = resultInteger;
        result.fractionalPart = resultFractional;

        return result;
     }
      
      bool isZero(const string &num)
      {
      	for(int i = 0; i < num.size() -1 ; i++)
      	{
      		if(num[i] != '0')
      			return false;
      	}
      	return true;
      }
     
     string multiplyStrings(string &num1, string &num2) 
     {
    		size_t len1 = num1.size();
    		size_t len2 = num2.size();
    
   		 // Initialize the result array with zeroes
    		 vector<int> result(len1 + len2,0);
    
   		 // Multiply the numbers digit by digit
   		 for (int i = len1 - 1; i >= 0; --i)
    		 {
    	   		 for (int j = len2 - 1; j >= 0; --j) 
    		    	 {
    	        		int product = (num1[i] - '0') * (num2[j] - '0');
    	        		int sum = product + result[i + j + 1];
    	        
    	        		// Update the result array
    	        		result[i + j + 1] = sum % 10;
    	        		result[i + j] += sum / 10;
    		      	 }
   	 	}
    
    		// Convert the result array back to a string
	    	string strResult;
	    	bool leadingZero = true;
	    	for (int num : result) 
	    	{
	        	if (leadingZero && num == 0) 
	            	continue; // Skip leading zeros
	        
		        leadingZero = false;
		        strResult.push_back(num + '0');
	        }
    
    		// If the result is empty (all zeroes), return "0"
	       return strResult.empty() ? "0" : strResult;
	}
  
    // Operator overload for addition
    Float Float::operator+(const Float &other) const
    {    
         // Determine if the operands are negative
        bool num1IsNegative = integerPart[0] == '-';
        bool num2IsNegative = other.integerPart[0] == '-';
        
        // Prepare the absolute values for the operation
        Float absNum1 = num1IsNegative ? Float(integerPart.substr(1) + '.' + fractionalPart) : *this;
        Float absNum2 = num2IsNegative ? Float(other.integerPart.substr(1) + '.' + other.fractionalPart) : other;
        
        Float result;
         
         if (num1IsNegative && num2IsNegative)       // Both operands are negative, perform addition and keep result negative
         {
              result = absNum1 + absNum2;
              result.integerPart = '-' + result.integerPart;   	
         }
         else if (num1IsNegative && !num2IsNegative)// If the first number is negative and the second is positive, perform subtraction
            return absNum2 - (absNum1);
            
         else if (!num1IsNegative && num2IsNegative) // If the first number is positive and the second is negative, perform subtraction
            return absNum1 - (absNum2);

        else
        	result = addStrings(absNum1.integerPart, absNum2.integerPart, absNum1.fractionalPart, absNum2.fractionalPart);   
        
        return result; 
    }  

    // Operator overload for subtraction
    Float Float::operator-(const Float &other) const
    {
        // Determine if the operands are negative
        bool num1IsNegative = integerPart[0] == '-';
        bool num2IsNegative = other.integerPart[0] == '-';

        // Prepare the absolute values for the operation
        Float absNum1 = num1IsNegative ? Float(integerPart.substr(1) + '.' + fractionalPart) : *this;
        Float absNum2 = num2IsNegative ? Float(other.integerPart.substr(1) + '.' + other.fractionalPart) : other;
        
        // Initialize the result
        Float result;

        if (num1IsNegative && num2IsNegative)
            // Both operands are negative
            result = absNum2 - absNum1;

        else if (num1IsNegative  && !num2IsNegative)
        {
            // num1 is negative and num2 is positive
            result = absNum1 + absNum2;
            result.integerPart = '-' + result.integerPart;
        }
        else if (num2IsNegative && !num1IsNegative)
         {
            // num1 is positive and num2 is negative
            result = absNum1 + absNum2;
         }
        else
        {
            // Both operands are positive: num1 - num2
            // Determine if the absolute value of num1 is less than num2
            if (compare_Strings(absNum2.integerPart, absNum1.integerPart) > 0)     
            {
                // num1 < num2, swap operands and negate the result
                result = absNum2 - absNum1;
                result.integerPart = '-' + result.integerPart;
            }
            else           // num1 >= num2, perform normal subtraction
                result = subtractStrings(absNum1.integerPart, absNum2.integerPart, absNum1.fractionalPart, absNum2.fractionalPart);
        }
        
        return result;
    }
       
     // Operator overload for multiplication
    Float Float::operator*(const Float &other) const 
      {
        
       	// Determine the signs of the input numbers
    	bool isNegative1 = integerPart[0] == '-';
    	bool isNegative2 = other.integerPart[0] == '-';
    
    	// Prepare the input strings by removing the signs if necessary
    	string absNum1 = isNegative1 ? integerPart.substr(1) + fractionalPart : integerPart + fractionalPart;
    	string absNum2 = isNegative2 ? other.integerPart.substr(1) + other.fractionalPart : other.integerPart + other.fractionalPart;
    	
    	string result;
    	
    	if(isZero(absNum1) || isZero(absNum2))
    	{
    		result = "0";
        	return Float(result); 
        }
             
    	// Calculate the total length of the fractional part in the result
    	size_t totalFractionalLength = fractionalPart.size() + other.fractionalPart.size();
    
    	// Multiply the absolute values of the numbers using the string multiplication function
    	result = multiplyStrings(absNum1, absNum2);
    
   	// Determine the sign of the final result based on the input signs
    	bool isResultNegative = (isNegative1 != isNegative2);
    
    	// Calculate the integer and fractional parts of the result
   	// Insert a decimal point at the appropriate position
    	string integerPartResult;
    	string fractionalPartResult;
    
    	if (result.size() <= totalFractionalLength) 
    	{
        	// If the length of the result is less than or equal to the total fractional length,
        	// prepend zeros to integer part
       	        integerPartResult = "0";
       	        fractionalPartResult = string(totalFractionalLength - result.size(), '0') + result;
        } else 
   	 {
       		 integerPartResult = result.substr(0, result.size() - totalFractionalLength);
       		 fractionalPartResult = result.substr(result.size() - totalFractionalLength);
    	 }
    
    	// Remove leading and trailing zeros from the integer and fractional parts
    	removeLeadingZeros(integerPartResult);
    	removeTrailingZeros(fractionalPartResult);
    
   	 // Add a negative sign to the integer part if the result is negative
    	if (isResultNegative) 
    	{
        	integerPartResult = "-" + integerPartResult;
        }
    
   	 // Construct and return the final Float result
   	 return Float(integerPartResult + "." + fractionalPartResult);
     }      
}  