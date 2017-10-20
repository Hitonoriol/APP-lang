#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cstring>
using namespace std;
double c[256];
string sc[256];
int ide = 0;
int u = 0;
int ech = 1;
int mode = 0;

void pxtc(string arg);
void initRandom()
{
	srand(time(NULL));
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

void param(int par, int state)
{
	int suc = 0;
	if (par == 666)
	{
		ide = state;
		suc = 1;
	}
	if (par == 0)
	{
		ech = state;
		suc = 1;
	}
	if (par == 1)
	{
		mode = state;
		suc = 1;
	}
	if (par == 2)
	{
		u = state;
		suc = 1;
	}
	if (suc == 1)
		cout << endl << "INTERPRETER PARAM " << par << " SET TO " << state <<
			endl;
	else
		cout << endl << "NO PARAM WITH THIS ID!" << endl;
}
bool cmds(string arg){
	if (arg=="cls"){
		system("cls");
		return true;
	}
	return false;
}
void op(string arg)
{
if(ide==0){
	int i = 0;
	int nn = 0;
	
	if (cmds(arg))
	return;
	nn = arg.size();
	string op;
	while (i < nn)
	{
		op = arg.substr(i, 1);
		if(op==" ")op="_";
		if (op == "a")
			c[u] = 0;
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
			char a;
			a = c[u];
			cout << a;
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
				cin >> c[u];
			}
			else
			{
				cout << "INPUT STRING: ";
				cin >> sc[u];
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
			if (c[u - 2] == c[u - 1])
			{
				c[u] = 1;
			}
			else
			{
				c[u] = 0;
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
		else if (op == "@")
		{
			int aa, bb;
			cout << endl << "PARAM ID: ";
			cin >> aa;
			cout << endl << "VALUE: ";
			cin >> bb;
			param(aa, bb);
		}
		else
		{
			if (ech == 1)
				cout << endl << "UNKNOWN OP: '" + op + "'" << endl;
		}
		i++;
	}
	}
	else{
	cout <<"OP: "<<spl(arg,0);
	}
}

void pxtc(string arg)
{
	op(arg);
}

main()
{
	string in;
	echo("APP CONSOLE INTERPRETER \n");
	while (true)
	{
		cout << endl << ">> ";
		getline(std::cin, in);
		op(in);
	}
}
