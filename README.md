# Original decryptor source: https://github.com/AMGarkin

===============================================================================

### BIN_TO_TEXT - Конвертирует бинарный .loc файл в текстовый.

### TEXT_TO_BIN - Конвертирует текстовый файл в бинарный .loc файл.

### MERGE - пока не готово

### TRANSLATE - пока не готово

По умолчанию расположение файлов установлено в папке ./data/. Папку и название файла по умолчанию, можно поменять в окне настроек. Настройки хранятся в файле config.cfg в папке с программой и загружаются при старте программы. Настройки по умолчанию можно вернуть, удалив этот файл.

Файл вывода имеет то же расположение и название, что и файл ввода но с добавлением постфикса (.txt - для BIN_TO_TEXT, либо .bin - для TEXT_TO_BIN) в конце файла (можно не переименовывать файлы - при каждой ковертации к их предыдущму имени будет добавлено .txt - для текстового, либо .bin - для бинарного).
