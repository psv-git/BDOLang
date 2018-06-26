#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class SettingsWindow; }
class LanguageWidget;


class SettingsWindow : public QWidget {
Q_OBJECT

public:
  explicit SettingsWindow(QWidget *parent = nullptr);
  ~SettingsWindow();

signals:
  void buttonClicked(MODE mode);

public slots:
  void show();

private slots:
  void buttonClick();

private:
  Ui::SettingsWindow *ui = nullptr;
  Settings *settings     = nullptr;
  QVector<LanguageWidget*> languagesList;

  void addLanguageWidget(bool deletable, const QString &language, const QString &locFileName, const QString &textFileName);
  void deleteLanguageWidgets();

};


#endif // SETTINGSWINDOW_HPP
