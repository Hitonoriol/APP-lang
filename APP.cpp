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
using namespace std;
int c[BUFCAP];
string sc[BUFCAP];
int ide = 0;
int u = 4;	//cells 0,1,2,3 are data registers
int ech = 0;
int mode = 0;
int lp = 0;
bool debugrun = false;
bool translate = true;
string translated = "";
string cbuf;

void op (string arg);
void pxtc(string arg);
void reset(){
	mode = 0;
	ech=0;
	memset(c, 0, sizeof(c));
	u = 0;
	int i = 0;
	while (i<BUFCAP){
		sc[i]="";
		i++;
	}
	return;
}
void reinit(){
	translated = "#DEFINE BUFCAP 4096\n#DEFINE DATA0 0\n#DEFINE DATA1 1\n#include <iostream>\n#include <stdlib.h>\n#include <iomanip>\n#include <ctime>\n#include <cstring>\n#include <string>\n#include <sstream>\n#include <fstream>\n\nusing namespace std;\nint lp;\nint c[4096];\nstring sc[4096];\nint u = 0;\nint mode=0;\nvoid reset(){mode = 0;ech=0;memset(c, 0, sizeof(c));u = 0;int i = 0;while (i<BUFCAP){sc[i]=\"\";i++;}return;\nstring gt(){string arg;getline(std::cin,arg);return arg;}void initRandom(){srand(time(NULL));}\nstring charc(char a){stringstream ss;string s;ss << a;ss >> s;return s;}int srnd(int first, int last){int val = first + rand() % last;return val;}\nmain(){\n";
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
		cout<<"INTERPRETER COMMANDS:\n**********\nech - debug mode on/of\nrb - run commands from command buffer (last used)\nsave <filename> - save command buffer to file\nload <filename> - load file to command buffer\nrun <filename> - run file\ncls - clear screen\ntranslate <filename> - translate current command buffer to C++ code\nDo you want to see operators list? (y/n): ";	
		if (gt()=="y"){
		cout<<"\n**********\nOPERATORS:\n**********\n";
		cout<<"a\nSets current int cell to 0 if MODE is 0 and if MODE is 1, clears current string cell\n\np\nIncrements current cell\n\nm\nDecrements current cell\n\nw\nWrites current int cell value if current mode is 0 and writes current string cell value if mode is 1\n\n_\nEchoes end of line\n\n>\nNext cell\n\n<\nPrevious cell\n\n.\nPuts a symbol with code from current int cell to current string cell\n\nv\nAdds 5 to current cell\n\nx\nAdds 10 to current cell\n\ni\nIf MODE is 0, gets int from keyboard to int cell, if MODE is 1, gets string from keyboard.\n\n+\nSets value of current cell to sum of two previous cells (cell[current] = cell[current-2] + cell[current-1])\n\n-\nSets value of current cell to cell[current-2] - cell[current-1]\n\n?\nIf cell[current-2] == cell[current-1], sets current cell to 1, otherwise, to 0.\n\n g\nIf cell[current-2] > cell[current-1], sets current cell to 1, otherwise, to 0.\n\n s\nIf cell[current-2] < cell[current-1], sets current cell to 1, otherwise, to 0.\n\n r\nSets current cell value to random int in range min = cell[current-2] & max = cell[current-1]\n\n{\nRepeats 1 operator after it cell[current-1] times\n\n!\nExecutes next operator if cell[current-1] == 1\n\nc\nPrints current cell number\n\nS\nSwitches MODE between 0 (int) and 1 (string)\n\n/\nMakes cell[current] = cell[current-2] / cell[current-1]\n\nR\nMakes cell[current] = cell[current-2] / cell[current-1]\n";
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
void smop(string arg){
	vector<string> args = spl(arg," ");
	string cmd = args[0];
	if (cmd == "jmp") {lp = u; u = iconv(args[1]);translated+="lp=u;u="+args[1]+";";}
	if (cmd == "ret") {u = lp;translated+="u=lp;";}
}
void op(string arg)
{
	int echof = 0;
	int i = 0;
	int nn = 0;
	if (cmds(arg))
	return;
	nn = arg.size();
	string op;
	string scmd = "";
	cbuf = arg;
	string smbuf = "";
	bool iscmd = false;
	bool isms = false;
	translated+="\n\n/* TRANSLATED FROM APP To C++ */\n/* PROGRAM LISTING IN APP:"+arg+" */\n\n";
	try{
	while (i < nn){
		op = arg.substr(i, 1);
		if (op == "\\"){
			if (iscmd) iscmd = false;
			else iscmd = true;
		}
		if (op == "[")	isms = true;
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
		else if (op == ">" && u < 255){
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
			if (translate) translated += "if (mode == 0){cout << \"INPUT INT: \";c[u]=iconv(gt());}else{cout << \"INPUT STRING: \";sc[u] = gt();}";
			if (mode == 0)
			{
				cout << "INPUT INT: ";
				if (!debugrun)
				c[u]=iconv(gt());
			}
			else
			{
				cout << "INPUT STRING: ";
				if (!debugrun)
				sc[u] = gt();
			}
		}
		else if (op == "+")
		{
			c[u] = c[DATA0] + c[DATA1];
			if (translate) translated += "c[u] = c[0] + c[1];";
		}
		else if (op == "-")
		{
			c[u] = c[DATA0] - c[DATA1];
			if (translate) translated += "c[u] = c[0] - c[1];";
		}
		else if (op == "?")
		{
			if (translate) translated += "if (mode==0){if (c[0] == c[1]){c[u] = 1;}else{c[u] = 0;}else{if (sc[0] == sc[1]){c[u] = 1;}else{c[u] = 0;}}";
			if (mode==0){
			if (c[DATA0] == c[DATA1])
			{
				c[u] = 1;
			}
			else
			{
				c[u] = 0;
			}
		}
		else
		{
			if (sc[DATA0] == sc[DATA1])
			{
				c[u] = 1;
			}
			else
			{
				c[u] = 0;
			}
		}
		}
		else if (op == "g")
		{
			if (translate) translated += "if (c[DATA0] > c[DATA1]){c[u] = 1;}else{c[u] = 0;}";
			if (c[DATA0] > c[DATA1])
			{
				c[u] = 1;
			}
			else
			{
				c[u] = 0;
			}
		}
		else if (op == "s")
		{
			if (translate) translated += "if (c[DATA0] < c[DATA1]){c[u] = 1;}else{c[u] = 0;}";
			if (c[DATA0] < c[DATA1])
			{
				c[u] = 1;
			}
			else
			{
				c[u] = 0;
			}
		}
		else if (op == "r")
		{
			if (translate) translated += "initRandom();c[u] = srnd(c[0], c[1]);";
			initRandom();
			c[u] = srnd(c[DATA0], c[DATA1]);
		}
		else if (op == "{")
		{
			string tmpbuf = cbuf;
			if (translate) translated += "for (int i = 0; i < c[DATA0]; ++i){";
			int cc = 0;
			string ao = arg.substr(i + 1, 1);
			while (cc < c[DATA0])
			{
				pxtc(ao);
				translate = false;
				cc++;
			}
			i++;
			translate = true;
			cbuf = tmpbuf;
		}
		else if (op == "!")
		{
			if (translate) translated += "if (c[DATA0] == 1)";
			if (c[DATA0] == 1)
			{
				pxtc(arg.substr(i + 1, 1));
			}
			i++;
		}
		else if (op == "c")
		{
			if (translate) translated += "cout<<u;";
			cout << u;
		}
		else if (op == "C")
		{
			if (translate) translated += "if (mode==0)c[c[DATA0]] = c[u];else sc[c[DATA0]] = sc[u];";
			if (mode==0)
			c[c[DATA0]] = c[u];
			else
			sc[c[DATA0]] = sc[u];
		}
		else if (op == "G")
		{
			if (translate) translated += "//goto";
			i = c[u];
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
			if (translate) translated += "c[u] = (c[DATA0] * 1.0) / (c[DATA1] * 1.0);";
			c[u] = (c[DATA0] * 1.0) / (c[DATA1] * 1.0);
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
	debugrun = false;
}
catch (std::exception &e){
	cout<<"AN ERROR HAS OCCURED\nRESET...";
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
	string in;
	if (argc == 1)
		echo("APP CONSOLE INTERPRETER \nType 'help' to see the list of avalaible commands");
	if (argc > 1)
		{
			string runc = string(argv[0]);
			op(runc+".appl");
			cout<<"\nEND OF PROGRAM\nQuit? (y/n): ";
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
