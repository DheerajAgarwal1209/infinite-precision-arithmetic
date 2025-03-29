#include<bits/stdc++.h>
#include "infinitearithmetic.h"
using namespace std;

int main(int argc, char* argv[])
{
    // Implementation of the my_inf_arith executable
    if (argc != 5) 
    {
        cerr << "Usage: " << argv[0] << " <int/float> <add/sub/mul/div> <operand1> <operand2>\n";
        return 1;
    }

    // Parse command line arguments
    string type = argv[1];
    string operation = argv[2];
    string operand1 = argv[3];
    string operand2 = argv[4];

    // Perform the arithmetic operation based on the input
    if (type == "int")
     {
        InfiniteArithmetic::Integer num1 = InfiniteArithmetic::Integer::parse(operand1);
        InfiniteArithmetic::Integer num2 = InfiniteArithmetic::Integer::parse(operand2);
        InfiniteArithmetic::Integer result;

        if (operation == "add") 
           result = num1 + num2;
        else if (operation == "sub") 
           result = num1 - num2;
        else if (operation == "mul") 
           result = num1 * num2;
        else {
            cerr << "Invalid operation: " << operation << endl;
            return 1;
        }
        cout<<result<<endl;
     }   
    else if(type == "float")
     {
     	InfiniteArithmetic::Float num1 = InfiniteArithmetic::Float::parse(operand1);
        InfiniteArithmetic::Float num2 = InfiniteArithmetic::Float::parse(operand2);
        InfiniteArithmetic::Float result;

        if (operation == "add") 
           result = num1 + num2;
        else if (operation == "sub") 
           result = num1 - num2;
        else if (operation == "mul") 
           result = num1 * num2;
        else 
        {
            cerr << "Invalid operation: " << operation << endl;
            return 1;
        }     

        // Print the result
        cout<< result << endl; 
         
      }  
     else 
     {
        cerr << "Invalid type: " << type << endl;
        return 1;
     }
    return 0;
}