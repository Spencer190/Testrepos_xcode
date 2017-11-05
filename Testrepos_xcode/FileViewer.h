// FileViewer.h

#ifndef _FileViewer_h_
#define _FileViewer_h_

#include <string>

#include "Buffer.h"

class FileViewer
{
public:
    void run();
    
private:
    void display();
    
    Buffer buffer;
    int window_height_;
    int line_size_;
    std::string error_message_;
};

#endif
