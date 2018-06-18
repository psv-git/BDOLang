#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include <QString>


enum MODE { MERGE, BIN_TO_TEXT, TRANSLATE, SETTINGS, CLOSE, EXIT };
enum LANG { EN = 0, RU = 1 };

struct Settings {
  LANG language;
  QString dataPath;
  QString sourceFileName;
  QString targetFileName;
};

extern Settings DefaultSettings;
extern Settings ActiveSettings;


#endif // APPLICATIONGLOBAL_HPP
