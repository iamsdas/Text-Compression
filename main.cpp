#include <iostream>
#include <fstream>
#include <sstream>
#include "LZW.hpp"

int main()
{
	ios::sync_with_stdio(false);

	LZW lzw;
	char flag;
	string input_fname, output_fname;
	vector<uint16_t> encoded;
	fstream fio;

	cout << "Do you wish to compress (c) or decompress (d)? [c/d]: ";
	cin >> flag;
	cout << "Enter input file name: ";
	cin >> input_fname;
	cout << "Enter output file name: ";
	cin >> output_fname;

	switch (flag)
	{
	case 'c':
	{
		string input;
		vector<uint16_t> output;
		stringstream buffer;

		fio.open(input_fname, ios::in);
		buffer << fio.rdbuf();
		input = buffer.str();
		fio.close();

		output = lzw.encode(input);
		fio.open(output_fname, ios::out | ios::binary | ios::trunc);
		fio.write((char *)(&output[0]), output.size() * sizeof(uint16_t));
		fio.close();

		cout << input.length() << " characters read\n";
		cout << output.size() << " characters written\n";
		cout << "Successfully compressed\n";
		break;
	}
	case 'd':
	{
		vector<uint16_t> input;
		uint16_t tmp;
		string output;

		fio.open(input_fname, ios::in | ios::binary);
		while (fio.read((char *)&tmp, sizeof(tmp)))
			input.push_back(tmp);
		fio.close();

		output = lzw.decode(input);
		fio.open(output_fname, ios::out | ios::trunc);
		fio << output;
		fio.close();

		cout << input.size() << " characters read\n";
		cout << output.length() << " characters written\n";
		cout << "Successfully decompressed\n";
		break;
	}
	default:
		break;
	}

	return 0;
}