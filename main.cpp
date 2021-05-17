#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class LZW
{
private:
	unordered_map<string, uint16_t> code_table;
	unordered_map<uint16_t, string> string_table;
	uint16_t next_code;

public:
	void initEncoderTable();
	void initDecoderTable();
	vector<uint16_t> encode(string &);
	string decode(vector<uint16_t> &);
};

void LZW::initEncoderTable()
{
	code_table.clear();
	for (uint16_t i = 0; i < 256; i++)
	{
		string ch = "";
		ch += char(i);
		code_table[ch] = i;
	}
	next_code = 256;
}

void LZW::initDecoderTable()
{
	string_table.clear();
	for (int i = 0; i < 256; i++)
	{
		string ch = "";
		ch += char(i);
		string_table[i] = ch;
	}
	next_code = 256;
}

vector<uint16_t> LZW::encode(string &input)
{
	vector<uint16_t> encoded;
	string current_string = "";

	initEncoderTable();
	for (char c : input)
	{
		current_string = current_string + c;
		if (code_table.find(current_string) == code_table.end())
		{
			code_table[current_string] = next_code++;
			current_string.pop_back();
			encoded.push_back(code_table[current_string]);
			current_string = c;
		}
	}
	encoded.push_back(code_table[current_string]);
	return encoded;
}

string LZW::decode(vector<uint16_t> &input)
{
	string decoded = "";
	string prev = "";

	initDecoderTable();
	for (uint16_t c : input)
	{
		if (string_table.find(c) == string_table.end())
			string_table[c] = prev + prev[0];
		decoded = decoded + string_table[c];
		if (!prev.empty())
		{
			string_table[next_code++] = prev + string_table[c][0];
		}
		prev = string_table[c];
	}
	return decoded;
}

int main()
{
	ios::sync_with_stdio(false);

	LZW compressor;
	string input = "hello there how are you, I am fine over here";
	vector<uint16_t> encoded = compressor.encode(input);

	for (uint16_t code : (encoded))
		cout << ((code < 256) ? string(1, char(code)) : to_string(code));
	if (compressor.decode(encoded) == input)
		cout << "\nstring decoded successfully\n";
	return 0;
}