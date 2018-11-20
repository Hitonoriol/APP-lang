class APPStringUtils {
public:
	static std::string str_prec(const double a_value, const int n = 0);
	static std::string gt();
	static int iconv(std::string Text);
	static std::string charc(char a);
	static std::vector <std::string> spl(std::string s, std::string delimiter);
	static std::string split(std::string s, std::string delimiter, int numr);
	static std::string replace(std::string str, const std::string& from, const std::string& to);
	static std::string sconv(int Number);
	static std::string joinFrom(char* arg[], int from, int argc);
};
