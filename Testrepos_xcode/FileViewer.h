// FileViewer.h

#include <string>

#include "Buffer.h"

class FileViewer
{
public:
    void run();

private:
    void display();
    void execute_command(char command, bool & done);

    Buffer buffer_;
    int window_height_;
    std::string error_message_;
};
