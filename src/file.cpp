#include "file.h"
//#include <unistd.h> removed: not crossing platform
using namespace hldb;
status_t FileManipulator::PageWriteSync(page_t page_num, char* page_data)
{
    // TODO
    return status_t::Normal;
}

status_t FileManipulator::PageReadSync(page_t page_num, char* page_date)
{
    // TODO
    return status_t::Normal;
}

status_t FileManipulator::PageReadAsync(page_t page_num, const char* page_data)
{
    // TODO
    return status_t::Normal;
}

status_t FileManipulator::PageWriteAsync(page_t page_num, const char* page_data)
{
    //TODO
    return status_t::Normal;
}
