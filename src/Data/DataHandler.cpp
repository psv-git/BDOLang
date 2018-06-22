#include "DataHandler.hpp"
#include "DataRow.hpp"
#include <zlib.h>


DataHandler::DataHandler() {}


DataHandler::~DataHandler() {
  resetData();
}

// PUBLIC METHODS =============================================================

// TODO: complete this
void DataHandler::mergeTwoFiles(const QString &filePath1, const QString &filePath2) {
//  std::string replace_name = argv[1];
//  std::string original_name = argv[2];
//  std::string target_name = argv[3];
//  std::wifstream replace(replace_name, std::ios::binary);
//  if (replace.fail()){
//    std::cerr << "Error opening " << replace_name << std::endl;
//    return 1;
//  }
//  replace.imbue(std::locale(replace.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
//  if (replace.get() != BOM_UTF16LE) {
//    replace.unget();
//  }
//  std::wifstream original(original_name, std::ios::binary);
//  if (original.fail()){
//    std::cerr << "Error opening " << original_name << std::endl;
//    return 1;
//  }
//  original.imbue(std::locale(original.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
//  if (original.get() != BOM_UTF16LE) {
//    original.unget();
//  }
//  std::wofstream target(target_name, std::ios::binary);
//  if (target.fail()){
//    std::cerr << "Error opening " << target_name << std::endl;
//    return 1;
//  }
//  target.imbue(std::locale(target.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
//  target.put(BOM_UTF16LE);
//  ///create lookup table
//  std::vector<DataRow> lookup;
//  std::wstring row;
//  std::cout << "Reading \"" << replace_name << "\"..." ;
//  while (std::getline(replace, row)){
//    DataRow dataRow;
//    std::wstringstream ss;
//    ss.str(row);
//    ss >> dataRow;
//    lookup.push_back(dataRow);
//  }
//  std::cout << " (" << lookup.size() << " lines found)" << std::endl;
//  //sorting is necessary so I can speed up searching using a map (lookupHelper)
//  std::sort(lookup.begin(), lookup.end());
//  //lookupHelper is a map which assigns pair of pointers, start and end (something like row numbers),
//  //to the sheet number (first number on the row in text file)
//  std::map<int, std::pair<std::vector<DataRow>::iterator, std::vector<DataRow>::iterator> > lookupHelper;
//  std::vector<DataRow>::iterator it, first, last;
//  first = lookup.begin();
//  int sheet = first->sheet;
//  for (it = lookup.begin(); it != lookup.end(); ++it) {
//    last = it;
//    if (sheet < it->sheet){
//      lookupHelper[sheet] = std::make_pair(first, --last); ///last is now the first line of the new sheet, so we need to get previous value
//      first = it;
//      sheet = it->sheet;
//    }
//  }
//  lookupHelper[sheet] = std::make_pair(first, last); ///write the last one
//  //main loop
//  std::cout << "Copying lines from \"" << original_name << "\" to \"" << target_name << "\"..." << std::endl;
//  bool found = false;
//  unsigned int changed = 0, unchanged = 0;
//  std::map<int, std::pair<std::vector<DataRow>::iterator, std::vector<DataRow>::iterator> >::iterator iHelp; ///I love this type!
//  while (std::getline(original, row)){
//    DataRow originalRow;
//    std::wstringstream ss;
//    ss.str(row);
//    ss >> originalRow;
//    found = false;
//    iHelp = lookupHelper.find(originalRow.sheet);
//    if (iHelp != lookupHelper.end()){
//      it = iHelp->second.first; //I don't want to search for key multiple times using map[key], so I'm using less comprehensible
//      while (it <= iHelp->second.second) { //dereferencing form iterator. It points to map pair<key, value> and I have stored in value
//        if (originalRow.sheet == it->sheet &&  ///another pair. It looks like this: pair<key, value<first, second>>
//          originalRow.id1 == it->id1 &&      ///Pair members are accessible as .first and .second, so I have to use: pointer->second.first
//          originalRow.id2 == it->id2 && originalRow.id3 == it->id3 && originalRow.id4 == it->id4 &&
//          originalRow.loc.substr(0,4) != L"http" && isUTF16Cyrillic(it->loc)) {
//            found = true;
//            break;
//        } else {
//          it++;
//        }
//      }
//    }
//    if (found){
//      originalRow.loc = it->loc;
//      changed++;
//    } else {
//      unchanged++;
//    }
//    target << originalRow << '\n';
//  }
//  std::cout << "Processed lines: " << changed + unchanged <<  " (replaced: " << changed << ", original: " << unchanged << ")\nDone!" << std::endl;
//  return 0;
}


//
void DataHandler::convertBinFileToTextFile(const QString &binFilePath) {
  resetData(); // be on the safe side
  QString path(binFilePath);
  QFile inputFile(path);
  QFile outputFile(path + ".txt"); // TODO: change this
  try {
    OpenFile(inputFile,  QIODevice::ReadOnly, "DataHandler::convertBinFileToTextFile()");
    OpenFile(outputFile, QIODevice::WriteOnly, "DataHandler::convertBinFileToTextFile()");
    QDataStream input(&inputFile);
    QTextStream output(&outputFile);
    output.setCodec("UTF-8");
    output.setGenerateByteOrderMark(true);

    readDataFromBinFile(input);
    writeDataToTextFile(output);

    CloseFile(inputFile,  "DataHandler::convertBinFileToTextFile()");
    CloseFile(outputFile, "DataHandler::convertBinFileToTextFile()");
  }
  catch (...) {
    if (inputFile.isOpen())  CloseFile(inputFile,  "DataHandler::convertBinFileToTextFile()");
    if (outputFile.isOpen()) CloseFile(outputFile, "DataHandler::convertBinFileToTextFile()");
    throw;
  }
  resetData();
}


//
void DataHandler::convertTextFileToBinFile(const QString &textFilePath) {
  resetData(); // be on the safe side
  QString path(textFilePath);
  QFile inputFile(path);
  QFile outputFile(path + ".bin"); // TODO: change this
  try {
    OpenFile(inputFile,  QIODevice::ReadOnly, "DataHandler::convertTextFileToBinFile()");
    OpenFile(outputFile, QIODevice::WriteOnly, "DataHandler::convertTextFileToBinFile()");
    QTextStream input(&inputFile);
    QDataStream output(&outputFile);
//    input.setCodec("UTF-8");
    input.setAutoDetectUnicode(true);
    input.skipWhiteSpace();

    readDataFromTextFile(input);
    writeDataToBinFile(output);

    CloseFile(inputFile,  "DataHandler::convertTextFileToBinFile()");
    CloseFile(outputFile, "DataHandler::convertTextFileToBinFile()");
  }
  catch (...) {
    if (inputFile.isOpen())  CloseFile(inputFile,  "DataHandler::convertTextFileToBinFile()");
    if (outputFile.isOpen()) CloseFile(outputFile, "DataHandler::convertTextFileToBinFile()");
    throw;
  }
  resetData();
}

// PRIVATE METHODS ============================================================

// delete existed data
void DataHandler::resetData() {
  for (size_t i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
  dataRowsContainer.clear();
}


// read data rows from compressed input binary file
void DataHandler::readDataFromBinFile(QDataStream& input) {
  try {
    decryptFile(input, dataRowsContainer);
  }
  catch (...) { throw; }
}


// write data rows to compressed output bin file
void DataHandler::writeDataToBinFile(QDataStream& output) {
  try {
    encryptFile(dataRowsContainer, output);
  }
  catch (...) { throw; }
}


// read data rows from input text file (BOM_UTF16LE)
void DataHandler::readDataFromTextFile(QTextStream& input) {
  try {
    while (true) {
      DataRow* dataRow = new DataRow();
      dataRow->readTextDataFrom(input);
      if (input.atEnd()) break; // skip last empty string ??
      dataRowsContainer.push_back(dataRow);
    }
  }
  catch (...) { throw; }
}


// write data rows to output text file (BOM_UTF16LE)
void DataHandler::writeDataToTextFile(QTextStream& output) {
  try {
    for (size_t i = 0; i < dataRowsContainer.size(); i++) {
      dataRowsContainer[i]->writeTextDataTo(output);
    }
  }
  catch (...) { throw; }
}

// ============================================================================

// decrypt data from input file to data container
void DataHandler::decryptFile(QDataStream& from, std::vector<DataRow*>& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::decryptFile()");
    QDataStream tmp(&tmpFile);

    uncompressFile(from, tmp);

    tmp.device()->seek(0); // set pos to file begin

    // decrypting uncompressed data
    while (true) {
      DataRow* dataRow = new DataRow();
      dataRow->readBinDataFrom(tmp);
      to.push_back(dataRow);
      if (tmp.atEnd()) break;
    }
  }
  catch (...) {
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::decryptFile()");
    RemoveFile(tmpFile, "DataHandler::decryptFile()");
    throw;
  }
  CloseFile(tmpFile,  "DataHandler::decryptFile()");
  RemoveFile(tmpFile, "DataHandler::decryptFile()");
}


// uncompress data from input file to tmp data file
void DataHandler::uncompressFile(QDataStream& from, QDataStream& to) {
  unsigned long compressedDataSize   = 0;
  unsigned long uncompressedDataSize = 0;
  size_t ulSize      = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long
  size_t dataLength  = 0;

  dataLength         = from.device()->size();
  compressedDataSize = dataLength - ulSize; // 1st 4 bytes holds information about uncompressed data size

  if (dataLength < MIN_DATA_LENGTH) {
    AddException("In function \"DataHandler::uncompressFile()\" bad data length.");
    throw;
  }

  ReadDataFromStream(from, uncompressedDataSize, ulSize, "DataHandler::uncompressFile()");

  uint8_t *inBuff  = nullptr;
  uint8_t *outBuff = nullptr;
  try {
    inBuff = new uint8_t[compressedDataSize];
    outBuff = new uint8_t[uncompressedDataSize];
    ReadDataFromStream(from, *inBuff, compressedDataSize, "DataHandler::uncompressFile()");
  }
  catch (...) {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::uncompressFile()\" allocated memory was failed.");
    throw;
  }

  int result = uncompress(outBuff, &uncompressedDataSize, inBuff, compressedDataSize);

  if (result == Z_OK) {
    WriteDataToStream(to, *outBuff, uncompressedDataSize, "DataHandler::uncompressFile()");
  } else {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"uncompressFile()\" uncompress was failed.");
    throw;
  }
}


// ============================================================================

// encrypt data to output binary file from data container
void DataHandler::encryptFile(std::vector<DataRow*>& from, QDataStream& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::encryptFile()");
    QDataStream tmp(&tmpFile);

    // write data rows to uncompressed tmp data file
    for (size_t i = 0; i < from.size(); i++) {
      from[i]->writeBinDataTo(tmp);
    }

    tmp.device()->seek(0); // set pos to file begin

    compressFile(tmp, to); // compress tmp data file to output file
  }
  catch (...) {
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::encryptFile()");
    RemoveFile(tmpFile, "DataHandler::encryptFile()");
    throw;
  }
  CloseFile(tmpFile,  "DataHandler::encryptFile()");
  RemoveFile(tmpFile, "DataHandler::encryptFile()");
}


//
void DataHandler::compressFile(QDataStream& from, QDataStream& to) {
  unsigned long uncompressedDataSize = 0;
  unsigned long compressedDataSize   = 0;
  size_t ulSize = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long

  uncompressedDataSize = from.device()->size();
  compressedDataSize   = compressBound(uncompressedDataSize);

  uint8_t *inBuff      = nullptr;
  uint8_t *outBuff     = nullptr;
  try {
    inBuff = new uint8_t[uncompressedDataSize];
    outBuff = new uint8_t[compressedDataSize];
    ReadDataFromStream(from, *inBuff, uncompressedDataSize, "DataHandler::compressFile()");
  }
  catch (...) {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::compressFile()\" allocated memory was failed.");
    throw;
  }

  int result = compress2(outBuff, &compressedDataSize, inBuff, uncompressedDataSize, Z_BEST_SPEED);

  if (result == Z_OK) {
    WriteDataToStream(to, uncompressedDataSize, ulSize, "DataHandler::compressFile()");
    WriteDataToStream(to, *outBuff, compressedDataSize, "DataHandler::compressFile()");
  } else {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::compressFile()\" compress was failed.");
    throw;
  }
}
