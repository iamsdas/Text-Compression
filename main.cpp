#include <iostream>
#include "LZW.hpp"

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