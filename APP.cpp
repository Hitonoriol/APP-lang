#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#define BUFCAP 4096
using namespace std;
int c[BUFCAP];
string sc[BUFCAP];
int ide = 0;
int u = 0;
int ech = 0;
int mode = 0;
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
		return true;
	}
	if (arg == "rb"){
		op(cbuf);
		return true;
	}
	if (arg=="cls"){
		system("cls");
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
		cout<<"INTERPRETER COMMANDS:\n**********\nech - debug mode on/of\nrb - run commands from command buffer (last used)\nsave <filename> - save command buffer to file\nload <filename> - load file to command buffer\nrun <filename> - run file\ncls - clear screen\n\nDou you want to see operators list? (y/n): ";	
		if (gt()=="y"){
		cout<<"\n**********\nOPERATORS:\n**********\n";
		cout<<"a\nSets current int cell to 0 if MODE is 0 and if MODE is 1, clears current string cell\n\np\nIncrements current cell\n\nm\nDecrements current cell\n\nw\nWrites current int cell value if current mode is 0 and writes current string cell value if mode is 1\n\n_\nEchoes end of line\n\n>\nNext cell\n\n<\nPrevious cell\n\n.\nPuts a symbol with code from current int cell to current string cell\n\nv\nAdds 5 to current cell\n\nx\nAdds 10 to current cell\n\ni\nIf MODE is 0, gets int from keyboard to int cell, if MODE is 1, gets string from keyboard.\n\n+\nSets value of current cell to sum of two previous cells (cell[current] = cell[current-2] + cell[current-1])\n\n-\nSets value of current cell to cell[current-2] - cell[current-1]\n\n?\nIf cell[current-2] == cell[current-1], sets current cell to 1, otherwise, to 0.\n\n g\nIf cell[current-2] > cell[current-1], sets current cell to 1, otherwise, to 0.\n\n s\nIf cell[current-2] < cell[current-1], sets current cell to 1, otherwise, to 0.\n\n r\nSets current cell value to random int in range min = cell[current-2] & max = cell[current-1]\n\n{\nRepeats 1 operator after it cell[current-1] times\n\n!\nExecutes next operator if cell[current-1] == 1\n\nc\nPrints current cell number\n\nS\nSwitches MODE between 0 (int) and 1 (string)\n\n/\nMakes cell[current] = cell[current-2] / cell[current-1]\n\nR\nMakes cell[current] = cell[current-2] / cell[current-1]\n";
	}
	}
	return false;
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
	bool iscmd = false;
	try{
	while (i < nn){
		op = arg.substr(i, 1);
		if (op == "\\"){
			if (iscmd) iscmd = false;
			else iscmd = true;
		}
		if (!iscmd && scmd!=""){
			cmds(scmd);
			scmd = "";
		}
		if (iscmd && op!="\\"){
			scmd+=op;
		}else{
		if (op == "\"")
			if (echof == 1)
			echof = 0;
			else echof = 1;
			if (echof==1 && op!="\"")
			sc[u]+=op;
			else{
		if (op == "a"){
			if (mode == 0)
				c[u] = 0;
			else
			sc[u] = "";
		}
		else if (op == "p")
			c[u]++;
		else if (op == "m")
			c[u]--;
		else if (op == "w")
			if (mode == 0)
			{
				cout << c[u];
			}
			else
			{
				cout << sc[u];
			}
		else if (op == "_")
			cout << endl;
		else if (op == ">" && u < 255)
			u++;
		else if (op == "<" && u > 0)
			u--;
		else if (op == ".")
		{
			int aa = c[u];
			char t = aa;
			string a = charc(t);
			sc[u]+=a;
		}
		else if (op == "v")
		{
			c[u] += 5;
		}
		else if (op == "x")
		{
			c[u] += 10;
		}
		else if (op == "i")
		{
			if (mode == 0)
			{
				cout << "INPUT INT/CHAR: ";
				c[u]=iconv(gt());
			}
			else
			{
				cout << "INPUT STRING: ";
				sc[u] = gt();
			}
		}
		else if (op == "+")
		{
			c[u] = c[u - 2] + c[u - 1];
		}
		else if (op == "-")
		{
			c[u] = c[u - 2] - c[u - 1];
		}
		else if (op == "?")
		{
			if (mode==0){
			if (c[u - 2] == c[u - 1])
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
			if (sc[u - 2] == sc[u - 1])
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
			if (c[u - 2] > c[u - 1])
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
			if (c[u - 2] < c[u - 1])
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
			initRandom();
			c[u] = srnd(c[u - 2], c[u - 1]);
		}
		else if (op == "{")
		{
			int cc = 0;
			string ao = arg.substr(i + 1, 1);
			while (cc < c[u - 1])
			{
				pxtc(ao);
				cc++;
			}
			i++;
		}
		else if (op == "!")
		{
			if (c[u - 1] == 1)
			{
				pxtc(arg.substr(i + 1, 1));
			}
			i++;
		}
		else if (op == "c")
		{
			cout << u;
		}
		else if (op == "C")
		{
			if (mode==0)
			c[c[u-1]] = c[u];
			else
			sc[c[u-1]] = sc[u];
		}
		else if (op == "G")
		{
			i = c[u];
		}
		else if (op == "S")
		{
			if (mode == 0)
				mode = 1;
			else
				mode = 0;
			if (ech == 1)
				cout << endl << "SWITCHED TO MODE " << mode << endl;
		}
		else if (op == "/")
		{
			c[u] = (c[u - 2] * 1.0) / (c[u - 1] * 1.0);
		}
		else if (op == "R")
		{
			sc[u] = arg.substr(i + 1, c[u - 1]);
			i += c[u - 1];
		}
		else
		{
			if (ech == 1)
				cout << endl << "UNKNOWN OP: '" + op + "'" << endl;
		}
	}
	}
		i++;
	}
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
