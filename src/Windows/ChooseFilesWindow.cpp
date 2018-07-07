#include "ChooseFilesWindow.hpp"
#include "ui_ChooseFilesWindow.h"


ChooseFilesWindow::ChooseFilesWindow(QWidget *parent) : QWidget(parent), m_ui(new Ui::ChooseFilesWindow) {
  m_settingsHandler = &SettingsHandler::getInstance();
  m_languageHandler = &LanguageHandler::getInstance();
  initUi();
}


ChooseFilesWindow::~ChooseFilesWindow() {
  delete m_ui;
}

// events =====================================================================

void ChooseFilesWindow::closeEvent(QCloseEvent *event) {
  emit buttonClicked(MODE::CLOSE);
  QWidget::closeEvent(event);
}

// public slots ===============================================================

void ChooseFilesWindow::show(MODE mode) {
  m_mode = mode;
  addAllowedLanguages();
  update();
  QWidget::show();
}

// private slots ==============================================================

void ChooseFilesWindow::update() {
  QString dataPath = m_settingsHandler->getSetting("", "data_path", DEFAULT_SETTINGS.dataDirectoryName).toString();
  if (dataPath.back() != '/') dataPath += '/';
  QString sourcePath, targetPath;

  if (m_mode == MODE::BIN_TO_TEXT) {
    m_ui->sourcePathLabel->setText("Choose path to .loc file:");
    m_ui->targetPathLabel->setText("Choose path to text file:");
    sourcePath = m_settingsHandler->getSetting(m_ui->sourceLanguageComboBox->currentText(), "loc_file_name", "").toString();
    targetPath = m_settingsHandler->getSetting(m_ui->targetLanguageComboBox->currentText(), "text_file_name", "").toString();
  } else if (m_mode == MODE::TEXT_TO_BIN) {
    m_ui->sourcePathLabel->setText("Choose path to text file:");
    m_ui->targetPathLabel->setText("Choose path to .loc file:");
    sourcePath = m_settingsHandler->getSetting(m_ui->sourceLanguageComboBox->currentText(), "text_file_name", "").toString();
    targetPath = m_settingsHandler->getSetting(m_ui->targetLanguageComboBox->currentText(), "loc_file_name", "").toString();
  } else if (m_mode == MODE::MERGE_BIN) {
    m_language = m_languageHandler->toLang(m_ui->sourceLanguageComboBox->currentText());
    m_ui->sourcePathLabel->setText("Choose path to translated .loc file:");
    m_ui->targetPathLabel->setText("Choose path to original .loc file (WILL BE REWRITE):");
    sourcePath = m_settingsHandler->getSetting(m_ui->sourceLanguageComboBox->currentText(), "loc_file_name", "").toString();
    targetPath = m_settingsHandler->getSetting(m_ui->targetLanguageComboBox->currentText(), "loc_file_name", "").toString();
  } else if (m_mode == MODE::MERGE_TEXT) {
    m_language = m_languageHandler->toLang(m_ui->sourceLanguageComboBox->currentText());
    m_ui->sourcePathLabel->setText("Choose path to translated text file:");
    m_ui->targetPathLabel->setText("Choose path to original text file (WILL BE REWRITE):");
    sourcePath = m_settingsHandler->getSetting(m_ui->sourceLanguageComboBox->currentText(), "text_file_name", "").toString();
    targetPath = m_settingsHandler->getSetting(m_ui->targetLanguageComboBox->currentText(), "text_file_name", "").toString();
  }

  m_ui->sourcePathEdit->setText(dataPath + sourcePath);
  m_ui->targetPathEdit->setText(dataPath + targetPath);
}


void ChooseFilesWindow::buttonClick () {
  QObject* obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "cancelButton") emit buttonClicked(MODE::CLOSE);
  else if (objName == "sourcePathButton") {
    m_ui->sourcePathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  } else if (objName == "targetPathButton") {
    m_ui->targetPathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  } else if (objName == "okButton") {
    QString srcFilePath(m_ui->sourcePathEdit->text());
    QString targFilePath(m_ui->targetPathEdit->text());
    emit buttonClicked(srcFilePath, targFilePath, m_language);
  }
}

// private methods ============================================================

void ChooseFilesWindow::initUi() {
  m_ui->setupUi(this);

  m_ui->sourcePathLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));
  m_ui->sourcePathEdit->setFont(m_settingsHandler->getFont("Liberation Mono", "Regular", 10));
  m_ui->sourcePathButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->sourceLanguageComboBox->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  m_ui->targetPathLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));
  m_ui->targetPathEdit->setFont(m_settingsHandler->getFont("Liberation Mono", "Regular", 10));
  m_ui->targetPathButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->targetLanguageComboBox->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  m_ui->okButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->cancelButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(m_ui->okButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->sourcePathButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->targetPathButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->sourceLanguageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
  connect(m_ui->targetLanguageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
}


void ChooseFilesWindow::addAllowedLanguages() {
  m_ui->sourceLanguageComboBox->clear();
  m_ui->targetLanguageComboBox->clear();
  QStringList allowedLanguages = m_languageHandler->getAllowedLanguages();
  for (int i = 0; i < allowedLanguages.size(); i++) {
    m_ui->sourceLanguageComboBox->addItem(allowedLanguages[i]);
    m_ui->targetLanguageComboBox->addItem(allowedLanguages[i]);
  }
}
