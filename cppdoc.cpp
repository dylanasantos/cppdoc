//CPPDOC VERSION 0.8
#include "cppdoc.h"

#include<iostream>
#include<fstream>
#include<ostream>

#include<vector>
#include<unordered_map>

using namespace std;

struct function
{
    string return_type;
    string name;

    vector<string> param_var_name;
    vector<string> param_data_type;
    vector<string> param_default;

    string main_definition;
    unordered_map<string, string> args;
    string return_definition = "N/A";
    vector<string> examples;
};



string format_line(string line)
{
    string temp = line;

    size_t colon_pos = (line.find(':'));
    if (colon_pos == string::npos) return "";

    do
    {
        colon_pos++;
    } while(temp[colon_pos] == ' ');

    return temp = temp.substr(colon_pos);
}



void console_display(vector<function> fn_list)
{
    for(function fn : fn_list)
    {
        cout << "\n!CPPDOC FUNCTION DECLARATION:\n";
        
        cout << "Function Name: " << fn.name << "\n";
        cout << "Return Type: " << fn.return_type << "\n\n";

        cout << "DEF: " << fn.main_definition << "\n";
        cout << "RET: " << fn.return_definition << "\n\n";

        cout << "Function Value(s):\n";
        for(int i = 0; i < fn.param_data_type.size(); i++)
        {
            cout << "{Data Type Name: " << fn.param_var_name.at(i) << " || Data Type: " 
            << fn.param_data_type.at(i) << " || Default Value: " << fn.param_default.at(i) << "}\n"
            "ARG DEF: " << fn.args.at(fn.param_var_name.at(i)) << "\n\n";
        }

        cout << "EX(s):\n";
        for(int i = 0; i < fn.examples.size(); i++)
        {
            cout << "{" << fn.examples.at(i) << "}\n";
        }
        cout << endl;
    }
}


    //TODO IN v1.0 -> add href link to program origin
 void create_documentation(vector<function> fn_list, string file_name, size_t cpp_extension)
{
    string program_name = file_name.substr(0, cpp_extension);
    string html_file_name = program_name + (".html");

    ofstream html_document(html_file_name);
    if(html_document.is_open())
    {
            html_document <<
                "<!DOCTYPE html>" "\n"
                R"(<html lang="en">)" "\n"
                "<head>" "\n"
                    "\t" R"(<meta charset="UTF-8">)" "\n"
                    "\t" R"(<meta name="viewport" content="width=device-width, initial-scale=1.0">)" "\n"
                    "\t<title>" + program_name + "</title>\n"
                "</head>" "\n\n"
                "<body>" "\n"
                    "\t<h1>" + program_name + "</h1>\n"
                    "\t" R"(<h2 style="padding-left: 20px;">)" "Functions:</h2>\n";
            
            for(function fn : fn_list)
            {
                html_document <<
                    "\n\t\t" R"(<section style="padding-left: 60px;">)" "\n"
                        "\t\t\t" R"(<h3 style="margin-bottom: -10px;">)" + fn.return_type + " " + fn.name + "(values)</h3>" "\n"
                        "\t\t\t" R"(<div style="padding-left: 30px;">)" "\n"
                            "\t\t\t\t" "<p>" + fn.main_definition + "</p>" "\n"
                            "\t\t\t\t" R"(<h4 style="margin-bottom: -10px;">Parameters:</h4>)" "\n"
                            "\t\t\t\t<ul>\n";
                for(int i = 0; i < fn.param_var_name.size(); i++)
                {
                    string var_name = fn.param_var_name.at(i);
                    html_document << 
                        "\t\t\t\t\t<li>\n" 
                            "\t\t\t\t\t\t" R"(<p style="margin-bottom: -10px;">)" + fn.param_data_type.at(i) + " " + var_name +
                            " (Default Value = " + fn.param_default.at(i) + ")</p>\n"
                            "\t\t\t\t\t\t" R"(<p style="padding-left: 10px;">)" + fn.args.at(var_name) + "</p>\n"
                         "\t\t\t\t\t</li>\n";
                }
                html_document <<
                    "\t\t\t\t</ul>\n"
                    "\t\t\t</div>\n"
                    "\t\t</section>\n"
                    "\t\t<br>\n";
            }
                
            html_document <<        
            "</body>" "\n"
            "</html>";
    }
    else
    {
        cerr << "!CPPDOC; Unexpected Error at Runtime -> @create_documentation() unable to create " + html_file_name << "\n";
        throw runtime_error("!CPPDOC; @create_documentation() [ofstream]: " + html_file_name + " != open");
    }
    html_document.close();
}



void inspect_declr(function &fn, string line)
{
    string temp = line;
    function inspecting_fn;

    size_t open_pos = temp.find('(');
    size_t close_pos = temp.find(')');
    temp[open_pos] = ' ';
    temp[close_pos] = ' ';

    while(temp.find(',') != string::npos)
        temp.erase(temp.find(','), 1);
        
    while(temp.find("  ") != string::npos)
        temp.erase(temp.find("  "), 1);
    

    size_t start = 0;
    bool is_default = false;
    bool is_data_type = true;

    for(size_t i = 0; i < temp.length(); i++)
    {
        char current_pos = temp[i];
        string sub = temp.substr(start, i - start);

        if(current_pos == '=') //default value
        {
            do
            {
                i++;
                start++;
            } while (temp[start] == ' ');

            is_default = true;
            continue;
        }

        if(current_pos == ' ')
        {
            if(is_default)
            {
                fn.param_default.back() = sub;
                is_default = false;

                start = i + 1;
                continue;
            }

            if(fn.return_type.empty())
            {
                fn.return_type = sub;
            }
            else if(fn.name.empty())
            {
                fn.name = sub;
            }
            else if(is_data_type)
            {
                fn.param_data_type.push_back(sub);
                is_data_type = false;
            }
            else
            {
                fn.param_var_name.push_back(sub);
                fn.param_default.push_back("N/A");
                is_data_type = true;

                if(!fn.args.count(fn.param_var_name.back()))
                {
                    fn.args[fn.param_var_name.back()] = "N/A";
                }
            }
            start = (i < temp.length() - 1) ? i + 1 : 0;
        }
    }
}




void smart_file_read(string file_name, bool activate_console, bool update_html) //Default value = "main.cpp"
{
    vector<function> functions;
    vector<string> function_declares;

    size_t cpp_extension = file_name.find(".cpp");
    if(file_name.find(".cpp") == string::npos) 
    {
        cerr << "!CPPDOC Error; Given file is not a cpp document\n";
        throw invalid_argument("!CPPDOC; @smart_file_read() [file: " + file_name + " != .cpp");
    }

    fstream file(file_name);
    if(!file)
    {
        cerr << "!CPPDOC; Error reading file -> @smart_file_read() File not found. [file: " << file_name << "]\n";
        throw invalid_argument("!CPPDOC; @smart_file_read() [file: " + file_name + " == !file");
    }

    string possible_function;

    bool in_function = false;
    bool in_comment = false;
    bool in_ext_comment = false;

    bool def_found = false;
    bool in_args = false;
    bool ret_found = false;

    string line;
    while(getline(file, line))
    {
        int op_pos = -1;
        int cp_pos = -1;
        
        // Works for iterating for functions on a global scope
        for(int char_index = 0; char_index < line.length(); char_index++)
        {
            char current_char = line[char_index];

            if(in_ext_comment) //Skips over multi-line comment regions not apart of function declarations
            {
                if((char_index < line.length() - 1) && (current_char == '*' && line[char_index + 1] == '/'))
                    in_ext_comment = false;
                else
                    break;
            }

            if((char_index < line.length() - 1) && (current_char == '/' && line[char_index + 1] == '/')) break; //Remainder of line is commented
            if(current_char == ';') break;

            if(current_char == '(')
            {
                op_pos = char_index;
            }
            else if(op_pos > -1 && current_char == ')')
            {
                cp_pos = char_index;
                possible_function = line.substr(0, cp_pos + 1);
            }
            else if(current_char == '{' && !possible_function.empty())
            {
                if(possible_function.find("main(") != string::npos) break; //removes main function from being considered 

                function temp;
                functions.push_back(temp);

                function_declares.push_back(possible_function);
                in_function = true;

                possible_function.clear();
            }
            if((char_index < line.length() - 1) && (current_char == '/') && (line[char_index + 1] == '*')) //Checking for the /* under function declaration
            {
                if(in_function) in_comment = true;
                else in_ext_comment = true;
            }
            else if(current_char == '}')
            {
                in_function = false;
                in_comment = false;

                def_found = false;
                ret_found = false;

                op_pos = -1;
                cp_pos = -1;
            }
        }

    
        if(in_comment && (line.find("DEF") != string::npos))
        {
            if(def_found)
            {
                cerr << "!CPPDOC; DEF block was declared twice in singular cppdoc comment\n";
                throw invalid_argument("!CPPDOC; @smart_file_read() DEF @[" + function_declares.back() + "] >= 2");
            }

            functions.back().main_definition = format_line(line);;
            def_found = true;
        }
            if((line.find("RET") != string::npos))
            {
                if(!def_found)
                {
                    cerr << "!CPPDOC; REF block was declared before DEF in cppdoc comment\n";
                    throw invalid_argument("!CPPDOC; @smart_file_read() DEF @[" + function_declares.back() + "] == null");
                }
                if(ret_found)
                {
                    cerr << "!CPPDOC; RET block was declared twice in singular cppdoc comment\n"; 
                    throw invalid_argument("!CPPDOC; @smart_file_read() RET @[" + function_declares.back() + "] >= 2");
                }

                functions.back().return_definition = format_line(line);;
                ret_found = true;
                in_args = false;
            }
            else if(line.find("EX") != string::npos)
            {
                if(!def_found)
                {
                    cerr << "!CPPDOC; EX block was declared before DEF in cppdoc comment\n";
                    throw invalid_argument("!CPPDOC; @smart_file_read() DEF @[" + function_declares.back() + "] == null");
                }

                functions.back().examples.push_back(format_line(line));
                in_args = false;
            }
            else if(line.find("ARGS") != string::npos)
            {
                if(in_args)
                {
                    cerr << "!CPPDOC; ARGS block was declared twice in singular cppdoc comment\n";
                    throw invalid_argument("!CPPDOC; @smart_file_read() ARGS @[" + function_declares.back() + "] >= 2");
                }
                in_args = true;
            }
            else if(in_args)
            {
                string arg_def;
                string arg_var;

                size_t colon_pos = line.find(':');
                if (colon_pos == string::npos) continue;

                int starting_index = 0;
                int ending_index = colon_pos;

                while(ending_index - 1 == ' ')
                    ending_index--;

                while(starting_index < ending_index && line[starting_index] == ' ')//grabbing variable side
                    starting_index++;

                arg_var = line.substr(starting_index, colon_pos - starting_index );

                starting_index = colon_pos;
                do //grabbing definition side   <-format better for v0.9
                {
                    starting_index++;
                } while(starting_index < line.length() && line[starting_index] == ' ');
                arg_def = line.substr(starting_index);

                if (arg_var.length() == 0 || arg_var == " ")
                {
                    cerr << "!CPPDOC; ARGS variable pronounced (':'), but no name was given\n";
                    throw invalid_argument("!CPPDOC; @smart_file_read() ARGS @[" + function_declares.back() + "]");
                }

                if(arg_def.length() == 0) arg_def = "N/A";
                functions.back().args[arg_var] = arg_def;

                //NOTE: EX still needs to be properly formatted <- Work on in v0.9
            }
        }
    file.close();
    
    for(int i = 0; i < function_declares.size(); i++)
        inspect_declr(functions.at(i), function_declares.at(i)); //formatting function vars based off function_declares strings

    if(activate_console) console_display(functions);
    if(update_html) create_documentation(functions, file_name, cpp_extension);
}



void type_cast_file_read(string file_name, bool title_inclusive, bool activate_console, bool update_html)
{ //TODO: Finish on cppdoc_v0.9

}



void input_file() //Allows for direct input into console
{
    string file_name;

    cout << "CPPDOC: Enter file for scan or (q)uit: ";
    getline(cin, file_name);

    if (file_name == "q" || file_name == "Q")
    {
        cout << "CPPDOC: Quitting scan...\n";
        return;
    }
    
    fstream file(file_name); //TODO: Finish on cppdoc_v1.0
    if(!file)
    {
        cerr << "!CPPDOC; Error reading file -> @input_file() File not found. [file: " << file_name << "]\n";
        throw invalid_argument("!CPPDOC; @input_file() [file: " + file_name + " == !file");
    }
}