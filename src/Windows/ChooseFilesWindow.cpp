#include "ChooseFilesWindow.hpp"
#include "ui_ChooseFilesWindow.h"


ChooseFilesWindow::ChooseFilesWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ChooseFilesWindow) {
  settingsHandler = &SettingsHandler::getInstance();
  languageHandler = &LanguageHandler::getInstance();
  initUi();
}


ChooseFilesWindow::~ChooseFilesWindow() {
  delete ui;
}

// events =====================================================================

void ChooseFilesWindow::closeEvent(QCloseEvent *event) {
  emit buttonClicked(MODE::CLOSE);
  QWidget::closeEvent(event);
}

// public slots ===============================================================

void ChooseFilesWindow::show(MODE mode) {
  ChooseFilesWindow::mode = mode;
  addAllowedLanguages();
  update();
  QWidget::show();
}

// private slots ==============================================================

void ChooseFilesWindow::update() {
  QString dataPath = settingsHandler->getSetting("", "data_path", DEFAULT_SETTINGS.dataDirectoryName).toString();
  if (dataPath.back() != '/') dataPath += '/';
  QString sourcePath, targetPath;

  if (mode == MODE::BIN_TO_TEXT) {
    ui->sourcePathLabel->setText("Choose path to .loc file:");
    ui->targetPathLabel->setText("Choose path to text file:");
    sourcePath = settingsHandler->getSetting(ui->sourceLanguageComboBox->currentText(), "loc_file_name", "").toString();
    targetPath = settingsHandler->getSetting(ui->targetLanguageComboBox->currentText(), "text_file_name", "").toString();
  } else if (mode == MODE::TEXT_TO_BIN) {
    ui->sourcePathLabel->setText("Choose path to text file:");
    ui->targetPathLabel->setText("Choose path to .loc file:");
    sourcePath = settingsHandler->getSetting(ui->sourceLanguageComboBox->currentText(), "text_file_name", "").toString();
    targetPath = settingsHandler->getSetting(ui->targetLanguageComboBox->currentText(), "loc_file_name", "").toString();
  } else if (mode == MODE::MERGE_BIN) {
    ui->sourcePathLabel->setText("Choose path to translated .loc file:");
    ui->targetPathLabel->setText("Choose path to original .loc file (WILL BE REWRITE):");
    sourcePath = settingsHandler->getSetting(ui->sourceLanguageComboBox->currentText(), "loc_file_name", "").toString();
    targetPath = settingsHandler->getSetting(ui->targetLanguageComboBox->currentText(), "loc_file_name", "").toString();
  } else if (mode == MODE::MERGE_TEXT) {
    ui->sourcePathLabel->setText("Choose path to translated text file:");
    ui->targetPathLabel->setText("Choose path to original text file (WILL BE REWRITE):");
    sourcePath = settingsHandler->getSetting(ui->sourceLanguageComboBox->currentText(), "text_file_name", "").toString();
    targetPath = settingsHandler->getSetting(ui->targetLanguageComboBox->currentText(), "text_file_name", "").toString();
  }

  ui->sourcePathEdit->setText(dataPath + sourcePath);
  ui->targetPathEdit->setText(dataPath + targetPath);
}


void ChooseFilesWindow::buttonClick () {
  QObject* obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "cancelButton") emit buttonClicked(MODE::CLOSE);
  else if (objName == "sourcePathButton") {
    ui->sourcePathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  } else if (objName == "targetPathButton") {
    ui->targetPathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  } else if (objName == "okButton") {
    QString srcFilePath(ui->sourcePathEdit->text());
    QString targFilePath(ui->targetPathEdit->text());
    emit buttonClicked(srcFilePath, targFilePath);
  }
}

// private methods ============================================================

void ChooseFilesWindow::initUi() {
  ui->setupUi(this);

  ui->sourcePathLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));
  ui->sourcePathEdit->setFont(settingsHandler->getFont("Liberation Mono", "Regular", 10));
  ui->sourcePathButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));
  ui->sourceLanguageComboBox->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  ui->targetPathLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));
  ui->targetPathEdit->setFont(settingsHandler->getFont("Liberation Mono", "Regular", 10));
  ui->targetPathButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));
  ui->targetLanguageComboBox->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  ui->okButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));
  ui->cancelButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(ui->okButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->sourcePathButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->targetPathButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->sourceLanguageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
  connect(ui->targetLanguageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
}


void ChooseFilesWindow::addAllowedLanguages() {
  ui->sourceLanguageComboBox->clear();
  ui->targetLanguageComboBox->clear();
  QStringList allowedLanguages = languageHandler->getAllowedLanguages();
  for (int i = 0; i < allowedLanguages.size(); i++) {
    ui->sourceLanguageComboBox->addItem(allowedLanguages[i]);
    ui->targetLanguageComboBox->addItem(allowedLanguages[i]);
  }
}
