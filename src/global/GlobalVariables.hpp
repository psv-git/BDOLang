#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include "headers.hpp"


enum class MODE : int { MERGE_BIN, MERGE_TEXT, BIN_TO_TEXT, TEXT_TO_BIN, SETTINGS, CLOSE, EXIT, NONE };
enum class PROCESS_MODE : int { DECRYPT, ENCRYPT, READ, WRITE, NONE };
enum LANG : int { EMPTY, EN, AR, BE, EL, DA, IW, ES, IT, ZH, KO, DE, RU, TR, UK, FR, JA, NONE };
Q_DECLARE_METATYPE(LANG)

struct DefaultSettings {
  int compressingLevel;
  QString dataDirectoryName;
  QString configFileName;
  QString logFileName;
} const DEFAULT_SETTINGS { 1, "data", "config.ini", "log.txt" };


#endif // APPLICATIONGLOBAL_HPP
