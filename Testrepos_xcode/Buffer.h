// Buffer.h
//This is a fantastic comment
// more words
//more
// did we get it yet
#include <vector>
#include <string>

class Buffer
{
public:
    void display() const;
    const std::string & file_name() const { return file_name_; }
    void move_to_next_page();
    void move_to_previous_page();
    bool open(const std::string & file_name);
    void set_window_height(int h) { window_height_ = h; }

private:
    std::vector<std::string> v_lines_;
    int ix_top_line_ = 0;
    std::string file_name_;
    int window_height_;
};

inline void Buffer::move_to_next_page()
{
    if (ix_top_line_ + window_height_ < v_lines_.size())
        ix_top_line_ += window_height_;
}

inline void Buffer::move_to_previous_page()
{
    if (ix_top_line_ > 0)
        ix_top_line_ -= window_height_;
}
//buffer::format_page()
