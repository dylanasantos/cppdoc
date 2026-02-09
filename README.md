# cppdoc
Stemming off the concept of the pydoc library. cppdoc is meant to read function comments created by users in a neat formatting, which automates HTML documentation of the intended functions.

As cppdoc is developed, it will become smarter & more able to detect cppdoc comments off the syntax of multi-lined comments inside functions.

IMPROTANT FUNCTION CALLS:

  smart_file_read(file_name = "main.cpp", activate_console = false, update_html = true)
    Reads input file as a text file, and will detect cppdoc comments based off the syntax of multi-lined comments inside of function definitions. As cppdoc develops, detection of cppdoc comments is meant to become smarter (considering fucntions inside classes, structs, etc), and optomized. Here's an example of a function smart_file_read() would work on:

    string function_example(int x, string y = "default")
    {
        /*
            DEF: function definition

            RET: string skipping every x amount of characters the user inputs

            EX: function_example(2, "hello world") >>> hlwl
        */
        string temp;
          //code block
        return temp;
    }

    //in main
    int main()
    {
        smart_file_read("example.cpp");

        return 0;
    }

  NOTE: RET and EX are optional inputs, cppdoc will document the function as long as "DEF" is defined, if RET and EX are not defined, then RET will autofill with the given data type, and EX: will autofill with N/A. If inputting EX, make sure to include ">>>" so cppdoc understands the return, and multiple EX: lines can be made.


  direct_file_read(file_name = "main.cpp", title_inclusive = false, activate_console = false, update_html = true)
    Reads input file as text file, and will detect cppdoc comments based off those that have !CPPDOC written inside them, this allows for the exact file reading you want or expect when smart_file_read() doesnt provide properly. For direct_file_read(), the comment should be underneath the desired function. Spacing is allowed, but no characters should interfere between the declaration and the comment. 
    
    string function_example(int x, string y = "default")
    {
        /*
            !CPPDOC
            DEF: function definition

            RET: string skipping every x amount of characters the user inputs

            EX: function_example(2, "hello world") >>> hlwl
        */
        string temp;
          //code block
        return temp;
    }

    //in main
    int main()
    {
        direct_file_read("example.cpp");

        return 0;
    }
  There may be a unexpected scenario where cppdoc does not properly read the function. If this is the case, set the title_inclsuive variable to "true", then define your cppdoc comment as such:
    
    string function_example(int x, string y = "default")
    {
        /*
            !CPPDOC
            string function_example(int x, string y = "default")
            DEF: function definition

            RET: string skipping every x amount of characters the user inputs

            EX: function_example(2, "hello world") >>> hlwl
        */
        string temp;
          //code block
        return temp;
    }

    //in main
    int main()
    {
        direct_file_read("example.cpp", true);

        return 0;
    }

  cppdoc is intended to be able to read all functional syntax. However, if the user adds multiple DEF or RET blocks underneath either file_read() functions, an error will be thrown on runtime to imrpove documentation understanding and formatting.

  cppdoc comes with a very standard HTML formatting style, but further down in development, multiple HTML presets will be offered to the user.

  For debugging purposes, cppdoc also gives you the option to print out to the console. Console printing is activated by the activate_console variable in both read functions. When activate_console is set to true, cppdoc will update HTML files still, if you do not want to update the HTML files, set update_html to false.
