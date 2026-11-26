#include "playground.h"


rem::code playground::run()
{
    playground prog;
    prog.start_logbook_thread();
    book::message << "Starting the logging playground..." << book::eol;
    book::write << "This is a test message." << book::eol;
    book::write << "Logging system is operational." << book::eol;
    prog.stop_logbook_thread();
    system("cat logbook_playground.log");
    return rem::Ok;
}

rem::code playground::start_logbook_thread() {
    m_book.open(std::ios_base::out|std::ios_base::trunc);
    book::info << rem::this_location() << book::end;
    book::write << "Started logbook thread." << book::end;
    return rem::Ready;
}

rem::code playground::stop_logbook_thread() {
    book::info << rem::this_location() << book::end;

    m_book.stop(); // waits for  the book::file::run to gracefully terminates.
    return rem::Done;
}
