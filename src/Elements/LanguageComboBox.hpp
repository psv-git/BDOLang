#ifndef LANGUAGECOMBOBOX_HPP
#define LANGUAGECOMBOBOX_HPP

#include <QComboBox>
#include "ApplicationGlobal.hpp"


class LanguageComboBox : public QComboBox {
Q_OBJECT

public:
  LanguageComboBox(QWidget *parent = 0);
  ~LanguageComboBox();

  LANG getCurrentLanguage();
  void setCurrentLanguage(LANG language);

signals:


public slots:


private:


};


#endif // LANGUAGECOMBOBOX_HPP
