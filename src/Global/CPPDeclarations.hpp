#ifndef CPPDECLARATIONS_HPP
#define CPPDECLARATIONS_HPP

#include "MyException.hpp"

union uint8_16_t {
  uint16_t    solid;
  uint8_t  split[2];
};

// =============================================================================

typedef std::basic_ifstream<char16_t> u16ifstream;
typedef std::basic_ofstream<char16_t> u16ofstream;

// symbols codes ===============================================================

const uint16_t BOM_UTF16BE  = 0xFEFF;
const uint16_t BOM_UTF16LE  = 0xFFFE;

const uint16_t CR_CODE      = 0x000D;
const uint16_t LF_CODE      = 0x000A;

const uint16_t RU_BEG       = 0x0400;
const uint16_t RU_END       = 0x04FF;

//const uint16_t SLASH_CODE   = 0x002F;
//const uint16_t N_CODE       = 0x006E;
//const uint16_t QOTE_CODE    = 0x0022;

// =============================================================================

const uint32_t MAX_CODE      = 0x10ffff;

const size_t MIN_DATA_LENGTH = 20; // minimal data size length in bytes

const uint16_t quotesCodes[] = { 0x201C, 0x201D, 0x201E, 0x201F };

extern const char* TMP_FILE_NAME;


#endif // CPPDECLARATIONS_HPP
