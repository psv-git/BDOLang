#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include "headers.hpp"
#include "SettingsHandler.hpp"
#include "ErrorHandler.hpp"
#include "LanguageHandler.hpp"


enum class MODE : int { MERGE_BIN, MERGE_TEXT, BIN_TO_TEXT, TEXT_TO_BIN, SETTINGS, CLOSE, EXIT, NONE };
enum class PROCESS_MODE : int { DECRYPT, ENCRYPT, READ, WRITE, NONE };


#endif // APPLICATIONGLOBAL_HPP
