# logbook

A small, standalone **C++23 console text-journal / logging library**.

`logbook` is a shared library (CMake target `logbook`; see *Build* for the actual output name) that
writes timestamped, colorized, glyph-decorated log entries to a text file (and the console), using a
simple `std::ostream`-style streaming API. It also ships a tiny `playground` demo program and a couple
of reusable support components.

- **Version:** `0.1.0` (`project(logbook VERSION 0.1.0)` in `CMakeLists.txt`)
- **Language / standard:** C++23 (`CMAKE_CXX_STANDARD 23`, `CMAKE_CXX_STANDARD_REQUIRED ON`)
- **Build system:** CMake
- **Author:** Serge Lussier (`serge.lussier@oldbitsnbytes.club` / `lussier.serge@gmail.com`)
- **License:** intentionally loose/unclear. Headers say "Open source FREE licence... GNU FREE GPL-1,2,
  MIT... or whatever - apply" **and** "all source code that I am the only author, I reserve for myself,
  the rights to make it to restricted private license". `glyphs.h` says "Read the LICENSE provided with
  this project", but **no `LICENSE` file is present**. No `README` existed before this one.

> This project is explicitly a *work in progress*. The upstream commit history itself calls out a
> "quick fixe", and there are numerous known bugs / malfunctions. They are collected at the bottom
> under **[Known buggy states & malfunctions (TODO)](#known-buggy-states--malfunctions-todo)**.

---

## What it does

`logbook` provides:

- **`book`** (`logbook/book.h`): the main logger.
  - `book::book(std::string book_filename)` — constructs the logger. The first instance becomes the
    singleton `book::logbook`; a `book::file` named `<book_filename>.book` is created. `".book"` is
    appended automatically (`book::file::file`, `logbook/book.file.cxx`).
  - `book::open(std::ios_base::openmode)` — open output (and start a background `std::jthread` flusher).
  - `book::close()` / `book::stop()` — close output; `stop()` requests worker stop, `join()`s, then
    closes. `book::stop()` **must not** be called from inside the `book::file::run` worker thread
    ("Never-ever call this method within the own book::file::run thread! duh!!", `book.cxx`).
  - `book::log` — a per-channel entry accumulator. Static pre-created channels:
    `book::error`, `book::status`, `book::warning`, `book::fatal`, `book::except`, `book::message`,
    `book::write`, `book::debug`, `book::info`, `book::comment`, `book::syntax`, `book::test`,
    `book::interrupted`, `book::aborted`, `book::segfault`. Streaming `operator<<` for strings,
    `tux::string`, `rem::channel`, `rem::code`, `rem::Action`, colors, `book::ctrl`, `double`, and a
    generic `template<typename T> operator<<`.
  - `book::ctrl` control codes: `book::end` (0), `book::eol` (1), `book::push` (2), `book::time` (3).
    `book::eol`/`book::push` flush current text as a line; `book::end` flushes and resets to `head`;
    `book::time` inserts an `HH-MM-SS-mmm` timestamp.
  - `book::exception` (`: std::exception`), `what()`, `operator[](const book::log&)`.
  - `book::file` — output sink; `cached_lines`, `seuil` (4096), `flush()`, `push()`, `mode`, `mtx`,
    `std::jthread worker`; `file_ptr` falls back to `&std::cout`.
- **`rem`** (`logbook/rem.h`): "a coherent Return Enumeration Mnemonics (system)".
  - `rem::code` — ~45 status codes (`Ok`, `Accepted`, `Success`, `Rejected`, `Failed`, `Empty`, `Full`,
    `NotImplemented`, `Eof`, `Eos`, `NullPtr`, `NotExist`, `Exist`, `Unexpected`, `Blocked`, `Locked`,
    `Overflow`, `Oob`, `Done`, `Complete`, `Finish`, `Ready`, `Terminate`, `Timeout`, `Divbyzero`,
    `Cancel`, `UnHandled`, `Zero`, `Hup`, `NotReady`, `NotFound`, `Found`, `Dismissed`, `SyntaxError`,
    `Applied`, `NotApplicable`, `Valid`, `Invalid`, `Removed`, `Break`, …).
  - `rem::channel` — message kinds (`None`, `Err`, `Warning`, `Fatal`, `Except`, `Message`, `Output`,
    `Debug`, `Info`, `Comment`, `Syntax`, `Status`, `Test`, `Interrupted`, `Aborted`, `Segfault`,
    `Book`, `Normal`, `Grace`).
  - `rem::Fn` — `F`, `Eol`, `File`, `Line`, `Stamp`, `Hour`, `Minute`, `Seconds`, `Weekday`, `Dayname`,
    `Month`, `Day`, `MonthNum`, `Year`, `Loc`.
  - `rem::Action` — `Enter`, `Leave`, `Commit`, `Begin`, `End`, `Continue`, `Dismiss`.
  - `rem::to_string(...)`, `rem::render(...)`, `rem::channel_attributes`, `rem::return_code_attributes`,
    `rem::function_attributes`, `rem::action_attributes`, `rem::this_location(std::source_location)`.
  - Operators on `rem::code`: `operator!` (true if **not** a success state; success = `Ok`, `Accepted`,
    `Success`, `Done`, `Ready`, `Finish`, `Complete`, `Found`, `Applied`, `NotApplicable`, `Exist`,
    `Valid`), `operator+`, `operator*`, `operator-`, `operator<<(std::ostream&, rem::code)`.
- **`tux`** support types:
  - `tux::string` (`logbook/string.h`): a `std::string` wrapper with `operator*`, streaming `operator<<`
    for strings, `int`, `float`, colors, `rem::channel`, `rem::code`, `grapheme::value`, …; assignment
    from `std::string`/`const char*`/`char`/numeric; `clear`, `empty`, `size`, `length`, `begin`, `end`;
    `fill`; static `fill`; `binary`, `hex`, `Hex`, `bytes`, `make_list`, `make_str`, `make_viewlist`,
    `tokenize`, `eat`, `now`, `HH_MM_SS_mmm`; `token`, `location`, `argument`.
  - `tux::color` (`logbook/colors.h`): 256-color `color::value`, `color::css`, `color::pair`, `color::table`,
    `color::css_t`, `color::ansi` (`fg`, `bg`, `pair`, `reset`, `reset_pair`, `reset_fg`, `reset_bg`,
    `out_mode::compaq`/`rgb`, `mode`), `color::scan`, `color::name`, `color::query_data`, `color::pretty_names`,
    140-CSS-color table, `color::R`/`color::Reset`/`color::Z` == 255. Emits ANSI escape sequences.
  - `tux::grapheme` (`logbook/glyphs.h`): `grapheme::value` (`u8`), `grapheme::db`, `glyph::table`
    (`unicode_glyphs_table.i.h`), `scan`, `scan_name`, `name`, `text`; ~122 named glyphs (Nerd Font /
    Unicode). `tux::glyph`.
  - `tux::buffer` (`logbook/buffer.h`): fixed-capacity byte buffer; `operator<<`, `operator*`, `operator++`,
    `operator--`, `operator bool`, `clear`, `empty`, `full`, `state` flags, `MAX_SIZE`. *(very buggy, see below)*
  - `tux::border_glyphes_set` (`logbook/border_glyphes_set.h`): Unicode box-drawing frame; `frame_data`,
    `frame_weight`, `MatrixData_S`, `Push`/`Pop`, `operator=`, `operator[]`, `FMatrix_S`. *(from FTXUI)*
- **`Integers`** (`logbook/exports.h`): `u8/u16/u32/u64/i8/i16/i32/i64`, `U8…U64`, `I8…I64`, `byte`, `f32`,
  `f64`, `f128`, …; plus `CLASSNAME_START`, `CLASSNAME`, `CLASSNAME_DERIVED`, `LOGBOOK_LIB`, and a
  `pragma warning`-carrying Windows branch. Note `string.h`, `buffer.h`, `rem.h`, `border_glyphes_set.h`
  do `using namespace Integers;` / `using tux::color; using tux::grapheme;` / `using namespace std::literals;`.
- **`playground`** (`playground/`): a tiny demo executable. `playground::run()` constructs
  `book m_book{"logbook_playground"}`, opens it `trunc`, logs a few lines, `m_book.stop()`, then
  `system("cat logbook_playground.book")`, returns `rem::Ok`. `main` prints
  `playground::run() returned: <...>` and returns `!!r ? 0 : -1`. `playground` links `sqlite3` + `logbook`.

### Output format

Each `book::log` entry, once `stage()` has run, begins with:

```
<hh-mm-ss-mmm timestamp><ansi color>::<Channel><ansi reset> <message...>
```

(`book::log::stage`, `logbook/book.log.cxx`; `rem::render(rem::Fn::Stamp)`, `rem::render(channel)`). The
documented grammar in `book.h` is `HH-MM-SS-mmm [channel] {?file,?line,(?function -> EOL)}` — but the
`{?file,?line,?function}` part is **not currently emitted** automatically; `rem::this_location()` must be
streamed explicitly. `book::write` (`rem::Output`) uses no channel name. ANSI color sequences
(`\x1b[38;5;Nm`, `\x1b[48;5;Nm`, `\x1b[39m`, `\x1b[49m`, `\x1b[39;49m`, …) and Unicode glyphs are embedded
in the text. Lines are buffered in `book::file::cached_lines` and flushed by the worker every ~500 ms once
`cached_lines.size() > seuil`, or on `stop_worker`/`join`, with `'\n'` per line. On close a
`book::file::close filesystem @<ts> : [<Ok>].` line is appended and a message printed.

---

## Layout

```
CMakeLists.txt                 # root project; adds playground/
logbook/                       # the library ("logbook")
  book.h / book.cxx            # class book, book::log, book::file, book::exception, ctrl
  book.log.cxx                 # book::log operator<< / stage(); static channel instances
  book.file.cxx                # book::file open/close/push/flush/run(stop_token)/stop_worker
  rem.h / rem.cxx              # rem:: enums + to_string/render/attributes + operators
  string.h / string.cxx        # tux::string
  buffer.h / buffer.cxx        # tux::buffer
  colors.h / colors.cxx        # tux::color (256-color + CSS + ANSI)
  glyphs.h / glyphs.cxx        # tux::grapheme + tux::glyph
  unicode_glyphs_table.i.h     # generated/static glyph table included by glyphs.cxx
  border_glyphes_set.h/.cxx    # tux::border_glyphes_set (FTXUI-derived)
  exports.h                    # Integers, CLASSNAME_*, export macros, mandatory includes
  logbook_export               # generated by CMake generate_export_header (build tree; EXPORT_FILE_NAME)
playground/
  CMakeLists.txt               # playground exe; cmake_minimum_required(VERSION 4.0 ...)
  playground.h / playground.cxx# class playground
  main.cxx                     # auto main() -> int
```

`CMakeLists.txt` lists headers `exports.h colors.h glyphs.h unicode_glyphs_table.i.h rem.h string.h
buffer.h book.h border_glyphes_set.h`, sources `colors.cxx glyphs.cxx string.cxx rem.cxx buffer.cxx
book.cxx book.file.cxx border_glyphes_set.cxx book.log.cxx`, `add_library(logbook SHARED ...)`,
`CMAKE_CXX_STANDARD 23`, `logbook_DEBUG=$<CONFIG:Debug>`, `generate_export_header(... EXPORT_FILE_NAME
logbook_export)`, `target_link_libraries(logbook ${CMAKE_DL_LIBS} sqlite3)`, install + uninstall targets.

---

## Requirements

- A **C++23** compiler (tested here with **GCC 16.2.1**; Clang 23 also present; `<format>`, `<chrono>`
  `zoned_time`, `std::jthread`, `std::source_location`, `std::string::contains`-era C++20/23 features are
  used).
- **CMake ≥ 3.40** for the root project **but `playground/CMakeLists.txt` requires CMake ≥ 4.0**; tested
  with **CMake 4.5.1**. (`cmake_minimum_required(VERSION 3.40 FATAL_ERROR)` vs `VERSION 4.0 FATAL_ERROR`.)
- **sqlite3** library + headers (`-lsqlite3`; `sqlite3.h` found at `/usr/include/sqlite3.h`). It is
  **linked but never used** — no `#include <sqlite3.h>` / no SQL anywhere. Still a hard link dependency.
- `${CMAKE_DL_LIBS}` (`dl`). `pthread`/threads via `std::jthread`.
- A terminal with **UTF-8 + Nerd Font / Unicode glyph** support and **ANSI color** to render output nicely
  (output is still produced without it).
- Linux-ish environment for `playground`'s `system("cat ...")`. `unistd.h` on non-Windows.

---

## Build

```sh
cmake -S . -B build
cmake --build build
# optional demo:
cmake --build build --target playground
```

With Ninja:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

What gets built:

- shared library **`lib.logbook.so.0.1.0`** with symlinks `lib.logbook.so.0`, `lib.logbook.so`
  (`set_target_properties(logbook PROPERTIES OUTPUT_NAME ${FRAMEWORK}.${PROJECT_NAME} VERSION 0.1.0
  SOVERSION 0)`, and `${FRAMEWORK}` is **never set** → output name `.logbook`, i.e. `lib` + `.logbook`).
  On this system it lands at `build/lib.logbook.so*`.
- executable **`build/playground/playground`**.

Run the demo (writes `logbook_playground.book` in the current directory):

```sh
cd /tmp && LD_LIBRARY_PATH=/path/to/build /path/to/build/playground/playground
```

Install:

```sh
cmake --install build
```

`install(TARGETS logbook LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bi§
PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/logbook)`, `PUBLIC_HEADER` = the listed
`logbook/*` headers, `EXPORT logbook`. A `uninstall_logbook` target is added. *(See known issues.)*

---

## Usage (minimal)

```cpp
#include <logbook/book.h>

int main() {
    book m_book{"my_journal"};                       // -> my_journal.book ; singleton book::out_file

    auto r = m_book.open(std::ios_base::out | std::ios_base::trunc);   // rem::code
    if (+r) {                                        // rem::operator+ == success
        book::info << "started" << book::eol;        // or book::end
        book::warning << rem::this_location() << book::end;
        book::write << "plain output" << book::end;
        book::error << rem::Failed << book::end;     // rem::code streaming
        book::info << tux::color::Red << "red text" << tux::color::R << book::eol;
    }
    m_book.stop();                                   // stop worker, join, close  (returns rem::code)
    // ... m_book destructor: if book::logbook==this, delete book::out_file
}
```

Return codes are `rem::code`; check with `if (!r)`, `if (+r)`, `if (*r)`, or `rem::to_string(r)` /
`rem::render(r)`. **Caveat:** see `rem::operator-` / `Zero` / `Hup` issues below.

---

## Current status

**Builds cleanly** as a C++23 shared library + `playground` on GCC 16.2.1 / CMake 4.5.1 / sqlite3 3.54.1,
and `playground` runs (exit 0, produces `logbook_playground.book` with ANSI+glyph output). There is **no
test suite**, no CI, no `LICENSE`, no prior `README`. Many features are scaffolded/commented-out
(`book::log::operator<<(rem::Fn)`, `operator<<(std::source_location&&)`, `rem::Fn::Loc`,
`book::file::file_ptr`, CSS-color `operator<<`, `argument`-based formatting, `state::commit`, `rem::code`
"to be continued", …), and several are outright broken.

---

## Known buggy states & malfunctions (TODO)

> `- [ ]` = not fixed. Items marked **(verified)** were reproduced/observed on **GCC 16.2.1 + CMake
> 4.5.1** in this environment; others are inferred from reading the code (and may still be UB /
> platform-dependent). Cross-reference `file:line`.

### CMake / packaging

- [ ] **`RUNTIME DESTINATION bi§`** — stray `§` typo in `install(TARGETS ...)` (`CMakeLists.txt`, ~line
  83). Binaries would install to a `bi§/` directory. *(verified by reading)*
- [ ] **`OUTPUT_NAME ${FRAMEWORK}.${PROJECT_NAME}` with `FRAMEWORK` unset** → library is
  `lib.logbook.so`, output name `.logbook`. `uninstall_logbook` removes `lib${PROJECT_NAME}++*` =
  `liblogbook++*`, which **does not match** `lib.logbook.so*`, and uses `lib`/`include` rather than
  `${CMAKE_INSTALL_PREFIX}` for `lib`. *(verified by reading; lib name verified by building)*
- [ ] **`EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)`** — missing **destination** argument; `copy_if_different`
  needs `<file>... destination`. When `compile_commands.json` exists (e.g. `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`,
  second configure) CMake errors. `IF(EXISTS ...)` doesn't prevent it. *(verified)*
- [ ] **`cmake_minimum_required` mismatch**: root `VERSION 3.40 FATAL_ERROR`, `playground` `VERSION 4.0
  FATAL_ERROR`. Building with CMake < 4.0 fails in `add_subdirectory(playground)`.
- [ ] **`PUBLIC_HEADER`** set to `logbook/...` paths and not including generated `logbook_export`; install
  `PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}`; `target_include_directories`
  doesn't expose `${CMAKE_CURRENT_BINARY_DIR}` for `logbook_export`. `glyphs.h` references a `LICENSE`
  that isn't installed/shipped. `EXPORT logbook` but no `logbookConfig.cmake`. *(partially verified)*
- [ ] **`target_link_libraries(logbook ${CMAKE_DL_LIBS} sqlite3)` + `playground ... sqlite3 logbook`**:
  hard **sqlite3** dependency, but no sqlite header/use in code. *(verified: no `#include <sqlite3.h>`)*
- [ ] **`pragma warning(disable : 4996)`** — missing `#` (should be `#pragma warning(...)`) in
  `exports.h` Windows branch (`_MSC_VER`/`_WIN32`/...); Windows branch says "not supported...yet..." and
  `LOGBOOK_LIB` is defined but never applied to classes. Non-Windows unaffected.
- [ ] **`#define out std::cout` / `#define lend std::endl;`** (and `numeric_construct`, `AssignNumeric`)
  in `string.cxx` — global macros leaking; `lend` expands to `std::endl;`. *(verified by reading)*
- [ ] Broken English / non-ASCII noise in comments and identifiers; `appliTuxion`, `Tuxed`, `trunTuxed`,
  `publiTuxions`, `concluxion`, `Bookger`, `rem::Fn::...`, mixed `Err`/`Error`, `book::ent` (renamed
  `book::log`) in stale comments, French comments. Cosmetic.

### `book::` logging core

- [ ] **`book::log::operator<<(rem::channel type_)` emits literal `":<16"`** — `text <<
  std::format(":<16", rem::render(type_));` (`book.log.cxx`). `std::format` called with a format string
  containing **no `{}` replacement field**; the `rem::render(type_)` argument is **discarded**; intended
  `std::format("{:<16}", rem::render(type_))`. On libstdc++ it appends `":<16"`; on standard-strict
  `std::format` it throws `std::format_error`. *(verified: `.book` output contains `:<16`, channel name
  absent)*
- [ ] **`book::out_file` null dereference** — `book::out_file` is `static book::file* = nullptr`.
  `book::log::operator<<(book::ctrl)` calls `book::out_file->push(...)`; `book::open`/`book::close`/
  `book::stop` deref `book::out_file`. Streaming any `book::*` channel with `book::eol`/`book::end`/
  `book::push` **before constructing any `book`** (or before `book::open`) → **segfault / UB**. No null
  checks. *(verified segfault)*
- [ ] **Only the first `book` owns the output** — `book::book` `if (!book::logbook) { book::logbook=this;
  book::out_file=new book::file(...); }`; `book::~book` `if (book::logbook==this){ book::logbook=nullptr;
  delete book::out_file; }`. A second `book` shares `book::out_file`; `book::open`/`book::close`/
  `book::stop` called on a second instance operate on the first's `out_file`. `book::logbook` name vs
  `book::out_file`.
- [ ] **`book::file::open()` always returns `rem::Accepted`**; `out.open(filename, mode)`; if
  `!out.is_open()` **`file_ptr = &std::cout` silently** (logs fall back to console); `is_open = true`
  unconditionally. `book::open` `if (!book::out_file->open()) return rem::Failed;` can **never** return
  `rem::Failed`. No error reported. *(verified: `book::open` returned `Accepted` for a nonexistent
  directory; output went to stdout)*
- [ ] **`book::file::close()` doesn't stop/join the worker**; `book::close()` (non-`stop`) leaves
  `worker` running and `is_open=false`, **pending `cached_lines` are not flushed**; `book::file::close`
  itself doesn't `flush()`. `book::file::~file()` is empty (`//close();`) and doesn't `close()`. Only
  `book::stop()` does `stop_worker(); worker.join(); close();`. `book::file::run` keeps `flush()`-ing;
  `book::file::flush` returns `rem::Rejected` when `!is_open`. (`std::jthread`'s own destructor will
  `request_stop()`+`join()`, so no `std::terminate`, but no guaranteed flush.) *(partially verified)*
- [ ] **`book::stop()`** `if (!book::out_file->is_open) return rem::Rejected; stop_worker();
  worker.join(); close(); return rem::Accepted;`. `std::jthread::join()` on a **non-joinable** thread →
  `std::system_error`; called from the `run` thread itself → `std::system_error`. `stop_worker()`
  `worker.request_stop(); stop=true;`. Not guarded. `book::stop` `close()`. 
- [ ] **`book::file::run` flush logic**: `while(!stoken.stop_requested()){ sleep 500ms; unique_lock(mtx);
  if(cached_lines.size() > seuil){ flush(); cached_lines.clear(); } } flush();`. `seuil=4096`. `flush()`
  itself `cached_lines.clear()`. Final `flush()` checks `is_open`. *(partially verified)*
- [ ] **`book::file::close` doesn't clear `cached_lines`**; writes `book::file::close filesystem
  @<ts> : [<Ok>].` + `std::cout` `book::file::close filesystem : [...]` only if `file_ptr==&out`; if
  `file_ptr==&std::cout` no close marker. `out.close()`. `is_open=false`, `file_ptr=nullptr`.
- [ ] **Data races / thread safety**: `book::log::ent_mtx` exists but `book::log::operator<<(ctrl)`
  doesn't lock it; `book::file::push` doesn't lock `book::file::mtx`; `book::file::flush` doesn't lock
  `mtx`; `cached_lines` (`std::vector`) mutated by logging threads and read/cleared by `run`. Only
  `book::open` (`std::lock_guard(ent_mtx)`) and `book::log::operator<<(rem::Action)`
  (`std::unique_lock(ent_mtx); if(lock.owns_lock())...`) lock. Static `book::info`, `book::error`, …
  share `tux::string text`. `ent_mtx` commented-out in most `operator<<`. *(inferred)*
- [ ] **`book::log::operator=(const book::log& e)` copies only `code` and `type`** — **not `text`, not
  `line_state`** (`book.h`). `book::log::operator=(book::log&&)` is `= default`. `book::log::log(const
  book::log&)=default`. Consequence: `book::exception::operator[](const book::log&)` `_log_=el;` does
  **not** copy the log's `text`. *(verified)*
- [ ] **`book::exception` broken**: `what()` `if(!_log_.text.empty()) _msg_=*_log_.text; else
  _msg_="Exception message is empty";`. Because `operator=` doesn't copy `text`, `_log_.text` is empty.
  `_msg_` set by `exception(const char*)`/`exception(const std::string&)` is **overwritten**.
  `book::exception("x").what()` → `"Exception message is empty"`. `_e_` is **uninitialized** in the
  `txt` constructors (`_e_=true/false` only in `exception()`); `_e_` is never read. `_msg_.clear()` in
  `~exception`. `operator[]` returns `book::exception`. `_log_`. *(verified)*
- [ ] **`book::log::stage()`** `rem::render(rem::Fn::Stamp) + color::White + "::" + rem::render(type)`
  for non-`rem::Output`, else `rem::render(type) + "    "`; `rem::render` uses
  `color::ansi::pair` + `\x1b[39m`. `state::commit` is declared but **never set**; only `head`/`inputs`.
  `book::log::line_state` `state::head`. `reset()`. `book::end` `line_state=head`. `book::eol/push`
  `line_state=inputs`. `book::time`. 
- [ ] **`book::log::operator<<(rem::channel type_)`** also called on `rem::channel::None`/`Output`
  (commented-out early return); `rem::render(rem::Output)` `to_string`→`"    "`. 
- [ ] **`book::log::operator<<(rem::code)`** `rem::to_string(code_)` — **`rem::code::Zero`/`Hup` (and any
  unmapped code) throw**; `rem::to_string` returns `nullptr`→`std::string`. *(verified)*
- [ ] **`book::log::operator<<(rem::Fn ...)` / `operator<<(std::source_location&&)`** are commented out /
  not implemented. `book::log::operator<<(rem::Action)` prints `[<...>]`.
- [ ] `book::file::mode` default `app|out`, `book::file::file` constructor default `trunc|out`, but
  `book::open` overwrites `mode`; `book::file::open` uses `out.open(filename, mode)`. `filename += ".book"`.
  `book::file::file(...)`. 
- [ ] `book::file::flush` returns `rem::Empty`/`rem::Complete`/`rem::Rejected`; `rem::operator!` treats
  `rem::Empty` as failure, `rem::Complete` as success. `book::file::push` `rem::Accepted`/`rem::Rejected`.
- [ ] `book::open` returns `rem::Rejected` if `is_open`, `rem::Failed`, `rem::Accepted`; `book::close`
  `rem::Rejected`/`rem::Accepted`; `book::stop`. 
- [ ] `book::file::file_ptr` `std::ostream*` `file_ptr`. `book::file::out`. `file_ptr=&std::cout`.
  `book::file::file_ptr`. `book::file::file_ptr` "Ununsed yet..." comment. `book::file::mode`.
- [ ] `book::log::ent_mtx`. `book::log::ent_mtx`. 
- [ ] `book::log::code` `rem::code::Ok`. `book::log::type`. `rem::channel::None`. `book::log::text`.
  `tux::string`. `book::log::operator<<(tux::string)`. `*str_`. 
- [ ] `book::book::logbook`. `book::book::out_file`. 

### `rem::` return codes

- [ ] **`bool operator -(rem::code);` is declared in `rem.h` but never defined** → **`undefined reference
  to 'operator-(rem::code)'`** at link if used. *(verified)* (`operator!`, `operator+`, `operator*` are
  defined; `operator*` `return !!c;`.)
- [ ] **`rem::to_string(rem::code::Zero)` throws `std::logic_error`** ("basic_string: construction from
  null is not valid"). `rem::code::Zero` has **no entry** in `return_codes_dictionary`. `to_string`
  `return return_codes_dictionary[value];`, `std::map::operator[]` inserts `nullptr`, returning
  `std::string` from `nullptr`. On other STLs `std::string(nullptr)` is UB. Same for **`rem::render(...)`,
  `operator<<(ostream, rem::code)`, `book::log::operator<<(rem::code)`** which call `to_string`.
  *(verified `Zero`)*
- [ ] **`rem::to_string(rem::code::Hup)` throws** — `rem::code::Hup` has no `return_codes_dictionary`
  entry. *(verified)*
- [ ] **`rem::to_string(rem::code::Success)` returns `"Success "` with a trailing space**. *(verified)*
- [ ] **`rem::to_string` / `rem::render` / `rem::*_attributes` use `std::map::operator[]` on non-const
  maps** (`channels_db`, `return_codes_dictionary`, `functions_db`, `actions_db`, `channels_data_db`,
  `codes_database`, `functions_data_db`, `actions_color_db`); **missing keys silently insert defaults**
  (`const char*=nullptr`, `pair{}`, `grapheme::ok`, `color::pair{White,Grey11}`) rather than erroring.
  `rem::code::Zero`/`Hup` missing from `return_codes_dictionary`; `rem::code::Zero`/`Hup` missing from
  `codes_database`; `rem::Fn::Eol` missing from `functions_data_db`. *(partially verified)*
- [ ] `rem::code::Applied` appears **twice** in `operator!` / `operator+`. `rem::code::NotApplicable`
  counted as **success**. `rem::code::Empty`/`Rejected`/`Failed`/`Invalid`… are "not success".
- [ ] `rem::operator*` `return !!c;` (uses `operator!`); `rem::operator+` same success set as `operator!`.
- [ ] `rem::operator<<(std::ostream&, rem::code)`. 
- [ ] `rem::to_string(rem::Fn::Stamp)` returns `color::ansi::pair(...) + tux::string::HH_MM_SS_mmm()`
  **without** `\x1b[39m`; `rem::render(rem::Fn::Stamp)` wraps `color::ansi::pair(col) ... "\x1b[39m"`.
  `rem::render` `color::ansi::pair`. `rem::Fn::Stamp`. `rem::Fn::Month`/`Dayname` `switch`.
  `rem::Fn::Loc` `"Obsolete!, use sourcelocation"`. `rem::Fn::Eol`. 
- [ ] `rem::render(rem::channel::Output)`. `rem::to_string(None||Output)`. `"    "`. 
- [ ] `rem::render` `tux::grapheme::db[g]`. `color::ansi::pair`. `\x1b[39m`. 
- [ ] `rem::this_location` — `clean_pretty_function`: `end_paren = find(')', paren)`; if `npos`,
  `substr(0, end_paren+1)` = `substr(0,0)`; `rfind(' ', paren)`. `tokenize(tokens,false,"/")`. Uses
  `tux::string::token::operator*` `{begin,last+1}` (past-end, UB). `std::format(" {:<20s}",...)`.
  `file_name`, `line`, `function_name`. `rem::Fn::File/Line/F`. 
- [ ] `rem::channel` names incl. odd ones; `rem::channel::Book`→`"Log"`; `Grace`→`"Gracefully
  Terminated/Done/Clean."`. `rem::channel::Output`→`""`. `rem::channel::None`→`"    "`. 
- [ ] `rem::code` `operator!`. `rem::code::Success`. 

### `tux::string`

- [ ] **`tux::string::fill(size_t n, char c=0x20)` is broken / UB**: `if(!_d.empty()) std::fill_n(_d.end()-1,
  n, c); else std::fill_n(_d.begin(), n, c);`. Writes **`n` chars starting at `end()-1`, past `end()`**;
  on empty string `fill_n(begin(),n,c)` into a 0-size string; **doesn't append**, overwrites last char;
  `n`-times semantic vs "fills with c n times at the end". `length()` unchanged. *(verified output + UB;
  not always crashing)*
- [ ] **`tux::string::operator=(numeric)` appends instead of replaces**: `operator=(u8/u16/u32/u64/i8/
  i16/i32/i64/float/double)` use `AssignNumeric` = `{ std::ostringstream os; os<<(v); _d += os.str();
  return *this; }` → **`_d +=`**, not `_d =`. `s=5; s=3;` → `"x53"`. (`operator=(const std::string&)`,
  `operator=(const char*)`, `operator=(char)`, `operator=(nullptr_t)`, `operator=(const string&)`,
  `operator=(string&&)` do replace.) *(verified)*
- [ ] **`tux::string::operator=(u8/i8)` appends a *character*, not a number**: `os << uint8_t/int8_t`
  prints a byte; `s = (u8)65;` appends `'A'`. And `s << (u8)65` via `operator<<` template appends `'A'`,
  while `s << 65` (int) appends `"65"`. `tux::string::string(u8/i8)` constructors likewise build a
  1-char string. *(verified `u8`; `i8` inferred)*
- [ ] **`tux::string::operator<<(float)`** `_d += std::to_string(c)` (e.g. `1.500000`); **no
  `operator<<(double)`** specific (template `os<<`); **`tux::string` has `string(float)` but no
  `string(double)`** (double→float); `operator<<(int)` `std::to_string(int)`; `operator<<(u8)` template
  prints a character. Inconsistent numeric handling. `book::log::operator<<(double)`.
- [ ] **`tux::string::string(Integers::u8/i8)` `numeric_construct` uses `ostringstream << u8/i8`** →
  prints a character. `string::string(char)`. `string::string(u16/u32/...)`. `string::string(float)`.
  `numeric_construct`. `_d=os.str()`.
- [ ] **`tux::string::tokenize(...)` is broken** (`string.cxx`):
  - `if (auto off = _d.find(c, w.last-_d.begin()) != std::string::npos)` — **operator precedence**:
    `off` is `bool`, not the match offset; then `w.last = _d.begin() + off;` (i.e. `begin()+1`).
  - `while (std::isspace(*w.last) && w.last != _d.end()) ++w.last;` — `*w.last` checked **before**
    `w.last != _d.end()`; reads `*end()` (UB).
  - `std::isspace(*w.last)` with `char` not cast to `unsigned char` (negative → UB); also
    `std::string(a_sep).find(*w.last, 0)`.
  - `token::operator*` returns `{begin, last+1}`; `last+1` can be **past `end()`** (UB → `std::bad_alloc`).
  - quote handling (`'`/`"`) `keep_as_word`, `token::sync`, `w.offset`… 
  - `_d.size() < 2` `return 1`; `eat(...)`. `a_keep_as_word`. `string::default_separators`. 
  - *(verified `std::bad_alloc` on `say "hello world" end` with `keep_as_word=true, sep=" "`; basic
    tokenizing inside `rem::this_location` happens to work)*
- [ ] **`tux::string::token`**: `operator*` `{begin, last+1}`; `sync(std::string&)`; `offset` default `-1`;
  `begin/last`. `token::operator*` `std::string`.
- [ ] **`tux::string::location`**: `str_type::const_iterator`; `iterator begin{nullptr}`; `end`;
  `line/column/offset/length`; **never populated** by anything. `operator*`.
- [ ] **`tux::string::argument`**: `argument()=delete; ~argument(); argument(string&, std::string::iterator);
  argument(const argument&)=delete; argument(const argument&&)=delete; argument& operator=(const
  argument&)=delete;`, `fmt_fnptr`, `seq`, `begin/end`. **No definitions provided** for `~argument()` /
  `argument(string&,iterator)` → link error if used. *(verified no definitions)* "Future implementation..."
- [ ] **`tux::string::bytes(Byte* ASeq, size_t num_bytes)` (`string.cxx`)**: computes `sz =
  std::strlen(reinterpret_cast<char*>(ASeq))` but **never uses `sz`**; iterates `num_bytes`; `*B==27`
  branch: **`std::format("[x{:02x}|u{:d}'ESC'] ", *B, *B, static_cast<char>(*B))` passes 3 args for 2
  placeholders** (works on libstdc++, throws `std::format_error` on strict libs; output is correct on
  libstdc++); `std::isprint(*B)`. Null `ASeq` returns `{}`. `Byte`=`u8`.
- [ ] `tux::string::bytes(string_view, int count)` `ASeq[i]`, `std::isprint(ch)`; `bytes(vector<int>)`
  `std::isprint(n)` negative-UB; `bytes(vector<u8>)`. `std::format`. `count`.
- [ ] `tux::string::binary(...)`, `hex`, `Hex`. `binary`: `memcpy`, `u8 seq;`, `padd`, `f=128`, `1<<y`,
  `b&seq`, `stream`. `hex`/`Hex`. 
- [ ] **`tux::string::operator << (grapheme::value ig)`** appends **`tux::glyph::table[ig].value`**
  (with `if (ig > grapheme::debug_line) return *this;`), but `rem::render` /
  `book::log::operator<<(rem::code)` use **`tux::grapheme::db[g]`**, and `grapheme::text(gh)` uses
  `grapheme::db[gh]`. **Two different glyph tables**; `grapheme::db` vs `glyph::table`; no `ig<0`. 
- [ ] `tux::string::operator << (color::value)`, `(color::pair)`, `(rem::channel)`, `(rem::code)`,
  `(const string&)`, `(const std::string&)`, `(const char*)`, `(char)`, `(int)`, `(float)`, `(string_view)`,
  `template<typename T>`, `operator>>`. `color::ansi::fg/pair`. `rem::render`. `rem::to_string`. 
- [ ] `tux::string::now(str_fmt)`. `std::put_time(localtime(...))`. **`localtime`** (not thread-safe).
  `tux::string::HH_MM_SS_mmm`. `std::chrono::zoned_time(current_zone(),...)`, `floor<milliseconds>`,
  `std::format("{:%T}",...)`. 
- [ ] `tux::string::make_list`, `make_str`, `make_viewlist`. `operator=`. `string::string(string_view)`.
  `string::string(nullptr_t)`. `_d(a_str)`. `std::string(nullptr)`. `operator=(nullptr_t)`.
- [ ] `tux::string::operator=` `AssignNumeric`. `numeric_construct`. `_d +=`. `_d =`. `_d.clear()`.
  `CLASSNAME_START(string)`. `class_name`. `virtual ~string`. `_d`, `pos`. `pos` `std::string::iterator
  pos{}` uninitialized/unused. `begin/end`. `size/length/empty/clear`. 

### `tux::color`

- [ ] **`color::pretty_names(pair colors)`** `std::format("[bg:{}|fg:{}]", color::name(colors.Bg),
  color::name(colors.Fg))` → `[bg:<Bg>|fg:<Fg>]`. Labels match, but order is `bg:` first whereas
  `pair::Name()` returns `[fg:<Fg> bg:<Bg>]`. `pair::Name`. *(verified)*
- [ ] `color::name(color::value)`. `color::scan`. `color::query_data`. `color::name(...).returns
  "color::Reset"`. `color::scan(...)`. returns `color::Reset`. `color::name(255)`. 
- [ ] **`color::Reset`, `color::R`, `color::Z` all == 255**; `color::value::Reset`==255. `color::ansi::fg(
  color::R)` returns `fg_reset`; `bg==color::R` → `bgr_pair`; `Fg==color::Reset` → `fgr_pair`. `css_data`
  has duplicate `Reset`/`R`/`Z` at 255. `color::pair::Bg` default `color::Grey11`, `Fg` `color::White`.
- [ ] `color::ansi::mode` `out_mode::compaq`/`rgb`; `pair::operator()` `query_data`. `rgb_pair`.
  `color::ansi::pair`. `pair::operator>>`. `pair::operator==/!=`. `pair::Name`. 
- [ ] `color::css` / `color::css_t` / `CSSColors` / `CSSTable`, `CSSPair`; `color::css::Reset`.
  `color::scan`. CSS name typos (`OlivedRab`, `DarkkKaki`, `LightCoreateBlue`, `LightCoreateGrey`,
  `HotPin2`, `Hotpink3`, `CornFlowerBlue`, `DeepSkyblue`, `LightSkyblue`, `DarkViolet ` trailing space,
  `"DeepSkyBlue..."`, `Grey`/`Gray`…). `color::value` typos. 
- [ ] `color::name`/`query_data` scan `color::css_data`; `query_data` returns `{}`. `color::table`.
  `color::table::TableDB`. `color::css_data`. 
- [ ] `operator<<(std::ostream&, tux::color::value)`. `color::ansi::reset*`. `\x1b[39m` `\x1b[49m`
  `\x1b[39;49m`. `color::ansi::fg_seq/bg_seq/pair_seq/fgr_pair/bgr_pair`. 

### `tux::grapheme` / `tux::glyph`

- [ ] **`grapheme::db` order mismatch**: `grapheme::db` lists `c_left_towards_up_arrow, c_right_towards_up_arrow`
  at indices 112/113, but `grapheme::value` has `right_towards_up_arrow=112, left_towards_up_arrow=113`.
  `grapheme::db[g]`, `grapheme::text(gh)`, `rem::render`, `book::log::operator<<(rem::code)` would return
  **swapped** glyphs for 112/113. `glyph_names` keys use enum constants. *(verified by reading)*
- [ ] `grapheme::name(gh)` `glyph_names[gh]`; `std::map::operator[]` inserts `nullptr`; constructing
  `std::string` from `nullptr`. `grapheme::scan` returns `0`. `scan_name`. 
- [ ] `grapheme::db` `const char*`, `grapheme::value` `u8`, `grapheme::value_type`, `grapheme::list`.
  `grapheme::debug_line`==121. `grapheme::scan`. 
- [ ] `glyph::table` `unicode_glyphs_table.i.h`; `glyph::list`, `glyph::type`, `name/desc/value/width`.
  `tux::string::operator<<(grapheme::value)`. 
- [ ] `tux::string::operator << (grapheme::value)`. `glyph::table[ig].value`. 

### `tux::buffer`

- [ ] **`tux::buffer` is fundamentally broken** (`buffer.h`/`buffer.cxx`):
  - `operator << (char c) { *cursor++ = c; ++size; }` — **no bounds check** → buffer overflow past
    `data + capacity`. (`operator<<(const T&)` checks `if ((cursor + sizeof(T)) > (data + capacity))`
    `state=OVRFL`, but the `char` overload doesn't.)
  - `operator--() { if (cursor == 0) return false; --cursor; }` — checks **`cursor == 0` (nullptr)**
    instead of `cursor == data`. `--cursor` before `data` → UB.
  - `clear() { cursor = tail = data; memset(data, 0, capacity); }` — **`size` not reset**; `state` not
    reset; `free` unused. `empty()` `size==0` stays false.
  - `operator++() { if (cursor == tail) return false; ++cursor; }`; `tail` is only set to `data`, never
    advanced. `operator bool() { return (cursor != tail) && (size > 0); }`. `cursor`/`tail` inconsistent.
  - `operator << (const T& n)` `static_assert(is_trivially_copyable)`, `memcpy`, `cursor += sizeof(T)`,
    `size += sizeof(T)`. 
  - `state` flags `READ/WRITE/FULL/EMPTY/READY/ERROR/OVRFL`. `MAX_SIZE=1000000`. `capacity`. `free`.
    `buffer(size_t)`. `~buffer` `clear(); delete[] data;`. `operator*`. 
  - `state` `OVRFL` set on overflow for `T` but not `char`. 
- [ ] `buffer::clear`. `buffer::operator++/--`. `buffer::operator bool`. `buffer::operator*`. 

### `tux::border_glyphes_set`

- [ ] `frame_data::operator=(const frame_weight&)`. Builds `std::map<frame_weight, std::string_view> _`;
  `_[key].data()`. `std::map::operator[]` **inserts empty `string_view`**; `.data()` on empty
  `string_view` (nullptr) assigned to `const char*`. Resulting `TL/TR/BL/BR/HL/VL/CVH/CRL/CLR/CTD/CDT`
  can be `nullptr`/`""`. `_` local. 
- [ ] `border_glyphes_set::operator=(frame_weight Model)`. Sets **`frame`**, not `matrix`. `matrix`.
  `FMatrix_S`. `Push`/`Pop`. `Pop` guards empty. `matrix=FMatrix_S.top()`. `frame=matrix`. 
- [ ] `operator[](index)`. `seg_data[Ix]`. `*seg_data[Ix]`. no bounds check. `index`. 
- [ ] `frame_weight` bitfields `Left:2 Top:2 Right:2 Down:2 Round:1`; `operator<`. `matrix{2,2,2,2,0}`.
  `frame` default `╭╮╰╯─│┼┤├┬┴`. `MatrixData_S`. `seg_data`. `width/height`. `color::pair`. `colors`.
  `FMatrix_S`. `Push`. `Pop`. 
- [ ] `using namespace Integers; using namespace std::literals;`. 

### `playground` / app

- [ ] **`playground::run` calls `system("cat logbook_playground.book")`** — shells out to `cat`, assumes
  it's on `PATH`, **cwd**, the produced `.book` name. `system()` return ignored. (Recent commit "Corrigé
  appel à system(...)... quick fixe".) 
- [ ] `m_book.open(...)` return ignored in `start_logbook_thread`. `m_book.stop()` return ignored.
- [ ] `main` `return !!r ? 0 : -1;`. `rem::to_string(r)`. `rem::operator!`. `-1`. 
- [ ] `book m_book{"logbook_playground"}`. `.book`. `playground::start_logbook_thread` /
  `stop_logbook_thread`. `rem::Ready`/`rem::Done`. `rem::Ok`. 
- [ ] `playground` links `sqlite3` unnecessarily; `cmake_minimum_required(VERSION 4.0 FATAL_ERROR)`.

### Build hygiene / other

- [ ] `rem::Fn::Loc` `"Obsolete!, use sourcelocation"`. `rem::Fn::...` commented `rem::Fn Fn_`. 
- [ ] `book::log::operator<<(rem::Fn)` / `operator<<(std::source_location&&)` commented out. 
- [ ] `rem::code` `//...to be continued`. `rem::channel`. 
- [ ] `tux::string::argument`. `string::location`. `CLASSNAME`. `exports.h`. `LOGBOOK_LIB`. `LOGBOOK_EXPORT`.
- [ ] `book::file::file_ptr`. `book::file::stop`. `book::file::mode`. `book::file::out`. `book::file::mode`.
- [ ] `rem::code::operator-`. `rem::operator-`. 
- [ ] `rem::render`. `rem::to_string`. `rem::*_attributes`. `std::map::operator[]`. 
- [ ] No tests, no CI, no `LICENSE`, no `README`. `.gitignore`. `unicode_glyphs_table.i.h`. 
- [ ] `tux::string::string(std::nullptr_t)`. `string::operator=(std::nullptr_t)`. `string::string(const char*)`.
- [ ] `tux::string::fill`. `tux::string::AssignNumeric`. `numeric_construct`. `operator=`. 
- [ ] `#pragma` Windows. `exports.h`. `_MSC_VER`. `LOGBOOK_LIB`. `pragma warning`. `_CRT_SECURE_NO_WARNINGS`.
  `NOMINMAX`. `unistd.h`. 
- [ ] `rem::this_location`. `clean_pretty_function`. `tux::string::tokenize`. 

---

## Rough edges worth knowing

- The library target is **`logbook`, output `lib.logbook.so`**, not `liblogbook.so`.
- `book::file` always appends **`.book`** to the filename.
- Construct a **`book` before** any `book::*` streaming, and prefer **`book::stop()`** before destruction;
  `book::close()` alone doesn't stop the worker or flush.
- `book::open` returns `rem::Accepted` even when the file can't be opened (falls back to `std::cout`);
  check `book::out_file->is_open` / `book::file::file_ptr`.
- `rem::to_string` on **`rem::code::Zero` / `rem::code::Hup`** throws; **`operator-(rem::code)`** is a
  link error; `rem::code::Success` has a trailing space.
- `book::log::operator<<(rem::channel)` currently emits **`:<16`** literally.
- `tux::string::operator=(number)` **appends**; `tux::string::fill` is UB; `tux::string::tokenize` is
  fragile (precedence, `*end`, quote handling, `last+1`); `tux::string::bytes` ESC has an extra `format`
  arg; `tux::string::operator<<(u8/i8)` prints a byte.
- `book::log::operator=` doesn't copy `text`; `book::exception::what()` then always says
  `"Exception message is empty"`; `_e_` is uninitialized.
- **No thread safety** guarantees around `cached_lines` / `book::log::text`.
- `tux::buffer` has no bounds checks and `clear()` doesn't reset `size`; `operator--` checks `nullptr`.
- `sqlite3` is linked but unused; `system("cat ...")` in `playground`.
- CMake issues: `bi§`, `lib.logbook` + `liblogbook++*`, `copy_if_different` missing destination, CMake
  3.40-vs-4.0, missing `LICENSE`, `pragma`/`#pragma`.
