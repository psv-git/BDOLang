#ifndef LANGUAGEWIDGET_HPP
#define LANGUAGEWIDGET_HPP

#include <QWidget>

namespace Ui { class LanguageWidget; }


class LanguageWidget : public QWidget {
Q_OBJECT

public:
  explicit LanguageWidget(QWidget *parent = 0);
  ~LanguageWidget();

  bool needToDelete();

  void setDeletable(bool value);
  void setLanguage(const QString &language);
  void setLocFileName(const QString &fileName);
  void setTextFileName(const QString &fileName);

private:
  Ui::LanguageWidget *ui;
};


#endif // LANGUAGEWIDGET_HPP
