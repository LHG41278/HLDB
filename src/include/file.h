#include <fstream>
#include <iostream>
#include "log.h"
#include "status.h"

class FileManipulator {
public:
    using page_t = uint64_t; 
    Status PageWriteSync(page_t page_num, const char *page_data);
    Status PageReadSync(page_t page_num, char *page_date);
    Status PageReadAsync(page_t page_num, const char *page_data);
    Status PageWriteAsync(page_t page_num, const char *page_data);


private:
    std::string name;
    std::ifstream ifile;
    std::ofstream ofile;
};
