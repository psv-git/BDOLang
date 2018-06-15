#include "bintotextbutton.hpp"


BinToTextButton::BinToTextButton(QMainWindow *parent) : QMainWindow(parent), ui(new Ui::BinToTextButton) {
  ui->setupUi(this);
//  connect(this, &Ui::BinToTextButton::released, &Ui::MainWindow::onButtonClick);
//  connect(this, &Ui::BinToTextButton::released, &Ui::ChooseFileWindow::onButtonClick);
}


BinToTextButton::~BinToTextButton() {
  delete ui;
}
