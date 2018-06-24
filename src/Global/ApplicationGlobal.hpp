#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include "ApplicationHeaders.hpp"
#include "Settings.hpp"


enum WTYPE { CFEW, CFSW, MAINW, PROCW, SETTW, TRANSW };
enum MODE  { MERGE_BIN, MERGE_TEXT, BIN_TO_TEXT, TEXT_TO_BIN, BIN_TO_BIN, TEXT_TO_TEXT, TRANSLATE, COMP_BY_SIZE, COMP_BY_STR, SETTINGS, CLOSE, EXIT, NONE };

// ============================================================================

extern const char* TMP_FILE_NAME;


#endif // APPLICATIONGLOBAL_HPP
