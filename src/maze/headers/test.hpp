#ifndef TEST_HPP
#define TEST_HPP

#include "maze.hpp"

#include <chrono>
#include <locale>
#include <codecvt>

void testMazeCreation();
void testMazePrint();
void testMazeString();
void testMazeSave();
void testMazeLoad();
void testGetNeighbors();

template <typename func, typename... Args>
void timeTaken(func&& f, Args&&... args) {
    auto start = chrono::high_resolution_clock::now();
    f(forward<Args>(args)...);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << "ms" << endl;
}

//***********************************************************************************
// Unicode and Emoji support (for Windows no need to change or look at anything here)
//***********************************************************************************

#ifdef _WIN32
#include <Windows.h>
#define SET_CONSOLE_UTF8 SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8 on Windows
#endif // _WIN32

// Helper function to convert Unicode code points to UTF-8 encoded string
/*
    takes a Unicode code point and returns a UTF-8 encoded string
*/
inline string utf8_encode(char32_t codepoint) {
    if (codepoint <= 0x7F) { // 1 byte sequence : 0xxxxxxx  0x7F = 127
        return string(1, static_cast<char>(codepoint)); // in this case, the codepoint is the same as the UTF-8 code
    } else if (codepoint <= 0x7FF) { // 2 byte sequence : 110xxxxx 10xxxxxx 0x7FF = 2047
        return string(1, static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F))) +
               string(1, static_cast<char>(0x80 | (codepoint & 0x3F))); //use 2 bytes, the first byte is 110xxxxx and the second byte is 10xxxxxx
    } else if (codepoint <= 0xFFFF) { // 3 byte sequence : 1110xxxx 10xxxxxx 10xxxxxx 0xFFFF = 65535
        return string(1, static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F))) +
               string(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F))) +
               string(1, static_cast<char>(0x80 | (codepoint & 0x3F))); //use 3 bytes, the first byte is 1110xxxx, the second byte is 10xxxxxx and the third byte is 10xxxxxx
    } else if (codepoint <= 0x10FFFF) { // 4 byte sequence : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 0x10FFFF = 1114111
        return string(1, static_cast<char>(0xF0 | ((codepoint >> 18) & 0x07))) +
               string(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F))) +
               string(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F))) +
               string(1, static_cast<char>(0x80 | (codepoint & 0x3F))); //use 4 bytes, the first byte is 11110xxx, the second byte is 10xxxxxx, the third byte is 10xxxxxx and the fourth byte is 10xxxxxx
    } else {
        throw runtime_error("Invalid Unicode code point"); // if the codepoint is not in the range of 0x10FFFF, throw an error
    }
}

// Unicode code points for some emojis
const char32_t CHECK_EMOJI_CODEPOINT = U'\U00002714';
const char32_t CROSS_EMOJI_CODEPOINT = U'\U00002716';

// Global variables for the UTF-8 encoded emojis
// const string CHECK_EMOJI = utf8_encode(CHECK_EMOJI_CODEPOINT);
// const string CROSS_EMOJI = utf8_encode(CROSS_EMOJI_CODEPOINT);

// UTF-8 encoded emojis
const std::string CHECK_EMOJI = u8"✔";
const std::string CROSS_EMOJI = u8"✖";

#endif // TEST_HPP