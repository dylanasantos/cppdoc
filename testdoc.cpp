#include<iostream>

#include "cppdoc.h"

using namespace std;

/*
    This is a test file to test the cppdoc.h header file and its functions.

    In actual applications, this file should be removed
*/

string x = string("Hello"); //example of how only functions are considered for global scope

//Example of how cppdoc can be used:
string function_example(int some_value, string other_value =    "default")
{
    /*
        DEF: A function that iterates through a string, but skips based off int value some_string.

        ARGS:
            some_value:               
            other_value:     string being indexed

        RET: A modified value of the string.

        EX: function_example(2, "Hello World!") >>>HloWrd
        EX: function_example(0, "Hello World!") >>> Hello World!
    */

   string return_value;
   return return_value;
}

string other(     int   some_value =388  ,    string  other_value = "def") //spacing is irrelevant to cppdoc!
{
    /*
        DEF: Another, unique function

        ARGS: 
            some_value: Special value

        RET: A modified value of the string.

        EX:     function_example(2, "Hello World!") >>>   HloWrd
        Spacing and text prior to the definitions are ignored -> EX:function_example(0, idk) >>> idk
    */

   string return_value;
   return return_value;
}


void function_name()
{
}
//NOTE: cppdoc requires the "DEF:" declaration to be documented at minimum, the other will autofill to "N/A" 
//The function type, paramter types, and default variables will automatically be documented

//cppdoc will not naturally catch certain function types, such as lambdas. In these cases, if you want notation, simply put "!cppdoc" and the regular comment style

int main()
{
    bool activate_console = true;
    bool update_html = true;

    smart_file_read("testdoc.cpp", activate_console, update_html);

    return 0;
}