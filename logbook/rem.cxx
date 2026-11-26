#include <iostream>
#include <logbook/rem.h>
#include <logbook/string.h>
#include <map>
//#include <string.h>



/**
 * Checks whether a given `rem::code` status code represents a state that is neither successful nor completed.
 *
 * This operator negates a `rem::code` value and evaluates to `true` if the value is not one of the following:
 * - `rem::code::Accepted`
 * - `rem::code::ok`
 * - `rem::code::success`
 * - `rem::code::done`
 * - `rem::code::ready`
 * - `rem::code::finish`
 * - `rem::code::complete`
 * - `rem::code::found`
 * Otherwise, it returns `false`.
 *
 * @param C The status code of type `rem::code` to be evaluated.
 * @return `true` if the status code is not one of the successful or completed states, `false` otherwise.
 */
bool operator !(rem::code C)
{
    return (C != rem::code::Accepted)&&
           (C != rem::code::Ok)      &&
           (C != rem::code::Success) &&
           (C != rem::code::Done)    &&
           (C != rem::code::Ready)   &&
           (C != rem::code::Finish)  &&
           (C != rem::code::Complete)&&
           (C != rem::code::Found)   &&
           (C != rem::code::Applied) &&
           (C != rem::code::NotApplicable) &&
           (C != rem::code::Exist)   &&
           (C != rem::code::Applied) &&
           (C != rem::code::Valid);
}

bool operator+(rem::code C)
{
    return (C == rem::code::Accepted)||
       (C == rem::code::Ok)      ||
       (C == rem::code::Success) ||
       (C == rem::code::Done)    ||
       (C == rem::code::Ready)   ||
       (C == rem::code::Finish)  ||
       (C == rem::code::Complete)||
       (C == rem::code::Found)   ||
       (C == rem::code::Applied) ||
       (C == rem::code::NotApplicable) ||
       (C == rem::code::Exist)   ||
       (C == rem::code::Applied) ||
       (C == rem::code::Valid);
}

bool operator*(const rem::code c)
{
    return !!c;
}


namespace {
/**
 * A dictionary mapping `rem::channel` enumerations to their corresponding string representations.
 *
 * This `std::map` provides a convenient way to associate human-readable descriptions with
 * the enumeration values defined in `rem::channel`. It can be used for logging, debugging,
 * or displaying user-friendly status messages.
 *
 * Each key in the dictionary is an enumeration value from `rem::channel`, and the associated value
 * is a constant character pointer containing the string representation of that enumeration.
 *
 * Example mappings include:
 * - `rem::channel::none` -> "none"
 * - `rem::channel::err` -> "err"
 * - `rem::channel::fatal` -> "fatal"
 * - `rem::channel::syntax` -> "syntax error"
 * - `rem::channel::segfault` -> "segmentation fault"
 *
 * Enumerations in `rem::channel`, which do not have an explicit description, are mapped to an
 * empty string (e.g., `rem::channel::output`).
 */
std::map<rem::channel, const char*> channels_db = {
    {rem::channel::None,        "None"},
    {rem::channel::Err  ,       "Error"},
    {rem::channel::Warning,     "Warning"},
    {rem::channel::Fatal,       "Fatal"},
    {rem::channel::Except,      "Exception"},
    {rem::channel::Message,     "Message"},
    {rem::channel::Output,      ""},
    {rem::channel::Debug,       "Debug"},
    {rem::channel::Info,        "Info"},
    {rem::channel::Comment,     "Comment"},
    {rem::channel::Syntax,      "Syntax Error"},
    {rem::channel::Status,      "Status"},
    {rem::channel::Test,        "Test"},
    {rem::channel::Interrupted, "Interrupted"},
    {rem::channel::Aborted,     "Aborted"},
    {rem::channel::Segfault,    "Segmentation Fault"},
    {rem::channel::Book,         "Log"},
    {rem::channel::Normal,       "Normal"},
    {rem::channel::Grace,        "Gracefully Terminated/Done/Clean."}
};
}

namespace {
/**
 * A dictionary that maps `rem::code` status codes to their corresponding string representations.
 *
 * This `std::map` serves as a look-up table where each key is a `rem::code` enumeration value
 * and the associated value is a constant character pointer providing a human-readable description
 * of the respective status code. It can be used for debugging, logging, or displaying error or
 * status messages to the user.
 *
 * The keys represent various status codes defined in the `rem::code` namespace, such as:
 * - `rem::code::ok`: Represents a successful operation.
 * - `rem::code::Accepted`: Indicates that an operation was accepted.
 * - `rem::code::timeout`: Signifies that an operation exceeded the allowed time limit.
 * - `rem::code::syntax_error`: Represents a syntax error.
 *
 * The corresponding string values are concise descriptions of these status codes, for example:
 * - `"ok"`
 * - `"accepted"`
 * - `"timeout"`
 * - `"syntax error"`
 *
 * This dictionary provides an efficient way to obtain descriptive strings for `rem::code` values
 * for purposes such as error reporting, message generation, or status monitoring.
 */
std::map<rem::code, const char*> return_codes_dictionary = {
    {rem::code::Ok,               "Ok"},
    {rem::code::Accepted,         "Accepted"},
    {rem::code::Success,          "Success "},
    {rem::code::Rejected,         "Rejected"},
    {rem::code::Failed,           "Failed"},
    {rem::code::Empty,            "Empty"},
    {rem::code::Full,             "Full"},
    {rem::code::NotEmpty,         "Not Empty"},
    {rem::code::Implemented,      "Implemented"},
    {rem::code::NotImplemented,   "Not Implemented"},
    {rem::code::UnTested,         "Untested"},
    {rem::code::Eof,              "End Of File"},
    {rem::code::Eos,              "End Of Stream Or String"},
    {rem::code::NullPtr,          "Null Pointer"},
    {rem::code::NotExist,         "Does Not Exist"},
    {rem::code::Exist,            "Exist"},
    {rem::code::Unexpected,       "Unexpected"},
    {rem::code::Expected,         "Expected"},
    {rem::code::Blocked,          "Blocked"},
    {rem::code::Locked,           "Locked"},
    {rem::code::Overflow,         "Buffer Overflow"},
    {rem::code::Oob,              "Out Of Boundaries"},
    {rem::code::Reimplement,      "Need To Be Re-Implemented In Derived Instances"},
    {rem::code::Done,             "Done"},
    {rem::code::Complete,         "Completed"},
    {rem::code::Finish,           "Finished"},
    {rem::code::Undefined,        "Undefined"},
    {rem::code::Ready,            "Ready"},
    {rem::code::Terminate,        "Terminate"},
    {rem::code::Timeout,          "Timeout"},
    {rem::code::Divbyzero,        "Division By Zero"},
    {rem::code::NotVisible,       "Not Visible"},
    {rem::code::Cancel,           "Cancel"},
    {rem::code::ObjectPtr,        "Pointer To Object"},
    {rem::code::ObjectId ,        "Object Id"},
    {rem::code::UnHandled,        "Unhandled"},
    {rem::code::NotReady,         "Not Ready"},
    {rem::code::NotFound,         "Not Found"},
    {rem::code::Found,            "Found"},
    {rem::code::Dismissed,        "Dismissed"},
    {rem::code::SyntaxError,     "Syntax Error"},
    {rem::code::Applied,          "Applied"},
    {rem::code::NotApplicable,    "Not Applicable"},
    {rem::code::Valid,            "Valid"},
    {rem::code::Invalid,          "Invalid"},
    {rem::code::Removed,          "Removed"},
    {rem::code::Break,             "Break"},
};
}

namespace {
/**
 * A dictionary that maps `rem::action` enumeration values to their respective string representations.
 *
 * This `std::map` provides a convenient mapping between the values defined in the
 * `rem::action` enum and their human-readable representations as constant character strings.
 * It is useful for debugging, logging, or displaying descriptive labels for actions.
 *
 * Each key in the dictionary corresponds to an `rem::action` enumeration value, and the associated
 * value is a string that describes the action. The mappings provided include:
 * - `rem::action::enter`: "enter"
 * - `rem::action::leave`: "leave"
 * - `rem::action::begin`: "begin"
 * - `rem::action::end`: "end"
 * - `rem::action::commit`: "commit"
 * - `rem::action::cont`: "continue"
 * - `rem::action::dismiss`: "dismissed"
 *
 * This mapping can be leveraged to convert `rem::action` values into readable strings
 * for message generation, output descriptions, or status reporting.
 */
std::map<rem::Action, const char*> actions_db= {
    {rem::Action::Enter,   "Enter"},
    {rem::Action::Leave,   "Leave"},
    {rem::Action::Begin,   "Begin"},
    {rem::Action::End,     "End"},
    {rem::Action::Commit,  "Commit"},
    {rem::Action::Continue,"Continue"},
    {rem::Action::Dismiss, "Dismissed"},
};
}

namespace {
/**
 * A dictionary that maps `rem::fn` enumeration values to their corresponding string representations.
 *
 * This `std::map` provides a convenient way to associate enumeration values from `rem::fn` with
 * human-readable descriptions, which can be used for debugging, logging, or displaying descriptive outputs.
 *
 * The keys in this dictionary are `rem::fn` enumeration values representing time, date, or code-related
 * elements, while the associated values are constant character pointers describing the respective enumeration.
 *
 * Example mappings include:
 * - `rem::fn::eol` -> "end line"
 * - `rem::fn::file` -> "file"
 * - `rem::fn::hour` -> "hour"
 * - `rem::fn::dayname` -> "day Name"
 * - `rem::fn::year` -> "year"
 *
 * This dictionary facilitates efficient conversion of `rem::fn` enumeration values to concise,
 * readable string descriptions useful for various textual outputs or representations.
 */
std::map<rem::Fn, const char*> functions_db= {

    {rem::Fn::Eol,            "End Line"},
    {rem::Fn::F,              "Function"},
    {rem::Fn::File,           "File"},
    {rem::Fn::Line,           "Line"},
    {rem::Fn::Stamp,          "Stamp"},
    {rem::Fn::Hour,           "Hour"},
    {rem::Fn::Minute,         "Minute"},
    {rem::Fn::Seconds,        "Seconds"},
    {rem::Fn::Weekday,        "Weekday"},
    {rem::Fn::Month,          "Month Name"},
    {rem::Fn::Dayname,        "Day Name"},
    {rem::Fn::Day,            "Day"},
    {rem::Fn::MonthNum,       "Month Number"},
    {rem::Fn::Year,           "Year"},
    {rem::Fn::Loc,            "Obsolete!, use sourcelocation"}
};
}


namespace {
/**
 * A database mapping specific types of `rem::channel` to their corresponding tux::grapheme representation
 * and associated Color pair.
 *
 * Each entry in the map represents a `rem::channel` that is paired with a `tux::grapheme::type`
 * and a `color::pair` to define the visual rendering for that type in terms of both tux::grapheme
 * iconography and Color styling.
 *
 * This database serves as the primary lookup table for determining how a given `rem::channel`
 * should be visually represented and Color-coded. The design allows for standardized
 * appearance of messages, states, or objects across the appliTuxion, ensuring intuitive
 * and consistent user interaction.
 *
 * Key components:
 * - `rem::channel`: The enumeration of types that define different appliTuxion states or messages.
 * - `tux::tag::type`: The tux::tag or icon associated with the respective `rem::channel`.
 * - `color::pair`: A pair of Colors defining the foreground and background for visual styling.
 *
 * The entries include, but are not limited to:
 * - `rem::channel::none`: Represents no specific type, associated with a computer tux::tag and aquamarine1 Color.
 * - `rem::channel::err`: Indicates an error state, rendered with an error tux::tag and red Coloring.
 * - `rem::channel::fatal`: Represents a fatal error state, using a dead_head tux::tag with hotpink4 Color.
 * - `rem::channel::message`: Corresponds to a standard message, displayed with a comment tux::tag and green4 Color.
 *
 * This map can be expanded or modified to support additional `rem::channel` values and their
 * corresponding tux::tags and Colors as needed.
 */
std::map<rem::channel, std::pair<tux::grapheme::value, color::pair>> channels_data_db={

    {rem::channel::None,        {tux::grapheme::computer,  {.Fg = color::AquaMarine1         , .Bg = color::R}}},
    {rem::channel::Err,         {tux::grapheme::err1,      {.Fg = color::Red4                , .Bg = color::R}}},
    {rem::channel::Warning,     {tux::grapheme::warning,   {.Fg = color::Yellow              , .Bg = color::R}}},
    {rem::channel::Fatal,       {tux::grapheme::dead_head, {.Fg = color::HotPink4            , .Bg = color::R}}},
    {rem::channel::Except,      {tux::grapheme::bolt,      {.Fg = color::SkyBlue3            , .Bg = color::R}}},
    {rem::channel::Message,     {tux::grapheme::comment,   {.Fg = color::Green4              , .Bg = color::R}}},
    {rem::channel::Output,      {tux::grapheme::notepad,   {.Fg = color::Grey39              , .Bg = color::R}}},
    {rem::channel::Debug,       {tux::grapheme::bug,       {.Fg = color::Pink3               , .Bg = color::R}}},
    {rem::channel::Info,        {tux::grapheme::info,      {.Fg = color::LightSkyBlue4       , .Bg = color::R}}},
    {rem::channel::Comment,     {tux::grapheme::comment,   {.Fg = color::Grey42              , .Bg = color::R}}},
    {rem::channel::Syntax,      {tux::grapheme::handwrite, {.Fg = color::LightCoreateBlue    , .Bg = color::R}}},
    {rem::channel::Status,      {tux::grapheme::admin,     {.Fg = color::LightCyan3          , .Bg = color::R}}},
    {rem::channel::Test,        {tux::grapheme::file,      {.Fg = color::AquaMarine3         , .Bg = color::R}}},
    {rem::channel::Interrupted, {tux::grapheme::circle_x,     {.Fg = color::Khaki3              , .Bg = color::R}}},
    {rem::channel::Aborted,     {tux::grapheme::stop,      {.Fg = color::Red4                , .Bg = color::R}}},
    {rem::channel::Segfault,    {tux::grapheme::bomb,      {.Fg = color::SandyBrown          , .Bg = color::R}}},
    {rem::channel::Book,        {tux::grapheme::book,      {.Fg = color::OrangeRed1          , .Bg = color::R}}},
    {rem::channel::Normal,      {tux::grapheme::school,    {.Fg = color::OrangeRed1          , .Bg = color::R}}},
    {rem::channel::Grace,       {tux::grapheme::school,    {.Fg = color::Lime                , .Bg = color::R}}}
    //...
};
}

namespace {
/**
 * A mapping between `rem::action` types and their corresponding visual representations,
 * including graphical tux::tags and associated Color pairs.
 *
 * This database provides a visualization framework for `rem::action` codes, specifying:
 * - A tux::tag (`tux::tag::type`) symbolizing the action.
 * - A Color pair (`color::pair`) that defines the foreground and background Colors.
 *
 * Entries in the map pair a specific action type with its designated tux::grapheme and Color. The
 * visual representation aids in the interpretation of actions for user interface or logging systems.
 *
 * Keys:
 * - `rem::action`: Represents the type of action (e.g., `enter`, `leave`, `begin`, etc.).
 *
 * Values:
 * - A pair consisting of:
 *   - A `tux::tag::type` representing a visual symbol for the action.
 *   - A `color::pair` specifying the display Colors, with the foreground Color followed by
 *     the background R Color.
 *
 * Example mappings:
 * - `rem::action::enter` maps to `{tux::tag::enter, {color::White, color::R}}`.
 * - `rem::action::dismiss` maps to `{tux::tag::arrow_dhead_right, {color::Yellow, color::R}}`.
 */
std::map<rem::Action      , std::pair<tux::grapheme::value, color::pair>> actions_color_db = {
    {rem::Action::Enter   , {tux::grapheme::enter        , {.Fg = color::White               , .Bg = color::R}}},
    {rem::Action::Leave   , {tux::grapheme::file         , {.Fg = color::White               , .Bg = color::R}}},
    {rem::Action::Begin   , {tux::grapheme::chronos      , {.Fg = color::White               , .Bg = color::R}}},
    {rem::Action::End     , {tux::grapheme::dead_head    , {.Fg = color::White               , .Bg = color::R}}},
    {rem::Action::Commit  , {tux::grapheme::pencil_dr    , {.Fg = color::White               , .Bg = color::R}}},
    {rem::Action::Continue, {tux::grapheme::success      , {.Fg = color::White               , .Bg = color::R}}},
    {rem::Action::Dismiss , {tux::grapheme::arrow_dbl_head_right , {.Fg = color::Yellow       , .Bg = color::R}}},
};
}


namespace {
/**
 * A database mapping status codes (`rem::code`) to their corresponding visual representations.
 *
 * This variable, `codes_database`, associates each `rem::code` status code with a pair comprising:
 * - A tux::tag (`tux::tag::type`) representing the status visually.
 * - A pair of Colors (`color::pair`) that define the foreground and background context for the tux::tag.
 *
 * Each entry in the map represents a unique status code with its corresponding tux::grapheme and Color association,
 * providing a consistent way to visually interpret status codes in user interfaces or log outputs.
 */
std::map<rem::code, std::pair<tux::grapheme::value, color::pair>> codes_database={
    {rem::code::Ok,              {tux::grapheme::thumb_up,        {.Fg = color::Lime              ,.Bg = color::R }}},
    {rem::code::Accepted,        {tux::grapheme::thumb_up,        {.Fg = color::Lime              ,.Bg = color::R }}},
    {rem::code::Success,         {tux::grapheme::success,         {.Fg = color::DarkGreen         ,.Bg = color::R }}},
    {rem::code::Rejected,        {tux::grapheme::stop,            {.Fg = color::HotPink4          ,.Bg = color::R }}},
    {rem::code::Failed,          {tux::grapheme::poop,            {.Fg = color::DarkGoldenRod     ,.Bg = color::R }}},
    {rem::code::Empty,           {tux::grapheme::arrow_right,     {.Fg = color::LightCoreateGrey  ,.Bg = color::R }}},
    {rem::code::Full,            {tux::grapheme::small_dot,       {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::NotEmpty,        {tux::grapheme::big_dot,         {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::Implemented,     {tux::grapheme::arrow_head_right,{.Fg = color::Lime              ,.Bg = color::R }}},
    {rem::code::NotImplemented,  {tux::grapheme::err1,            {.Fg = color::Orange3           ,.Bg = color::R }}},
    {rem::code::UnTested,        {tux::grapheme::flag,            {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::Eof,             {tux::grapheme::baseline,        {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::Eos,             {tux::grapheme::baseline,        {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::NullPtr,         {tux::grapheme::circle_x,           {.Fg = color::HotPink4          ,.Bg = color::R }}},
    {rem::code::NotExist  ,      {tux::grapheme::circle_x ,          {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::Exist     ,      {tux::grapheme::star5 ,          {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::Unexpected,      {tux::grapheme::flag ,           {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::Expected  ,      {tux::grapheme::Tux ,          {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::Blocked   ,      {tux::grapheme::unauth ,         {.Fg = color::IndianRed3        ,.Bg = color::R }}},
    {rem::code::Locked    ,      {tux::grapheme::err3 ,           {.Fg = color::White             ,.Bg = color::R }}},
    {rem::code::Overflow  ,      {tux::grapheme::dead_head,       {.Fg = color::Red4              ,.Bg = color::R }}},
    {rem::code::Oob       ,      {tux::grapheme::alien,           {.Fg = color::LightCoral        ,.Bg = color::R }}},
    {rem::code::Reimplement,     {tux::grapheme::book,            {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::Done       ,     {tux::grapheme::ok,              {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::Complete   ,     {tux::grapheme::ok,              {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::Finish     ,     {tux::grapheme::ok,              {.Fg = color::Lime              ,.Bg = color::R }}},
    {rem::code::Undefined  ,     {tux::grapheme::err3,            {.Fg = color::Red               ,.Bg = color::R }}},
    {rem::code::Ready      ,     {tux::grapheme::ok,              {.Fg = color::Aqua              ,.Bg = color::R }}},
    {rem::code::Terminate  ,     {tux::grapheme::flag,            {.Fg = color::HotPink4          ,.Bg = color::R }}},
    {rem::code::Timeout    ,     {tux::grapheme::chronos,         {.Fg = color::Lime              ,.Bg = color::R }}},
    {rem::code::Divbyzero  ,     {tux::grapheme::circle_x,           {.Fg = color::Red4              ,.Bg = color::R }}},
    {rem::code::NotVisible ,     {tux::grapheme::circle_x,           {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::Cancel     ,     {tux::grapheme::circle_x,           {.Fg = color::Red4              ,.Bg = color::R }}},
    {rem::code::ObjectPtr ,      {tux::grapheme::edit_pencil_br,  {.Fg = color::LightSteelBlue3   ,.Bg = color::R }}},
    {rem::code::ObjectId ,       {tux::grapheme::arrow_right,     {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::UnHandled ,      {tux::grapheme::alien,           {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::NotReady ,       {tux::grapheme::circle_x,           {.Fg = color::Orange5           ,.Bg = color::R }}},
    {rem::code::NotFound,        {tux::grapheme::circle_x,           {.Fg = color::Red               ,.Bg = color::R }}},
    {rem::code::Found,           {tux::grapheme::success,         {.Fg = color::Fuchsia           ,.Bg = color::R }}},
    {rem::code::Dismissed,       {tux::grapheme::circle_x,           {.Fg = color::Yellow            ,.Bg = color::R }}},
    {rem::code::SyntaxError,     {tux::grapheme::circle_x,           {.Fg = color::HotPink4          ,.Bg = color::R }}},
    {rem::code::Applied,         {tux::grapheme::success,         {.Fg = color::Green             ,.Bg = color::R }}},
    {rem::code::NotApplicable,   {tux::grapheme::circle_x,           {.Fg = color::HotPink4          ,.Bg = color::R }}},
    {rem::code::Valid,           {tux::grapheme::success,         {.Fg = color::Green             ,.Bg = color::R }}},
    {rem::code::Invalid,         {tux::grapheme::circle_x,           {.Fg = color::HotPink4          ,.Bg = color::R }}},
    {rem::code::Removed,         {tux::grapheme::circle_x,           {.Fg = color::HotPink4          ,.Bg = color::R }}},
    {rem::code::Break  ,         {tux::grapheme::err1,            {.Fg = color::HotPink4          ,.Bg = color::R }}},

};
}

namespace {
/**
 * A database mapping function identifiers (`rem::fn`) to their associated tux::grapheme representations and Color pairs.
 *
 * This map serves as a lookup table that associates specific functions (identified by `rem::fn` enumeration values)
 * with their corresponding tux::grapheme type (from `tux::grapheme::type`) and a pair of Colors (`color::pair`) used for visual representation.
 * These mappings are useful for rendering or displaying information in a visually meaningful way, such as in logs,
 * debugging output, or graphical user interfaces.
 *
 * Each entry in the database consists of:
 * - A `rem::fn` function identifier (e.g., `stamp`, `func`, `file`, etc.).
 * - A pair containing:
 *   - A tux::tag type from `tux::tag::type` (e.g., `chronos`, `function`, `file`, etc.).
 *   - A Color pair consisting of foreground and background Colors (e.g., `color::skyblue3`, `color::R`, etc.).
 *
 * Duplicate keys may override earlier entries based on implementation of the std::map container.
 *
 * The database encapsulates mappings for functionalities related to timestamps, files, lines, time components, weekdays,
 * months, day names, and numeric representations of dates.
 *
 */
std::map<rem::Fn, std::pair<tux::grapheme::value, color::pair>> functions_data_db={
    {rem::Fn::F         ,      {tux::grapheme::function ,   {.Fg = color::SkyBlue3          ,.Bg = color::R }}},
    {rem::Fn::File      ,      {tux::grapheme::file     ,   {.Fg = color::LightCyan3        ,.Bg = color::R }}},
    {rem::Fn::Line      ,      {tux::grapheme::debug_line , {.Fg = color::Lime              ,.Bg = color::R }}},
    {rem::Fn::Stamp     ,      {tux::grapheme::chronos  ,   {.Fg = color::LightCyan3        ,.Bg = color::R }}},
    {rem::Fn::Hour      ,      {tux::grapheme::chronos  ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::Minute    ,      {tux::grapheme::chronos  ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::Seconds   ,      {tux::grapheme::chronos  ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::Weekday   ,      {tux::grapheme::fabric   ,   {.Fg = color::Violet            ,.Bg = color::R }}},
    {rem::Fn::Month     ,      {tux::grapheme::chronos  ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::Dayname   ,      {tux::grapheme::star5    ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::Day       ,      {tux::grapheme::star5    ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::MonthNum  ,      {tux::grapheme::star5    ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::Year      ,      {tux::grapheme::star5    ,   {.Fg = color::White             ,.Bg = color::R }}},
    {rem::Fn::Loc       ,      {tux::grapheme::file     ,   {.Fg = color::SkyBlue3          ,.Bg = color::R }}}

};
}


namespace rem
{
/**
 * Retrieves the attributes associated with a specified type.
 *
 * This function accesses a database to retrieve a pair consisting of the tux::grapheme type
 * and Color pair associated with the provided `rem::channel`.
 *
 * @param ty The type of `rem::channel` for which attributes are to be fetched.
 * @return A `std::pair` containing the tux::tag type and Color pair associated with the specified type.
 */
std::pair<tux::grapheme::value, color::pair> channel_attributes(const rem::channel ty)
{
    return channels_data_db[ty];
}


/**
 * Retrieves the associated attributes for a given `rem::code` status code.
 *
 * This function looks up the provided status code in the `rem::CCs_database`
 * and returns a pair containing the corresponding tux::grapheme type and Color pair.
 *
 * @param Cod The status code of type `rem::code` for which the attributes are to be retrieved.
 * @return A std::pair containing a `tux::tag::type` representing the tux::tag type
 *         and a `color::pair` representing the associated Color attributes.
 */
std::pair<tux::grapheme::value, color::pair> return_code_attributes(const rem::code Cod)
{
    return codes_database[Cod];
}


/**
 * Retrieves the attributes of a specified function from the functions database.
 *
 * This function fetches a pair of attributes for the given function identifier,
 * including its tux::grapheme type and Color pair, from the `rem::FunctionsDataDB`.
 *
 * @param FnEnum The function identifier of type `rem::fn` whose attributes are to be retrieved.
 * @return A pair containing the tux::tag type (`tux::tag::type`) and Color pair (`color::pair`) associated with the given function identifier.
 */
std::pair<tux::grapheme::value, color::pair> function_attributes(const rem::Fn FnEnum)
{
    return functions_data_db[FnEnum];
}


/**
 * Retrieves the attributes associated with a given action, including its tux::grapheme type
 * and Color pair information.
 *
 * The attributes for the specified action are fetched from a predefined action-to-attribute
 * mapping database.
 *
 * @param A The action of type `rem::action` for which attributes are to be retrieved.
 * @return A pair containing the tux::tag type (`tux::tag::type`) and the Color pair
 * (`color::pair`) associated with the specified action.
 */
std::pair<tux::grapheme::value, color::pair> action_attributes(const rem::Action A)
{
    return actions_color_db[A];
}


std::string render(const rem::code C)
{

    auto [g,col] = return_code_attributes(C);
    std::string text = color::ansi::pair(col);
    text += tux::grapheme::db[g];
    text += ' ';
    text += rem::to_string(C);
    text += "\x1b[39m";
    return text;
}


std::string render(const rem::channel C)
{
    auto [g,col] = channel_attributes(C);
    std::string text = color::ansi::pair(col);
    // text += tux::grapheme::db[g];
    // if (tux::glyph::table[g].width > 1)
    //     text += ' ';

    text += rem::to_string(C);
    text += "\x1b[39m ";
    return text;
}

static std::string_view clean_pretty_function(std::string_view pretty) {
    // 1. Retirer la liste des paramètres pour trouver la fin du nom de la fonction
    size_t paren = pretty.find('(');
    if (paren == std::string_view::npos) return pretty;

    // Trouver la fin des paramètres (la parenthèse fermante)
    size_t end_paren = pretty.find(')', paren);
    std::string_view function_with_args = pretty.substr(0, end_paren + 1);

    // 2. Retirer le type de retour au début
    // On cherche le premier espace avant la parenthèse ouvrante
    size_t space = function_with_args.rfind(' ', paren);
    if (space != std::string_view::npos) {
        function_with_args.remove_prefix(space + 1);
    }

    return function_with_args;
}


std::string this_location(std::source_location &&loc) {
    tux::string text;
    tux::string file_location = loc.file_name();

    tux::string::token::list tokens{};
    auto count = file_location.tokenize(tokens,false,"/");

    if (count) {
        auto [FileIcon, FileColors] = function_attributes(rem::Fn::File);
        //text << " " <<  FileColors << FileIcon << *words.back();
        // text << color::White<< "file:" << FileColors << FileIcon << std::format(" {:<20s}",*tokens.back()) << color::R;
        text << color::White<< "file:" << FileColors << std::format(" {:<20s}",*tokens.back()) << color::R;
    }

    auto [LineIcon, LineColors] = function_attributes(rem::Fn::Line);
    //text << color::R << ' ' << LineColors << LineIcon  << ' ' << std::format("{:<4d}",loc.line());
    text << color::White << "Line #" << LineColors << std::format("{:<4d}",loc.line());
    auto [FunctionIcon, FunctionColors] = function_attributes(rem::Fn::F);
    text <<  " " << FunctionColors << FunctionIcon << color::White << ':' << FunctionColors << clean_pretty_function(loc.function_name()) << color::R;
    loc = {}; // Do not let trailing garbage.
    return *text;
}



std::string render(rem::Fn C)
{
    auto [g,col] = function_attributes(C);
    std::string text = color::ansi::pair(col);
    text += rem::to_string(C);
    text += "\x1b[39m";
    return text;
}


std::string to_string(rem::channel ty)
{
    if (ty == rem::channel::None || ty == rem::channel::Output)
        return "    ";
    // auto [g,col] = channel_attributes(ty);
    // std::string text = color::ansi::fg(color::White) + "[";
    // text += color::ansi::pair(col) + tux::glyph::table[g].value + channels_db[ty] + color::ansi::fg(color::White) + "]\x1b[39m ";

    return channels_db[ty];
}

std::string to_string(rem::code value)
{

    return return_codes_dictionary[value];
}

std::string to_string(rem::Fn fn) {

    switch (fn) {
        case Fn::F:         return "function";
        case Fn::File:      return "file";
        case Fn::Line:      return "line";
        case Fn::Stamp: {
            auto [g,col] = function_attributes(Fn::Stamp);
            std::string text = color::ansi::pair(col);
            text += tux::string::HH_MM_SS_mmm();
            return text;
        }
        case Fn::Hour:      return "hour";
        case Fn::Minute:    return "minute";
        case Fn::Seconds:   return "seconds";
        case Fn::Weekday:   return "weekday";
        case Fn::Month:     return "month";
        case Fn::Dayname:   return "day name";
        default: break;
    }
    return functions_db[fn];
}


// std::string to_string(rem::Fn fn)
// {
//     switch (fn)
//     {
//         case rem::Fn::Stamp: return cat::strwb::HH_MM_SS_mmm();
//             //...
//         default:break;
//     }
//     return functions_db[fn];
// }

std::string to_string(rem::Action ac)
{
    return actions_db[ac];
}



}


std::ostream & operator<<(std::ostream &os, const rem::code cod) {
    auto [g,col] = rem::return_code_attributes(cod);
    os << color::ansi::pair(col) << tux::grapheme::db[g] << ' ' << rem::to_string(cod) << color::R;
    return os;
}

