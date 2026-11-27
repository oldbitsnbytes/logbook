//
// Created by bretzelus on 2026-07-01.
//



#include <logbook/book.h>
#include <iostream>



book::file::file(std::string book_filename, std::ios_base::openmode mode_) {
    filename = std::move(book_filename);
    mode = mode_;
    filename += ".book";
}

book::file::~file() {
    //close();
}

rem::code book::file::open() {

    out.open(filename, mode);
    if (out.is_open())
        file_ptr = &out;
    else
        file_ptr = &std::cout;


    //...
    //std::cout << " Starting the file worker thread:" << std::endl;

    is_open = true;
    worker = std::jthread(&book::file::run, this);
    //std::cout << "[main thread] file worker thread started." << std::endl;
    book::info << "[main thread] book::file::open :" <<  book::time << book::eol;
    return rem::Accepted;
}

rem::code book::file::close() {
    //if (!file_ptr)
    //    return rem::Rejected;

    if (file_ptr == &out) {
        std::cout << "book::file::close filesystem : [" << rem::Ok << "]." << std::endl;
        out << "book::file::close filesystem @" << tux::string::HH_MM_SS_mmm() << " : [" << rem::Ok << "]." << std::endl;
        out.close();
    }
    file_ptr = nullptr;
    is_open = false;
    //std::cout << "book::file::close : [" << rem::Accepted << "] - Request worker stop:" << std::endl;

    return rem::Accepted;
}

rem::code book::file::push(std::string str) {
    std::lock_guard<std::recursive_mutex> lock(mtx);
    if (!is_open) {
        //std::cout << "book::file::push : [" << rem::Rejected << "] - !is_open." << std::endl;
        return rem::Rejected;
    }
    cached_lines.push_back(std::move(str));
    //std::cout << "book::file::push : [" << cached_lines.back() << "] [" << rem::Accepted << "]." << cached_lines.size() << " lines " << std::endl;
    return rem::Accepted;
}

rem::code book::file::flush() {
    std::lock_guard<std::recursive_mutex> lock(mtx);
    if (!is_open) {
        //std::cout << "book::file::flush : [" << rem::Rejected << "] - !is_open." << std::endl;
        return rem::Rejected;
    }
    if (cached_lines.empty()) {
        //std::cout << "book::file::flush : [" << rem::Empty << "]." << std::endl;
        return rem::Empty;
    }
    //std::cout << "book::file::flush : [ flushing " << cached_lines.size() << " lines ]." << std::endl;
    for (const auto& line : cached_lines)
        (*file_ptr) << line << '\n';
 
    cached_lines.clear();
    //std::cout << "book::file::flush : [" << rem::Complete << "]." << std::endl;
    return rem::Complete;
}

void book::file::run(const std::stop_token &stoken) {
    while (!stoken.stop_requested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // sleep for .5 seconds.
        std::unique_lock<std::mutex> lock(mtx);
        //std::cout << "book::file::run : [" << rem::Locked << "]." << std::endl;
        if (cached_lines.size() > seuil) {
            flush();
        }
    }
    //std::cout << "book::file::run : [" << rem::Complete << "]. Flushing remaining lines in buffer..." << std::endl;
    flush();
}

void book::file::stop_worker() {
    worker.request_stop();
    stop = true;
}

