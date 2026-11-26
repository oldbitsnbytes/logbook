//
// Created by bretzelus on 15/09/2026.
//

#include <logbook/buffer.h>


namespace tux {
buffer::buffer(size_t capacity_value) : capacity{capacity_value} {
    data = new u8[capacity];
    clear();
}


/**
 * @brief Destructor for the `buffer` class.
 *
 * Cleans up the allocated resources associated with the `buffer` object.
 * The `clear` function is used to ensure that no residual data remains
 * in the buffer before deallocating the memory.
 *
 * Deletes the dynamically allocated array `data` and prepares the
 * buffer for destruction.
 */
buffer::~buffer() {
    clear(); // On ne laisse absolument rien trainer!
    delete[] data;
}



void buffer::clear() {
    cursor = tail = data;
    std::memset(data, 0, capacity);
}

bool buffer::operator++() {
    if (cursor == tail) return false;
    ++cursor;
    return true;
}

bool buffer::operator--() {
    if (cursor == 0) return false;
    --cursor;
    return true;
}


} // namespace text