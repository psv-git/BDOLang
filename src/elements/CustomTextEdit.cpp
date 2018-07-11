// Copyright (c) 2018 PSV
// https://github.com/psv-git

#include "CustomTextEdit.hpp"


CustomTextEdit::CustomTextEdit(QWidget *parent) : QTextEdit(parent) {}


CustomTextEdit::~CustomTextEdit() {}

// events =====================================================================

void CustomTextEdit::mousePressEvent(QMouseEvent *event) {
  if (event->type() == QEvent::MouseButtonPress) {
    if (event->button() == Qt::LeftButton) {
      QString url = anchorAt(event->pos());
      if (!url.isEmpty()) {
        QDesktopServices::openUrl(QUrl(url));
      }
    }
  }
  return QWidget::mousePressEvent(event);
}
