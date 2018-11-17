#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <stack> 
#include <thread>
#include <fstream>
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
# define DATA4 4
# define DATA5 5
# define DATA6 6
# define DATA7 7
# define STARTPOINT 8
using namespace std;

class APPFileUtils {
public:
	static bool writeFile(string filename, string arg);
	static string readFile(string path);
};

class APPStringUtils {
public:
	static string str_prec(const double a_value, const int n = 0);
	static string gt();
	static int iconv(string Text);
	static string charc(char a);
	static vector <string> spl(string s, string delimiter);
	static string split(string s, string delimiter, int numr);
	static string replace(string str, const string& from, const string& to);
	static string sconv(int Number);
	static string joinFrom(char* arg[], int from, int argc);
};

class APPDump {
public:
	vector <double> c;
	vector <string> sc;
	stack <double> s;
	stack <string> ss;
	int dc[4];
	APPDump(vector <double> oldc, vector <string> oldsc, stack <double> olds, stack <string> oldss, int d0, int d1, int d2, int d3) {
		c = oldc;
		sc = oldsc;
		s = olds;
		ss = oldss;
		dc[0] = d0;
		dc[1] = d1;
		dc[2] = d2;
		dc[3] = d3;
	}
};

class APPGraphUtils {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	thread graph;
	
	void graphRender();
	void graphSetColor(int r, int g, int b);
	void graphCls();
	void graphDrawPlot(int x, int y);
	void graphDrawLine(int x1, int y1, int x2, int y2);
	void graphStop();
	void SDLpollEvents();
	void SDLsandbox();
};
