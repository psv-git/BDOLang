#ifndef APPLICATIONGLOBAL_HPP
#define APPLICATIONGLOBAL_HPP

#include <QString>


enum MODE : qint32 { MERGE, BIN_TO_TEXT, TRANSLATE, SETTINGS, CLOSE, EXIT, NONE };
enum LANG : qint32 { EN = 0, RU = 1 };

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


#endif // APPLICATIONGLOBAL_HPP
