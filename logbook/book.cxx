//
// Created by bretzelus on 2026-07-01.
//

#include <logbook/book.h>

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
book*       book::logbook{nullptr};
book::file* book::out_file{nullptr};

book::book(std::string book_filename) {
    if (!book::logbook) {
        book::logbook = this;
        book::out_file = new book::file(std::move(book_filename));
    }
}

book::~book() {
    if (book::logbook == this) {
        book::logbook = nullptr;
        delete book::out_file;
    }
}

std::mutex book::log::ent_mtx{};

/**
 * Stops the worker associated with the book instance and closes the associated output file.
 *
 * This method ensures that if the output file is open, the worker is stopped, joined, and the
 * file is properly closed. If the output file is not open, the method returns a Rejected code
 * without performing any operations.
 *
 * @note Never-ever call this method within the own book::file::run thread! duh!!
 * @return rem::code - Returns rem::Accepted if the worker was stopped and the output file was
 *                     successfully closed. Returns rem::Rejected if the output file was not open.
 */
rem::code book::stop() {
    if (!book::out_file->is_open)
        return rem::Rejected;
    //std::cout << "book::stop : [" << rem::Accepted << "]." << std::endl;
    book::out_file->stop_worker();
    book::out_file->worker.join();
    close();
    return rem::Accepted;
}

rem::code book::open(std::ios_base::openmode a_mode) {

    std::lock_guard<std::mutex> lock(book::log::ent_mtx);
    if (book::out_file->is_open)
        return rem::Rejected;
    book::out_file->mode = a_mode;
    if (!book::out_file->open())
        return rem::Failed;


    // tux::string ouverture = tux::string::now("%A le %d %B %Y, %H:%M:%S");
    // book::info <<  ouverture <<  " : [" <<  rem::Accepted <<  "]." << book::push;
    return rem::Accepted;
}

rem::code book::close() {
    if (!book::out_file->is_open) {
        //std::cout << "book::close : [" << rem::Rejected << "]." << std::endl;
        return rem::Rejected;
    }
    book::out_file->close();
    //std::cout << "book::close : [" << rem::Accepted << "]." << std::endl;

    return rem::Accepted;
}





const char * book::exception::what() const noexcept {
    if(!_log_.text.empty()) _msg_ = *_log_.text;
    else _msg_ = "Exception message is empty";
    return _msg_.c_str();
}

book::exception book::exception::operator[](const book::log &el) {
    _log_ = el;
    return *this;
}





// --------------------------------------------------
