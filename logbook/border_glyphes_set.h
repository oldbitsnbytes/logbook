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

#include <logbook/colors.h>
#include <logbook/glyphs.h>
#include <stack>
#include <map>


using namespace Integers;
using namespace std::literals;

namespace tux
{

struct border_glyphes_set
{
    color::pair colors{color::Aqua,color::Black};     ///< base_colors of the box::frame
    int         width{0};
    int         height{0};


/*!
 * @brief 1v x 4h matrix for addressing Frame components
 * @note  : Source : https://github.com/ArthurSonzogni/FTXUI/blob/main/src/ftxui/screen/string.cpp
 */
    struct  frame_weight
    {
        u8 Left : 2;
        u8 Top  : 2;
        u8 Right: 2;
        u8 Down : 2;
        u8 Round: 1;

        bool operator < (border_glyphes_set::frame_weight RHS) const;
    };

    struct  frame_data
    {
        grapheme::value_type TL; ///< Top Left
        grapheme::value_type TR; ///< Top Right
        grapheme::value_type BL; ///< Bottom Left
        grapheme::value_type BR; ///< Bottom Right
        grapheme::value_type HL; ///< Horizontal Line
        grapheme::value_type VL; ///< Vertical Line
        grapheme::value_type CVH;///< Cross Vertical-Horizontal
        grapheme::value_type CRL;///< Cross Right-towards-Left
        grapheme::value_type CLR;///< Cross Left-towards-Right
        grapheme::value_type CTD;///< Cross Top-towards-Down
        grapheme::value_type CDT;///< Cross Down-towards-Top
        border_glyphes_set::frame_data& operator = (const border_glyphes_set::frame_weight& FrameModel);
    }frame{ "╭", "╮", "╰", "╯", "─", "│", "┼", "┤", "├", "┬", "┴" }; ///< By ...default, hardcode the ...default model.
/*           ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃
             ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┗━━{x,x,x,0,0}
             ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┗━━━━━━━{x,0,x,x,0}
             ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┗━━━━━━━━━━━━{0,x,x,x,0}
             ┃    ┃    ┃    ┃    ┃    ┃    ┃    ┗━━━━━━━━━━━━━━━━━{x,x,0,x,0}
             ┃    ┃    ┃    ┃    ┃    ┃    ┗━━━━━━━━━━━━━━━━━━━━━━{x,x,x,x,0}
             ┃    ┃    ┃    ┃    ┃    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━{0,x,0,x,0}
             ┃    ┃    ┃    ┃    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━{x,0,x,0,0}
             ┃    ┃    ┃    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━{x,x,0,0,1}
             ┃    ┃    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━{0,x,x,0,1}
             ┃    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━{x,0,0,x,1}
             ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━{0,0,x,x,1}

*/
    border_glyphes_set();
    border_glyphes_set::frame_weight matrix{2,2,2,2,0}; ///< (default) Frame model to apply to frame_data.
    static std::map<std::string_view, border_glyphes_set::frame_weight> MatrixData_S;
    const char** seg_data[11] = {&frame.TL, &frame.TR,&frame.BL,&frame.BR,&frame.HL,&frame.VL,&frame.CVH,&frame.CRL,&frame.CLR,&frame.CTD,&frame.CDT};
    enum index : int
    {
        TopLeft=0, TopRight, BottomLeft, BottomRight, Horizontal, Vertical, Cross, VerticalTowardsLeft, VerticalTowardsRight, TopTowardsDown, DownTowardsUp
    };

    static std::stack<border_glyphes_set::frame_weight> FMatrix_S;
    static void Push(border_glyphes_set::frame_weight FrameModel);
    static void Pop();

    border_glyphes_set& operator=(border_glyphes_set::frame_weight Model);
    // .Frame[Mem & CharMask]; Enum: Cadre::TopLeft

    /**
     * @brief Retrieves the string representation of a frame component at the given index.
     *
     * This operator allows access to specific components of the frame by their index,
     * returning their respective String representation.
     *
     * @param Ix The index of the frame component to retrieve. It must be a valid value
     *           of the `cadre::index` enumeration.
     * @return std::string The string representation of the frame component at the given index.
     */
    std::string operator [](border_glyphes_set::index Ix)
    {
        //const char* -> std::String(const char*); // Creates a deep copy and that is what we want.
        // if(Ix > DownTowardsUp)
        //     throw rem::Exception() [rem::Fatal() << "cadres::index oob (" << Ix << ")!"];
        return *seg_data[Ix];
    }


};

} // namespace Ui
