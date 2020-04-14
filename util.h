#ifndef UTIL_H
#define UTIL_H

#include <string>

using std::string;

void logError(string identifier, string message);
bool valid_file(string file_path);
int getIthFile(string filename);

#endif /* UTIL_H */
