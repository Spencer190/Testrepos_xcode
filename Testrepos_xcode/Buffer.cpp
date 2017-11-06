// Buffer.cpp

#include "Buffer.h"
#include "FileViewer.h"

#include <fstream>
#include <iomanip>
#include <iostream>
using std::cout;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;//n

void Buffer::display() const
{
    int ix_stop_line_ = ix_top_line_ + window_height_;
    for (int i = ix_top_line_; i < ix_stop_line_; ++i) {
        if (i < v_lines_.size())
            cout << std::setw(6) << i+1 << "  " << v_lines_[i];
        cout << '\n';
    }
}

bool Buffer::open(const string & new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file)
        return false;

    v_lines_.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.
    browser_files_.clear();//n
    link_num_ = 1;
    string line;
    while (getline(file, line))
        v_lines_.push_back(line);

    file_name_ = new_file_name;
    ix_top_line_ = 0;
    return true;
}
void Buffer::format_lines()
{
    
    for (int i = 0; i < v_lines_.size(); i++) {
        int start_index = v_lines_[i].find ("<");
        int end_index = v_lines_[i].find (">");
        int anchor_length = end_index - start_index;
        
        if (start_index == -1) {
            continue;
        } else {
            string text = v_lines_[i].substr(start_index, end_index);
            istringstream iss(text);
            string start_of_anch;
            string browser_file_name;
            string anchor_text;
            iss >> start_of_anch >> browser_file_name >> anchor_text;
            browser_files_.push_back(browser_file_name);
            
            string anchor;
            anchor = "<" ;
            anchor += anchor_text;
            anchor += "[";
            anchor += (link_num_ + '0');
            anchor += "]";
            v_lines_[i].replace(start_index, anchor_length +1, anchor);
            link_num_++;
        }
    }
    
}

void Buffer::size_lines()
{
    string word;
    string line;
    string chunk;
    string start_of_new_paragraph;
    for (int i= 0; i < v_lines_.size(); i++) {
        if (v_lines_[i] == "\n") {
            istringstream iss(v_lines_[i]);
            iss >> start_of_new_paragraph;
        } else {
            chunk += v_lines_[i]+ " ";
        }
    }
    istringstream iss(chunk);
    int length_of_line = 0;
    while (iss >> word) {
        word += ' ';
        length_of_line += word.size();
        if(length_of_line < line_size_) {
            line += word;
        } else {
            formatted_lines_.push_back(line);
            int size = formatted_lines_.size();
            if (formatted_lines_[size].find(start_of_new_paragraph)) formatted_lines_.push_back ("\n");
            length_of_line = word.size();
            line = word;
        }
    }
    if(iss.eof()) formatted_lines_.push_back(line);
}
