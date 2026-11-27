# logbook

A small, standalone **C++23** console text-journal / logging library. `logbook` writes
timestamped, colorized, glyph-decorated log entries to a text file (and the console) using a
simple `std::ostream`-style streaming API.

- `logbook/` — the shared library (CMake target `logbook`): `book` logger, `rem` return-code
  system, and `tux` support types (`string`, `color`, `grapheme`, `buffer`, `border_glyphes_set`).
- `playground/` — tiny demo executable.

## Build

Requires a C++23 compiler, CMake, and sqlite3.

```sh
cmake -S . -B build
cmake --build build
cmake --build build --target playground   # optional demo
```

Run the demo (writes `logbook_playground.book` in the current directory):

```sh
./build/playground/playground
```

## Minimal usage

```cpp
#include <logbook/book.h>

int main() {
    book m_book{"my_journal"};                              // -> my_journal.book
    m_book.open(std::ios_base::out | std::ios_base::trunc); // returns rem::code
    book::info << "started" << book::eol;                   // or book::end
    book::warning << "check this" << book::end;
    m_book.stop();                                          // stop worker, join, close
}
```

Entries are timestamped `HH-MM-SS-mmm`, prefixed with a colored channel name, and `.book` is
appended to the filename automatically.

## License

See `LICENSE`. Author: Serge Lussier.

---

*This README.md is opencode generated, reviewed as is.*
