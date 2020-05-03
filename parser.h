#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <stdexcept>
#include <vector>
using std::string;
using std::vector;

#define FILE_COMMENT_LINE_CHAR '#'
#define FILE_LINE_SEPARATOR_CHAR ','

class Parser {
private:
    std::ifstream readFile;
    bool moreLines = true;
    void SkipComments();
public:
    Parser (){};
    Parser (const string& filePath);
    void LoadFile(const string& filePath);
    Parser& operator>>(vector<string>& data);
    bool Good(){return moreLines;}
};

#endif /* PARSER_H */
