#include "headers/APP.h"

string in; //input buffer

void promtExit(bool force = false){
	if (force) exit(0);
	cout << "\nQuit? (y/n): ";
   		if (APPStringUtils::gt() == "y") {
      		exit(0);
    	}
}

int main(int argc, char * argv[]) {
	APPInterpreter app;
	APPFileUtils files;
  if (argc == 1)
    cout << "APP INTERPRETER || STARTPOINT: " << STARTPOINT << "\nReserved memory cells:\n[DATA0] and [DATA1] data registers\n[DATA2] logical cell (0/1)\n[DATA3] cycle counter\n[DATA4] JMP pointer\n[DATA5] floating point precision value\n[DATA6] copy buffer\n[DATA7] output buffer" << "\nType \"help\" to see the list of available commands\n";
  if (argc > 1) {
    string runc = string(argv[1]);
    if (runc == "--file"){
    cout << "Running user program...\n\n";
    app.op(APPFileUtils::readFile(argv[2]));
    promtExit(true);
	}
	if (runc == "--code"){
		string fp = APPStringUtils::joinFrom(argv,2,argc);
		app.op(fp);
		promtExit(true);
	}
	if (runc == "--help" || runc == "--usage"){
		cout<<"Usage: app [--file <filename.appl>] or [--code <APP code>]"<<endl;
		promtExit(true);
	}
  }
  while (true) {
    cout << endl << ">> ";
    getline(std::cin, in );
	if (in == "exit") promtExit();
	else
    app.op(in);
  }
}
