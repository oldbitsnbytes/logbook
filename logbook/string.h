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
//------------------------------------------------------------------------------------------

#pragma once



#include <string>
#include <string_view>
#include <sstream>
#include <cstring>


#include <functional>
#include <logbook/rem.h>
#include <logbook/colors.h>
using namespace Integers;

namespace tux
{



/*
    " ...  %{}
*/


class string
{
    CLASSNAME_START(string)

public:
    using list = std::vector<std::string>;
    using viewlist = std::vector<std::string_view>;

    std::string::iterator begin() { return _d.begin();}
    std::string::iterator end()   { return _d.end();}
    using iterator = std::string::iterator;
protected:
    std::string             _d{};
    std::string::iterator   pos{};

    // ----- Abstract argument support data-----------
    // Future implementation...
    struct argument {

        std::string::iterator   begin{};
        std::string::iterator   end{};
        std::string             seq{};  ///< Very important d'initialiser avec la sequence complete "%{...}" !

        using fmt_fnptr = std::function<bool(string::argument&)>;
        argument()=delete;
        ~argument();
        argument(const argument&)=delete;
        argument(const argument&&)=delete;
        argument(string& src, string::iterator pos);
        argument& operator=(const argument&)=delete;


    };

    // -----------------------------------------------

public:
    string() = default;
    string(const string&);
    string(string&&) noexcept = default;
    virtual ~string();

    string(std::string  str);
    string(std::string_view str);
    string(const char* str);
    string(char a_ch);
    string(Integers::u8  val);
    string(Integers::u16 val);
    string(Integers::u32 val);
    string(Integers::u64 val);
    string(Integers::i8  val);
    string(Integers::i16 val);
    string(Integers::i32 val);
    string(Integers::i64 val);
    string(float val);



    string& operator=(const string& str);
    string& operator=(const std::string& str);
    string& operator=(const char* str);
    string& operator=(std::nullptr_t);
    string& operator=(string&& ) noexcept=default;

    string& operator=(char Ch);
    string& operator=(u8  val);
    string& operator=(u16 val);
    string& operator=(u32 val);
    string& operator=(u64 val);
    string& operator=(i8  val);
    string& operator=(i16 val);
    string& operator=(i32 val);
    string& operator=(i64 val);
    string& operator=(float val);
    string& operator=(double val);
    
    std::string operator *() const { return _d; }


    // - inputs --------------

    string& operator << (color::value color);
    string& operator << (color::pair colors);
    //string& operator <<(color::css AColor);
    //string& operator <<(color::CSSPair Cpair);
    string& operator << (grapheme::value ig);


    string& operator << (const char* a_str) { _d += a_str; return *this; }
    string& operator << (const std::string& a_str) { _d += a_str; return *this; }
    string& operator << (char c) { _d += c; return *this;}
    string& operator << (int  c) { _d += std::to_string(c); return *this;}
    string& operator << (float  c) { _d += std::to_string(c); return *this;}
    string& operator << (std::string_view sv) { _d += sv; return *this; }
    string& operator << (const string& tstr) { _d += tstr._d; return *this; }
    string& operator<<(rem::channel t);
    string& operator<<(rem::code c);
    template<typename T> string& operator << (const T& t) { std::ostringstream os; os << (t); _d += os.str(); return *this; }
    template<typename T> string& operator >> (T& t) { std::istringstream is(_d); is >> (t); return *this; }
    //------------------------------------------------------------------------------
    string& fill(size_t n, char c=0x20);
    static std::string fill(char c, size_t n);

    template<typename T> static std::string binary(T _arg, bool padd = false, int f = 128)
    {
        u8 seq;
        int nbytes = sizeof(T);

        uint8_t tableau[sizeof(T)];
        memcpy(tableau, reinterpret_cast<u8*>(&_arg), nbytes);
        std::string stream;
        int s = 0;
        //bool Discard = false;
        for (int x = 1; x <= nbytes; x++) {
            seq = tableau[nbytes - x];
            if ((x == 1 && !padd && !seq) || (stream.empty() && !padd && !seq))
                continue;
            for (int y = 7; y >= 0; y--) { // est-ce que le bit #y est à 1 ?
                if (s >= f) {
                    stream += ' ';
                    s = 0;
                }
                ++s;
                uint8_t b = 1 << y;
                if (b & seq)
                    stream += '1';
                else
                    stream += '0';
            }
        }
        /*tableau.Clear();*/
        return stream;
    }


    template <typename T>  static std::string hex(const T& num)
    {
        std::stringstream ss;
        ss << std::hex << std::nouppercase << "0x" << std::hex << num;
        ss << std::dec;
        return ss.str();
    }

    template <typename T>  static std::string Hex(const T& num)
    {
        std::stringstream ss;
        ss << std::hex << std::uppercase << "0x" << std::hex << num;
        ss << std::dec << std::nouppercase;
        return ss.str();
    }

    static std::string bytes(Byte* a_seq, size_t num_bytes);
    static std::string bytes(const std::vector<Integers::u8>& a_seq);
    static std::string bytes(std::string_view a_seq, int count);
    static std::string bytes(const std::vector<int>& a_seq);
    //template<typename T=char> static std::string bytes(const lib::buffer<T>& bloc);

    void clear() { _d.clear(); }
    template<typename str_type=std::string_view> struct  location final
    {
        Integers::u32 line{1};
        Integers::u32 column{1};
        Integers::i64 offset{0};
        using iterator = str_type::const_iterator;
        iterator begin{nullptr};
        iterator end{nullptr}; ///< not the typename str_type::End() but really the last valid character pointer into the segment.
        size_t   length{0};
        std::string operator *() const;
        using list = std::vector<location>;
    };



    struct  token final
    {
        std::string::iterator begin{};
        std::string::iterator last{};
        Integers::i64         offset{-1};
        std::string           operator *() const { return {begin, last+1}; };
        void                  sync(std::string& ref) { begin=last; offset = begin-ref.begin(); };
        using list = std::vector<token>;
        using iterator = list::iterator;
    };


    static constexpr const char* default_separators = "\\%(){}[]`$#@!;,~?^&<>=+-*/:.";
    size_t tokenize(string::token::list& a_list,  bool keep_as_word=true, const char* a_sep = string::default_separators);
    bool eat(string::token& w);
    static string::list make_list(int argc, char** argv, int offset=0);

    static std::string make_str(const string::list& _list);
    static std::vector<std::string_view> make_viewlist(int count, char** s, int offset);
    static std::string now(const std::string &str_fmt);
    static std::string HH_MM_SS_mmm();
    [[nodiscard]] size_t size() const { return _d.size(); }
    [[nodiscard]] size_t length() const { return _d.length(); }
    [[nodiscard]] bool empty() const { return _d.empty(); }
private:

};


// template<typename T> std::string string::bytes(const buffer<T> &bloc) {
//     if (bloc.empty())
//         return "{}";
//     std::string outstr{};
//     auto sz = bloc.size();
//     for (size_t X = 0; X < sz;  X++) {
//         outstr += std::format("[{:02x}] ", bloc[X]);
//     }
//     return outstr;
// }

template<typename str_type> std::string string::location<str_type>::operator*() const
{
     std::ostringstream  str;
    str << "{ line #" << line << " column #" << column << " offset :" << offset << " length :" << length << "}";
    return str.str();
}


}


