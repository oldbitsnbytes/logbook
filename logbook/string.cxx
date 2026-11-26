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

#include <chrono>
#include <iomanip>
#include <string.h>

#include <utility>
#include <logbook/rem.h>
#include <logbook/string.h>

#define out std::cout
#define lend std::endl;



namespace tux
{

#define numeric_construct(v) { std::ostringstream os; os << (v); _d = os.str(); }
#define AssignNumeric(v) { std::ostringstream os; os << (v); _d += os.str(); return *this; }


string::string(std::string  a_str): _d(std::move(a_str)){}

string::string(std::string_view a_str) { _d.assign(a_str.data(), a_str.size()); }


string::string(const char* a_str): _d(a_str){}


string::string(const string& a_str):_d(a_str._d){}
string::string(char a_ch)numeric_construct(a_ch)


string::string(Integers::u8 v)  numeric_construct(v)
string::string(Integers::u16 v) numeric_construct(v)
string::string(Integers::u32 v) numeric_construct(v)
string::string(Integers::u64 v) numeric_construct(v)
string::string(Integers::i8 v)  numeric_construct(v)
string::string(Integers::i16 v) numeric_construct(v)
string::string(Integers::i32 v) numeric_construct(v)
string::string(Integers::i64 v) numeric_construct(v)
string::string(float v)         numeric_construct(v)


string::~string()
{
    _d.clear();
}


string& string::operator=(const string& a_str) { _d = a_str._d; return *this; }


string& string::operator<<(rem::channel t)
{
    _d += rem::render(t);
    return *this;
}

string& string::operator<<(rem::code c)
{
    _d += rem::to_string(c);
    return *this;
}


/////////////////////////////////////////////////////////////////////
/// \brief string::fill
///     Fills with \arg c n times at the end of _d ( begin or end-1 ).
/// \param n
/// \param c
/// \return ref-to-self
///
string &string::fill(size_t n, char c)
{
    if(!_d.empty())
        std::fill_n(_d.end()-1, n, c);
    else
        std::fill_n(_d.begin(),n,c);
    return *this;
}

///////////////////////////////////////////////////////////////
/// \brief string::fill
///     static version that creates and return pre-filled std::string with \arg c
///     usage: Mostly for indentation with spaces
/// \param c
/// \param n
/// \return
///
std::string string::fill(char c, size_t n)
{
    return std::basic_string<char>(n,c);
}


string& string::operator=(const char* a_str)   { _d = a_str; return *this; }

string & string::operator=(std::nullptr_t) {
    _d.clear();
    return *this;
}

string& string::operator=(char a_ch)           { _d = a_ch; return *this; }
string& string::operator=(Integers::u8 v)      AssignNumeric(v)
string& string::operator=(Integers::u16 v)     AssignNumeric(v)
string& string::operator=(Integers::u32 v)     AssignNumeric(v)
string& string::operator=(Integers::u64 v)     AssignNumeric(v)
string& string::operator=(Integers::i8 v)      AssignNumeric(v)
string& string::operator=(Integers::i16 v)     AssignNumeric(v)
string& string::operator=(Integers::i32 v)     AssignNumeric(v)
string& string::operator=(Integers::i64 v)     AssignNumeric(v)
string& string::operator=(const std::string& a_str) { _d = a_str; return *this; }
string& string::operator=(float v)             AssignNumeric(v)
string& string::operator=(double v)            AssignNumeric(v)


string& string::operator << (color::value color) { _d += color::ansi::fg(color); return *this; }
string& string::operator << (color::pair colors) { _d += color::ansi::pair(colors); return *this; }
//string& string::operator<<(color::css AColor) { _d += color::render(AColor); return *this; }
//string& string::operator<<(color::CSSPair Cpair) { _d += color::render(Cpair); return *this; }
string& string::operator << (grapheme::value ig) { if(ig > grapheme::debug_line) return *this; _d += glyph::table[ig].value; return *this; }


//string& string::operator << (AccentFR::value_type ac) { _d += AccentFR::Data[ac]; return *this; }


//string& string::operator << (border_glyphes_set::Index fri) { _d += border_glyphes_set()[fri]; return *this; }

// string& string::operator<<(crect r)
// {
//     _d += r.infos();
//     return *this;
// }






/*!
 * \brief string::words
 * \param a_list
 * \param a_keep_as_word
 * \param a_sep
 * \return
 * \note The code below is very hard to read, I know, even from myself being the author... I had to choose between speed + efficiency + weight - and readability. I have chosen speed...
 */
size_t string::tokenize(string::token::list& a_list, bool a_keep_as_word, const char* a_sep)
{
    if(_d.empty()) return 0;

    string::token w{_d.begin(),_d.begin(), 0};
    if(!a_sep) a_sep = string::default_separators;

    if(_d.size() < 2) return 1;
    //...
    do
    {
        if(std::string(a_sep).find(*w.last, 0/* duh!!!!!!!!!!!!!!!!!!!*/) != std::string::npos)
        {
            if(w.last > w.begin)
            {
                a_list.push_back({w.begin, w.last-1, w.begin-_d.begin()});
                w.sync(_d);
            }
            if(a_keep_as_word)
            {
                a_list.push_back({w.begin, w.last, w.begin-_d.begin()});
                w.sync(_d); //!!
            }
            if(!eat(w))
                break;

            w.sync(_d);
            continue;
        }

        if(std::isspace(*w.last))
        {
            // out << " in white spaces ..." << std::endl;
            if(w.last > w.begin)
            {
                a_list.push_back({w.begin,w.last-1, w.begin-_d.begin()});
                // out << "push before whitespace: '" << *a_list.back() << '\'' << lend;
                if(!eat(w)) break;
            }
            while(std::isspace(*w.last) && w.last != _d.end()) ++w.last;
            if(w.last == _d.end()) break;

            w.sync(_d);
            continue;
        }

        if(*w.last == '"' || *w.last == '\'')
        {
            auto c = *w.last;
            if(!eat(w)) break; // advance w.last ...
            if(auto off = _d.find(c, w.last-_d.begin()) != std::string::npos)
            {
                if(a_keep_as_word)
                {
                    a_list.push_back({w.begin,w.begin,w.offset});

                    ++w.begin;
                    ++w.offset;
                }
                w.last = _d.begin()+off;
                // w.last now on the second quote, closing the string.
                // push "string" content.
                a_list.push_back({w.begin,w.last-1,w.begin-_d.begin()});
                // out << "push : '" << *a_list.back() << '\'' << lend;
                w.sync(_d);
                if(a_keep_as_word)
                {
                    a_list.push_back({w.begin,w.begin,w.offset});
                    ++w.begin;
                    ++w.offset;
                }

                if(!eat(w)) break;
                w.sync(_d);
                continue;
            }
            // else
            // {
            //     // unterminated enclosed string : " blah <=> 'halb ...";
            //     a_list.push_back({w.begin,w.last,w.begin-_d.begin()});
            //     out << "push : '" << *a_list.back() << '\'' << lend;
            //     break;
            // }
        }
        if(!eat(w)) break;

    }while(w.last != _d.end());
    if(w.last > w.begin)
        a_list.push_back({w.begin,w.last, w.begin-_d.begin()});

    return a_list.size();
}


bool string::eat(string::token& w)
{
    if(w.last == _d.end()) return false;
    ++w.last;
    if(w.last == _d.end())
    {
        --w.last;
        return false;
    }
    return true;
}


std::string string::make_str(const string::list& _list)
{
    std::string str="{";
    int col=0;
    for (auto const& c:_list)
    {
        if (col++)
            str += ',';
        str += c;
    }
    str += '}';
    return str;
}



//////////////////////////////////////////////////////////////
/// \brief string::now
///
///     \b time/date format, given by \a str_fmt.
///
///     [https://cpluxplux.com/reference/ctime/strftime]
///
///   \li %a	Abbreviated weekday name
///   \li %A	Full weekday name
///   \li %b	Abbreviated month name
///   \li %B	Full month name
///   \li %c	Date and time representation (ex.:)	Thu Aug 23 14:55:02 2001
///   \li %C	Year divided by 100 and trunTuxed to integer (00-99)
///   \li %d	Day of the month, zero-padded (01-31)
///   \li %D	Short MM/DD/YY date, equivalent to %m/%d/%y
///   \li %e	Day of the month, space-padded ( 1-31)
///   \li %F	Short YYYY-MM-DD date, equivalent to %y-%m-%d
///   \li %g	Week-based year, last two digits (00-99)
///   \li %G	Week-based year
///   \li %h	Abbreviated month name * (same as %b)
///   \li %H	Hour in 24h format (00-23)
///   \li %I	Hour in 12h format (01-12)
///   \li %j	Day of the year (001-366)
///   \li %m	Month as a decimal number (01-12)
///   \li %M	Minute (00-59)
///   \li %n	New-line character ('\n')
///   \li %p	AM or PM designation
///   \li %r	12-hour clock time
///   \li %R	24-hour HH:MM time, equivalent to %H:%M
///   \li %s	Second (00-61)
///   \li %t	Horizontal-tab character ('\t')
///   \li %T	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%s
///   \li %u	ISO 8601 weekday as number with Monday as 1 (1-7)
///   \li %U	Week number with the first Sunday as the first day of week one (00-53)
///   \li %V	ISO 8601 week number (01-53)
///   \li %w	Weekday as a decimal number with Sunday as 0 (0-6)
///   \li %W	Week number with the first Monday as the first day of week one (00-53)
///   \li %x	Date representation
///   \li %x	Time representation
///   \li %y	Year, last two digits (00-99)
///   \li %y	Year
///   \li %z	ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100)
///   \li %Z	Timezone name or abbreviation
///
///...
////// https://stackoverflow.com/questions/24686846/get-current-time-in-milliseconds-or-hhmmssmmm-format :
/// ...
///   EDIT: A post C++20 version:

// #include <chrono>
// #include <format>
// #include <string>
//
// std::string time_in_HH_MM_SS_MMM()
// {
//     using namespace std::chrono;
//
//     // get current UTC wall time as local time
//     auto zt = zoned_time(current_zone(), system_clock::now());
//     auto now = zt.get_local_time();
//
//     // floor<milliseconds>(now) will produce millisecond
//     // accurate output.
//     return std::format("{:%T}", floor<milliseconds>(now));
// }
//
// int main()
// {
//     std::cout << time_in_HH_MM_SS_MMM() << '\n';
// }
/// \param str_fmt
/// \return string
///
///
///
std::string string::now(const std::string& str_fmt)
{
    // Old archaic Code...
    // time_t rawtime;
    // struct tm* timeinfo;
    // char tmb[180];
    // std::time(&rawtime);
    // timeinfo = std::localtime(&rawtime);
    // std::strftime(tmb, 60, str_fmt.c_str(), timeinfo);
    // std::string _d = tmb;
    // //return tmb;


    auto current = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::to_time_t(current);
    auto local = localtime(&now);
    std::ostringstream out_str;
    out_str << std::put_time(local, str_fmt.c_str());
    return out_str.str();
}

std::string string::HH_MM_SS_mmm()
{
    ////// https://stackoverflow.com/questions/24686846/get-current-time-in-milliseconds-or-hhmmssmmm-format :

     // get current UTC wall time as local time
     auto zt = std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now());
     auto now = zt.get_local_time();

     // floor<milliseconds>(now) will produce millisecond
     // accurate output.
     return std::format("{:%T}", floor<std::chrono::milliseconds>(now));
}

std::string string::bytes(std::string_view ASeq, int count)
{
    std::string OutStr{};
    for(int i = 0; i<count; i++)
    {
        if(auto ch = ASeq[i]; std::isprint(ch))
            OutStr += std::format("[x{:02x}|u{:d}'{}'] ", ch,ch, static_cast<char>(ch) );
        else
            OutStr += std::format("[x{:02x}|u{:d}] ", ch,ch);
    }
    return OutStr;
}

std::string string::bytes(const std::vector<int>& a_seq)
{
    std::string OutStr{};
    for(auto n  : a_seq)
    {
        if(std::isprint(n))
            OutStr += std::format("[x{:02x}|u{:d}'{}'] ", n,n, static_cast<char>(n) );
        else
            OutStr += std::format("[x{:02x}|u{:d}] ", n,n);
    }

    return OutStr;
}


std::string string::bytes(const std::vector<Integers::u8>& a_seq)
{
    std::string out_str{};
    for(auto n  : a_seq)
    {
        if(std::isprint(n))
            out_str += std::format("[x{:02x}|u{:d}'{}'] ", n,n, static_cast<char>(n) );
        else
            out_str += std::format("[x{:02x}|u{:d}] ", n,n);
    }

    return out_str;
}

std::string string::bytes(Byte* ASeq, size_t num_bytes)
{
    if (!ASeq)
    {
        //Log::Error() << Rem::Fn::Loc << " Called with nullptr!" << Log::End;
        return {};
    }
    std::string outstr{};
    Byte* B = ASeq;

    auto sz = std::strlen(reinterpret_cast<char*>(ASeq));
    for (size_t X = 0; X < num_bytes;  X++)
    {
        if (*B==27)
            outstr += std::format("[x{:02x}|u{:d}'ESC'] ", *B,*B, static_cast<char>(*B) );
        else
            if(std::isprint(*B))
                outstr += std::format("[x{:02x}|u{:d}'{}'] ", *B,*B, static_cast<char>(*B) );
            else
                outstr += std::format("[x{:02x}|u{:d}] ", *B,*B);
        ++B;


    }

    return outstr;
}


std::vector<std::string_view> string::make_viewlist(int Count, char** s, int offset)
{
    std::vector<std::string_view> result;
    if (offset == Count) return {};
    for(int i = offset; i < Count; ++i) result.emplace_back(s[i]);
    return result;
}


string::list string::make_list(int argc, char** argv, int offset)
{
    std::vector<std::string> result;
    for(int i = offset; i < argc; ++i) result.emplace_back(argv[i]);
    return result;
}




} // cat
