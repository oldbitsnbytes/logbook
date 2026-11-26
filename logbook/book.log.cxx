//
// Created by bretzelus on 31/08/2026.
//

#include <logbook/book.h>



book::log::log(rem::channel type_):type(type_),code(rem::code::Ok){}

book::log::~log() {
    text.clear();
}



void book::log::reset() {
    text.clear();
    line_state = state::head;
    stage();
}

/*!
 * INPUTS state.
 * @param str_
 * @return ref to self
 */
book::log & book::log::operator<<(std::string str_) {
    //std::unique_lock<std::mutex> lock(book::ent::ent_mtx);
    // On vérifie si le verrou a été obtenu avec succès
    //if (lock.owns_lock()) {
        //..
        stage();
        text << str_;
        //...
    //} else {
    //    std::cout << "book::ent::operator<<(book::ctrl) : [" << rem::Rejected << "] - !lock.owns_lock(). thread id : " << std::this_thread::get_id() <<  std::endl;
    //}
    // Le mutex est automatiquement libéré ici si owns_lock() était vrai (grâce au RAII)

    return *this;
}

book::log & book::log::operator<<(tux::string str_) {
    //std::unique_lock<std::mutex> lock(book::ent::ent_mtx);
    // On vérifie si le verrou a été obtenu avec succès
    //if (lock.owns_lock()) {
        //...
        stage();
        text << *str_;
        //...
    //} else {
    //    std::cout << "book::ent::operator<<(book::ctrl) : [" << rem::Rejected << "] - !lock.owns_lock(). thread id : " << std::this_thread::get_id() <<  std::endl;
    //}
    return *this;
}

book::log & book::log::operator<<(const char *str_) {
    //std::unique_lock<std::mutex> lock(book::ent::ent_mtx);
    // On vérifie si le verrou a été obtenu avec succès
    //if (lock.owns_lock()) {
        //...
        stage();
        text << str_;
    //} else {
    //    std::cout << "book::ent::operator<<(book::ctrl) : [" << rem::Rejected << "] - !lock.owns_lock(). thread id : " << std::this_thread::get_id() <<  std::endl;
    //}
        //...
    return *this;
}

book::log & book::log::operator<<(rem::channel type_) {
    //if (type_ == rem::channel::None || type_ == rem::channel::Output) return *this;
    stage();
    text << std::format(":<16", rem::render(type_));
    return *this;
}

book::log & book::log::operator<<(rem::code code_) {
    //std::unique_lock<std::mutex> lock(book::ent::ent_mtx);
    // On vérifie si le verrou a été obtenu avec succès
    //if (lock.owns_lock()) {
    stage();
    auto [g,col] = rem::return_code_attributes(code_);
    text << color::White << '<' << color::ansi::pair(col) << tux::grapheme::db[g] << ' ' << rem::to_string(code_) << color::White << '>' << color::R;
    //}else {
    //    std::cout << "book::ent::operator<<(book::ctrl) : [" << rem::Rejected << "] - !lock.owns_lock(). thread id : " << std::this_thread::get_id() <<  std::endl;
    //}
    return *this;
}




//
//
// book::ent & book::ent::operator<<(rem::Fn Fn_) {
//     std::unique_lock<std::mutex> lock(book::ent::ent_mtx);
//     // On vérifie si le verrou a été obtenu avec succès
//     if (lock.owns_lock()) {
//         text << '[' << color::HotPink4 << " rem::Fn is not implemented." << color::R << ']';
//     }
//     return *this;
// }

book::log & book::log::operator<<(rem::Action A_) {
    std::unique_lock<std::mutex> lock(book::log::ent_mtx);
    // On vérifie si le verrou a été obtenu avec succès
    stage();
    if (lock.owns_lock()) {
        text << '['<< rem::to_string(A_) << ']';
    }
    return *this;
}

book::log & book::log::operator<<(ctrl ctrl_) {
    //std::unique_lock<std::mutex> lock(book::ent::ent_mtx);
    // On vérifie si le verrou a été obtenu avec succès
    //if (lock.owns_lock()) {
        switch (ctrl_) {
            case book::eol:
                book::out_file->push(*text);
                text.clear();
                line_state = state::inputs;
                break;
            case book::end:
                line_state = state::head;
                book::out_file->push(*text);
                text.clear();
                break;
            case book::push:
                book::out_file->push(*text);
                text.clear();
                line_state = state::inputs;
                break;
            case::book::time: {
                auto [g,col] = rem::function_attributes(rem::Fn::Stamp);
                //text += tux::grapheme::db[g];
                text << "[";
                text << color::ansi::pair(col);
                text << tux::string::HH_MM_SS_mmm();
                text << "]\x1b[39m";
                line_state = state::inputs;
                break;
            }
            default: break;
        }
    //} else {
    //    std::cout << "book::ent::operator<<(book::ctrl) : [" << rem::Rejected << "] - !lock.owns_lock(). thread id : " << std::this_thread::get_id() <<  std::endl;
    //}
    return *this;
}

book::log & book::log::operator<<(color::value col) {

    stage();
    text << color::ansi::fg(col);
    return *this;
}

book::log & book::log::operator<<(color::pair colors) {
    stage();
    text << color::ansi::pair(colors);
    return *this;
}

rem::code book::log::stage()
{
    switch (line_state) {
        case state::head:
        {
            if (type != rem::Output ) {
                text << rem::render(rem::Fn::Stamp) << color::White << "::" << rem::render(type);
            }
            else {
                text << rem::render(type) << "    ";
            }
            line_state = state::inputs;
            break;
        }
        default:break;
    }
    return rem::Done;
}


// book channels instantiation:
book::log book::error      (rem::channel::Err         );
book::log book::status     (rem::channel::Status      );
book::log book::warning    (rem::channel::Warning     );
book::log book::fatal      (rem::channel::Fatal       );
book::log book::except     (rem::channel::Except      );
book::log book::message    (rem::channel::Message     );
book::log book::write      (rem::channel::Output      );
book::log book::debug      (rem::channel::Debug       );
book::log book::info       (rem::channel::Info        );
book::log book::comment    (rem::channel::Comment     );
book::log book::syntax     (rem::channel::Syntax      );
book::log book::test       (rem::channel::Test        );
book::log book::interrupted(rem::channel::Interrupted );
book::log book::aborted    (rem::channel::Aborted     );
book::log book::segfault   (rem::channel::Segfault    );
