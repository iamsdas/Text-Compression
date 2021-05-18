#include "LZW.hpp"

void LZW::buildEncoderTable()
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

void LZW::buildDecoderTable()
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

	buildEncoderTable();
	for (char c : input)
	{
		current_string = current_string + c;
		if (code_table.find(current_string) == code_table.end())
		{
			if (next_code == UINT16_MAX)
				buildEncoderTable();

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

	buildDecoderTable();
	for (uint16_t c : input)
	{
		if (string_table.find(c) == string_table.end())
			string_table[c] = prev + prev[0];

		decoded = decoded + string_table[c];
		if (!prev.empty())
		{
			if (next_code == UINT16_MAX)
				buildDecoderTable();

			string_table[next_code++] = prev + string_table[c][0];
		}
		prev = string_table[c];
	}
	return decoded;
}