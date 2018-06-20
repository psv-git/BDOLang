#ifndef CPPDECLARATIONS_HPP
#define CPPDECLARATIONS_HPP

#include "MyException.hpp"

union uint8_16_t {
  uint16_t    solid;
  uint8_t  split[2];
};

const uint32_t MAX_CODE    = 0x10ffff;
const uint16_t BOM_UTF16LE = 0xFEFF;

const uint16_t CR_CODE     = 0x000D;
const uint16_t LF_CODE     = 0x000A;
const wchar_t CR           = 0x000D;
const wchar_t LF           = 0x000A;

const size_t MIN_DATA_LENGTH = 20; // minimal data size length in bytes

const uint16_t quotesCodes[] = { 0x201C, 0x201D, 0x201E, 0x201F };

extern const char* TMP_FILE_NAME;


#endif // CPPDECLARATIONS_HPP
