#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include "headers.hpp"
#include "IOError.hpp"
#include "ALError.hpp"
#include "FLError.hpp"
#include "SettingsHandler.hpp"
#include "ErrorHandler.hpp"
#include "LanguageHandler.hpp"


enum class MODE  : int { MERGE_BIN, MERGE_TEXT, BIN_TO_TEXT, TEXT_TO_BIN, TRANSLATE, COMP_BY_SIZE, COMP_BY_STR, SETTINGS, CLOSE, EXIT, NONE };


#endif // APPLICATIONGLOBAL_HPP
