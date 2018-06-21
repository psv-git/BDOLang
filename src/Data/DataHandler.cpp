#include <QString>
#include "DataHandler.hpp"
#include "DataRow.hpp"
#include "FileFunctions.hpp"


DataHandler::DataHandler() {}


DataHandler::~DataHandler() {
  resetData();
}

// PUBLIC METHODS ==============================================================

// TODO:
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
  std::fstream input;
  u16ofstream output;
  std::string path;
  try {
    path = binFilePath.toStdString();
    openInputFile(input, path, "DataHandler::convertBinFileToTextFile()");
    readDataFromBinFile(input);
    closeFile(input, path, "DataHandler::convertBinFileToTextFile()");
    path += ".txt";
    openOutputFile(output, path, "DataHandler::convertBinFileToTextFile()");
    writeDataToTextFile(output);
    closeFile(output, path, "DataHandler::convertBinFileToTextFile()");
  }
  catch (const std::exception &e) {
    if (input.is_open()) closeFile(input, path, "DataHandler::convertBinFileToTextFile()");
    if (output.is_open()) closeFile(output, path, "DataHandler::convertBinFileToTextFile()");
    throw;
  }
  resetData();
}


//
void DataHandler::convertTextFileToBinFile(const QString &textFilePath) {
  resetData(); // be on the safe side
  u16ifstream input;
  std::fstream output;
  std::string path;
  try {
    path = textFilePath.toStdString();
    openInputFile(input, path, "DataHandler::convertTextFileToBinFile()");
    readDataFromTextFile(input);
    closeFile(input, path, "DataHandler::convertTextFileToBinFile()");
    path += ".bin";
    openOutputFile(output, path, "DataHandler::convertTextFileToBinFile()");
    writeDataToBinFile(output);
    closeFile(output, path, "DataHandler::convertTextFileToBinFile()");
  }
  catch (const std::exception &e) {
    if (input.is_open()) closeFile(input, path, "DataHandler::convertTextFileToBinFile()");
    if (output.is_open()) closeFile(output, path, "DataHandler::convertTextFileToBinFile()");
    throw;
  }
  resetData();
}

// PRIVATE METHODS ==============================================================

// delete existed data
void DataHandler::resetData() {
  for (size_t i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
  dataRowsContainer.clear();
}


// read data rows from compressed input binary file
void DataHandler::readDataFromBinFile(std::fstream& input) {
  try {
    decryptFile(input, dataRowsContainer);
  }
  catch (const std::exception& e) {
    throw;
  }
}


// write data rows to compressed output bin file
void DataHandler::writeDataToBinFile(std::fstream& output) {
  try {
    encryptFile(dataRowsContainer, output);
  }
  catch (const std::exception& e) {
    throw;
  }
}


// read data rows from input text file (BOM_UTF16LE)
void DataHandler::readDataFromTextFile(u16ifstream& input) {
  try {
//    input.imbue(std::locale(input.getloc(), new std::codecvt_utf16<wchar_t, MAX_CODE, std::little_endian>));
//    wchar_t bom;
//    bom = input.peek();
////    input.read(reinterpret_cast<wchar_t*>(&bom), 2); // check BOM exist
//    if (bom == BOM_UTF16BE || bom == BOM_UTF16LE) {
////      input.seekg(0, std::ios::beg);
//        std::cerr << "test" << std::endl;
//        input.read(reinterpret_cast<char*>(&bom), sizeof(wchar_t));
//    }
    while (true) {
      DataRow* dataRow = new DataRow();
      input >> *dataRow;
      if (input.eof()) break;
      dataRowsContainer.push_back(dataRow);
    }
  }
  catch (const std::exception &e) {
    throw;
  }
}


// write data rows to output text file (BOM_UTF16LE)
void DataHandler::writeDataToTextFile(u16ofstream& output) {
  try {
//    output.imbue(std::locale(output.getloc(), new std::codecvt_utf16<char16_t, MAX_CODE>));
//    output.put(BOM_UTF16LE);
    for (size_t i = 0; i < dataRowsContainer.size(); i++) {
      output << *dataRowsContainer[i];
    }
  }
  catch (const std::exception &e) {
    throw;
  }
}
