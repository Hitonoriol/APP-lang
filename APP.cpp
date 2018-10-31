#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#define DATA0 0
# define DATA1 1
# define DATA2 2
# define DATA3 3
# define DATA4 4
# define DATA5 5
# define DATA6 6
# define DATA7 7
# define STARTPOINT 8
using namespace std;
int i = 0; //global execution iterator
string in ; //input buffer
vector < double > c; //double cells
vector < string > sc; //string cells
int u = STARTPOINT;
int ech = 0; //debug mode
bool ide = false; //persistent memory flag
int mode = 0; //string/int mode
int lp = 0; //pointer for JMP and RET
bool debugrun = false; //flag to silence output when saving/translating
string cbuf; //APP code buffer

void op(string arg);
void pxtc(string arg);

double getCell(int pos) {
  if (pos < c.size()) return c[pos];
  else return 0;
}

void cellSet(double value) {
  if (u < c.size()) c.at(u) = value;
  else {
    c.resize(u + 1);
    c.at(u) = value;
  }
}

void cellSet(double value, int pos) {
  int cu = u;
  u = pos;
  cellSet(value);
  u = cu;
}

string SgetCell(int pos) {
  if (pos < sc.size()) return sc[pos];
  else return "";
}

void ScellSet(string value) {
  if (u < sc.size()) sc.at(u) = value;
  else {
    sc.resize(u + 1);
    sc.at(u) = value;
  }
}

void ScellSet(string value, int pos) {
  int cu = u;
  u = pos;
  ScellSet(value);
  u = cu;
}

void ScellContSet(string val, int start, int end) {
  while (start <= end) {
    ScellSet(val, start);
    start++;
  }
}

void reset() {
  mode = 0;
  ech = 0;
  c.clear();
  sc.clear();
  cellSet(DATA4, DATA4);
  cellSet(3, DATA5);
  u = STARTPOINT;
  return;
}
string gt() {
  string arg;
  getline(std::cin, arg);
  return arg;
}

void initRandom() {
  srand(time(NULL));
}

int iconv(string Text) {
  int Result;
  stringstream convert(Text);
  if (!(convert >> Result)) Result = 0;
  return Result;
}

string charc(char a) {
  stringstream ss;
  string s;
  ss << a;
  ss >> s;
  return s;
}

int srnd(int first, int last) {
  int val = first + rand() % last;
  return val;
}

string spl(string s, int i) {
  std::string delimiter = " ";
  return s.substr(i, s.find(delimiter));
}

void echo(string arg) {
  cout << arg << endl;
}

bool writeFile(string filename, string arg) {
  ofstream fout(filename.c_str());
  fout << arg;
  fout.close();
  return true;
}

string readFile(string path) {
  ifstream input(path.c_str());
  string str, result;
  while (std::getline(input, str)) {
    result += str;
  }
  return result;
}
vector < string > spl(string s, string delimiter) {
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

string split(string s, string delimiter, int numr) {
  s += delimiter;
  string trues = s;
  size_t pos = 0;
  int i = 0;
  string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    i++;
    s.erase(0, pos + delimiter.length());
  }
  s = trues;
  string ret[i];
  i = 0;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    ret[i] = token;
    i++;
    s.erase(0, pos + delimiter.length());
  }
  return ret[numr];
}

bool cmds(string arg) {
  string bufa = arg;
  arg = split(arg, " ", 0);
  if (arg == "status") {
    cout << "STATUS\n----------\nI/O mode: " << mode << "\nCurrent position: " << u << "\nMode0 value: " << c[u] << "\nMode1 value: " << sc[u] << "\nPersistent memory: " << ide << "\nReserved cells values: ";
    int tci = 0;
    while (tci < STARTPOINT) {
      cout << "[" << c[tci] << "|" << sc[tci] << "]";
      if (STARTPOINT - tci > 1) cout << ">";
      tci++;
    }
    cout << "\n----------";
    return true;
  }
  if (arg == "reset") {
    reset();
    return true;
  }
  if (arg == "runmode") {
    if (ide) {
      ide = false;
      if (ech) cout << "Persistent memory off!\n(all data cells will be wiped after program execution)\n";
    } else {
      ide = true;
      cout << "Persistent memory on!\n(data cells won't be wiped after program execution')\n";
    }
    return true;
  }
  if (arg == "rb") {
    op(cbuf);
    return true;
  }
  if (arg == "pb") {
    cout << cbuf;
    return true;
  }
  if (arg == "cls") {
    system("cls");
    return true;
  }
  if (arg == "ech") {
    if (ech == 1)
      ech = 0;
    else
      ech = 1;
    return true;
  }
  if (arg == "save") {
    string fn = split(bufa, " ", 1);
    fn += ".appl";
    writeFile(fn, cbuf);
    cout << "Saved current command buffer to " + fn + ".";
    return true;
  }
  if (arg == "load") {
    string fname = split(bufa, " ", 1) + ".appl";
    cbuf = readFile(fname);
    cout << "Loaded " + fname + " to the command buffer.";
    return true;
  }
  if (arg == "run") {
    string fname = split(bufa, " ", 1) + ".appl";
    cout << "Running " << fname << endl;
    op(readFile(fname));
    cout << "End of program.";
    return true;
  }
  if (arg == "help") {
    cout << "INTERPRETER COMMANDS:\n**********\nstatus - debug info\nech - debug mode on/of\nrb - run commands from command buffer (last used)\npb - print command buffer contents\nsave <filename> - save command buffer to file\nload <filename> - load file to command buffer\nrun <filename> - run file\ncls - clear screen\nrunmode - toggle one-line and interactive mode (one-line by default)\n\nDo you want to see operators list? (y/n): ";
    if (gt() == "y") {
      cout << "\n**********\nOPERATORS:\n**********\n";
      cout << "\nOperators:\na\nSets current int cell to 0 if MODE is 0 and if MODE is 1, clears current string cell\n\np\nIncrements current cell\n\nm\nDecrements current cell\n\nw\nWrites current int cell value if current mode is 0 and writes current string cell value if mode is 1\n\n_\nEchoes end of line\n\n>\nNext cell\n\n<\nPrevious cell\n\n.\nPuts a symbol with code from current int cell to current string cell\n\nv\nAdds 5 to current cell\n\nx\nAdds 10 to current cell\n\ni\nIf MODE is 0, gets int from keyboard to int cell, if MODE is 1, gets string from keyboard.\n\n+\nIf MODE is 0, sets value of current cell to sum of DATA0 and DATA1 cells (cell[current] = cell[DATA0] + cell[DATA1]), otherwise, joins two strings from DATA0 and DATA1 string cells to current string cell\n\n-\nSets value of current cell to cell[DATA0] - cell[DATA1]\n\n?\nIf cell[DATA0] == cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n g\nIf cell[DATA0] > cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n s\nIf cell[DATA0] < cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n r\nSets current cell value to random int in range min = cell[DATA0] & max = cell[DATA1]\n\n{...}\nRepeats operators inside of it (0 to cell[DATA3] times)\n\n!...;\nExecutes operators inside of it if cell[DATA2] == 1\n\nc\nPrints current cell number\n\nS\nSwitches MODE between 0 (int) and 1 (string)\n\n/\nMakes cell[current] = cell[DATA0] / cell[DATA1]\n\nj\nJumps to #CELL[DATA4]; first jmp is always to DATA4 cell\n\nR\nReturns to previous memory cell\n\nP\nPuts current string cell value to file with name from string cell DATA0\n\nl\nLoads string from file with name from string cell DATA0 to current string cell/n/n&\nIf MODE is 0, appends current number cell to string cell, otherwise, converts value from current string cell to current number cell\n\n[:labelname]\nCreates label\n\n[e]\nSkip next goto\n\n[#label]\nGo to label\n\n[s]\nJumps to DATA4 cell\n\n[!123]\nSet current cell to value\n\n[>5]\nJumps to cell\n\nA\nPuts substring from string in previous cell to current cell with start position from DATA0 and length from DATA1\n\nb\nPuts current string cell length to current number cell";
      return true;
    }
  }

  return false;
}

string sconv(int Number) {
  string Result;
  stringstream convert;
  convert << Number;
  Result = convert.str();
  return Result;
}
bool goskip = false;
void smop(string arg) {
  string ni = arg.substr(0, 1);
  string cmd = arg;
  if (ni == "#") {
    if (!goskip) {
      i = cbuf.find(":" + arg.substr(1)) + arg.substr(1).length();
    } else goskip = false;
  }
  if (ni == ":") {}
  if (ni == ">") {
    u = iconv(arg.substr(1));
  }
  if (ni == "!") {
    cellSet(stod(arg.substr(1)));
  }
  if (ni == "s") {
    u = DATA4;
  }
  if (ni == "e") goskip = true;
}
string trace = "";

bool nestflag = false;

void op(string arg) {
  int echof = 0;
  i = 0;
  int nn = 0;
  if (cmds(arg))
    return;
  nn = arg.size();
  string op;
  string scmd = "";
  if (!nestflag)
    cbuf = arg;
  string smbuf = "";
  bool iscmd = false;
  bool isms = false;
  try {
    while (i < nn) {
      trace += arg.substr(i, 1);
      cout << std::fixed << setprecision((int) c[DATA5]);
      op = arg.substr(i, 1);
      if (op == "\\") {
        if (iscmd) iscmd = false;
        else iscmd = true;
      }
      if (op == "[") {
        isms = true;
      }
      if (op == "]") {
        isms = false;
        smop(smbuf);
        smbuf = "";
      }
      if (isms && op != "[" && op != "]") smbuf += op;
      if (!iscmd && scmd != "") {
        cmds(scmd);
        scmd = "";
      }
      if (iscmd && op != "\\") {
        scmd += op;
      }
      if (!iscmd && !isms) {
        if (op == "\"")
          if (echof == 1) {
            echof = 0;
          }
        else {
          echof = 1;
        }
        if (echof == 1 && op != "\"") {
        	ScellSet(SgetCell(u)+op);
        } else {
          if (op == "a") {	//0:Int[current] = 0 1:String[current] = ""
            if (mode == 0) {
              cellSet(0);
            } else {
              ScellSet("");
            }
          } else if (op == "p") {	//Int[current]++
            cellSet(getCell(u) + 1);
          } else if (op == "j") {	//jump to memory cell with position Int[DATA4]
            lp = u;
            u = (int) getCell(DATA4);
          } else if (op == "R") {	//return from memory jump
            u = lp;
          } else if (op == "m") {	//Int[current]--
            cellSet(getCell(u) - 1);
          } else if (op == "w") {	//0: write int to output buffer 1: same with strings
            if (mode == 0) {
              ScellSet(SgetCell(DATA7) + to_string(getCell(u)), DATA7);
            } else {
              ScellSet(SgetCell(DATA7) + SgetCell(u), DATA7);
            }
          } else if (op == "W") {	//write output buffer to string
            cout << SgetCell(DATA7);
          } else if (op == "P") {	// "" --> String[DATA7](clear the output buffer)
            ScellSet("", DATA7);
          } else if (op == "_") {	//line break --> String[DATA7](output buffer)
            ScellSet(SgetCell(DATA7) + "\n", DATA7);
          } else if (op == ">") {	//next memory cell
            u++;
          } else if (op == "<" && u > 0) {	//previous memory cell
            u--;
          } else if (op == ".") {	//char(Int[current]) --> append String[current]
            int aa = c[u];
            char t = aa;
            string a = charc(t);
            ScellSet(SgetCell(u) + a);
          } else if (op == "v") {	//Int[current]+=5
            if (mode == 0) {
              cellSet(getCell(u) + 5);
            } else {
              cellSet(getCell(u) - 5);
            }
          } else if (op == "x") {	//Int[current]+=10
            if (mode == 0) {
              cellSet(getCell(u) + 10);
            } else {
              cellSet(getCell(u) - 10);
            }
          } else if (op == "@") {
            cellSet(getCell(u) * (-1));
          } else if (op == "i") {	//0:get value from keyboard and put into Int[current] 1: same with strings
            if (mode == 0) {
              if (!debugrun) {
                string t;
                getline(std::cin, t);
                cellSet(stod(t));
              }
            } else {
              if (!debugrun)
                ScellSet(gt());
            }
          } else if (op == "+") {	//Int[DATA0] + Int[DATA1] --> Int[current]
            if (mode == 0)
              cellSet(getCell(DATA0) + getCell(DATA1));
            else
              ScellSet(SgetCell(DATA0) + SgetCell(DATA1));
          } else if (op == "-") {	//Int[DATA0] - Int[DATA1] --> Int[current]
            cellSet(getCell(DATA0) - getCell(DATA1));
          } else if (op == "?") {	//0: if Int[DATA0] == Int[DATA1] --> Int[DATA2]=1 1:same, but with strings
            if (mode == 0) {
              if (getCell(DATA0) == getCell(DATA1)) {
                cellSet(1, DATA2);
              } else {
                cellSet(0, DATA2);
              }
            } else {
              if (SgetCell(DATA0) == SgetCell(DATA1)) {
                cellSet(1, DATA2);
              } else {
                cellSet(0, DATA2);
              }
            }
          } else if (op == "g") {	//if Int[DATA0] > Int[DATA1] --> Int[DATA2]=1
            if (getCell(DATA0) > getCell(DATA1)) {
              cellSet(1, DATA2);
            } else {
              cellSet(0, DATA2);
            }
          } else if (op == "s") {	//if Int[DATA0] < Int[DATA1] --> Int[DATA2]=1
            if (getCell(DATA0) < getCell(DATA1)) {
              cellSet(1, DATA2);
            } else {
              cellSet(0, DATA2);
            }
          } else if (op == "r") {	//random between Int[DATA0] and Int[DATA1] --> Int[current]
            initRandom();
            cellSet(srnd(getCell(DATA0), getCell(DATA1)));
          } else if (op == "A") {	//substring from String[current-1] starting on Int[DATA0] with length Int[DATA1] --> String[current]
            ScellSet(SgetCell(u - 1).substr(getCell(DATA0), getCell(DATA1)));
          } else if (op == "b") {	//String[current].length() --> Int[current]
            cellSet(SgetCell(u).length());
          } else if (op == "}" || op == ";") {} else if (op == "{") {	//executes everything between {...} Int[DATA3] times
            nestflag = true;
            bool lastide = ide;
            ide = true;
            int lastpos = i;
            string tmpbuf = cbuf;
            int cc = 0, kk = 0;
            string ao;
            cc = i;
            while (arg.substr(cc, 1) != "}") {
              kk++;
              cc++;
            }
            cc--;
            int fw = kk, inner = 1;
            int oo = ::i;
            cc = 0;
            while (inner < fw) {
              ao += arg.substr(oo + inner, 1);
              inner++;
            }
            while (cc < (int) getCell(DATA3)) {
              if (cc >= (int) getCell(DATA3)) break;
              pxtc(ao);
              cc++;
            }
            i = lastpos + fw;
            cbuf = tmpbuf;
            ide = lastide;
            nestflag = false;
          } else if (op == "!") {	//if Int[DATA2]==1 executes everything between !...;
            nestflag = true;
            bool lastide = ide;
            ide = true;
            int lastpos = i;
            string tmpbuf = cbuf;
            int cc = 0, kk = 0;
            string ao;
            cc = i;
            while (arg.substr(cc, 1) != ";") {
              kk++;
              cc++;
            }
            cc--;
            int fw = kk, inner = 1;
            int oo = ::i;
            if (getCell(DATA2) == 1) {
              cc = 0;
              while (inner < fw) {
                ao += arg.substr(oo + inner, 1);
                inner++;
              }
              pxtc(ao);
              i = lastpos + fw;
              cbuf = tmpbuf;
              ide = lastide;
            } else {
              i = lastpos + fw;
              ide = lastide;
            }
            nestflag = false;
          } else if (op == "c") {	//Current memory position --> String[DATA7](output buffer)
            ScellSet(to_string(u), DATA7);
          } else if (op == "C") {	//0: Int[Int[DATA6]] <-- Int[current] 1:same thing, but w\ strings
            if (mode == 0)
              cellSet(getCell(u), (int) getCell(DATA6));
            else
              ScellSet(SgetCell(u), (int) getCell(DATA6));
          } else if (op == "S") {	//mode switch
            if (mode == 0)
              mode = 1;
            else
              mode = 0;
            if (ech == 1)
              cout << endl << "SWITCHED TO MODE " << mode << endl;
          } else if (op == "/") {	//Int[DATA0] / Int[DATA1] --> Int[current]
            cellSet(getCell(DATA0) / getCell(DATA1));
          } else if (op == "&") {	//0: Int[current] --> String[current] 1: String[current] --> Int[current]
            if (mode == 0) ScellSet(to_string(getCell(u)));
            else cellSet(stod(SgetCell(u)));
          } else if (op == "P") {	//write String[current] to file String[DATA0]
            writeFile(SgetCell(DATA0), SgetCell(u));
          } else if (op == "l") {	//read file String[DATA0] --> String[current]
            ScellSet(readFile(SgetCell(DATA0)));
          } else if (op == "q") { //search for String[DATA1] in String[DATA0] --> Int[current]
            cellSet(SgetCell(DATA0).find(SgetCell(DATA1)));
          } else if (op == "Q") { //erase character from String[DATA0] with position Int[DATA0], length Int[DATA1] --> String[current] 
            ScellSet(SgetCell(DATA0).erase(getCell(DATA0), getCell(DATA1)));
          } else if (op == "e") {
          	int lastpos = i;
          	string rbf = SgetCell(u);
          	bool tide = ide;
          	ide = true;
          	pxtc(rbf);
          	i = lastpos;
          	ide = tide;
		  }
		  
		   else {
            if (ech == 1)
              cout << endl << "UNKNOWN OP: '" + op + "'" << endl;
          }
        }
      }
      if (echof == 0 && !isms && !iscmd) {}
      i++;
    }
    if (!ide) reset();
    debugrun = false;
    trace += "\n";
  } catch (std::exception & e) {
    cout << "\nAN ERROR HAS OCCURED\n" << e.what() << "\nNEAR: " << trace << endl << "\nRESET...\n";
    reset();
    return;
  }
}

void pxtc(string arg) {
  op(arg);
}

int main(int argc, char * argv[]) {
  reset();
  if (argc == 1)
    cout << "APP INTERPRETER || STARTPOINT: " << STARTPOINT << "\nReserved memory cells:\n[DATA0] and [DATA1] data registers\n[DATA2] logical cell (0/1)\n[DATA3] cycle counter\n[DATA4] JMP pointer\n[DATA5] floating point precision value\n[DATA6] copy buffer\n[DATA7] output buffer" << "\nType \"help\" to see the list of available commands\n";
  if (argc > 1) {
    string runc = string(argv[1]);
    cout << "Running user program...\n\n";
    op(readFile(runc));
    cout << "\nEnd of program. Quit? (y/n): ";
    if (gt() == "y") {
      return 0;
    }
  }
  while (true) {
    cout << endl << ">> ";
    getline(std::cin, in );
    op( in );
  }
}
