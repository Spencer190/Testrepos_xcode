// Buffer.h

#ifndef _Buffer_h_
#define _Buffer_h_

#include <vector>
using std::vector;

#include <string>
using std::string;

class Buffer
{

public:
    void display() const;
    const string & get_file_name() const {return file_name_;}
    void move_to_next_page();
    void move_to_previous_page();
    bool open(const string& file_name_);
    void set_window_height(int h) {window_height_ = h;}
    void set_line_size(int s) {line_size_=s;}
    void first_link ();
    void size_lines ();//DO WE NEED THIS?????????????
    void format_lines ();//DO WE NEED THIS?????????????
    string previous_file ();
    string linked_files(const int & anchor_num);
    
private:
    vector<string> v_lines_;
    vector<string> formatted_lines_;
    vector<string> browser_files_;
    vector<string> files_opened_;
    
    string file_name_;
    
    int ix_top_line_ = 0;
    int line_size_;
    int window_height_;
    int link_num_ = 1;
    int num_of_linked_files_ = 0;
};

inline void Buffer::move_to_next_page() {
    if(ix_top_line_ + window_height_ < v_lines_.size()){
        ix_top_line_ += window_height_;
    }
}

inline void Buffer::move_to_previous_page() {
    if(ix_top_line_ > 0){
        ix_top_line_ -= window_height_;
    }
}

inline void Buffer::first_link () {
    files_opened_.clear();
    files_opened_.push_back(file_name_);
    num_of_linked_files_ = 1;
}

inline string Buffer::linked_files(const int & anchor_num) {
    files_opened_.push_back(browser_files_[anchor_num]);
    num_of_linked_files_ = files_opened_.size() - 1;
    return browser_files_[anchor_num];
}

inline string Buffer::previous_file() {
    num_of_linked_files_--;
    return files_opened_[num_of_linked_files_];
}

#endif
