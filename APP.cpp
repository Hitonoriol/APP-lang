#include "headers/APP.h"

string in;

void promptExit(bool force = false){
	if (force) exit(0);
	//cout << "\nPress <Enter> to quit.";
    APPStringUtils::gt();
    exit(0);
}

int main(int argc, char * argv[]) {
    APPInterpreter app;

    if (argc == 1)
        cout << "APP INTERPRETER || STARTPOINT: " << STARTPOINT << "\nReserved memory cells:\n[DATA0] and [DATA1] data registers\n[DATA2] logical cell (0/1)\n[DATA3] cycle counter\n[DATA4] JMP pointer\n[DATA5] floating point precision value\n[DATA6] copy buffer\n[DATA7] output buffer" << "\nType \"help\" to see the list of available commands\n";
    if (argc > 1) {
        string runc = string(argv[1]);
        app.op(APPFileUtils::readFile(argv[1]));
        promptExit();
  }

  while (true) {
    cout << endl << ">> ";
    getline(std::cin, in );
	if (in == "exit")
        promptExit();
	else
        app.op(in);
  }
}
