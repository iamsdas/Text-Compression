#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

vector<uint16_t> compress(string input)
{
	vector<uint16_t> res;
	unordered_map<string, uint16_t> encoding;
	uint16_t next_code = 256;
	string current_string = "";

	for (uint16_t i = 0; i < 256; i++)
	{
		string ch = "";
		ch += char(i);
		encoding[ch] = i;
	}

	for (char c : input)
	{
		current_string = current_string + c;
		if (encoding.find(current_string) == encoding.end())
		{
			encoding[current_string] = next_code++;
			current_string.pop_back();
			res.push_back(encoding[current_string]);
			current_string = c;
		}
	}
	res.push_back(encoding[current_string]);

	return res;
}

string decompress(vector<uint16_t> input)
{
	string res;
	unordered_map<uint16_t, string> encoding;
	uint16_t next_code = 256;
	string prev = "";

	for (int i = 0; i < 256; i++)
	{
		string ch = "";
		ch += char(i);
		encoding[i] = ch;
	}

	for (uint16_t c : input)
	{
		if (encoding.find(c) == encoding.end())
			encoding[c] = prev + prev[0];
		res = res + encoding[c];
		if (!prev.empty())
		{
			encoding[next_code++] = prev + encoding[c][0];
		}
		prev = encoding[c];
	}

	return res;
}

int main()
{
	string in;
	in = "hello there how are you, I am fine over here";
	for (uint16_t code : compress(in))
		cout << ((code < 256) ? string(1, char(code)) : to_string(code));
	return 0;
}