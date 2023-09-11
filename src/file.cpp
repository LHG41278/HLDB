#include "file.h"
#include <unistd.h>

Status FileManipulator::PageWriteSync(page_t page_num, const char *page_data) {
    // TODO
    return Status::Normal;
}

Status FileManipulator::PageReadSync(page_t page_num, char *page_date) {
    // TODO
    return Status::Normal;
}

Status FileManipulator::PageReadAsync(page_t page_num, const char *page_data) {
    // TODO
    return Status::Normal;
}

Status FileManipulator::PageWriteAsync(page_t page_num, const char *page_data) {
    //TODO
    return Status::Normal;
}
