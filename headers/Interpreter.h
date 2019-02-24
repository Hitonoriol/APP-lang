#include "DataCells.h"
class APPInterpreter {
public:
	bool ech = 0; //debug mode
	int dest = STARTPOINT; //destination cell
	int i = 0; //global execution iterator
	bool wgt = false; //goto flag for block ops
	bool grflag = false;
	int u = STARTPOINT;
	bool ide = false; //persistent memory flag
	int mode = 0; //string/int mode
	int lp = 0; //pointer for JMP and RET
	bool debugrun = false; //flag to silence output when saving/translating
	std::string cbuf; //APP code buffer
	bool goskip = false;
	std::string trace = "";
	bool nestflag = false;
	std::stack <int> gotoStack;
	APPDataCells cells;
	APPInterpreter();
	APPInterpreter(std::string program, int start, APPDataCells dump);
	void op(std::string arg, int startpos = 0);
	bool cmds(std::string arg);
	void smop(std::string arg);
	void reset();
	void pxtc(std::string arg);
	void echo(std::string arg);
	void initRandom();
	int srnd(int first, int last);
};
