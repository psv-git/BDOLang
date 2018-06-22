#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include "ApplicationHeaders.hpp"


enum MODE : qint32 { MERGE_BIN, MERGE_TEXT, BIN_TO_TEXT, TEXT_TO_BIN, TRANSLATE, COMPARE, SETTINGS, CLOSE, EXIT, NONE };
enum LANG : qint32 { EN = 0, RU = 1 };

// ============================================================================

union uint8_16 {
  unsigned short solid;
  uint8_t        split[2];
};


struct Settings {
  LANG language;
  QString dataPath;
  QString sourceFileName;
  QString targetFileName;

  QString dataDirectoryName;
  QString configFileName;
};

extern const Settings DEFAULT_SETTINGS;
extern Settings active_settings;

// ============================================================================

const quint32 MAX_CODE     = 0x10FFFF;

const char16_t CR_CODE     = 0x000D;
const char16_t LF_CODE     = 0x000A;

const char16_t RU_BEG      = 0x0400;
const char16_t RU_END      = 0x04FF;

// ============================================================================

const size_t MIN_DATA_LENGTH = 20; // minimal data size length in bytes

// ============================================================================

extern const char* TMP_FILE_NAME;


#endif // APPLICATIONGLOBAL_HPP
