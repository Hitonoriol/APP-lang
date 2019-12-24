class APPDataCells {
public:
	std::vector <double> c;
	std::vector <std::string> sc;
	std::stack <double> s;
	std::stack <std::string> ss;
	int DATA0;
	int DATA1;
	int DATA2;
	int DATA3;
	APPDataCells(std::vector <double> oldc, std::vector <std::string> oldsc, std::stack <double> olds, std::stack <std::string> oldss, int d0, int d1, int d2, int d3) {
		c = oldc;
		sc = oldsc;
		s = olds;
		ss = oldss;
		DATA0 = d0;
		DATA1 = d1;
		DATA2 = d2;
		DATA3 = d3;
	}

	APPDataCells(){
		reset();
	}

	void reset();
	double getCell(int pos);
	void cellSet(double value, int pos);
	std::string SgetCell(int pos);
	void ScellSet(std::string value, int pos);
	void ScellContSet(std::string val, int start, int end);
};
