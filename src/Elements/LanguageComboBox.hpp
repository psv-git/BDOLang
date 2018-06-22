#ifndef LANGUAGECOMBOBOX_HPP
#define LANGUAGECOMBOBOX_HPP

#include "ApplicationGlobal.hpp"


class LanguageComboBox : public QComboBox {
Q_OBJECT

public:
  LanguageComboBox(QWidget *parent = 0);
  ~LanguageComboBox();

  LANG getCurrentLanguage();
  void setCurrentLanguage(LANG language);

};


#endif // LANGUAGECOMBOBOX_HPP
