#include "APP.h"

string APPStringUtils::str_prec(const double a_value, const int n) {
    ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

string APPStringUtils::gt() {
  string arg;
  getline(std::cin, arg);
  return arg;
}

int APPStringUtils::iconv(string Text) {
  int Result;
  stringstream convert(Text);
  if (!(convert >> Result)) Result = 0;
  return Result;
}

string APPStringUtils::charc(char a) {
  stringstream ss;
  string s;
  ss << a;
  ss >> s;
  return s;
}

string APPStringUtils::joinFrom(char* arg[], int from, int argc){
	string ret = "";
	while (from<argc){
		ret+=string(arg[from]);
		from++;
	}
	return ret;
}

vector <string> APPStringUtils::spl(string s, string delimiter) {
  vector < string > ret;
  s += delimiter;
  size_t pos = 0;
  string token;
  int i = 0;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    ret.push_back(token);
    s.erase(0, pos + delimiter.length());
    i++;
  }
  return ret;
}

string APPStringUtils::split(string s, string delimiter, int numr) {
  return spl(s,delimiter)[numr];
}

string APPStringUtils::replace(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

string APPStringUtils::sconv(int Number) {
  string Result;
  stringstream convert;
  convert << Number;
  Result = convert.str();
  return Result;
}
