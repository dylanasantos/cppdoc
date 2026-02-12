**cppdoc:**
  cppdoc is a C++ function declaration documenter based off of programs such as Doxygen or pydoc. cppdoc reads the given program as a text file and will navigate through all function definitions (with the exception of main), along with their additional cppdoc comments, annd will display these functions on an HTML-Style format.

  cppdoc format:
  
    string function_example(int some_value, string other_value = "default")
    {
        /*
            DEF: A function that iterates through a string, but skips based off int value some_string.
    
            ARGS:
                some_value: indexer
                other_value:     string being indexed
    
            RET: A modified value of the string.
    
            EX: function_example(2, "Hello World!") >>>HloWrd
            EX: function_example(0, "Hello World!") >>> Hello World!
        */
    
       string return_value;
       return return_value;
    }

  cppdoc is meant to be a flexible, yet syntax-focused documenter. There are tokens for documentation similar to other formaters such aspydoc, as shown above: "DEF", "ARGS", "RET", and "EX". While the user has the option to define (or not define) any and all of these 4 blocks in a fucntion, cppdoc requires a "DEF" block if any other block is included, and no block can repeat other than "EX".

  When declaring an ARGS block, atleast one variable is required with a proper definition, however cppdoc will not check for the validity of the variable you store.

  While cppdoc is considerate of whitespace, early versions of this program will rely on the smart_file_read() function which can arise potential, undiscovered bugs. In later versions, type_cast_file_read() will become available, along with input_file().


  **Difference in function calls:**

  **smart_file_read(string file_name = "main.cpp", bool activate_console = false, bool update_html = true):**
    Reads entire program, looks for standard function definition pattern, if a full pattern is met, the function becomes documented. Requires a file name (or searches for a main.cpp file), has the ability for users to print out their documentation to the shell, and the ability to enable/disable html documentation updates.

  **type_cast_file_read():** //TBD: v0.9
    Reads the entire program, looking for commennts specifically marked with "!CPPDOC", then documents them with their respective information.

  **input_file():** //TBD: v0.9
    Reads a requested file through the console.

  Later versions of cppdoc will come with more editing options on documentation style, ontop of progrsam optimisations, and more inclusive formatting (such as JSON).


**How it works:**
  cppdoc iterates through any .cpp file, searching for function declarations, storing each function in a struct data type called function, which are then located inside a vector. For smart_file_read(), the program will search line by line top to bottom looking for both an opening, and closing parenthesis on the same line. If a line meets this criteria, it is stored as a possible function string. If an opening brace is found after its declaration, then the string will be pushed into a vector for later formatting. Given another set of parenthesis is found before the declaration of an opening bracket, cppdoc will replace the possible function string with the new line.
  
  Once all strings have been recovered, cppdoc will then reformat each string given in order to properly fit each value into its respective function struct. This includes autofilling certain pieces of data with N/A that have not been filled.
  
  Afterwards, cppdoc will check if there was a request for console printing, and HTML documenting. If cppdoc is requested to document an HTML file, it will take the name of the program given, and create a .html extension, which will then manually format the html code through strings, allowing for better source code readability, and flexibility.

**[ABOUT VERSION 0.8]**
Version 0.8 does not come with all intended packages & optimizations, version 0.9 will come with more catch case scenarios & options, however cppdoc v0.8 is able to handle most common cases you will find in function declarations.
