#include <logbook/book.h>

class playground{
    book m_book{"logbook_playground"};
    rem::code start_logbook_thread();
    rem::code stop_logbook_thread();
public:
    static rem::code run();
};
