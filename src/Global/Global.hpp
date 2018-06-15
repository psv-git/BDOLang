#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <zlib.h>


// !!! SMALL BUFFER NOT WORKED CORRECTLY !!!
// const size_t BUFF_SIZE     = 327680; // decompress bufer size 40kB

const size_t MB_SIZE         = 1048576; // bytes in MB
const size_t MIN_DATA_LENGTH = 20; // minimal data size length in bytes

const uint16_t CHAR_CR       = 0x000D;
const uint16_t CHAR_LF       = 0x000A;
const uint16_t BOM_UTF16LE   = 0xFEFF;
const uint32_t MAX_CODE      = 0x10ffff;

const wchar_t CHAR_TAB       = 0x0009;

// extern const char* IN_FILE_NAME;
// extern const char* TEXT_OUT_FILE_NAME;
// extern const char* BIN_OUT_FILE_NAME;
extern const char* TMP_FILE_NAME;

enum LANG { RU, EN };


#endif // GLOBAL_HPP
