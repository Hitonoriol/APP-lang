#include "headers/APP.h"

void APPDataCells::reset(){
	DATA0 = 0;
	DATA1 = 1;
	DATA2 = 2;
	DATA3 = 3;
	s = stack<double>();
	ss = stack<string>();
	c.clear();
	sc.clear();
	cellSet(DATA4, DATA4);
	cellSet(3, DATA5);
}

double APPDataCells::getCell(int pos) {
  if (pos < c.size()) return c[pos];
  else return 0;
}

void APPDataCells::cellSet(double value, int pos) {
  if (pos < c.size()) c.at(pos) = value;
  else {
    c.resize(pos + 1);
    c.at(pos) = value;
  }
}

string APPDataCells::SgetCell(int pos) {
  if (pos < sc.size()) return sc[pos];
  else return "";
}

void APPDataCells::ScellSet(string value, int u) {
  if (u < sc.size()) sc[u] = value;
  else {
    sc.resize(u + 1);
    sc[u] = value;
  }
}

void APPDataCells::ScellContSet(string val, int start, int end) {
  while (start <= end) {
    ScellSet(val, start);
    start++;
  }
}
