#include "headers/APP.h"

APPInterpreter::APPInterpreter()
{
    reset();
}

APPInterpreter::APPInterpreter(string program, int start, APPDataCells dump)
{
    cbuf = program;
    cells = dump;
    op(program, start);
    delete this;
}

int APPInterpreter::alias_get(std::string var)
{
    if (alias_exists(var))
        return this->var[var];
    else
        return -1;
}

bool APPInterpreter::alias_exists(std::string arg)
{
    if (this->var.find(arg) == this->var.end())
        return false;
    else
        return true;
}

void APPInterpreter::alias_set(std::string var, int c)
{
    if (alias_exists(var))
        this->var.erase(var);
    this->var.insert(std::make_pair(var, c));
}

void APPInterpreter::op(string arg, int startpos, int len)
{
    int echof = 0;
    i = startpos;
    int nn = 0;
    if (cmds(arg))
        return;
    if (len == -1)
        nn = arg.size();
    else
        nn = i + len;
    string op;
    string scmd = "";
    cbuf = arg;
    string smbuf = "";
    bool iscmd = false;
    bool isms = false;
    try
    {
        while (i < nn)
        {
            trace += arg.substr(i, 1);
            op = arg.substr(i, 1);
            if (op == "\\")
                iscmd = !iscmd;

            if (op == "[")
                isms = true;

            if (op == "]")
            {
                isms = false;
                smop(smbuf);
                smbuf = "";
                i++;
                continue;
            }
            if (isms && op != "[" && op != "]")
                smbuf += op;
            if (!iscmd && scmd != "")
            {
                cmds(scmd);
                scmd = "";
            }
            if (iscmd && op != "\\")
            {
                scmd += op;
            }
            if (!iscmd && !isms)
            {
                if (op == "\"")
                {
                    if (echof == 1)
                    {
                        echof = 0;
                    }
                    else
                    {
                        echof = 1;
                    }
                }

                if (echof == 1 && op != "\"")
                {
                    cells.ScellSet(cells.SgetCell(u)+op,u);
                }
                else
                {
                    if (op == "a")  	//0:Int[current] = 0 1:String[current] = ""
                    {
                        if (mode == 0)
                        {
                            cells.cellSet(0, u);
                        }
                        else
                        {
                            cells.ScellSet("",u);
                        }
                    }
                    else if (op == "p")  	//Int[current]++
                    {
                        cells.cellSet(cells.getCell(u) + 1, u);
                    }
                    else if (op == "j")  	//jump to memory cell with position Int[DATA4]
                    {
                        lp = u;
                        u = (int) cells.getCell(DATA4);
                    }
                    else if (op == "R")  	//return from memory jump
                    {
                        u = lp;
                    }
                    else if (op == "m")  	//Int[current]--
                    {
                        cells.cellSet(cells.getCell(u) - 1, u);
                    }
                    else if (op == "w")  	//0: write int to output buffer 1: same with strings
                    {
                        if (mode == 0)
                        {
                            cells.ScellSet(cells.SgetCell(DATA7) + APPStringUtils::str_prec(cells.getCell(u),cells.getCell(DATA5)), DATA7);
                        }
                        else
                        {
                            cells.ScellSet(cells.SgetCell(DATA7) + cells.SgetCell(u), DATA7);
                        }
                    }
                    else if (op == "W")  	//write output buffer to string
                    {
                        cout << cells.SgetCell(DATA7);
                        cells.ScellSet("", DATA7);
                    }
                    else if (op == "P")  	// "" --> String[DATA7](clear the output buffer)
                    {
                        cells.ScellSet("", DATA7);
                    }
                    else if (op == "_")  	//append line break --> String[DATA7](output buffer)
                    {
                        cells.ScellSet(cells.SgetCell(DATA7) + "\n", DATA7);
                    }
                    else if (op == ">")  	//next memory cell
                    {
                        u++;
                    }
                    else if (op == "<" && u > 0)  	//previous memory cell
                    {
                        u--;
                    }
                    else if (op == ".")  	//char(Int[current]) --> append to String[current]
                    {
                        int aa = cells.c[u];
                        char t = aa;
                        string a = APPStringUtils::charc(t);
                        cells.ScellSet(cells.SgetCell(u) + a,u);
                    }
                    else if (op == "v")  	//Int[current]+=5
                    {
                        if (mode == 0)
                        {
                            cells.cellSet(cells.getCell(u) + 5,u);
                        }
                        else
                        {
                            cells.cellSet(cells.getCell(u) - 5,u);
                        }
                    }
                    else if (op == "x")  	//Int[current]+=10
                    {
                        if (mode == 0)
                        {
                            cells.cellSet(cells.getCell(u) + 10,u);
                        }
                        else
                        {
                            cells.cellSet(cells.getCell(u) - 10,u);
                        }
                    }
                    else if (op == "@")
                    {
                        if (cells.getCell(u) == 1)
                            cells.cellSet(0, u);
                        else
                            cells.cellSet(1, u);
                    }
                    else if (op == "i")  	//0:get value from keyboard and put into Int[current] 1: same with strings
                    {
                        if (mode == 0)
                        {
                            if (!debugrun)
                            {
                                string t;
                                getline(std::cin, t);
                                cells.cellSet(atof(t.c_str()),u);
                            }
                        }
                        else
                        {
                            if (!debugrun)
                                cells.ScellSet(APPStringUtils::gt(),u);
                        }
                    }
                    else if (op == "+")  	//Int[DATA0] + Int[DATA1] --> Int[current] or concat two strings
                    {
                        if (mode == 0)
                            cells.cellSet(cells.getCell(cells.DATA0) + cells.getCell(cells.DATA1),u);
                        else
                        {
                            cells.ScellSet(cells.SgetCell(cells.DATA0) + cells.SgetCell(cells.DATA1),u);
                        }
                    }
                    else if (op == "-")  	//Int[DATA0] - Int[DATA1] --> Int[current]
                    {
                        cells.cellSet(cells.getCell(cells.DATA0) - cells.getCell(cells.DATA1),u);
                    }
                    else if (op == "?")  	//0: if Int[DATA0] == Int[DATA1] --> Int[DATA2]=1 1:same, but with strings
                    {
                        if (mode == 0)
                        {
                            if (cells.getCell(cells.DATA0) == cells.getCell(cells.DATA1))
                            {
                                cells.cellSet(1, cells.DATA2);
                            }
                            else
                            {
                                cells.cellSet(0, cells.DATA2);
                            }
                        }
                        else
                        {
                            if (cells.SgetCell(cells.DATA0) == cells.SgetCell(cells.DATA1))
                            {
                                cells.cellSet(1, cells.DATA2);
                            }
                            else
                            {
                                cells.cellSet(0, cells.DATA2);
                            }
                        }
                    }
                    else if (op == "g")  	//if Int[DATA0] > Int[DATA1] --> Int[DATA2]=1
                    {
                        if (cells.getCell(cells.DATA0) > cells.getCell(cells.DATA1))
                        {
                            cells.cellSet(1, cells.DATA2);
                        }
                        else
                        {
                            cells.cellSet(0, cells.DATA2);
                        }
                    }
                    else if (op == "s")  	//if Int[DATA0] < Int[DATA1] --> Int[DATA2]=1
                    {
                        if (cells.getCell(cells.DATA0) < cells.getCell(cells.DATA1))
                        {
                            cells.cellSet(1, cells.DATA2);
                        }
                        else
                        {
                            cells.cellSet(0, cells.DATA2);
                        }
                    }
                    else if (op == "r")  	//random between Int[DATA0] and Int[DATA1] --> Int[current]
                    {
                        initRandom();
                        cells.cellSet(srnd(cells.getCell(cells.DATA0), cells.getCell(cells.DATA1)),u);
                    }
                    else if (op == "A")  	//substring from String[DATA0] starting on Int[DATA0] with length Int[DATA1] --> String[dest]
                    {
                        cells.ScellSet(cells.SgetCell(u)+cells.SgetCell(cells.DATA0).substr(cells.getCell(cells.DATA0), cells.getCell(cells.DATA1)),dest);
                    }
                    else if (op == "b")  	//String[current].length() --> Int[current]
                    {
                        cells.cellSet(cells.SgetCell(u).length(),u);
                    }
                    else if (op == "}" || op == ";") {}
                    else if (op == "{")  	//executes everything between {...} Int[DATA3] times
                    {
                        nestflag = true;
                        bool lastide = ide;
                        ide = true;
                        int lastpos = i;
                        string tmpbuf = cbuf;
                        int cc = 0, kk = 0;
                        string ao;
                        while (arg.substr(lastpos+kk, 1) != "}")
                            kk++;

                        int spos = i+1;
                        while (cc < (int) cells.getCell(cells.DATA3))
                        {
                            this->op(arg, spos, kk-1);
                            cc++;
                        }

                        i = spos + kk-1;
                        wgt = false;
                        cbuf = tmpbuf;
                        ide = lastide;
                        nestflag = false;
                    }
                    else if (op == "!")  	//if Int[DATA2]==1 executes everything between !...;
                    {
                        nestflag = true;
                        bool lastide = ide;
                        ide = true;
                        int lastpos = i;
                        string tmpbuf = cbuf;
                        int kk = 0;

                        while (arg.substr(lastpos + kk, 1) != ";")
                            kk++;

                        if (cells.getCell(cells.DATA2) == 1)
                        {
                            this->op(arg, lastpos + 1, kk-1);

                            i = lastpos + kk;
                            cbuf = tmpbuf;
                            ide = lastide;
                        }
                        else
                        {
                            i = lastpos + kk;
                            ide = lastide;
                        }
                        nestflag = false;
                    }
                    else if (op == "c")  	//Current memory position
                    {
                        cells.cellSet(u, u);
                    }
                    else if (op == "C")  	//0: Int[Int[DATA6]] <-- Int[current] 1:same thing, but w\ strings
                    {
                        if (mode == 0)
                            cells.cellSet(cells.getCell(u), (int) cells.getCell(DATA6));
                        else
                            cells.ScellSet(cells.SgetCell(u), (int) cells.getCell(DATA6));
                    }
                    else if (op == "S")  	//mode switch
                    {
                        if (mode == 0)
                            mode = 1;
                        else
                            mode = 0;
                        echo("SWITCHED TO MODE "+mode);
                    }
                    else if (op == "/")  	//Int[DATA0] / Int[DATA1] --> Int[current]
                    {
                        cells.cellSet(cells.getCell(cells.DATA0) / cells.getCell(cells.DATA1),u);
                    }
                    else if (op == "*")  	//Int[DATA0] * Int[DATA1] --> Int[current]
                    {
                        cells.cellSet(cells.getCell(cells.DATA0) * cells.getCell(cells.DATA1),u);
                    }
                    else if (op == "&")  	//0: Int[current] --> String[current] 1: String[current] --> Int[current]
                    {
                        if (mode == 0)
                            cells.ScellSet(APPStringUtils::str_prec(cells.getCell(u)),u);
                        else
                            cells.cellSet(atof(cells.SgetCell(u).c_str()),u);
                    }
                    else if (op == "P")  	//write String[current] to file String[DATA0]
                    {
                        APPFileUtils::writeFile(cells.SgetCell(cells.DATA0), cells.SgetCell(u));
                    }
                    else if (op == "l")  	//read file String[DATA0] --> String[current]
                    {
                        cells.ScellSet(APPFileUtils::readFile(cells.SgetCell(cells.DATA0)),u);
                    }
                    else if (op == "q")     //search for String[DATA1] in String[DATA0] --> Int[dest]
                    {
                        cells.cellSet(cells.SgetCell(cells.DATA0).find(cells.SgetCell(cells.DATA1)),dest);
                    }
                    else if (op == "Q")     //erase character from String[DATA0] with position Int[DATA0], length Int[DATA1] --> String[dest]
                    {
                        cells.ScellSet(cells.SgetCell(cells.DATA0).erase(cells.getCell(cells.DATA0), cells.getCell(cells.DATA1)),dest);
                    }
                    else if (op == "e")     //execute APP code from String[Int[DATA0]]
                    {
                        int lastpos = i;
                        string rbf = cells.SgetCell(cells.getCell(cells.DATA0));
                        bool tide = ide;
                        ide = true;
                        string tbf = cbuf;
                        pxtc(rbf);
                        cbuf = tbf;
                        i = lastpos;
                        ide = tide;
                    }
                    else if (op=="D")     //set destination to current cell
                    {
                        dest = u;
                    }
                    else if (op=="z")  	//push current cell to stack
                    {
                        if (mode == 0)
                            cells.s.push(cells.getCell(u));
                        else
                        {
                            echo ("Pushing "+cells.SgetCell(u)+" to stack");
                            cells.ss.push(cells.SgetCell(u));
                        }
                    }
                    else if (op == "Z") 	//put the top stack value to cell
                    {
                        if (mode==0)
                        {
                            cells.cellSet(cells.s.top(),u);
                            cells.s.pop();
                        }
                        else
                        {
                            cells.ScellSet(cells.SgetCell(u)+cells.ss.top(),u);
                            cells.ss.pop();
                        }
                    }
                    else if (op == "0") 	//set DATA0 to current cell
                    {
                        cells.DATA0 = u;
                    }
                    else if (op == "1") 	//set DATA1 to curent cell
                    {
                        cells.DATA1 = u;
                    }
                    else if (op == "2") 	//set DATA2 to curent cell
                    {
                        cells.DATA2 = u;
                    }
                    else if (op == "3") 	//set DATA3 to curent cell
                    {
                        cells.DATA3 = u;
                    }
                    else if (op == "E")       //set current cell to stack size
                    {
                        if (mode == 0)
                            cells.cellSet(cells.s.size(),u);
                        else
                            cells.cellSet(cells.ss.size(),u);
                    }
                    else
                    {
                        echo("UNKNOWN OP: '" + op + "' AT "+APPStringUtils::str_prec(i));
                    }
                }
            }
            i++;
        }
        if (!ide)
            reset();
        debugrun = false;
        trace += "\n";
    }
    catch (std::exception & e)
    {
        cout << "\nAN ERROR HAS OCCURED\n" << e.what() << "\nNEAR: " << trace << endl << "\nRESETTING...\n";
        reset();
        return;
    }
}

bool APPInterpreter::cmds(string arg)
{
    string bufa = arg;
    arg = APPStringUtils::split(arg, " ", 0);
    if (arg == "status")
    {
        cout << "Mode: " << mode << "\nCurrent memory cell: " << u << "\nPersistent memory: " << ide;
        return true;
    }
    if (arg == "reset")
    {
        reset();
        return true;
    }
    if (arg == "rb")
    {
        op(cbuf);
        return true;
    }
    if (arg == "pb")
    {
        cout << cbuf;
        return true;
    }
    if (arg == "save")
    {
        string fn = APPStringUtils::split(bufa, " ", 1);
        fn += ".appl";
        APPFileUtils::writeFile(fn, cbuf);
        cout << "Saved current command buffer to " + fn + ".";
        return true;
    }
    if (arg == "load")
    {
        string fname = APPStringUtils::split(bufa, " ", 1) + ".appl";
        cbuf = APPFileUtils::readFile(fname);
        cout << "Loaded " + fname + " to the command buffer.";
        return true;
    }
    if (arg == "run")
    {
        string fname = APPStringUtils::split(bufa, " ", 1) + ".appl";
        cout << "Running " << fname << endl;
        cbuf = APPFileUtils::readFile(fname);
        op(cbuf);
        cout << "\nEnd of program.";
        return true;
    }
    if (arg == "help")
    {
        cout << "status - info\nreset - reset the interpreter\nrb - run commands from command buffer (last used)\npb - print command buffer contents\nsave <filename> - save command buffer to file\nload <filename> - load file to command buffer\nrun <filename> - run file\n";
    }

    return false;
}

void APPInterpreter::smop(string arg)
{
    string ni = arg.substr(0, 1);
    string cmd = arg;
    if (ni == "#")
    {
        if (!goskip)
        {
            string lbl = ":" + arg.substr(1);
            int relpos = arg.substr(1).length();
            gotoStack.push(i);
            i = cbuf.find(lbl) + relpos+1;

            wgt = true;
            echo("Going to "+lbl+" raw: "+cbuf.substr(i));
        }
        else
            goskip = false;
    }
    if ((cmd == "ret" || cmd == "return") && gotoStack.size() > 0)
    {
        i = gotoStack.top();
        gotoStack.pop();
        wgt = true;
    }
    if (cmd == "mode_str")
        mode = 1;
    if (cmd == "mode_num")
        mode = 0;
    if (ni == ":") {/*Just so you know this char is in use*/}
    if (ni == "_") {/*Just so you know this char is in use[2]*/}

    if (ni == "*")  //[*5=source]
    {
        vector<string> bff = APPStringUtils::spl(arg.substr(1),"=");
        std::string value = bff[1];
        if (bff[0] == "c")
            bff[0] = APPStringUtils::str_prec(u);
        int pos = atoi(bff[0].c_str());
        alias_set(value, pos);
    }

    if (ni == "$")   //$25=13 <--set 25th cell to 13 || $25=$13 <--set 25th cell to 13th value || $25=%appwW <-- exec operators in 25th cell
    {
        vector<string> bff = APPStringUtils::spl(arg.substr(1),"=");
        string fch = bff[1].substr(0,1);
        if (bff[0]=="c")
            bff[0] = APPStringUtils::str_prec(u);
        if (alias_exists(bff[0]))
            bff[0] = std::to_string(alias_get(bff[0]));
        if (bff[1].substr(1)=="c")
            bff[1]=fch+APPStringUtils::str_prec(u);
        if (fch == "$") 	//check:xvwWP_W[$0=$8][$0=%PwW]
        {
            std::string cellnum = bff[1].substr(1);
            if (alias_exists(cellnum))
                cellnum = std::to_string(alias_get(cellnum));
            int value = atoi(cellnum.c_str()), pos = atoi(bff[0].c_str());
            if (mode == 0)
            {
                cells.cellSet(cells.getCell(value), pos);
            }
            else
            {
                cells.ScellSet(cells.SgetCell(value), pos);
            }
        }
        else if (fch == "#")
        {
            int ti = i, tu = u;
            bool tide = ide;
            ide = true;
            if (alias_exists(bff[0]))
                bff[0] = std::to_string(alias_get(bff[0]));
            u = atoi(bff[0].c_str());
            string rbg = cells.SgetCell(atoi(bff[1].substr(1).c_str()));
            string tbf = cbuf;
            pxtc(rbg);
            cbuf = tbf;
            ide = tide;
            u = tu;
            i = ti;
        }
        else if (fch == "%")
        {
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

        }
        else
            cells.cellSet(atoi(bff[1].c_str()), atoi(bff[0].c_str()));
    }
    if (ni == ">")
    {
        std::string cellnum = arg.substr(1);
        if (alias_exists(cellnum))
            cellnum = std::to_string(alias_get(cellnum));
        u = APPStringUtils::iconv(cellnum);
    }
    if (ni == "!")
    {
        cells.cellSet(atof(arg.substr(1).c_str()),u);
    }
    if (ni == "e")
        goskip = true;
}

void APPInterpreter::pxtc(string arg)
{
    op(arg);
}

void APPInterpreter::reset()
{
    mode = 0;
    u = STARTPOINT;
    cells.c.clear();
    cells.sc.clear();
    for (int i = 0; i < 4; ++i)
        cells.c.push_back(0);
    cells.c.push_back(DATA4);
    cells.c.push_back(3);
    return;
}

void APPInterpreter::echo(string arg)
{
    if (ech)
        cout << arg << endl;
}


void APPInterpreter::initRandom()
{
    srand(time(NULL));
}

int APPInterpreter::srnd(int first, int last)
{
    int val = first + rand() % last;
    return val;
}
