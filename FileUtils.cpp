#include "APP.h"

bool APPFileUtils::writeFile(string filename, string arg) {
  ofstream fout(filename.c_str());
  fout << arg;
  fout.close();
  return true;
}

string APPFileUtils::readFile(string path) {
  ifstream input(path.c_str());
  string str, result;
  while (std::getline(input, str)) {
    result += str;
  }
  return result;
}
