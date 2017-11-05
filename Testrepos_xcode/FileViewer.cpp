// FileViewer.cpp

#include "FileViewer.h"
#include "Buffer.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

void FileViewer::display()
{
    const string long_separator(50, '-');
    const string short_separator(8, '-');

    if (!error_message_.empty()) {
        cout << "ERROR: " + error_message_ << endl;
        error_message_.clear();
    }

    string file_name = buffer_.get_file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer_.display();
    cout << long_separator << endl;
    cout << "  next  previous  open  quit\n";
    cout << short_separator << endl;
}

void FileViewer::run()
{
    cout << "Window height? ";
    cin >> window_height_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_height(window_height_);
    
    cout << "Line size? ";
    cin >> line_size_;
    cin.get(); //'\n'
    cout << '\n';
    buffer_.set_line_size(line_size_);
    
    bool done = false;
    while (!done) {
        display();

        cout << "choice: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        //execute_command(command, done);
        switch (command) {
            case 'n': {
                buffer_.move_to_next_page();
                break;
            }
                
            case 'o': {
                cout << "file name: ";
                string file_name;
                getline(cin, file_name);
                if (!buffer_.open(file_name))
                    error_message_ = "Could not open " + file_name;
                buffer_.format_lines();
                buffer_.size_lines();
                buffer_.first_link();
                break;
            }
                
            case 'p': {
                buffer_.move_to_previous_page();
                break;
            }
                
            case 'q': {
                done = true;
                break;
            }
                
            case 'b': {
                string file = buffer_.previous_file();
                if(!buffer_.open(file))
                    error_message_ = "Could not open " + file;
                buffer_.format_lines();
                buffer_.size_lines();
                break;
            }
            case 'g': {
                cout << "link number: ";
                int anchor_num;
                cin >> anchor_num;
                string file_name = buffer_.linked_files (anchor_num-1);
                if (!buffer_.open(file_name))
                    error_message_ = "Could not open " + file_name;
                buffer_.format_lines();
                buffer_.size_lines();
                anchor_num = 0;
                
                break;
            }
        }
        cout << endl;
    }//while
    return;
}


