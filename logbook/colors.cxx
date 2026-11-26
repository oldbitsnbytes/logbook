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

#include <logbook/colors.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>

#include <vector>
namespace tux
{
/*!
 *   140 css colors :
 *
 */

std::vector<color::css_t> CSSColors = {
{color::css::Black               ,"Black"               ,0x00,0x00,0x00},
{color::css::Silver              ,"Silver"              ,0xC0,0xC0,0xC0},
{color::css::Grey                ,"Grey"                ,0x80,0x80,0x80},
{color::css::White               ,"White"               ,0xFF,0xFF,0xFF},
{color::css::Maroon              ,"Maroon"              ,0x80,0x00,0x00},
{color::css::Red                 ,"Red"                 ,0xFF,0x00,0x00},
{color::css::Purple              ,"Purple"              ,0x80,0x00,0x80},
{color::css::Magenta             ,"Magenta"             ,0xFF,0x00,0xFF},
{color::css::Green               ,"Green"               ,0x00,0x80,0x00},
{color::css::Lime                ,"Lime"                ,0x00,0xFF,0x00},
{color::css::Olive               ,"Olive"               ,0x80,0x80,0x00},
{color::css::Azure               ,"Azure"               ,0xF0,0xFF,0xFF},
{color::css::Beige               ,"Beige"               ,0xF5,0xF5,0xDC},
{color::css::Bisque              ,"Bisque"              ,0xFF,0xE4,0xC4},
{color::css::BlanchedAlmond      ,"BlanchedAlmond"      ,0xFF,0xEB,0xCD},
{color::css::BlueViolet          ,"BlueViolet"          ,0x8A,0x2B,0xE2},
{color::css::Brown               ,"Brown"               ,0xA5,0x2A,0x2A},
{color::css::BurlyWood           ,"BurlyWood"           ,0xDE,0xD8,0x87},
{color::css::CadetBlue           ,"CadetBlue"           ,0x5F,0x9E,0xA0},
{color::css::Chartreuse          ,"Chartreuse"          ,0x7F,0xFF,0x00},
{color::css::Chocolate           ,"Chocolate"           ,0xA2,0x60,0x1A},
{color::css::Coral               ,"Coral"               ,0xFF,0x7F,0x50},
{color::css::CornFlowerBlue      ,"CornFlowerBlue"      ,0x64,0x95,0xED},
{color::css::CornSilk            ,"CornSilk"            ,0xFF,0xF8,0xDC},
{color::css::Crimson             ,"Crimson"             ,0xDC,0x14,0x3C},
{color::css::DarkBlue            ,"DarkBlue"            ,0x00,0x00,0x8B},
{color::css::DarkCyan            ,"DarkCyan"            ,0x00,0x8B,0x8B},
{color::css::DarkGoldenRod       ,"DarkGoldenRod"       ,0xB8,0x86,0x0B},
{color::css::DarkGrey            ,"DarkGrey"            ,0xA9,0xA9,0xA9},
{color::css::DarkGreen           ,"DarkGreen"           ,0x00,0x64,0x00},
{color::css::DarkKhaki           ,"DarkKhaki"           ,0xBD,0xB7,0x6B},
{color::css::DarkMagenta         ,"DarkMagenta"         ,0x8B,0x00,0x8B},
{color::css::DarkOliveGreen      ,"DarkOliveGreen"      ,0x55,0x6B,0x2F},
{color::css::DarkOrange          ,"DarkOrange"          ,0xFF,0x8C,0x00},
{color::css::DarkOrchid          ,"DarkOrchid"          ,0x99,0x32,0xCC},
{color::css::DarkRed             ,"DarkRed"             ,0x8B,0x00,0x00},
{color::css::DarkSalmon          ,"DarkSalmon"          ,0xE9,0x96,0x7A},
{color::css::DarkSeagreen        ,"DarkSeagreen"        ,0x8F,0xBC,0x8F},
{color::css::DarkSlateblue       ,"DarkSlateblue"       ,0x48,0x3D,0x8B},
{color::css::DarkSlategrey       ,"DarkSlategrey"       ,0x2F,0x4F,0x4F},
{color::css::DarkTurquoise       ,"DarkTurquoise"       ,0x00,0xCE,0xD1},
{color::css::DarkViolet          ,"DarkViolet "         ,0x94,0x00,0xD3},
{color::css::DeepPink            ,"DeepPink"            ,0xFF,0x14,0x93},
{color::css::DeepSkyblue         ,"DeepSkyblue"         ,0x00,0xBF,0xFF},
{color::css::DimGrey             ,"DimGrey"             ,0x69,0x69,0x69},
{color::css::DodgerBlue          ,"DodgerBlue"          ,0x1E,0x90,0xFF},
{color::css::FireBrick           ,"FireBrick"           ,0xB2,0x22,0x22},
{color::css::FloralWhite         ,"FloralWhite"         ,0xFF,0xFA,0xF0},
{color::css::ForestGreen         ,"ForestGreen"         ,0x22,0x8B,0x22},
{color::css::GainsBoro           ,"GainsBoro"           ,0xDC,0xDC,0xDC},
{color::css::GhostWhite          ,"GhostWhite"          ,0xF8,0xF8,0xFF},
{color::css::Gold                ,"Gold"                ,0xFF,0xD7,0x00},
{color::css::GoldenRod           ,"GoldenRod"           ,0xDA,0xA5,0x20},
{color::css::GreenYellow         ,"GreenYellow"         ,0xAD,0xFF,0x2F},
{color::css::HoneyDew            ,"HoneyDew"            ,0xF0,0xFF,0xF0},
{color::css::HotPink             ,"HotPink"             ,0xFF,0x69,0xB4},
{color::css::IndianRed           ,"IndianRed"           ,0xCD,0x5C,0x5C},
{color::css::Indigo              ,"Indigo"              ,0x4B,0x00,0x82},
{color::css::Ivory               ,"Ivory"               ,0xFF,0xFF,0xF0},
{color::css::Khaki               ,"Khaki"               ,0xF0,0xE6,0x8C},
{color::css::Lavender            ,"Lavender"            ,0xE6,0xE6,0xFA},
{color::css::LavenderBlush       ,"LavenderBlush"       ,0xFF,0xF0,0xF5},
{color::css::LawnGreen           ,"LawnGreen"           ,0x7C,0xFC,0x00},
{color::css::LemonChiffon        ,"LemonChiffon"        ,0xFF,0xFA,0xCD},
{color::css::LightBlue           ,"LightBlue"           ,0xAD,0xD8,0xE6},
{color::css::LightCoral          ,"LightCoral"          ,0xF0,0x80,0x80},
{color::css::LightCyan           ,"LightCyan"           ,0xE0,0xFF,0xFF},
{color::css::LightGoldenRodYellow,"LightGoldenRodYellow",0xFA,0xFA,0xD2},
{color::css::LightGrey           ,"LightGrey"           ,0xD3,0xD3,0xD3},
{color::css::LightGreen          ,"LightGreen"          ,0x90,0xEE,0x90},
{color::css::LightPink           ,"LightPink"           ,0xFF,0xB6,0xC1},
{color::css::LightSalmon         ,"LightSalmon"         ,0xFF,0xA0,0x7A},
{color::css::LightSeagreen       ,"LightSeagreen"       ,0x20,0xB2,0xAA},
{color::css::LightSkyblue        ,"LightSkyblue"        ,0x87,0xCE,0xFA},
{color::css::LightSlategrey      ,"LightSlategrey"      ,0x77,0x88,0x99},
{color::css::LightSteelblue      ,"LightSteelblue"      ,0xB0,0xC4,0xDE},
{color::css::LightYellow         ,"LightYellow"         ,0xFF,0xFF,0xE0},
{color::css::Linen               ,"Linen"               ,0xFA,0xF0,0xE6},
{color::css::MediumAquamarine    ,"MediumAquamarine"    ,0x66,0xCD,0xAA},
{color::css::MediumBlue          ,"MediumBlue"          ,0x00,0x00,0xCD},
{color::css::MediumOrchid        ,"MediumOrchid"        ,0xBA,0x55,0xD3},
{color::css::MediumPurple        ,"MediumPurple"        ,0x93,0x70,0xDB},
{color::css::MediumSeaGreen      ,"MediumSeaGreen"      ,0x3C,0xB3,0x71},
{color::css::MediumSlateBlue     ,"MediumSlateBlue"     ,0x7B,0x68,0xEE},
{color::css::MediumSpringGreen   ,"MediumSpringGreen"   ,0x00,0xFA,0x9A},
{color::css::MediumTurquoise     ,"MediumTurquoise"     ,0x48,0xD1,0xCC},
{color::css::MediumVioletRed     ,"MediumVioletRed"     ,0xC7,0x15,0x85},
{color::css::MidnightBlue        ,"MidnightBlue"        ,0x19,0x19,0x70},
{color::css::MintCream           ,"MintCream"           ,0xF5,0xFF,0xFA},
{color::css::MistyRose           ,"MistyRose"           ,0xFF,0xE4,0xE1},
{color::css::Moccasin            ,"Moccasin"            ,0xFF,0xE4,0xB5},
{color::css::NavajoWhite         ,"NavajoWhite"         ,0xFF,0xDE,0xAD},
{color::css::OldLace             ,"OldLace"             ,0xFD,0xF5,0xE6},
{color::css::OlivedRab           ,"OlivedRab"           ,0x6B,0x8E,0x23},
{color::css::Orange              ,"Orange"              ,0xFF,0xA5,0x00},
{color::css::OrangeRed           ,"OrangeRed"           ,0xFF,0x45,0x00},
{color::css::Orchid              ,"Orchid"              ,0xDA,0x70,0xD6},
{color::css::PaleGoldenRod       ,"PaleGoldenRod"       ,0xEE,0xE8,0xAA},
{color::css::PaleGreen           ,"PaleGreen"           ,0x98,0xFB,0x98},
{color::css::PaleTurquoise       ,"PaleTurquoise"       ,0xAF,0xEE,0xEE},
{color::css::PaleVioletRed       ,"PaleVioletRed"       ,0xDB,0x70,0x93},
{color::css::PapayaWhip          ,"PapayaWhip"          ,0xFF,0xEF,0xD5},
{color::css::PeachPuff           ,"PeachPuff"           ,0xFF,0xDA,0xB9},
{color::css::Peru                ,"Peru"                ,0xCD,0x85,0x3F},
{color::css::Pink                ,"Pink"                ,0xFF,0xC0,0xCB},
{color::css::Plum                ,"Plum"                ,0xDD,0xA0,0xDD},
{color::css::PowderBlue          ,"PowderBlue"          ,0xB0,0xE0,0xE6},
{color::css::RebeccaPurple       ,"RebeccaPurple"       ,0x66,0x33,0x99},
{color::css::RosyBrown           ,"RosyBrown"           ,0xBC,0x8F,0x8F},
{color::css::RoyalBlue           ,"RoyalBlue"           ,0x41,0x69,0xE1},
{color::css::SaddleBrown         ,"SaddleBrown"         ,0x8B,0x45,0x13},
{color::css::Salmon              ,"Salmon"              ,0xFA,0x80,0x72},
{color::css::SandyBrown          ,"SandyBrown"          ,0xF4,0xA4,0x60},
{color::css::SeaGreen            ,"SeaGreen"            ,0x2E,0x8B,0x57},
{color::css::SeaShell            ,"SeaShell"            ,0xFF,0xF5,0xEE},
{color::css::Sienna              ,"Sienna"              ,0xA0,0x52,0x2D},
{color::css::SkyBlue             ,"SkyBlue"             ,0x87,0xCE,0xEB},
{color::css::SlateBlue           ,"SlateBlue"           ,0x6A,0x5A,0xCD},
{color::css::SlateGray           ,"SlateGray"           ,0x70,0x80,0x90},
{color::css::Snow                ,"Snow"                ,0xFF,0xFA,0xFA},
{color::css::SpringGreen         ,"SpringGreen"         ,0x00,0xFF,0x7F},
{color::css::SteelBlue           ,"SteelBlue"           ,0x46,0x82,0xB4},
{color::css::Tan                 ,"Tan"                 ,0xD2,0xB4,0x8C},
{color::css::Thistle             ,"Thistle"             ,0xD8,0xBF,0xD8},
{color::css::Tomato              ,"Tomato"              ,0xFF,0x63,0x47},
{color::css::Turquoise           ,"Turquoise"           ,0x40,0xE0,0xD0},
{color::css::Violet              ,"Violet"              ,0xEE,0x82,0xEE},
{color::css::Wheat               ,"Wheat"               ,0xF5,0xDE,0xB3},
{color::css::WhiteSmoke          ,"WhiteSmoke"          ,0xF5,0xF5,0xF5},
{color::css::YellowGreen         ,"YellowGreen"         ,0x9A,0xCD,0x32},
{color::css::Yellow              ,"Yellow"              ,0xFF,0xFF,0x00},
{color::css::AshGray	         ,"AshGray"             ,0xB2,0xBE,0xB5},
{color::css::BlueGray	         ,"BlueGray"            ,0x73,0x93,0xB3},
{color::css::Charcoal	         ,"Charcoal"            ,0x36,0x45,0x4F},
{color::css::DarkGray	         ,"DarkGray"            ,0xA9,0xA9,0xA9},
{color::css::Glaucous	         ,"Glaucous"            ,0x60,0x82,0xB6},
{color::css::Gray	             ,"Gray"                ,0x80,0x80,0x80},
{color::css::GunmetalGray	     ,"GunmetalGray"        ,0x81,0x85,0x89},
{color::css::LightGray	         ,"LightGray"           ,0xD3,0xD3,0xD3},
{color::css::Pewter	             ,"Pewter"              ,0x89,0x94,0x99},
{color::css::Platinum	         ,"Platinum"            ,0xE5,0xE4,0xE2},
{color::css::SageGreen	         ,"SageGreen"           ,0x8A,0x9A,0x5B},
{color::css::SilverGrey          ,"SilverGrey"          ,0xC0,0xC0,0xC0},
{color::css::SlateGrey	         ,"SlateGrey"           ,0x70,0x80,0x90},
{color::css::Smoke	             ,"Smoke"               ,0x84,0x88,0x84},
{color::css::SteelGray	         ,"SteelGray"           ,0x71,0x79,0x7E}

};

color::css_t::List &color::css_t::CSSTable() { return CSSColors; }


/*!
 *  https://www.ditig.com/publiTuxions/256-colors-cheat-sheet
 */
std::vector<color::table> color::css_data = {
    /*0   */ {color::Black,              "Black"                , 0x00, 0x00, 0x00},
    /*1   */ {color::Maroon,             "Maroon"               , 0x80, 0x00, 0x00},
    /*2   */ {color::Green,              "Green"                , 0x00, 0x80, 0x00},
    /*3   */ {color::Olive,              "Olive"                , 0x30, 0x50, 0x00},
    /*4   */ {color::Navy,               "Navy"                 , 0x00, 0x00, 0x80},
    /*5   */ {color::Purple,             "Purple"               , 0x80, 0x00, 0x80},
    /*6   */ {color::Cyan,               "Cyan"                 , 0x00, 0x80, 0x80},
    /*7   */ {color::Silver,             "Silver"               , 0xc0, 0xc0, 0xc0},
    /*8   */ {color::Grey,               "Grey"                 , 0x80, 0x80, 0x80},
    /*9   */ {color::Red,                "Red"                  , 0xff, 0x00, 0x00},
    /*10  */ {color::Lime,               "Lime"                 , 0x00, 0xff, 0x00},
    /*11  */ {color::Yellow,             "Yellow"               , 0xff, 0xff, 0x00},
    /*12  */ {color::Blue,               "Blue"                 , 0x00, 0x00, 0xff},
    /*13  */ {color::Fuchsia,            "Fuchsia"              , 0xff, 0x00, 0xff},
    /*14  */ {color::Aqua,               "Aqua"                 , 0x00, 0xff, 0xff},
    /*15  */ {color::White,              "White"                , 0xff, 0xff, 0xff},
    /*16  */ {color::Grey0,              "Grey0"                , 0x00, 0x00, 0x00},
    /*17  */ {color::NavyBlue,           "NavyBlue"             , 0x00, 0x00, 0x5f},
    /*18  */ {color::DarkBlue,           "DarkBlue"             , 0x00, 0x00, 0x87},
    /*19  */ {color::Blue3,              "Blue3"                , 0x00, 0x00, 0xaf},
    /*20  */ {color::Blue4,              "Blue4"                , 0x00, 0x00, 0xd7},
    /*21  */ {color::Blue1,              "Blue1"                , 0x00, 0x00, 0xff},
    /*22  */ {color::DarkGreen,          "DarkGreen"            , 0x00, 0x5f, 0x00},
    /*23  */ {color::DeepSkyBlue4,       "DeepSkyBlue4"         , 0x00, 0x5f, 0x5f},
    /*24  */ {color::DeepSkyBlue5,       "DeepSkyBlue5"         , 0x00, 0x5f, 0x87},
    /*25  */ {color::DeepSkyBlue6,       "DeepSkyBlue6"         , 0x00, 0x5f, 0xaf},
    /*26  */ {color::DodgerBlue3,        "DodgerBlue3"          , 0x00, 0x5f, 0xd7},
    /*27  */ {color::DodgerBlue2,        "DodgerBlue2"          , 0x00, 0x5f, 0xff},
    /*28  */ {color::Green4,             "Green4"               , 0x00, 0x87, 0x00},
    /*29  */ {color::SpringGreen4,       "SpringGreen4"         , 0x00, 0x87, 0x5f},
    /*30  */ {color::Turquoise4,         "Turquoise4"           , 0x00, 0x87, 0x87},
    /*31  */ {color::DeepSkyBlue3,       "DeepSkyBlue3"         , 0x00, 0x87, 0xaf},
    /*32  */ {color::DeepSkyBlue7,       "DeepSkyBlue7"         , 0x00, 0x87, 0xd7},
    /*33  */ {color::DodgerBlue1,        "DodgerBlue1"          , 0x00, 0x87, 0xff},
    /*34  */ {color::Green3,             "Green3"               , 0x00, 0xaf, 0x00},
    /*35  */ {color::SpringGreen3,       "SpringGreen3"         , 0x00, 0xaf, 0x5f},
    /*36  */ {color::DarkCyan,           "DarkCyan"             , 0x00, 0xaf, 0x87},
    /*37  */ {color::LightSeaGreen,      "LightSeaGreen"        , 0x00, 0xaf, 0xaf},
    /*38  */ {color::DeepSkyBlue2,       "DeepSkyBlue2"         , 0x00, 0xaf, 0xd7},
    /*39  */ {color::DeepSkyBlue1,       "DeepSkyBlue1"         , 0x00, 0xaf, 0xff},
    /*40  */ {color::Green5,             "Green5"               , 0x00, 0xd7, 0x00},
    /*41  */ {color::SpringGreen5,       "SpringGreen5"         , 0x00, 0xd7, 0x5f},
    /*42  */ {color::SpringGreen2,       "SpringGreen2"         , 0x00, 0xd7, 0x87},
    /*43  */ {color::Cyan3,              "Cyan3"                , 0x00, 0xd7, 0xaf},
    /*44  */ {color::DarkTurquoise,      "DarkTurquoise"        , 0x00, 0xd7, 0xd7},
    /*45  */ {color::Turquoise2,         "Turquoise2"           , 0x00, 0xd7, 0xff},
    /*46  */ {color::Green1,             "Green1"               , 0x00, 0xff, 0x00},
    /*47  */ {color::SpringGreen6,       "SpringGreen6"         , 0x00, 0xff, 0x5f},
    /*48  */ {color::SpringGreen1,       "SpringGreen1"         , 0x00, 0xff, 0x87},
    /*49  */ {color::MediumSpringGreen,  "MediumSpringGreen"    , 0x00, 0xff, 0xff},
    /*50  */ {color::Cyan2,              "Cyan2"                , 0x00, 0xff, 0xd7},
    /*51  */ {color::Cyan1,              "Cyan1"                , 0x00, 0xff, 0xff},
    /*52  */ {color::DarkRed,            "DarkRed"              , 0x5f, 0x00, 0x00},
    /*53  */ {color::DeepPink4,          "DeepPink4"            , 0x5f, 0x00, 0x5f},
    /*54  */ {color::Purple4,            "Purple4"              , 0x5f, 0x00, 0x87},
    /*55  */ {color::Purple5,            "Purple5"              , 0x5f, 0x00, 0xaf},
    /*56  */ {color::Purple3,            "Purple3"              , 0x5f, 0x00, 0xd7},
    /*57  */ {color::BlueViolet,         "BlueViolet"           , 0x5f, 0x00, 0xff},
    /*58  */ {color::Orange4,            "Orange4"              , 0x5f, 0x5f, 0x00},
    /*59  */ {color::Grey37,             "Grey37"               , 0x5f, 0x5f, 0x5f},
    /*60  */ {color::MediumPurple4,      "MediumPurple4"        , 0x5f, 0x5f, 0x87},
    /*61  */ {color::SlateBlue3,         "SlateBlue3"           , 0x5f, 0x5f, 0xaf},
    /*62  */ {color::SlateBlue4,         "SlateBlue4"           , 0x5f, 0x5f, 0xd7},
    /*63  */ {color::RoyalBlue1,         "RoyalBlue1"           , 0x5f, 0x5f, 0xff},
    /*64  */ {color::Chartreuse4,        "Chartreuse4"          , 0x5f, 0x87, 0x00},
    /*65  */ {color::DarkSeaGreen4,      "DarkSeaGreen4"        , 0x5f, 0x87, 0x5f},
    /*66  */ {color::PaleTurquoise4,     "PaleTurquoise4"       , 0x5f, 0x87, 0x87},
    /*67  */ {color::SteelBlue,          "SteelBlue"            , 0x5f, 0x87, 0xaf},
    /*68  */ {color::SteelBlue3,         "SteelBlue3"           , 0x5f, 0x87, 0xd7},
    /*69  */ {color::CornFlowerBlue,     "CornFlowerBlue"       , 0x5f, 0x87, 0xff},
    /*70  */ {color::Chartreuse3,        "Chartreuse3"          , 0x5f, 0xaf, 0x00},
    /*71  */ {color::DarkSeaGreen5,      "DarkSeaGreen5"        , 0x5f, 0xaf, 0x5f},
    /*72  */ {color::CadetBlue,          "CadetBlue"            , 0x5f, 0xaf, 0x87},
    /*73  */ {color::CadetBlue2,         "CadetBlue2"           , 0x5f, 0xaf, 0xaf},
    /*74  */ {color::SkyBlue3,           "SkyBlue3"             , 0x5f, 0xaf, 0xd7},
    /*75  */ {color::SteelBlue1,         "SteelBlue1"           , 0x5f, 0xaf, 0xff},
    /*76  */ {color::Chartreuse5,        "Chartreuse5"          , 0x5f, 0xd7, 0x00},
    /*77  */ {color::PaleGreen3,         "PaleGreen3"           , 0x5f, 0xd7, 0x5f},
    /*78  */ {color::SeaGreen3,          "SeaGreen3"            , 0x5f, 0xd7, 0x87},
    /*79  */ {color::AquaMarine3,        "AquaMarine3"          , 0x5f, 0xd7, 0xaf},
    /*80  */ {color::MediumTurquoise,    "MediumTurquoise"      , 0x5f, 0xd7, 0xd7},
    /*81  */ {color::SteelBlue4,         "SteelBlue4"           , 0x5f, 0xd7, 0xff},
    /*82  */ {color::Chartreuse2,        "Chartreuse2"          , 0x5f, 0xff, 0x00},
    /*83  */ {color::SeaGreen2,          "SeaGreen2"            , 0x5f, 0xff, 0x5f},
    /*84  */ {color::SeaGreen1,          "SeaGreen1"            , 0x5f, 0xff, 0x87},
    /*85  */ {color::SeaGreen4,          "SeaGreen4"            , 0x5f, 0xff, 0xaf},
    /*86  */ {color::AquaMarine1,        "AquaMarine1"          , 0x5f, 0xff, 0xd7},
    /*87  */ {color::DarkSlateGray2,     "DarkSlateGray2"       , 0x5f, 0xff, 0xff},
    /*88  */ {color::DarkRed2,           "DarkRed2"             , 0x87, 0x00, 0x00},
    /*89  */ {color::DeepPink5,          "DeepPink5"            , 0x87, 0x00, 0x5f},
    /*90  */ {color::DarkMagenta,        "DarkMagenta"          , 0x87, 0x00, 0x87},
    /*91  */ {color::DarkMagenta2,       "DarkMagenta2"         , 0x87, 0x00, 0xaf},
    /*92  */ {color::DarkViolet,         "DarkViolet"           , 0x87, 0x00, 0xd7},
    /*93  */ {color::Purple2,            "Purple2"              , 0x87, 0x00, 0xff},
    /*94  */ {color::Orange5,            "Orange5"              , 0x87, 0x5f, 0x00},
    /*95  */ {color::LightPink4,         "LightPink4"           , 0x87, 0x5f, 0x5f},
    /*96  */ {color::Plum4,              "Plum4"                , 0x87, 0x5f, 0x87},
    /*97  */ {color::MediumPurple3,      "MediumPurple3"        , 0x87, 0x5f, 0xaf},
    /*98  */ {color::MediumPurple5,      "MediumPurple5"        , 0x87, 0x5f, 0xd7},
    /*99  */ {color::SlateBlue1,         "SlateBlue1"           , 0x87, 0x5f, 0xff},
    /*100 */ {color::Yellow4,            "Yellow4"              , 0x87, 0x87, 0x00},
    /*101 */ {color::Wheat4,             "Wheat4"               , 0x87, 0x87, 0x5f},
    /*102 */ {color::Grey53,             "Grey53"               , 0x87, 0x87, 0x87},
    /*103 */ {color::LightCoreateGrey,   "LightCoreateGrey"     , 0x87, 0x87, 0xaf},
    /*104 */ {color::MediumPurple,       "MediumPurple"         , 0x87, 0x87, 0xd7},
    /*105 */ {color::LightCoreateBlue,   "LightCoreateBlue"     , 0x87, 0x87, 0xff},
    /*106 */ {color::Yellow5,            "Yellow5"              , 0x87, 0xaf, 0x00},
    /*107 */ {color::DarkOliveGreen3,    "DarkOliveGreen3"      , 0x87, 0xaf, 0x5f},
    /*108 */ {color::DarkSeaGreen,       "DarkSeaGreen"         , 0x87, 0xaf, 0x87},
    /*109 */ {color::LightSkyBlue3,      "LightSkyBlue3"        , 0x87, 0xaf, 0xaf},
    /*110 */ {color::LightSkyBlue4,      "LightSkyBlue4"        , 0x87, 0xaf, 0xd7},
    /*111 */ {color::SkyBlue2,           "SkyBlue2"             , 0x87, 0xaf, 0xff},
    /*112 */ {color::Chartreuse6,        "Chartreuse6"          , 0x87, 0xd7, 0x00},
    /*113 */ {color::DarkOliveGreen4,    "DarkOliveGreen4"      , 0x87, 0xd7, 0x5f},
    /*114 */ {color::PaleGreen4,         "PaleGreen4"           , 0x87, 0xd7, 0x87},
    /*115 */ {color::DarkSeaGreen3,      "DarkSeaGreen3"        , 0x87, 0xd7, 0xaf},
    /*116 */ {color::DarkSlateGray3,     "DarkSlateGray3"       , 0x87, 0xd7, 0xd7},
    /*117 */ {color::SkyBlue1,           "SkyBlue1"             , 0x87, 0xd7, 0xff},
    /*118 */ {color::Chartreuse1,        "Chartreuse1"          , 0x87, 0xff, 0x00},
    /*119 */ {color::LightGreen,         "LightGreen"           , 0x87, 0xff, 0x5f},
    /*120 */ {color::LightGreen2,        "LightGreen2"          , 0x87, 0xff, 0x87},
    /*121 */ {color::PaleGreen1,         "PaleGreen1"           , 0x87, 0xff, 0xaf},
    /*122 */ {color::AquaMarine2,        "AquaMarine2"          , 0x87, 0xff, 0xd7},
    /*123 */ {color::DarkSlateGray1,     "DarkSlateGray1"       , 0x87, 0xff, 0xff},
    /*124 */ {color::Red3,               "Red3"                 , 0xaf, 0x00, 0x00},
    /*125 */ {color::DeepPink6,          "DeepPink6"            , 0xaf, 0x00, 0x5f},
    /*126 */ {color::MediumVioletRed,    "MediumVioletRed"      , 0xaf, 0x00, 0x87},
    /*127 */ {color::Magenta3,           "Magenta3"             , 0xaf, 0x00, 0xaf},
    /*128 */ {color::DarkViolet2,        "DarkViolet2"          , 0xaf, 0x00, 0xd7},
    /*129 */ {color::Purple6,            "Purple6"              , 0xaf, 0x00, 0xff},
    /*130 */ {color::DarkOrange3,        "DarkOrange3"          , 0xaf, 0x5f, 0x00},
    /*131 */ {color::IndianRed,          "IndianRed"            , 0xaf, 0x5f, 0x5f},
    /*132 */ {color::Hotpink3,           "Hotpink3"             , 0xaf, 0x5f, 0x87},
    /*133 */ {color::MediumOrchid3,      "MediumOrchid3"        , 0xaf, 0x5f, 0xaf},
    /*134 */ {color::MediumOrchid,       "MediumOrchid"         , 0xaf, 0x5f, 0xd7},
    /*135 */ {color::MediumPurple2,      "MediumPurple2"        , 0xaf, 0x5f, 0xff},
    /*136 */ {color::DarkGoldenRod,      "DarkGoldenRod"        , 0xaf, 0x87, 0x00},
    /*137 */ {color::LightSalmon3,       "LightSalmon3"         , 0xaf, 0x87, 0x5f},
    /*138 */ {color::RosyBrown,          "RosyBrown"            , 0xaf, 0x87, 0x87},
    /*139 */ {color::Grey63,             "Grey63"               , 0xaf, 0x87, 0xaf},
    /*140 */ {color::MediumPurple6,      "MediumPurple6"        , 0xaf, 0x87, 0xd7},
    /*141 */ {color::MediumPurple1,      "MediumPurple1"        , 0xaf, 0x87, 0xff},
    /*142 */ {color::Gold3,              "Gold3"                , 0xaf, 0xaf, 0x00},
    /*143 */ {color::DarkkKaki,          "DarkkKaki"            , 0xaf, 0xaf, 0x5f},
    /*144 */ {color::NavajoWhite3,       "NavajoWhite3"         , 0xaf, 0xaf, 0x87},
    /*145 */ {color::Grey69,             "Grey69"               , 0xaf, 0xaf, 0xaf},
    /*146 */ {color::LightSteelBlue3,    "LightSteelBlue3"      , 0xaf, 0xaf, 0xd7},
    /*147 */ {color::LightSteelBlue,     "LightSteelBlue"       , 0xaf, 0xaf, 0xff},
    /*148 */ {color::Yellow3,            "Yellow3"              , 0xaf, 0xd7, 0x00},
    /*149 */ {color::DarkOliveGreen5,    "DarkOliveGreen5"      , 0xaf, 0xd7, 0x5f},
    /*150 */ {color::DarkSeaGreen6,      "DarkSeaGreen6"        , 0xaf, 0xd7, 0x87},
    /*151 */ {color::DarkSeaGreen2,      "DarkSeaGreen2"        , 0xaf, 0xd7, 0xaf},
    /*152 */ {color::LightCyan3,         "LightCyan3"           , 0xaf, 0xd7, 0xd7},
    /*153 */ {color::LightSkyBlue1,      "LightSkyBlue1"        , 0xaf, 0xd7, 0xff},
    /*154 */ {color::GreenYellow,        "GreenYellow"          , 0xaf, 0xff, 0x00},
    /*155 */ {color::DarkOliveGreen2,    "DarkOliveGreen2"      , 0xaf, 0xff, 0x5f},
    /*156 */ {color::PaleGreen2,         "PaleGreen2"           , 0xaf, 0xff, 0x87},
    /*157 */ {color::DarkSeaGreen7,      "DarkSeaGreen7"        , 0xaf, 0xff, 0xaf},
    /*158 */ {color::DarkSeaGreen1,      "DarkSeaGreen1"        , 0xaf, 0xff, 0xd7},
    /*159 */ {color::PaleTurquoise,      "PaleTurquoise"        , 0xaf, 0xff, 0xff},
    /*160 */ {color::Red4,               "Red4"                 , 0xd7, 0x00, 0x00},
    /*161 */ {color::DeepPink3,          "DeepPink3"            , 0xd7, 0x00, 0x5f},
    /*162 */ {color::DeepPink7,          "DeepPink7"            , 0xd7, 0x00, 0x87},
    /*163 */ {color::Magenta4,           "Magenta4"             , 0xd7, 0x00, 0xaf},
    /*164 */ {color::Magenta5,           "Magenta5"             , 0xd7, 0x00, 0xd7},
    /*165 */ {color::Magenta2,           "Magenta2"             , 0xd7, 0x00, 0xff},
    /*166 */ {color::DarkOrange4,        "DarkOrange4"          , 0xd7, 0x5f, 0x00},
    /*167 */ {color::IndianRed2,         "IndianRed2"           , 0xd7, 0x5f, 0x5f},
    /*168 */ {color::HotPink4,           "HotPink4"             , 0xd7, 0x5f, 0x87},
    /*169 */ {color::HotPink2,           "HotPink2"             , 0xd7, 0x5f, 0xaf},
    /*170 */ {color::Orchid,             "Orchid"               , 0xd7, 0x5f, 0xd7},
    /*171 */ {color::MediumOrchid1,      "MediumOrchid1"        , 0xd7, 0x5f, 0xff},
    /*172 */ {color::Orange3,            "Orange3"              , 0xd7, 0x87, 0x00},
    /*173 */ {color::LightSalmon4,       "LightSalmon4"         , 0xd7, 0x87, 0x5f},
    /*174 */ {color::LightPink3,         "LightPink3"           , 0xd7, 0x87, 0x87},
    /*175 */ {color::Pink3,              "Pink3"                , 0xd7, 0x87, 0xaf},
    /*176 */ {color::Plum3,              "Plum3"                , 0xd7, 0x87, 0xd7},
    /*177 */ {color::Violet,             "Violet"               , 0xd7, 0x87, 0xff},
    /*178 */ {color::Gold4,              "Gold4"                , 0xd7, 0xaf, 0x00},
    /*179 */ {color::LightGoldenRod3,    "LightGoldenRod3"      , 0xd7, 0xaf, 0x5f},
    /*180 */ {color::Tan,                "Tan"                  , 0xd7, 0xaf, 0x87},
    /*181 */ {color::MistyRose3,         "MistyRose3"           , 0xd7, 0xaf, 0xaf},
    /*182 */ {color::Thistle3,           "Thistle3"             , 0xd7, 0xaf, 0xd7},
    /*183 */ {color::Plum2,              "Plum2"                , 0xd7, 0xaf, 0xff},
    /*184 */ {color::Yellow6,            "Yellow6"              , 0xd7, 0xd7, 0x00},
    /*185 */ {color::Khaki3,             "Khaki"                , 0xd7, 0xd7, 0x5f},
    /*186 */ {color::LightGoldenRod2,    "LightGoldenRod2"      , 0xd7, 0xd7, 0x87},
    /*187 */ {color::LightYellow3,       "LightYellow3"         , 0xd7, 0xd7, 0xaf},
    /*188 */ {color::Grey84,             "Grey84"               , 0xd7, 0xd7, 0xd7},
    /*189 */ {color::LightSteelBlue1,    "LightSteelBlue1"      , 0xd7, 0xd7, 0xff},
    /*190 */ {color::Yellow2,            "Yellow2"              , 0xd7, 0xff, 0x00},
    /*191 */ {color::DarkOliveGreen1,    "DarkOliveGreen1"      , 0xd7, 0xff, 0x5f},
    /*192 */ {color::DarkOliveGreen6,    "DarkOliveGreen6"      , 0xd7, 0xff, 0x87},
    /*193 */ {color::DarkSeaGreen8,      "DarkSeaGreen8"        , 0xd7, 0xff, 0xaf},
    /*194 */ {color::HoneyDew2,          "HoneyDew2"            , 0xd7, 0xff, 0xd7},
    /*195 */ {color::LightCyan1,         "LightCyan1"           , 0xd7, 0xff, 0xff},
    /*196 */ {color::Red1,               "Red1"                 , 0xff, 0x00, 0x00},
    /*197 */ {color::DeepPink2,          "DeepPink2"            , 0xff, 0x00, 0x5f},
    /*198 */ {color::DeepPink1,          "DeepPink1"            , 0xff, 0x00, 0x87},
    /*199 */ {color::DeepPink8,          "DeepPink8"            , 0xff, 0x00, 0xaf},
    /*200 */ {color::Magenta6,           "Magenta6"             , 0xff, 0x00, 0xd7},
    /*201 */ {color::Magenta1,           "Magenta1"             , 0xff, 0x00, 0xff},
    /*202 */ {color::OrangeRed1,         "OrangeRed1"           , 0xff, 0x5f, 0x00},
    /*203 */ {color::IndianRed1,         "IndianRed1"           , 0xff, 0x5f, 0x5f},
    /*204 */ {color::IndianRed3,         "IndianRed3"           , 0xff, 0x5f, 0x87},
    /*205 */ {color::HotPink,            "HotPink"              , 0xff, 0x5f, 0xaf},
    /*206 */ {color::HotPin2,            "HotPin2"              , 0xff, 0x5f, 0xd7},
    /*207 */ {color::MediumOrchid2,      "MediumOrchid2"        , 0xff, 0x5f, 0xff},
    /*208 */ {color::DarkOrange,         "DarkOrange"           , 0xff, 0x87, 0x00},
    /*209 */ {color::Salmon1,            "Salmon1"              , 0xff, 0x87, 0x5f},
    /*210 */ {color::LightCoral,         "LightCoral"           , 0xff, 0x87, 0x87},
    /*211 */ {color::PaleVioletRed1,     "PaleVioletRed1"       , 0xff, 0x87, 0xaf},
    /*212 */ {color::Orchid2,            "Orchid2"              , 0xff, 0x87, 0xd7},
    /*213 */ {color::Orchid1,            "Orchid1"              , 0xff, 0x87, 0xff},
    /*214 */ {color::Orange1,            "Orange1"              , 0xff, 0xaf, 0x00},
    /*215 */ {color::SandyBrown,         "SandyBrown"           , 0xff, 0xaf, 0x5f},
    /*216 */ {color::LightSalmon1,       "LightSalmon1"         , 0xff, 0xaf, 0x87},
    /*217 */ {color::LightPink1,         "LightPink1"           , 0xff, 0xaf, 0xaf},
    /*218 */ {color::Pink1,              "Pink1"                , 0xff, 0xaf, 0xd7},
    /*219 */ {color::Plum1,              "Plum1"                , 0xff, 0xaf, 0xff},
    /*220 */ {color::Gold1,              "Gold1"                , 0xff, 0xd7, 0x00},
    /*221 */ {color::LightGoldenRod4,    "LightGoldenRod4"      , 0xff, 0xd7, 0x5f},
    /*222 */ {color::LightGoldenRod5,    "LightGoldenRod5"      , 0xff, 0xd7, 0x87},
    /*223 */ {color::NavajoWhite1,       "NavajoWhite1"         , 0xff, 0xd7, 0xaf},
    /*224 */ {color::MistyRose1,         "MistyRose1"           , 0xff, 0xd7, 0xd7},
    /*225 */ {color::Thistle1,           "Thistle1"             , 0xff, 0xd7, 0xff},
    /*226 */ {color::Yellow1,            "Yellow1"              , 0xff, 0xff, 0x00},
    /*227 */ {color::LightGoldenRod1,    "LightGoldenRod1"      , 0xff, 0xff, 0x5f},
    /*228 */ {color::Khaki1,             "Khaki1"               , 0xff, 0xff, 0x87},
    /*229 */ {color::Wheat1,             "Wheat1"               , 0xff, 0xff, 0xaf},
    /*230 */ {color::CornSilk1,          "CornSilk1"            , 0xff, 0xff, 0xd7},
    /*231 */ {color::Grey100,            "Grey100"              , 0xff, 0xff, 0xff},
    /*232 */ {color::Grey3,              "Grey3"                , 0x08, 0x08, 0x08},
    /*233 */ {color::Grey7,              "Grey7"                , 0x12, 0x12, 0x12},
    /*234 */ {color::Grey11,             "Grey11"               , 0x1c, 0x1c, 0x1c},
    /*235 */ {color::Grey15,             "Grey15"               , 0x26, 0x26, 0x26},
    /*236 */ {color::Grey19,             "Grey19"               , 0x30, 0x30, 0x30},
    /*237 */ {color::Grey23,             "Grey23"               , 0x3a, 0x3a, 0x3a},
    /*238 */ {color::Grey27,             "Grey27"               , 0x44, 0x44, 0x44},
    /*239 */ {color::Grey30,             "Grey30"               , 0x4e, 0x4e, 0x4e},
    /*240 */ {color::Grey35,             "Grey35"               , 0x58, 0x58, 0x58},
    /*241 */ {color::Grey39,             "Grey39"               , 0x62, 0x62, 0x62},
    /*242 */ {color::Grey42,             "Grey42"               , 0x6c, 0x6c, 0x6c},
    /*243 */ {color::Grey46,             "Grey46"               , 0x76, 0x76, 0x76},
    /*244 */ {color::Grey50,             "Grey50"               , 0x80, 0x80, 0x80},
    /*245 */ {color::Grey54,             "Grey54"               , 0x8a, 0x8a, 0x8a},
    /*246 */ {color::Grey58,             "Grey58"               , 0x94, 0x94, 0x94},
    /*247 */ {color::Grey62,             "Grey62"               , 0x9e, 0x9e, 0x9e},
    /*248 */ {color::Grey66,             "Grey66"               , 0xa8, 0xa8, 0xa8},
    /*249 */ {color::Grey70,             "Grey70"               , 0xb2, 0xb2, 0xb2},
    /*250 */ {color::Grey74,             "Grey74"               , 0xbc, 0xbc, 0xbc},
    /*251 */ {color::Grey78,             "Grey78"               , 0xc6, 0xc6, 0xc6},
    /*252 */ {color::Grey82,             "Grey82"               , 0xd0, 0xd0, 0xd0},
    /*253 */ {color::Grey85,             "Grey85"               , 0xda, 0xda, 0xda},
    /*254 */ {color::Grey89,             "Grey89"               , 0xe4, 0xe4, 0xe4},
    /*255 */ {color::Reset,              "Reset"                , 0x00, 0x00, 0x00},
    /*255 */ {color::R,                  "R"                    , 0   , 0   , 0},
    /*255 */ {color::Z,                  "Z"                    , 0   , 0   , 0}

};


color::ansi::out_mode color::ansi::mode{color::ansi::out_mode::compaq};


std::string color::ansi::fg(color::value color_value) {
    if (color_value == color::value::Reset) { return color::ansi::fg_reset; }
    return std::format(fg_seq, static_cast<int>(color_value));
}

std::string color::ansi::bg(color::value color_value) {
    if (color_value == color::value::Reset) { return color::ansi::bg_reset; }
    return std::format(bg_seq, static_cast<int>(color_value));
}

std::string color::ansi::pair(color::value fg_color, color::value bg_color) {
    if (fg_color == color::Reset)
        return std::format(fgr_pair, static_cast<int>(bg_color));
    else if (bg_color == color::R)
        return std::format(bgr_pair, static_cast<int>(fg_color));

    return std::format(pair_seq, static_cast<int>(fg_color), static_cast<int>(bg_color));
}


std::string color::ansi::pair(color::pair colors) {
    if (colors.Fg == color::Reset)
        return std::format(fgr_pair, static_cast<int>(colors.Bg));
    else if (colors.Bg == color::R)
        return std::format(bgr_pair, static_cast<int>(colors.Fg));

    return std::format(pair_seq, static_cast<int>(colors.Fg), static_cast<int>(colors.Bg));
}


std::string color::ansi::reset() {
    return color::ansi::pair_reset;
}

std::string color::ansi::reset_pair() {
    return color::ansi::pair_reset;
}

std::string color::ansi::reset_fg() {
    return color::ansi::fg_reset;
}

std::string color::ansi::reset_bg() {
    return color::ansi::bg_reset;
}



color::value color::scan(const std::string &aColorName) {
  for (const auto& color_data : color::css_data)
    if (color_data.color_name == aColorName)
      return color_data.Index;
  return color::Reset;
}

std::string color::name(color::value color_value) {
  for (const auto &color_data : color::css_data)
    if (color_data.Index == color_value)
      return color_data.color_name;
  return "color::Reset";
}


color::table color::query_data(color::value color_value) {
  for (auto color_data : color::css_data)
    if (color_data.Index == color_value)
      return color_data;
  return {};
}

std::string color::pretty_names(pair colors) {
  return  std::format("[bg:{}|fg:{}]", color::name(colors.Bg), color::name(colors.Fg));
}

// color::element nul_element{};

std::string color::pair::operator()() const {
        if (color::ansi::mode == color::ansi::out_mode::rgb) {
            auto fg_data = color::query_data(Fg);
            auto bg_data = color::query_data(Bg);
            return std::format(color::ansi::rgb_pair, fg_data.R, fg_data.G, fg_data.B, bg_data.R, bg_data.G, bg_data.B);
        }
        else
            return color::ansi::pair(*this);//color::ansi::pair(color::pair{color::value{this->Fg}, color::value{this->Bg}});
}

color::pair &color::pair::operator>>(std::string &out) {
  out = (*this)();
  return *this;
}

std::string color::pair::Name() const {
  std::ostringstream txt;
  txt << "[fg:" << color::name(Fg) << " bg:" << color::name(Bg) << ']';
  return txt.str();
}

bool color::pair::operator==(const pair &colors) const {
  return Fg == colors.Fg && Bg == colors.Bg;
}

bool color::pair::operator!=(const pair &colors) const {
  return Fg != colors.Fg || Bg != colors.Bg;
}



} // namespace tux

std::ostream & operator<<(std::ostream &os, tux::color::value color_value) {
    os << tux::color::ansi::fg(color_value);
    return os;
}
