#include <fstream>
#include <iostream>
#include <cstdint> // fix: uint64_t declared here
#include "log.h"
#include "status.h"
namespace hldb
{
    class FileManipulator
    {
    public:
        using page_t = uint64_t;

    public:
        status_t PageWriteSync(page_t page_num, const char* page_data);
        status_t PageReadSync(page_t page_num, char* page_date);
        status_t PageReadAsync(page_t page_num, char* page_data);
        status_t PageWriteAsync(page_t page_num, const char* page_data);

    private:
        std::string   name;
        std::ifstream ifile;
        std::ofstream ofile;
    };

} // namespace hldb
