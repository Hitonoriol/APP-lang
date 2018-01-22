#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#define BUFCAP 4096
#define DATA0 0
#define DATA1 1
#define DATA2 2
#define DATA3 3
#define DATA4 4
#define DATA5 5
#define DATA6 6
#define STARTPOINT 7
using namespace std;
int i = 0;	//global execution iterator
string in;	//input buffer
double c[BUFCAP];	//double cells
string sc[BUFCAP];	//string cells
int u = STARTPOINT;	//DATA0 and DATA1 are data registers || DATA2 is a logical cell (0/1) || DATA3 is a cycle cell || DATA4 is a JMP pointer cell || DATA5 is a floating point precision cell || DATA6 is a copy buffer
int ech = 0; //debug mode
bool ide = false;	//flag to switch between interactive mode and one-line exec
int mode = 0; //string/int mode
int lp = 0;	//pointer for JMP and RET
bool debugrun = false;	//flag to silence output when saving/translating
bool translate = true;	//translate flag
string translated = "";	//translated code buffer
string cbuf;	//APP code buffer

void op (string arg);
void pxtc(string arg);
void reset(){
	mode = 0;
	ech=0;
	memset(c, 0, sizeof(c));
	c[DATA4] = DATA4;
	c[DATA5] = 3;
	u = STARTPOINT;
	int i = 0;
	while (i<BUFCAP){
		sc[i]="";
		i++;
	}
	return;
}
void reinit(){
	translated = "#define DATA6 6\n#define DATA5 5\n#define DATA2 2\n#define DATA3 3\n#define DATA4 4\n#DEFINE BUFCAP 4096\n#DEFINE DATA0 0\n#DEFINE DATA1 1\n#include <iostream>\n#include <stdlib.h>\n#include <iomanip>\n#include <ctime>\n#include <cstring>\n#include <string>\n#include <sstream>\n#include <fstream>\n\nusing namespace std;\nint lp;\nint c[4096];\nbool debugrun = false;\nstring sc[4096];\nint u = 0;\nint mode=0;\nvoid reset(){mode = 0;ech=0;memset(c, 0, sizeof(c));u = 0;int i = 0;while (i<BUFCAP){sc[i]=\"\";i++;}return;\nstring gt(){string arg;getline(std::cin,arg);return arg;}void initRandom(){srand(time(NULL));}\nstring charc(char a){stringstream ss;string s;ss << a;ss >> s;return s;}int srnd(int first, int last){int val = first + rand() % last;return val;}\nbool writeFile(string filename, string arg){ofstream fout(filename.c_str());fout << arg;fout.close();return true;}string readFile(string path){ifstream input(path.c_str());string str, result;while(std::getline(input, str)) {result += str;}return result;\nmain(){\n";
}
string gt(){
	string arg;
	getline(std::cin,arg);
	return arg;
}
void initRandom()
{
	srand(time(NULL));
}
int iconv(string Text){ 
	int Result; 
	stringstream convert(Text); 
	if ( !(convert >> Result) ) Result = 0; 
	return Result; 
}
string charc(char a){
stringstream ss;
string s;
ss << a;
ss >> s;
return s;
}

int srnd(int first, int last)
{
	int val = first + rand() % last;
	return val;
}

string spl(string s, int i)
{
	std::string delimiter = " ";
	return s.substr(i, s.find(delimiter));
}

void echo(string arg)
{
	cout << arg << endl;
}

bool writeFile(string filename, string arg){
	ofstream fout(filename.c_str()); 
	fout << arg;
	fout.close();
	return true;
}

string readFile(string path){
    ifstream input(path.c_str());
    string str, result;
    while(std::getline(input, str)) {
        result += str;
    }
    return result;
}
vector<string> spl(string s, string delimiter){
vector<string> ret;
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

string split(string s, string delimiter, int numr){
s+=delimiter;
string trues = s;
size_t pos = 0;
int i =0;
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

bool cmds(string arg){
	string bufa = arg;
	arg = split(arg," ",0);
	if (arg == "reset"){
		reset();
		translated+="reset();";
		return true;
	}
	if (arg == "runmode"){
		if (ide) {ide=false;if (ech) cout<<"Switched to IDE mode!\n(all data cells will be wiped after execution)\n";} else{ ide=true;cout<<"Switched to free mode!\n(data cells won't change after execution')\n";}
		return true;
	}
	if (arg == "rb"){
		op(cbuf);
		return true;
	}
	if (arg=="cls"){
		system("cls");
		translated+="system(\"cls\");";
		return true;
	}
	if (arg=="ech"){
		if (ech==1)
		ech=0;
		else
		ech=1;
		return true;
	}
	if (arg=="save"){
		string fn = split(bufa," ",1);
		fn+=".appl";
		writeFile(fn,cbuf);
		cout<<"Saved your program (only last command buffer) to "+fn;
		return true;
	}
	if (arg=="load"){
		cbuf = readFile(split(bufa," ",1)+".appl");
		cout<<"\nLoaded code to your command buffer!";
		return true;
	}
	if (arg=="run"){
		op(readFile(split(bufa," ",1)+".appl"));
		cout<<"\nFinished run from file!";
		return true;
	}
	if (arg=="help"){
		cout<<"INTERPRETER COMMANDS:\n**********\nech - debug mode on/of\nrb - run commands from command buffer (last used)\nsave <filename> - save command buffer to file\nload <filename> - load file to command buffer\nrun <filename> - run file\ncls - clear screen\ntranslate <filename> - translate current command buffer to C++ code\nrunmode - toggle one-line and interactive mode (one-line by default)\n\nDo you want to see operators list? (y/n): ";	
		if (gt()=="y"){
		cout<<"\n**********\nOPERATORS:\n**********\n";
		cout<<"Mappings:\n0, 1 - Data cells\n2 - logical cell (0/1)\n3 - cycle cell\n4 - jmp pointer cell\n5 - floating point precision cell\n6 - copy buffer\n\nOperators:\na\nSets current int cell to 0 if MODE is 0 and if MODE is 1, clears current string cell\n\np\nIncrements current cell\n\nm\nDecrements current cell\n\nw\nWrites current int cell value if current mode is 0 and writes current string cell value if mode is 1\n\n_\nEchoes end of line\n\n>\nNext cell\n\n<\nPrevious cell\n\n.\nPuts a symbol with code from current int cell to current string cell\n\nv\nAdds 5 to current cell\n\nx\nAdds 10 to current cell\n\ni\nIf MODE is 0, gets int from keyboard to int cell, if MODE is 1, gets string from keyboard.\n\n+\nIf MODE is 0, sets value of current cell to sum of DATA0 and DATA1 cells (cell[current] = cell[DATA0] + cell[DATA1]), otherwise, joins two strings from DATA0 and DATA1 string cells to current string cell\n\n-\nSets value of current cell to cell[DATA0] - cell[DATA1]\n\n?\nIf cell[DATA0] == cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n g\nIf cell[DATA0] > cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n s\nIf cell[DATA0] < cell[DATA1], sets cell[DATA2] to 1, otherwise, to 0.\n\n r\nSets current cell value to random int in range min = cell[DATA0] & max = cell[DATA1]\n\n{...}\nRepeats operators inside of it (0 to cell[DATA3] times)\n\n!...;\nExecutes operators inside of it if cell[DATA2] == 1\n\nc\nPrints current cell number\n\nS\nSwitches MODE between 0 (int) and 1 (string)\n\n/\nMakes cell[current] = cell[DATA0] / cell[DATA1]\n\nj\nJumps to #CELL[DATA4]; first jmp is always to DATA4 cell\n\nR\nReturns to previous memory cell\n\nP\nPuts current string cell value to file with name from string cell DATA0\n\nl\nLoads string from file with name from string cell DATA0 to current string cell/n/n&\nIf MODE is 0, appends current number cell to string cell, otherwise, converts value from current string cell to current number cell\n\n[:labelname]\nCreates label\n\n[e]\nSkip next goto\n\n[#label]\nGo to label\n\n[s]\nJumps to DATA4 cell\n\n[!123]\nSet current cell to value\n\n[>5]\nJumps to cell\n\nA\nPuts substring from string in previous cell to current cell with start position from DATA0 and length from DATA1\n\nb\nPuts current string cell length to current number cell";
		return true;
	}
}
	if (arg=="translate"){
		string fn = split(bufa," ",1);
		fn+=".cpp";
		reinit();
		debugrun = true;
		op(cbuf);
		writeFile(fn,translated);
		cout<<"\nTranslated your program (only last command buffer) to C++ to file "+fn;
		return true;
	}
	return false;
	}
	
string sconv(int Number){ 
	string Result; 
	stringstream convert; 
	convert << Number; 
	Result = convert.str(); 
	return Result; 
} 
bool goskip = false;
void smop(string arg){
	string ni = arg.substr(0,1);
	string cmd = arg;
	if (ni=="#") { if (!goskip){i = cbuf.find(":"+arg.substr(1))+arg.substr(1).length();translated+="goto "+arg.substr(1)+";";}else goskip = false;}
    if (ni==":") {translated+=arg.substr(1)+":";}
    if (ni==">") {u=iconv(arg.substr(1));}
    if (ni=="!") {c[u]=stod(arg.substr(1));translated+="c[u]="+arg.substr(1)+";";}
    if (ni=="s") {u=DATA4;}
    if (ni=="e") goskip = true;
}string trace = "";

bool nestflag = false;

void op(string arg)
{
	int echof = 0;
	i=0;
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
	translated+="\n\n/* TRANSLATED FROM APP To C++ */\n/* PROGRAM LISTING IN APP:"+arg+" */\n\n";
	try{
	while (i < nn){
		trace+=arg.substr(i,1);
		cout<<std::fixed<<setprecision((int)c[DATA5]);
		op = arg.substr(i, 1);
		if (op == "\\"){
			if (iscmd) iscmd = false;
			else iscmd = true;
		}
		if (op == "[")	{isms = true;}
		if (op == "]") {isms = false;smop(smbuf);smbuf="";}
		if (isms && op!="[" && op!="]") smbuf+=op;
		if (!iscmd && scmd!=""){
			cmds(scmd);
			scmd = "";
		}
		if (iscmd && op!="\\"){
			scmd+=op;
		}
		if (!iscmd && !isms){
		if (op == "\"")
			if (echof == 1){
			translated+="\";\n";
			echof = 0;
		}
			else {echof = 1; translated+="sc[u]+=\"";}
			if (echof==1 && op!="\""){
			sc[u]+=op;
			translated+=op;
		}
			else{
		if (op == "a"){
			if (translate) translated += "if (mode == 0){c[u] = 0;}else{sc[u] = \"\";}";
			if (mode == 0){
				c[u] = 0;
			}
			else{
			sc[u] = "";
			}
		}
		else if (op == "p"){
		if (translate) translated += "c[u]++;";
			c[u]++;
		}
		else if (op == "j"){
			lp = u;
			u = (int)c[DATA4];
			translated+="lp=u;u=c[DATA4];";
		}
		else if (op == "R"){
			u = lp;
			translated+="u=lp;";
		}
		else if (op == "m"){
		if (translate) translated += "c[u]--;";
			c[u]--;
		}
		else if (op == "w"){
		if (translate) translated += "if (mode == 0){cout<<c[u];}else{cout<<sc[u];}";
			if (mode == 0)
			{
				cout << c[u];
			}
			else
			{
				cout << sc[u];
			}
		}
		else if (op == "_"){
		if (translate) translated += "cout<<endl;";
			cout << endl;
		}
		else if (op == ">" && u < BUFCAP){
		if (translate) translated += "u++;";
			u++;
		}
		else if (op == "<" && u > 0){
			if (translate) translated += "u--;";
			u--;
		}
		else if (op == ".")
		{
			int aa = c[u];
			char t = aa;
			string a = charc(t);
			sc[u]+=a;
			if (translate) translated += "int aa = c[u];char t = aa;string a = charc(t);sc[u]+=a;";
		}
		else if (op == "v")
		{
			if (translate) translated += "if (mode==0){c[u] += 5;}else{c[u]-=5;}";
			if (mode==0){
			c[u] += 5;
		}
			else{
			c[u]-=5;
		}
		}
		else if (op == "x")
		{
			if (translate) translated += "if (mode==0){c[u] += 10;}else{c[u]-=10;}";
			if (mode==0){
			c[u] += 10;
		}
			else{
			c[u] -= 10;
		}
		}
		else if (op == "@")
		{
			c[u] *= -1;
			if (translate) translated += "c[u] *= -1;";
		}
		else if (op == "i")
		{
		if (translate) translated += "if (mode == 0){if (!debugrun){string t;getline(std::cin,t);c[u] = stod(t);}}else{if (!debugrun)sc[u] = gt();}";
			if (mode == 0)
			{
				if (!debugrun){
				string t;
				getline(std::cin,t);
				c[u] = stod(t);
			}
			}
			else
			{
				if (!debugrun)
				sc[u] = gt();
			}
		}
		else if (op == "+")
		{
			if (mode==0)
			c[u] = c[DATA0] + c[DATA1];
			else
			sc[u] = sc[DATA0] + sc[DATA1];
			if (translate) translated += "if (mode==0) c[u] = c[DATA0] + c[DATA1]; else sc[u] = sc[DATA0] + sc[DATA1];";
		}
		else if (op == "-")
		{
			c[u] = c[DATA0] - c[DATA1];
			if (translate) translated += "c[u] = c[0] - c[1];";
		}
		else if (op == "?")
		{
			if (translate) translated += "if (mode==0){if (c[0] == c[1]){c[DATA2] = 1;}else{c[DATA2] = 0;}else{if (sc[0] == sc[1]){c[DATA2] = 1;}else{c[DATA2] = 0;}}";
			if (mode==0){
			if (c[DATA0] == c[DATA1])
			{
				c[DATA2] = 1;
			}
			else
			{
				c[DATA2] = 0;
			}
		}
		else
		{
			if (sc[DATA0] == sc[DATA1])
			{
				c[DATA2] = 1;
			}
			else
			{
				c[DATA2] = 0;
			}
		}
		}
		else if (op == "g")
		{
			if (translate) translated += "if (c[DATA0] > c[DATA1]){c[DATA2] = 1;}else{c[DATA2] = 0;}";
			if (c[DATA0] > c[DATA1])
			{
				c[DATA2] = 1;
			}
			else
			{
				c[DATA2] = 0;
			}
		}
		else if (op == "s")
		{
			if (translate) translated += "if (c[DATA0] < c[DATA1]){c[DATA2] = 1;}else{c[DATA2] = 0;}";
			if (c[DATA0] < c[DATA1])
			{
				c[DATA2] = 1;
			}
			else
			{
				c[DATA2] = 0;
			}
		}
		else if (op == "r")
		{
			if (translate) translated += "initRandom();c[u] = srnd(c[0], c[1]);";
			initRandom();
			c[u] = srnd(c[DATA0], c[DATA1]);
		}
		else if (op == "A"){
			sc[u] = sc[u-1].substr(c[DATA0],c[DATA1]);
		}
		else if (op == "b"){
			c[u] = sc[u].length();
		}
		else if (op == "}" || op == ";") translated+="}";
		else if (op == "{")
		{
			nestflag = true;
			bool lastide = ide;
			ide = true;
			int lastpos = i;
			string tmpbuf = cbuf;
			if (translate) translated += "for (int i = 0; i < c[DATA3]; ++i){";
			int cc = 0,kk=0;
			string ao;
			cc=i;
			while(arg.substr(cc,1)!="}"){kk++;cc++;}
			cc--;
			int fw = kk,inner = 1;
			int oo = ::i;
			cc=0;
			while(inner<fw){
				ao += arg.substr(oo + inner, 1);
				translate = false;
				inner++;
			}
			while (cc < (int)c[DATA3])
			{
			if (cc>=(int)c[DATA3]) break;
				pxtc(ao);
				cc++;
			}
			i=lastpos+fw;
			translate = true;
			cbuf = tmpbuf;
			ide = lastide;
			nestflag = false;
		}
		else if (op == "!")
		{
			nestflag = true;
			bool lastide = ide;
		ide = true;
			int lastpos = i;
			string tmpbuf = cbuf;
			if (translate) translated += "";
			int cc = 0,kk=0;
			string ao;
			cc=i;
			while(arg.substr(cc,1)!=";"){kk++;cc++;}
			cc--;
			int fw = kk,inner = 1;
			int oo = ::i;
			if (c[DATA2] == 1){
			cc=0;
				while(inner<fw){
				ao += arg.substr(oo + inner, 1);
				translate = false;
				inner++;
			}
			pxtc(ao);
			i=lastpos+fw;
			translate = true;
			cbuf = tmpbuf;
			ide = lastide;
		}
		else
		{
			i = lastpos+fw;
		}
		nestflag = false;
		}
		else if (op == "c")
		{
			if (translate) translated += "cout<<u;";
			cout << u;
		}
		else if (op == "C")
		{
			if (translate) translated += "if (mode==0)c[c[DATA6]] = c[u];else sc[c[DATA6]] = sc[u];";
			if (mode==0)
			c[(int)c[DATA6]] = c[u];
			else
			sc[(int)c[DATA6]] = sc[u];
		}
		else if (op == "S")
		{
			if (translate) translated += "if (mode == 0)mode = 1;else mode = 0;";
			if (mode == 0)
				mode = 1;
			else
				mode = 0;
			if (ech == 1)
				cout << endl << "SWITCHED TO MODE " << mode << endl;
		}
		else if (op == "/")
		{
			if (translate) translated += "c[u] = (c[DATA0]) / (c[DATA1]);";
			c[u] = (c[DATA0]) / (c[DATA1]);
		}
		else if (op == "&"){
			translated+="if (mode==0) sc[u] += to_string(c[u]); else c[u] = stod(sc[u]);";
			if (mode==0) sc[u] += to_string(c[u]);
			else c[u] = stod(sc[u]);
		}
		else if(op == "P"){
			translated+="writeFile(sc[DATA0],sc[u]);";
			writeFile(sc[DATA0],sc[u]);
		}
		else if(op == "l"){
			translated+="sc[u] = readFile(sc[DATA0]);";
			sc[u] = readFile(sc[DATA0]);
		}
		else
		{
			if (ech == 1)
				cout << endl << "UNKNOWN OP: '" + op + "'" << endl;
		}
	}
	}
	if (echof==0 && !isms && !iscmd)
	translated+="\n";
		i++;
	}
	if (translate) translated+="}";
	if (!ide) reset();
	debugrun = false;
	trace+="\n";
}
catch (std::exception &e){
	cout<<"\nAN ERROR HAS OCCURED\n"<<e.what()<<"\nNEAR: "<<trace<<endl<<isms<<"\nRESET...\n";
	reset();
	return;
}
}

void pxtc(string arg)
{
	op(arg);
}

int main(int argc, char* argv[])
{
	c[DATA4] = DATA4;
	c[DATA5] = 3;
	if (argc == 1)
		cout<<"APP CONSOLE INTERPRETER || STARTPOINT: "<<STARTPOINT<<"\nType \"help\" to see the list of avalaible commands\n";
	if (argc > 1)
		{
			string runc = string(argv[1]);
			op(readFile(runc));
			cout<<"\n\nEnd of program. Quit? (y/n): ";
			if (gt() == "y"){
				return 0;
			}
		}
	while (true)
	{
		cout << endl << ">> ";
		getline(std::cin, in);
		op(in);
	}
}
