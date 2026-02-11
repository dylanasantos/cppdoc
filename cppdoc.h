#ifndef CPPDOC_H
#define CPPDOC_H

#include<string>

void smart_file_read(std::string file_name = "main.cpp", bool activate_console = false, bool update_html = true);

void type_cast_file_read(std::string file_name, bool title_inclusive = false, bool activate_console = false, bool update_html = true);

void input_file();

#endif // CPPDOC_H