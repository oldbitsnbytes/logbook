/******************************************************************************************
*   Copyright (C) ...,2025,... by Serge luxsier                                           *
 *   serge.lussier@oldbitsnbytes.club / lussier.serge@gmail.com                           *
 *   Read the LICENSE provided with this project.                                         *
 ******************************************************************************************/



///////////////////////////////////////////////
/// NOTES:
/// ------------------------------------------
/// This is a rough tags data board that I am not managing through UTF-8/16/32 codepoint.
/// I rely on the system, std::string, and the compiler's STL auto-management of wide chars (or wchar).

#pragma once
#include <logbook/exports.h>

namespace tux{
struct  grapheme
{
    using value_type = const char*;
    using value = Integers::u8;
    using list = std::vector<grapheme::value_type>;
    static constexpr value_type c_ok                    = "✓";       //  Ok “✓ ”
    static constexpr value_type c_comment               = "🗨";      //  Comment
    static constexpr value_type c_arrow_right           = "➜";       //  ArrowRight
    static constexpr value_type c_arrow_left            = "⬅";       //  ArrowLeft
    static constexpr value_type c_arrow_up              = "⬆";       //  ArrowUp
    static constexpr value_type c_arrow_down            = "⬇";       //  ArrowDown
    static constexpr value_type c_arrow_up_right        = "⬈";       //  ArrowUpRight
    static constexpr value_type c_arrow_up_left         = "⬉";       //  ArrowUpLeft
    static constexpr value_type c_arrow_down_right      = "⬊";       //  ArrowDownRight
    static constexpr value_type c_arrow_down_left       = "⬋";       //  ArrowDownLeft
    static constexpr value_type c_arrow_head_right      = "➤";       //  ArrowHeadRight
    static constexpr value_type c_arrow_dbl_head_right  = "⨠";       //  ArrowDheadRight
    static constexpr value_type c_pencil_dr             = "✎";       //  PencilDr
    static constexpr value_type c_pencil_ur             = "✐";       //  PencilUr
    static constexpr value_type c_err1                  = "✘";       //  Err1
    static constexpr value_type c_flag                  = "⚑";       //  Flag
    static constexpr value_type c_bolt                  = "⚡";       //  Butil_public
    static constexpr value_type c_success               = "👍";      //  Success
    static constexpr value_type c_small_dot             = "⚫";       //  SmallDot
    static constexpr value_type c_big_dot               = "⬤";       //  BigDot
    static constexpr value_type c_ball1                 = "❶";       //  Ball1
    static constexpr value_type c_ball2                 = "❷";       //  Ball2
    static constexpr value_type c_dead_head             = "☠";       //  DeadHead
    static constexpr value_type c_yinyang               = "☯";       //  YinYang
    static constexpr value_type c_sad_face              = "☹";       //  Sadface
    static constexpr value_type c_happy1                = "☺";       //  Happy1
    static constexpr value_type c_happy2                = "☻";       //  Happy2
    static constexpr value_type c_circle_x              = "⨂";       //  CircleX
    static constexpr value_type c_function              = "⨍";       //  Function
    static constexpr value_type c_cut1                  = "✂";       //  Cut1
    static constexpr value_type c_cut2                  = "✁";       //  Cut2
    static constexpr value_type c_cut3                  = "✂";       //  Cut3
    static constexpr value_type c_cmark_x               = "☒";       //  CMarkX
    static constexpr value_type c_baseline              = "󰉸";       //  Baseline
    static constexpr value_type c_star5                 = "✭";       //  Star5
    static constexpr value_type c_cmark_check           = "☑";       //  CMarkCheck
    static constexpr value_type c_sword_cross           = "⚔";       //  SwordCross
    static constexpr value_type c_hammer_cross          = "⚒";       //  HammerCross
    static constexpr value_type c_small_dot2            = "⚫";       //  SmallDot2
    static constexpr value_type c_err2                  = "✖";       //  Err2
    static constexpr value_type c_err3                  = "✗";       //  Err3
    static constexpr value_type c_squote1               = "❜";       //  SQuote1
    static constexpr value_type c_dquote_left           = "❝";       //  DQuoteLeft
    static constexpr value_type c_dquote_right          = "❞";       //  DQuoteRight
    static constexpr value_type c_down_to_bottom_left   = "⟀";       //  Downtobottomleft
    static constexpr value_type c_undo                  = "⟲";       //  Undo
    static constexpr value_type c_enter                 = "⤵";       //  Enter
    static constexpr value_type c_key_enter             = "⤶";       //  KeyEnter
    static constexpr value_type c_linux                 = "🐧";       //  Linux
    static constexpr value_type c_arch                  = "🐧";       //  Arch
    static constexpr value_type c_home                  = " ";       //  Home
    static constexpr value_type c_file                  = "";       //  File
    static constexpr value_type c_thumb_down            = "";       //  ThumbDown
    static constexpr value_type c_github_circle         = "";       //  GithubCircle
    static constexpr value_type c_github_folder         = "";       //  GithubFolder
    static constexpr value_type c_windows               = "";       //  Windows
    static constexpr value_type c_pi                    = "";       //  Pi
    static constexpr value_type c_folder                = "";       //  Folder
    static constexpr value_type c_bug                   = "";       //  Bug
    static constexpr value_type c_info                  = "ⓘ";       //  Info
    static constexpr value_type c_warning               = "";       //  Warning
    static constexpr value_type c_bomb                  = "💣";       //  Bomb
    static constexpr value_type c_edit_pencil_br        = "✎";       //  EditPencilBR
    static constexpr value_type c_edit_pencil_r         = "✏";       //  EditPencilR
    static constexpr value_type c_edit_pencil_ur        = "✐";       //  EditPencilUR
    static constexpr value_type c_neg_cross_check       = "❎";       //  NegCrossCheck
    static constexpr value_type c_shadowed_checkbox     = "❏";       //  ShadowedCheckBox
    static constexpr value_type c_spin_arrow_spin0      = "➩";       //  SpinArrowSpin0
    static constexpr value_type c_spin_arrow_spin1      = "➪";       //  SpinArrowSpin1
    static constexpr value_type c_spin_arrow_spin2      = "➫";       //  SpinArrowSpin2
    static constexpr value_type c_spin_arrow_spin3      = "➬";       //  SpinArrowSpin3
    static constexpr value_type c_spin_arrow_spin4      = "➭";       //  SpinArrowSpin4
    static constexpr value_type c_spin_arrow_spin5      = "➮";       //  SpinArrowSpin5
    static constexpr value_type c_spin_arrow_spin6      = "➯";       //  SpinArrowSpin6
    static constexpr value_type c_spin_arrow_spin7      = "➱";       //  SpinArrowSpin7
    static constexpr value_type c_thumb_up              = "👍";       //  ThumbUp
    static constexpr value_type c_chronos               = "⏱";       //  Chronos
    static constexpr value_type c_sand                  = "⏳";       //  Sand
    static constexpr value_type c_coffee                = "☕";       //  Coffee
    static constexpr value_type c_unauth                = "⛔";       //  UnAuth
    static constexpr value_type c_handwrite             = "✍";       //  Handwrite
    static constexpr value_type c_world                 = "🌎";      //  World
    static constexpr value_type c_world_grid            = "🌐";      //  WorldGrid
    static constexpr value_type c_school                = "🎓";      //  School
    static constexpr value_type c_hat                   = "🎩";      //  Hat
    static constexpr value_type c_admin                 = "🏛";      //  Admin
    static constexpr value_type c_fabric                = "🏭";      //  Fabric
    static constexpr value_type c_Tux                   = "🐈";      //  tux
    static constexpr value_type c_fish                  = "🐟";      //  Fish
    static constexpr value_type c_search                = "👓";      //  Search
    static constexpr value_type c_people                = "👪";      //  People
    static constexpr value_type c_alien                 = "👽";      //  Alien
    static constexpr value_type c_light                 = "💡";      //  Light
    static constexpr value_type c_poop                  = "💩";      //  Poop
    static constexpr value_type c_cash                  = "💰";      //  Cash
    static constexpr value_type c_computer              = "💻";      //  Computer
    static constexpr value_type c_notepad               = "📋";      //  NotePad
    static constexpr value_type c_books                 = "📚";      //  Books
    static constexpr value_type c_send                  = "📤";      //  Send
    static constexpr value_type c_recieve               = "📥";      //  Receive
    static constexpr value_type c_email                 = "📫";      //  Email
    static constexpr value_type c_email2                = "📬";      //  Email2
    static constexpr value_type c_nullptr               = "⨂";      //  NullPtr
    static constexpr value_type c_stop                  = "󱠰";      //Stop;
    static constexpr value_type c_debian                = "";
    static constexpr value_type c_terminal              = "";       // Terminal
    static constexpr value_type c_book                   = "";        // //book
    static constexpr value_type c_sqpixel               = "▀";       // Pixel
    static constexpr value_type c_fbox                  = "█";
    static constexpr value_type c_dnpixel               = "▄";
    static constexpr value_type c_rust_lang             = ""; // rust-lang symbol
    static constexpr value_type c_rust_crab             = "🦀"; //
    static constexpr value_type c_upcircle              = "󰁟";
    static constexpr value_type c_right_towards_up_arrow  = "󱞽";
    static constexpr value_type c_left_towards_up_arrow   = "";
    static constexpr value_type c_keyboard              = ""; // Keyboard tage
    static constexpr value_type c_mouse                 = "󰍽"; // mouse_ev
    static constexpr value_type c_label                 = "󰌕"; // label/grapheme
    static constexpr value_type c_tag                   = "󰓹"; // grapheme
    static constexpr value_type c_red_leaf              = "🍁"; //
    static constexpr value_type c_olivier               = "∫"; //
    static constexpr value_type c_esc                   = "󱊷"; // ESC
    static constexpr value_type c_debug_line            = "";



    static constexpr value ok                   = 0;
    static constexpr value comment              = 1;
    static constexpr value arrow_right           = 2;
    static constexpr value arrow_left           = 3;
    static constexpr value arrow_up             = 4;
    static constexpr value arrow_down           = 5;
    static constexpr value arrow_up_right       = 6;
    static constexpr value arrow_up_left        = 7;
    static constexpr value arrow_down_right     = 8;
    static constexpr value arrow_down_left      = 9;
    static constexpr value arrow_head_right     = 10;
    static constexpr value arrow_dbl_head_right = 11;
    static constexpr value pencil_dr            = 12;
    static constexpr value pencil_ur            = 13;
    static constexpr value err1                 = 14;
    static constexpr value flag                 = 15;
    static constexpr value bolt                 = 16;
    static constexpr value success              = 17;
    static constexpr value small_dot            = 18;
    static constexpr value big_dot              = 19;
    static constexpr value ball1                = 20;
    static constexpr value ball2                = 21;
    static constexpr value dead_head            = 22;
    static constexpr value yinyang              = 23;
    static constexpr value sad_face             = 24;
    static constexpr value happy1               = 25;
    static constexpr value happy2               = 26;
    static constexpr value circle_x             = 27;
    static constexpr value function             = 28;
    static constexpr value cut1                 = 29;
    static constexpr value cut2                 = 30;
    static constexpr value cut3                 = 31;
    static constexpr value cmark_x              = 32;
    static constexpr value baseline             = 33;
    static constexpr value star5                = 34;
    static constexpr value cmark_check          = 35;
    static constexpr value sword_cross          = 36;
    static constexpr value hammer_cross         = 37;
    static constexpr value small_dot2           = 38;
    static constexpr value err2                 = 39;
    static constexpr value err3                 = 40;
    static constexpr value squote1              = 41;
    static constexpr value dquote_left          = 42;
    static constexpr value dquote_right         = 43;
    static constexpr value down_to_bottom_left  = 44;
    static constexpr value undo                 = 45;
    static constexpr value enter                = 46;
    static constexpr value key_enter            = 47;
    static constexpr value linux_os             = 48;
    static constexpr value arch                 = 49;
    static constexpr value home                 = 50;
    static constexpr value file                 = 51;
    static constexpr value thumb_down           = 52;
    static constexpr value github_circle        = 53;
    static constexpr value github_folder        = 54;
    static constexpr value windows              = 55;
    static constexpr value pi                   = 56;
    static constexpr value folder               = 57;
    static constexpr value bug                  = 58;
    static constexpr value info                 = 59;
    static constexpr value warning              = 60;
    static constexpr value bomb                 = 61;
    static constexpr value edit_pencil_br       = 62;
    static constexpr value edit_pencil_r        = 63;
    static constexpr value edit_pencil_ur       = 64;
    static constexpr value neg_cross_check      = 65;
    static constexpr value shadowed_checkbox    = 66;
    static constexpr value spin_arrow_spin0     = 67;
    static constexpr value spin_arrow_spin1     = 68;
    static constexpr value spin_arrow_spin2     = 69;
    static constexpr value spin_arrow_spin3     = 70;
    static constexpr value spin_arrow_spin4     = 71;
    static constexpr value spin_arrow_spin5     = 72;
    static constexpr value spin_arrow_spin6     = 73;
    static constexpr value spin_arrow_spin7     = 74;
    static constexpr value thumb_up             = 75;
    static constexpr value chronos              = 76;
    static constexpr value sand                 = 77;
    static constexpr value coffee               = 78;
    static constexpr value unauth               = 79;
    static constexpr value handwrite            = 80;
    static constexpr value world                = 81;
    static constexpr value world_grid           = 82;
    static constexpr value school               = 83;
    static constexpr value hat                  = 84;
    static constexpr value admin                = 85;
    static constexpr value fabric               = 86;
    static constexpr value Tux                  = 87;
    static constexpr value fish                 = 88;
    static constexpr value search               = 89;
    static constexpr value people               = 90;
    static constexpr value alien                = 91;
    static constexpr value light                = 92;
    static constexpr value poop                 = 93;
    static constexpr value cash                 = 94;
    static constexpr value computer             = 95;
    static constexpr value notepad              = 96;
    static constexpr value books                = 97;
    static constexpr value send                 = 98;
    static constexpr value receive              = 99;
    static constexpr value email                = 100;
    static constexpr value email2               = 101;
    static constexpr value e_nullptr            = 102;
    static constexpr value stop                 = 103;
    static constexpr value debian               = 104;
    static constexpr value terminal             = 105;
    static constexpr value book                 = 106;
    static constexpr value sqpixel              = 107;
    static constexpr value fbox                 = 108;
    static constexpr value dnpixel              = 109;
    static constexpr value rust_lang            = 110;
    static constexpr value rust_crab            = 111;
    static constexpr value right_towards_up_arrow  = 112;
    static constexpr value left_towards_up_arrow   = 113;
    static constexpr value keyboard             = 114;
    static constexpr value mouse                = 115;
    static constexpr value label                = 116;
    static constexpr value itag                 = 117;
    static constexpr value red_leaf             = 118;
    static constexpr value olivier              = 119;
    static constexpr value esc                  = 120;
    static constexpr value debug_line           = 121;


    static grapheme::list db;

    static grapheme::value scan(const std::string& grapheme_name);
    static std::pair<bool, grapheme::value> scan_name(const std::string& grapheme_name);
    static std::string name(grapheme::value gh);
    static std::string text(grapheme::value gh);

};

struct glyph {
    using list = std::vector<glyph>;
    using type = const char*;
    std::string_view name{};
    std::string_view desc{};
    type value{};
    Integers::i8 width{0};
    static list table;
};

} //namespace tux
