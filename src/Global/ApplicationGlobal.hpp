#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include "ApplicationHeaders.hpp"
#include "Settings.hpp"
#include "ErrorHandler.hpp"


enum WTYPE { CFSW, MAINW, PROCW, SETTW, TRANSW };
enum MODE  { MERGE_BIN, MERGE_TEXT, BIN_TO_TEXT, TEXT_TO_BIN, TRANSLATE, COMP_BY_SIZE, COMP_BY_STR, SETTINGS, CLOSE, EXIT, NONE };

// ============================================================================

extern const char* TMP_FILE_NAME;


#endif // APPLICATIONGLOBAL_HPP
