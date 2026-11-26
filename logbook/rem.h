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

#include <source_location>
#include <logbook/colors.h>
#include <logbook/glyphs.h>
#include <source_location>


/*!
 * @brief  [ a coherent Return Enumeration Mnemonics (system) ]
 */

using tux::color;
using tux::grapheme;


namespace rem
{

/**
 * @enum rem::channel
 * @brief Enumerates various message and status types used in the application
 *
 * This enumeration defines a set of Message and Status identifiers, each
 * assigned a unique value of Type `tux::Integers::U8`. It is used to
 * represent and classify events or states within the system.
 *
 * ### Enumerators:
 * - `none`: Represents no type or an unspecified message/state.
 * - `error`: Indicates an error condition.
 * - `warning`: Represents a warning message.
 * - `fatal`: Denotes a fatal message or condition.
 * - `except`: Represents an exception type message.
 * - `message`: Generic message type.
 * - `output`: Designates output-related messages.
 * - `debug`: Indicates messages meant for debugging purposes.
 * - `info`: Represents informational messages.
 * - `comment`: Denotes comment messages or notes.
 * - `syntax`: Relates to syntax-specific messages.
 * - `status`: Represents status-related information.
 * - `test`: Denotes test-related output or messages.
 * - `interrupted`: Indicates an interrupted operation.
 * - `aborted`: Represents an aborted process or operation.
 * - `segfault`: Signifies a segmentation fault condition.
 * - `book`: Used for book-related status or operations.
 * - `normal`: Represents a normal or default state.
 */
enum channel : Integers::U8{
    None, Err, Warning, Fatal, Except, Message, Output, Debug, Info, Comment, Syntax, Status, Test, Interrupted, Aborted, Segfault, Book, Normal, Grace
};

/**
 * @enum code
 * @brief Enumerates various common result and status codes used in the system.
 *
 * This enumeration defines a broad range of identifiers for conveying the result
 * or state of operations, errors, conditions, and other system-defined statuses.
 * Each enumerator is of Type `tux::Integers::U8` and represents a specific meaning
 * or  to describe different conditions in the system.
 *
 * ### Enumerators:
 * - `ok`: Represents a successful or positive outcome.
 * - `accepted`: Indicates an action or request was accepted.
 * - `success`: Denotes that an operation completed successfully.
 * - `rejected`: Indicates that an action or request was rejected.
 * - `failed`: Represents a failure condition.
 * - `empty`: Denotes an empty state or data structure.
 * - `full`: Represents a full state or capacity reached.
 * - `notempty`: Indicates that an entity is not empty.
 * - `implemented`: Represents a feature or functionality that has been implemented.
 * - `notimplemented`: Indicates a feature or functionality is yet to be implemented.
 * - `untested`: Denotes a feature or condition that has not yet been tested.
 * - `eof`: Signifies the end of a file (EOF).
 * - `eos`: Represents the end of a stream, string, statement, or status.
 * - `null_ptr`: Indicates a null or invalid pointer reference.
 * - `notexist`: Indicates that an entity does not exist.
 * - `exist`: Represents that an entity already exists.
 * - `unexpected`: Denotes an unexpected condition.
 * - `expected`: Represents an expected condition.
 * - `blocked`: Indicates that a thread was blocked due to a locked mutex or resource.
 * - `locked`: Represents that a thread has successfully locked a mutex or resource.
 * - `overflow`: Indicates a buffer overflow condition.
 * - `oob`: Represents a buffer overflow, often due to out-of-bounds access.
 * - `reimplement`: Suggests reimplementation of a feature or functionality.
 * - `done`: Indicates the completion of an operation.
 * - `complete`: Represents that a task or process has been fully completed.
 * - `finish`: Marks the concluxion of an operation or process.
 * - `undefined`: Denotes an undefined state or value.
 * - `ready`: Indicates readiness for action or operation.
 * - `terminate`: Represents a termination condition or request.
 * - `timeout`: Denotes that an operation timed out.
 * - `divbyzero`: Represents a division by zero condition.
 * - `notvisible`: Indicates that an entity is not visible.
 * - `cancel`: Denotes a cancellation event or state.
 * - `object_ptr`: Refers to an object pointer.
 * - `object_id`: Refers to an object identifier.
 * - `unhandled`: Represents an unhandled condition or exception.
 * - `zero`: Represents a zero state or value.
 * - `hup`: Indicates a hang-up (HUP) signal or similar condition.
 * - `notready`: Denotes an entity is not yet ready.
 * - `notfound`: Represents that a requested entity or resource was not found.
 * - `found`: Indicates that a requested entity or resource was found.
 * - `dismissed`: Denotes that a condition or state was dismissed.
 * - `syntax_error`: Represents a syntax error condition.
 */
enum code : Integers::U16
{
    Ok  =0           , ///< Obviously;
    Accepted         ,
    Success          ,
    Rejected         ,
    Failed           ,
    Empty            ,
    Full             ,
    NotEmpty         ,
    Implemented      , ///< Like Notimplemented Or Already Implemented
    NotImplemented   , ///< "Please, Implement"
    UnTested         ,
    Eof              , ///< End Of File
    Eos              , ///< End Of Stream Or String Or Statement Or Status ( Machine State )
    NullPtr          , ///< It Will Happen. Trust Me :)
    NotExist         , ///< Does Not Exist
    Exist            , ///< Does Already Exist
    Unexpected       , ///< Unexpected
    Expected         , ///< Expected
    Blocked          , ///< Thread Trying To Lock A Mutex Has Failed Because The Mutex Is Already Locked Into Another Thread...
    Locked           , ///< Thread Trying To Lock A Mutex Has Become The Owner Of The Lock.
    Overflow         , ///< Buffer Overflow
    Oob              , ///< Buffer Overflow
    Reimplement      ,
    Done             ,
    Complete         ,
    Finish           ,
    Undefined        ,
    Ready            ,
    Terminate        ,
    Timeout          ,
    Divbyzero        ,
    NotVisible       ,
    Cancel           ,
    ObjectPtr        ,
    ObjectId        ,
    UnHandled        ,
    Zero             ,
    Hup              ,
    NotReady         ,
    NotFound         ,
    Found            ,
    Dismissed        ,
    SyntaxError     ,
    Applied          ,
    NotApplicable    ,
    Valid            ,
    Invalid          ,
    Removed         ,
    Break
    //...to be continued

};


/**
 * @enum rem::Fn
 * @brief Represents function-related identifiers and time components.
 *
 * This enumeration provides various function identifiers and time-related
 * components, each assigned a unique value of Type `tux::Integers::U8`.
 * It is used for identifying functions, timestamps, and other contextual
 * information within the appliTuxion.
 *
 * ### Enumerators:
 * - `func`: Represents a general function identifier.
 * - `endl`: Indicates the end of a line in the input format.
 * - `file`: Denotes a file identifier or reference.
 * - `line`: Represents a line reference or number.
 * - `stamp`: Indicates a fully detailed timestamp.
 * - `hour`: Refers to the hour component of a timestamp.
 * - `minute`: Represents the minute component of a timestamp.
 * - `seconds`: Denotes the seconds component of a timestamp.
 * - `weekday`: Represents the weekday of a date.
 * - `dayname`: Denotes the name of the day in a week.
 * - `month`: Represents the name of the month by default.
 * - `day`: Indicates the day of the month.
 * - `monthnum`: Represents the numeric representation of the month.
 * - `year`: Refers to the year component of a date.
 */
enum Fn : Integers::U32
{
    F                , ///< Function Signature From within the call to rem::to_string(rem::Fn::F)
    Eol              , ///< End Of Line Code, Input Format
    File             ,
    Line             ,
    Stamp            , ///< Fully Detailed Timestamp
    Hour             ,
    Minute           ,
    Seconds          ,
    Weekday          ,
    Dayname          ,
    Month            , ///< Par Defaut Month Name
    Day              ,
    MonthNum         , ///< Maintenant Explicite
    Year             ,
    Loc
};


/**
 * @enum rem::Action
 * @brief Represents a set of predefined actions or control signals for system processes.
 *
 * This enumeration defines various actions that control or manage
 * iterations, sections, loops, and commit operations within the system.
 * Each enumerator provides specific behavior or signals for processing
 * workflow and structure handling.
 *
 * ### Enumerators:
 * - `enter`: Enter a new block or increase indent level.
 * - `leave`: End accumulators and commit changes; terminate a section, reset attributes, or decrease indentation.
 * - `commit`: Signal to commit the current state or data.
 * - `begin`: Mark the start of a section or increase indent level.
 * - `end`: End a loop, action, or section; decrease indentation or finalize inputs.
 * - `cont`: Continue a loop or signal iteration.
 * - `dismiss`: Dismiss the current action or iteration; break the process or ignore the action.
 */
enum Action : Integers::u64
{
    Enter            , ///< Enter Pad Or Indentation
    Leave            , ///< End (Bookger: End Of Entry Accumulators, So Do Commit); End Of (Sel)Section, Attribute ( Auto-color::Reset ) And Unindent
    Commit           , ///< Commit...
    Begin            , ///< Begin (Sel)Section Or Augment Indentation Level
    End              , ///< End   Loop/Action Or End Selection Or Unindent One Level; Or End Inputs On The Current Bookentry Then Fluxh To File.
    Continue         , ///< Continue Loop And/Or Continue Signals::Action Iteration.
    Dismiss          , ///< The Current Action Or Iteration Has Been Dismissed : Break Run Or Actual Action.
};

std::string to_string(rem::channel ty);
std::string to_string(rem::code value);
std::string to_string(rem::Fn fn);
std::string to_string(rem::Action a);
std::pair<tux::grapheme::value,color::pair> channel_attributes(rem::channel ty);
std::pair<tux::grapheme::value,color::pair> return_code_attributes(rem::code Cod);
std::pair<tux::grapheme::value,color::pair> function_attributes(rem::Fn FnEnum);
std::pair<tux::grapheme::value,color::pair> action_attributes(rem::Action A);

std::string render(rem::code C);
std::string render(rem::channel C);
std::string render(rem::Fn f);

//std::string_view strip_gcc_function_name(std::string_view fnstr);

std::string this_location(std::source_location&& loc = std::source_location::current());

} // namespace rem



std::ostream& operator <<(std::ostream&,rem::code);
//std::ostream& operator <<(std::ostream&,rem::Fn);


bool operator !(rem::code);
bool operator +(rem::code);
bool operator -(rem::code);

bool operator *(rem::code c);