//
// Created by bretzelus on 15/09/2026.
//

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

#include <logbook/rem.h>
#include <cstring>
using namespace Integers;
namespace tux {

class buffer {
public:
    static constexpr auto MAX_SIZE = 1000000;
    static constexpr u8 READ  = 0x01;
    static constexpr u8 WRITE = 0x02;
    static constexpr u8 FULL  = 0x04;
    static constexpr u8 EMPTY = 0x08;
    static constexpr u8 READY = 0x10;
    static constexpr u8 ERROR = 0x20;
    static constexpr u8 OVRFL = 0x40;

private:
    u8 state{EMPTY};

    u8* data{nullptr};
    size_t size{0};
    size_t free{0};
    size_t capacity{0};
    u8*  cursor{nullptr};
    u8*  tail{nullptr};

public:
    buffer() = default;
    buffer(size_t capacity_value);
    ~buffer();

    void  clear();

    [[nodiscard]] bool empty() const { return size == 0; }
    [[nodiscard]] bool full() const { return size == capacity; }
    bool operator ++ ();
    bool operator -- ();
    operator bool() const { return (cursor != tail) && (size > 0); }
    char operator *() const { return static_cast<char>(*cursor); }

    buffer& operator << (char c) { *cursor++ = c; ++size; return *this; }


    template<typename T>  buffer& operator << (const T& n) {
        // Sécurité : Interdit les types complexes (pointeurs, std::string, etc.)
        static_assert(std::is_trivially_copyable<T>::value, "Le type doit etre trivialement copiable.");

        // Validation de l'espace restant
        if ((cursor + sizeof(T)) > (data + capacity)) {
            state = OVRFL;
            return *this;
        }

        // Version explicite (conversion en pointeur d'octets comme vous l'avez décrit) :
        const u8* src = reinterpret_cast<const u8*>(&n);

        // std::memcpy est optimisé par le compilateur en une seule instruction CPU
        // et gère parfaitement le non-alignement de 'cursor'
        std::memcpy(cursor, src, sizeof(T));

        // Progression du buffer
        cursor += sizeof(T);
        size += sizeof(T);

        return *this;
    }
};

} // text


