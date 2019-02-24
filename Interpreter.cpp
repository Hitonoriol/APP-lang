#include "headers/APP.h"

APPInterpreter::APPInterpreter(){
	reset();
}

APPInterpreter::APPInterpreter(string program, int start, APPDataCells dump){
	cbuf = program;
	cells = dump;
	op(program, start);
	delete this;
}

void APPInterpreter::op(string arg, int startpos) {
  int echof = 0;
  i = startpos;
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
        i++;
        continue;
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
        	cells.ScellSet(cells.SgetCell(u)+op,u);
        } else {
          if (op == "a") {	//0:Int[current] = 0 1:String[current] = ""
            if (mode == 0) {
              cells.cellSet(0, u);
            } else {
              cells.ScellSet("",u);
            }
          } else if (op == "p") {	//Int[current]++
            cells.cellSet(cells.getCell(u) + 1, u);
          } else if (op == "j") {	//jump to memory cell with position Int[DATA4]
            lp = u;
            u = (int) cells.getCell(DATA4);
          } else if (op == "R") {	//return from memory jump
            u = lp;
          } else if (op == "m") {	//Int[current]--
            cells.cellSet(cells.getCell(u) - 1, u);
          } else if (op == "w") {	//0: write int to output buffer 1: same with strings
            if (mode == 0) {
              cells.ScellSet(cells.SgetCell(DATA7) + APPStringUtils::str_prec(cells.getCell(u),cells.getCell(DATA5)), DATA7);
            } else {
              cells.ScellSet(cells.SgetCell(DATA7) + cells.SgetCell(u), DATA7);
            }
          } else if (op == "W") {	//write output buffer to string
            cout << cells.SgetCell(DATA7);
          } else if (op == "P") {	// "" --> String[DATA7](clear the output buffer)
            cells.ScellSet("", DATA7);
          } else if (op == "_") {	//append line break --> String[DATA7](output buffer)
            cells.ScellSet(cells.SgetCell(DATA7) + "\n", DATA7);
          } else if (op == ">") {	//next memory cell
            u++;
          } else if (op == "<" && u > 0) {	//previous memory cell
            u--;
          } else if (op == ".") {	//char(Int[current]) --> append to String[current]
            int aa = cells.c[u];
            char t = aa;
            string a = APPStringUtils::charc(t);
            cells.ScellSet(cells.SgetCell(u) + a,u);
          } else if (op == "v") {	//Int[current]+=5
            if (mode == 0) {
              cells.cellSet(cells.getCell(u) + 5,u);
            } else {
              cells.cellSet(cells.getCell(u) - 5,u);
            }
          } else if (op == "x") {	//Int[current]+=10
            if (mode == 0) {
              cells.cellSet(cells.getCell(u) + 10,u);
            } else {
              cells.cellSet(cells.getCell(u) - 10,u);
            }
          } else if (op == "@") {
            cells.cellSet(cells.getCell(u) * (-1),u);
          } else if (op == "i") {	//0:get value from keyboard and put into Int[current] 1: same with strings
            if (mode == 0) {
              if (!debugrun) {
                string t;
                getline(std::cin, t);
                cells.cellSet(atof(t.c_str()),u);
              }
            } else {
              if (!debugrun)
                cells.ScellSet(APPStringUtils::gt(),u);
            }
          } else if (op == "+") {	//Int[DATA0] + Int[DATA1] --> Int[current]
            if (mode == 0)
              cells.cellSet(cells.getCell(cells.DATA0) + cells.getCell(cells.DATA1),u);
            else{
              echo("Concat "+cells.SgetCell(cells.DATA0)+" and "+cells.SgetCell(cells.DATA1));
              cells.ScellSet(cells.SgetCell(cells.DATA0) + cells.SgetCell(cells.DATA1),u);
          }
          } else if (op == "-") {	//Int[DATA0] - Int[DATA1] --> Int[current]
            cells.cellSet(cells.getCell(cells.DATA0) - cells.getCell(cells.DATA1),u);
          } else if (op == "?") {	//0: if Int[DATA0] == Int[DATA1] --> Int[DATA2]=1 1:same, but with strings
            if (mode == 0) {
            	echo ("Compairing "+APPStringUtils::str_prec(cells.getCell(cells.DATA0))+" and "+APPStringUtils::str_prec(cells.getCell(cells.DATA1)));
              if (cells.getCell(cells.DATA0) == cells.getCell(cells.DATA1)) {
                cells.cellSet(1, cells.DATA2);
              } else {
                cells.cellSet(0, cells.DATA2);
              }
            } else {
            	echo ("Compairing "+(cells.SgetCell(cells.DATA0))+" and "+(cells.SgetCell(cells.DATA1)));
              if (cells.SgetCell(cells.DATA0) == cells.SgetCell(cells.DATA1)) {
                cells.cellSet(1, cells.DATA2);
              } else {
                cells.cellSet(0, cells.DATA2);
              }
            }
          } else if (op == "g") {	//if Int[DATA0] > Int[DATA1] --> Int[DATA2]=1
          	echo("if "+APPStringUtils::str_prec(cells.getCell(cells.DATA0))+">"+APPStringUtils::str_prec(cells.getCell(cells.DATA1)));
            if (cells.getCell(cells.DATA0) > cells.getCell(cells.DATA1)) {
              cells.cellSet(1, cells.DATA2);
            } else {
              cells.cellSet(0, cells.DATA2);
            }
          } else if (op == "s") {	//if Int[DATA0] < Int[DATA1] --> Int[DATA2]=1
            if (cells.getCell(cells.DATA0) < cells.getCell(cells.DATA1)) {
              cells.cellSet(1, cells.DATA2);
            } else {
              cells.cellSet(0, cells.DATA2);
            }
          } else if (op == "r") {	//random between Int[DATA0] and Int[DATA1] --> Int[current]
            initRandom();
            cells.cellSet(srnd(cells.getCell(cells.DATA0), cells.getCell(cells.DATA1)),u);
          } else if (op == "A") {	//substring from String[DATA0] starting on Int[DATA0] with length Int[DATA1] --> String[dest]
            cells.ScellSet(cells.SgetCell(u)+cells.SgetCell(cells.DATA0).substr(cells.getCell(cells.DATA0), cells.getCell(cells.DATA1)),dest);
          } else if (op == "b") {	//String[current].length() --> Int[current]
            cells.cellSet(cells.SgetCell(u).length(),u);
          } else if (op == "}" || op == ";") {} else if (op == "{") {	//executes everything between {...} Int[DATA3] times
            if (wgt) wgt = false;
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
            int oo = i;
            cc = 0;
            while (inner < fw) {
              ao += arg.substr(oo + inner, 1);
              inner++;
            }
            echo ("Cycling "+ao+" "+APPStringUtils::str_prec(cells.getCell(cells.DATA3))+" times");
            while (cc < (int) cells.getCell(cells.DATA3)) {
              pxtc(ao);
              cc++;
            }
            if (!wgt)
            i = lastpos + fw;
            wgt = false;
            cbuf = tmpbuf;
            ide = lastide;
            nestflag = false;
          } else if (op == "!") {	//if Int[DATA2]==1 executes everything between !...;
            if (wgt) wgt = false;
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
            int oo = i;
            if (cells.getCell(cells.DATA2) == 1) {
              cc = 0;
              while (inner < fw) {
                ao += arg.substr(oo + inner, 1);
                inner++;
              }
              pxtc(ao);
              if (!wgt)
              i = lastpos + fw;
              wgt = false;
              cbuf = tmpbuf;
              ide = lastide;
            } else {
              i = lastpos + fw;
              ide = lastide;
            }
            nestflag = false;
          } else if (op == "c") {	//Current memory position --> String[DATA7](output buffer)
            cells.cellSet(u,dest);
          } else if (op == "C") {	//0: Int[Int[DATA6]] <-- Int[current] 1:same thing, but w\ strings
            if (mode == 0)
              cells.cellSet(cells.getCell(u), (int) cells.getCell(DATA6));
            else
              cells.ScellSet(cells.SgetCell(u), (int) cells.getCell(DATA6));
          } else if (op == "S") {	//mode switch
            if (mode == 0)
              mode = 1;
            else
              mode = 0;
              echo("SWITCHED TO MODE "+mode);
          } else if (op == "/") {	//Int[DATA0] / Int[DATA1] --> Int[current]
            cells.cellSet(cells.getCell(cells.DATA0) / cells.getCell(cells.DATA1),u);
          } else if (op == "*") {	//Int[DATA0] * Int[DATA1] --> Int[current]
            cells.cellSet(cells.getCell(cells.DATA0) * cells.getCell(cells.DATA1),u);
          } else if (op == "&") {	//0: Int[current] --> String[current] 1: String[current] --> Int[current]
            if (mode == 0) cells.ScellSet(APPStringUtils::str_prec(cells.getCell(u)),u);
            else cells.cellSet(atof(cells.SgetCell(u).c_str()),u);
          } else if (op == "P") {	//write String[current] to file String[DATA0]
            APPFileUtils::writeFile(cells.SgetCell(cells.DATA0), cells.SgetCell(u));
          } else if (op == "l") {	//read file String[DATA0] --> String[current]
            cells.ScellSet(APPFileUtils::readFile(cells.SgetCell(cells.DATA0)),u);
          } else if (op == "q") { //search for String[DATA1] in String[DATA0] --> Int[dest]
            cells.cellSet(cells.SgetCell(cells.DATA0).find(cells.SgetCell(cells.DATA1)),dest);
          } else if (op == "Q") { //erase character from String[DATA0] with position Int[DATA0], length Int[DATA1] --> String[dest] 
            cells.ScellSet(cells.SgetCell(cells.DATA0).erase(cells.getCell(cells.DATA0), cells.getCell(cells.DATA1)),dest);
          } else if (op == "e") { //execute APP code from String[Int[DATA0]]
          	int lastpos = i;
          	string rbf = cells.SgetCell(cells.getCell(cells.DATA0));
          	bool tide = ide;
          	ide = true;
          	string tbf = cbuf;
          	pxtc(rbf);
          	cbuf = tbf;
          	i = lastpos;
          	ide = tide;
		  } else if (op=="D") { //set destination to current cell
		  	dest = u;
		  } else if (op=="z") {	//push current cell to stack
		  	if (mode == 0)
			  cells.s.push(cells.getCell(u));
			else{
			  echo ("Pushing "+cells.SgetCell(u)+" to stack");
			  cells.ss.push(cells.SgetCell(u));
		}
		  } else if (op == "Z"){	//put the top stack value to cell
		  	if (mode==0) {cells.cellSet(cells.s.top(),u); cells.s.pop();}
		  	else {cells.ScellSet(cells.SgetCell(u)+cells.ss.top(),u); cells.ss.pop();}
		  } else if (op == "0"){	//set DATA0 to current cell
		  	cells.DATA0 = u;
		  } else if (op == "1"){	//set DATA1 to curent cell
		  	cells.DATA1 = u;
		  } else if (op == "2"){	//set DATA1 to curent cell
		  	cells.DATA2 = u;
		  } else if (op == "3"){	//set DATA1 to curent cell
		  	cells.DATA3 = u;
		  } else if (op == "E"){
		  	if (mode == 0) cells.cellSet(cells.s.size(),u);
		  	else cells.cellSet(cells.ss.size(),u);
		  } else {
              echo("UNKNOWN OP: '" + op + "' AT "+APPStringUtils::str_prec(i));
          }
        }
      }
      i++;
    }
    if (!ide) reset();
    debugrun = false;
    trace += "\n";
  } catch (std::exception & e) {
    cout << "\nAN ERROR HAS OCCURED\n" << e.what() << "\nNEAR: " << trace << endl << "\nRESETTING...\n";
    reset();
    return;
  }
}

bool APPInterpreter::cmds(string arg) {
  string bufa = arg;
  arg = APPStringUtils::split(arg, " ", 0);
  if (arg == "status") {
    cout << "STATUS\n----------\nI/O mode: " << mode << "\nCurrent position: " << u << "\nMode0 value: " << cells.c[u] << "\nMode1 value: " << cells.sc[u] << "\nPersistent memory: " << ide << "\nReserved cells values: ";
    int tci = 0;
    while (tci < STARTPOINT) {
      cout << "[" << cells.c[tci] << "|" << cells.sc[tci] << "]";
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
      echo("Persistent memory off!\n(all data cells will be wiped after program execution)");
    } else {
      ide = true;
      echo("Persistent memory on!\n(data cells won't be wiped after program execution')");
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
    if (ech)
      ech = false;
    else
      ech = true;
    return true;
  }
  if (arg == "save") {
    string fn = APPStringUtils::split(bufa, " ", 1);
    fn += ".appl";
    APPFileUtils::writeFile(fn, cbuf);
    cout << "Saved current command buffer to " + fn + ".";
    return true;
  }
  if (arg == "load") {
    string fname = APPStringUtils::split(bufa, " ", 1) + ".appl";
    cbuf = APPFileUtils::readFile(fname);
    cout << "Loaded " + fname + " to the command buffer.";
    return true;
  }
  if (arg == "run") {
    string fname = APPStringUtils::split(bufa, " ", 1) + ".appl";
    cout << "Running " << fname << endl;
    cbuf = APPFileUtils::readFile(fname);
    op(cbuf);
    cout << "\nEnd of program.";
    return true;
  }
  if (arg == "help") {
    cout << "INTERPRETER COMMANDS:\n**********\nstatus - debug info\nech - debug mode on/of\nrb - run commands from command buffer (last used)\npb - print command buffer contents\nsave <filename> - save command buffer to file\nload <filename> - load file to command buffer\nrun <filename> - run file\ncls - clear screen\nrunmode - toggle one-line and interactive mode (one-line by default)\n\nDo you want to see operators list? (y/n): ";
    if (APPStringUtils::gt() == "y") {
      cout << "\n**********\nOPERATORS:\n**********\n";
      cout << "\nOperators:\na\nSets current int cell to 0 if MODE is 0 and if MODE is 1, clears current string cell\n\np\nIncrements current cell\n\nm\nDecrements current cell\n\nw\nWrites current int cell value if current mode is 0 and writes current string cell value if mode is 1\n\n_\nEchoes end of line\n\n>\nNext cell\n\n<\nPrevious cell\n\n.\nPuts a symbol with code from current int cell to current string cell\n\nv\nAdds 5 to current cell\n\nx\nAdds 10 to current cell\n\ni\nIf MODE is 0, gets int from keyboard to int cell, if MODE is 1, gets string from keyboard.\n\n+\nIf MODE is 0, sets value of current cell to sum of DATA0 and DATA1 cells (cell[current] = cell[DATA0] + cell[DATA1]), otherwise, joins two strings from DATA0 and DATA1 string cells to current string cell\n\n-\nSets value of current cell to cell[DATA0] - cell[DATA1]\n\n?\nIf cell[DATA0] == cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n g\nIf cell[DATA0] > cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n s\nIf cell[DATA0] < cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n r\nSets current cell value to random int in range min = cell[DATA0] & max = cell[DATA1]\n\n{...}\nRepeats operators inside of it (0 to cell[DATA3] times)\n\n!...;\nExecutes operators inside of it if cell[DATA2] == 1\n\nc\nPrints current cell number\n\nS\nSwitches MODE between 0 (int) and 1 (string)\n\n/\nMakes cell[current] = cell[DATA0] / cell[DATA1]\n\nj\nJumps to #CELL[DATA4]; first jmp is always to DATA4 cell\n\nR\nReturns to previous memory cell\n\nP\nPuts current string cell value to file with name from string cell DATA0\n\nl\nLoads string from file with name from string cell DATA0 to current string cell/n/n&\nIf MODE is 0, appends current number cell to string cell, otherwise, converts value from current string cell to current number cell\n\n[:labelname]\nCreates label\n\n[e]\nSkip next goto\n\n[#label]\nGo to label\n\n[s]\nJumps to DATA4 cell\n\n[!123]\nSet current cell to value\n\n[>5]\nJumps to cell\n\nA\nPuts substring from string in previous cell to current cell with start position from DATA0 and length from DATA1\n\nb\nPuts current string cell length to current number cell";
      return true;
    }
  }

  return false;
}

void APPInterpreter::smop(string arg) {
  string ni = arg.substr(0, 1);
  string cmd = arg;
  if (ni == "#") {
    if (!goskip) {
    	string lbl = ":" + arg.substr(1);
    	int relpos = arg.substr(1).length();
		gotoStack.push(i);
      i = cbuf.find(lbl) + relpos+1;
      
      wgt = true;
      echo("Going to "+lbl+" raw: "+cbuf.substr(i));
    } else goskip = false;
  }
  if ((cmd == "ret" || cmd == "return") && gotoStack.size() > 0) { 
  	i = gotoStack.top();
  	gotoStack.pop();
  	wgt = true;
  }
  if (ni == ":") {/*Just so you know this char is in use*/}
  if (ni == "_") {/*Just so you know this char is in use[2]*/}
  if (ni == "$") { //$25=13 <--set 25th cell to 13 || $25=$13 <--set 25th cell to 13th value || $25=%appwW <-- exec operators in 25th cell
  	vector<string> bff = APPStringUtils::spl(arg.substr(1),"=");
  	string fch = bff[1].substr(0,1);
  	if (bff[0]=="c") bff[0] == APPStringUtils::str_prec(u);
  	if (bff[1].substr(1)=="c") bff[1]=fch+APPStringUtils::str_prec(u);
  	if (fch == "$"){	//check:xvwWP_W[$0=$8][$0=%PwW]
  		int value = atoi(bff[1].substr(1).c_str()), pos = atoi(bff[0].c_str());
  		if (mode == 0){
  			cells.cellSet(cells.getCell(value), pos);
  		}
  		else {
  			cells.ScellSet(cells.SgetCell(value), pos);
  		}
	} else
	if (fch == "#"){
		int ti = i, tu = u;
		bool tide = ide;
		ide = true;
		u = atoi(bff[0].c_str());
		string rbg = cells.SgetCell(atoi(bff[1].substr(1).c_str()));
		string tbf = cbuf;
		pxtc(rbg);
		cbuf = tbf;
		ide = tide;
		u = tu;
		i = ti;
	}
	else if (fch == "%"){
		int ti = i, tu = u;
		bool tide = ide;
		ide = true;
		u = atoi(bff[0].c_str());
		string rbg = bff[1].substr(1);
		string tbf = cbuf;
		pxtc(rbg);
		echo(APPStringUtils::str_prec(u)+"c = "+APPStringUtils::str_prec(cells.getCell(u)));
		cbuf = tbf;
		ide = tide;
		u = tu;
		i = ti;
		
	} else
  		 cells.cellSet(atoi(bff[1].c_str()), atoi(bff[0].c_str()));
  }
  if (ni == ">") {
    u = APPStringUtils::iconv(arg.substr(1));
  }
  if (ni == "!") {
    cells.cellSet(atof(arg.substr(1).c_str()),u);
  }
  if (ni == "0") {
    mode = 0;
  }
  if (ni == "1") mode = 1;
  if (ni == "e") goskip = true;
}

void APPInterpreter::pxtc(string arg) {
  op(arg);
}

void APPInterpreter::reset() {
  echo ("RESETTING");
  mode = 0;
  u = STARTPOINT;
  return;
}

void APPInterpreter::echo(string arg) {
	if (ech) cout << arg << endl;
}


void APPInterpreter::initRandom() {
  srand(time(NULL));
}

int APPInterpreter::srnd(int first, int last) {
  int val = first + rand() % last;
  return val;
}
