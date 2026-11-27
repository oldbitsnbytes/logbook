////////////////////////////////////////////////////////////////////////////////////////////
//   Copyright (C) ...,2025,... by Serge Lussier
//   serge.lussier@oldbitsnbytes.club / lussier.serge@gmail.com
//   ----------------------------------------------------------------------------------
//   Unless otherwise specified, all Codes and files in this project is written
//   by the author and owned by the author (Serge Lussier), unless otherwise specified.
//   ----------------------------------------------------------------------------------
//   Copyrights from authors other than Serge Lussier also apply here.
//   Open source FREE licences also apply to the code from the author (Serge Lussier)
//   ----------------------------------------------------------------------------------
//   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.
//   ----------------------------------------------------------------------------------
//   NOTE : All source code that I am the only author, I reserve for myself, the rights to
//   make it to restricted private license.
////////////////////////////////////////////////////////////////////////////////////////////



#pragma once
#include <logbook/rem.h>
#include <logbook/string.h>

#include <source_location>
#include <fstream>

class book {
    static book* logbook;
public:

    enum ctrl : Integers::u8
    {
        end     = 0,
        eol     = 1,
        push    = 2,
        time    = 3,
    };

    book(std::string book_filename);
    ~book();

    /*!
     *   log entry:
     *   :START -> [channel <> Output ? HEADER : Indentation -> INPUTS]
     *   HEADER -> hh-mm-ss-mmm [channel] {?file,?line,(?function -> EOL)};
     *   :INPUTS
     *   :CONTROL-CODE: | Format | EOL | END INPUTS
     *   :Flush -> START
     */
    struct log {

        enum class state : Integers::u8
        {
            head,
            inputs,
            commit
        }line_state{state::head};

        static std::mutex ent_mtx;

        rem::code code{};
        rem::channel type{};
        rem::code stage();
        tux::string text{};
        log() = default;
        log(rem::channel type_);
        log(const book::log& e)=default;
        log(book::log&&) noexcept = default;
        log& operator=(const book::log& e){ code = e.code; type = e.type; return *this;};
        log& operator=(book::log&&) noexcept = default;
        ~log();
        void reset();
        log& operator<<(std::string str_);
        log& operator<<(tux::string str_);
        log& operator<<(const char* str_);
        log& operator<<(rem::channel type_);
        log& operator<<(rem::code code_);
        //ent& operator<<(std::source_location&& loc);
        //ent& operator<<(rem::Fn Fn_);
        log& operator<<(rem::Action A_);
        log& operator<<(ctrl ctrl_);
        log& operator<<(color::value col);
        log& operator<<(color::pair colors);
        log& operator<<(double v) { stage(); text << v; return *this; }
        template<typename T> log& operator << (const T& v) { stage(); text << v; return *this; }
    };

#pragma region book_channels
    // book 'channels' - outputs book::ent instances
    // Grâce á la recherche google ( possiblement l'IA ) à-propos de std::endl, je me suis rendu compte que  je pouvais
    // faire semblabe ici aussi et que ça économise grandement en cpu en pré-instantiant les channels d'entrés globales statiques au lieu de
    // re-créer systématiquement des book::ent en fou á chaque invocation!
    static book::log error      ;
    static book::log status     ;
    static book::log warning    ;
    static book::log fatal      ;
    static book::log except     ;
    static book::log message    ;
    static book::log write      ;
    static book::log debug      ;
    static book::log info       ;
    static book::log comment    ;
    static book::log syntax     ;
    static book::log test       ;
    static book::log interrupted;
    static book::log aborted    ;
    static book::log segfault   ;

    // -------------------------------------------------
#pragma endregion book_channels

    struct file {
        std::ostream*   file_ptr{nullptr}; ///< Ununsed yet, for future 'under-screen' console output alternative...
        // Inutilisé, pour les futures sorties alternatives en sous-écrans
        file(std::string book_filename, std::ios_base::openmode mode_=std::ios_base::trunc|std::ios_base::out);
        ~file();

        std::ios_base::openmode mode{std::ios_base::app|std::ios_base::out};
        std::ofstream   out{};
        std::string     filename;
        bool            is_open{false};
        std::vector<std::string> cached_lines{};
        rem::code       open();
        rem::code       close();
        rem::code       push(std::string str);
        rem::code       flush();

        size_t     seuil{4096};
        bool       stop{false};
        std::recursive_mutex mtx;
        std::jthread worker;
        void       run(const std::stop_token &stoken);
        void       stop_worker();

    } static *out_file;

    class exception :  public std::exception
    {
    public:

        explicit exception():std::exception() { _e_ = true; }
        explicit exception(const char *txt) { _msg_ = txt; _e_ = false; }
        explicit exception(const std::string &txt) { _msg_ = txt; _e_ = false; }

        ~exception() noexcept override {
            _msg_.clear();
        }

        const char* what() const noexcept override;

        book::exception operator[](const book::log& el);
    private:
        bool _e_;
        mutable std::string _msg_;
        book::log _log_;
    };
    rem::code stop();
    rem::code open(std::ios_base::openmode a_mode);
    rem::code close();
};


