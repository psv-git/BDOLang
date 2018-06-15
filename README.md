# Original source by https://github.com/AMGarkin

===============================================================================

# Utilities can be used to decrypt/encrypt localization files for Black Desert Online

BDO_decrypt \<encrypted file\> \<output file\><br>
BDO_encrypt \<decrypted file\> \<output file\>

WARNING! Output file will be overwritten without asking.


Example of use:

- Decrypt localization file:

    bdo_decrypt.exe ads\languagedata_en.loc languagedata_en.txt

- Do some stuff with that file (modify some texts)
- Encrypt it back to the original location:

    bdo_encrypt.exe languagedata_en.txt ads\languagedata_en.loc

===============================================================================

# ReplaceLanguage
Tool for replacing texts in *decrypted* Black Desert Online localization files (\<game\>\ads\\*.loc).<br>
Tools to decrypt/encrypt localization files: [BDOcrypt](https://github.com/AMGarkin/BDOcrypt)


### Usage:
ReplaceLanguage \<replace\> \<original\> \<target\>

\<replace\>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: file which contains translated/modified strings<br>
\<original\>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: original file with string table<br>
\<target\>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: output file<br>


languagedata_??.txt files contain the following tab separated data (\t = tab):

    <sheet_number>\t<ID1>\t<ID2>\t<ID3>\t<ID4>\t"<localized_text>"

Text file uses UTF-16LE encoding.

ReplaceLanguage reads \<original\> file line by line and tries to find corresponding line in \<replace\> file. If the line is found, program replaces localized_text with the value from <translated>. Otherwise line stays untouched.

This program can be used for example to replace guild quest texts (guild_quest_list_en.txt) in languagedata_en.txt after patch:

    ReplaceLanguage guild_quest_list_en.txt languagedata_en.txt modified.txt

Or it can replace texts in russian game client with corresponding english texts extracted from NA/EU client:

    ReplaceLanguage languagedata_en.txt languagedata_ru.txt modified.txt
