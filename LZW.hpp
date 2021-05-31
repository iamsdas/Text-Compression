/**
 * LZW.hpp
 * This is a header file containing the definitions for the LZW class and its functions.
 */
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// The LZW encoder/decoder class
class LZW
{
private:
	unordered_map<string, uint16_t> code_table;
	unordered_map<uint16_t, string> string_table;
	uint16_t next_code;

public:
	void buildEncoderTable();
	void buildDecoderTable();
	vector<uint16_t> encode(string &);
	string decode(vector<uint16_t> &);
};
