#include "ApplicationGlobal.hpp"


const Settings DEFAULT_SETTINGS {
  LANG::EN,
  "./data",
  "languagedata_en.loc",
  "languagedata_ru.loc",
  "config.cfg",
  "data"
};

Settings active_settings = DEFAULT_SETTINGS;
