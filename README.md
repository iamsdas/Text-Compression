# Text-Compression
This is a simple text compression utility using the lzw algorithm in c++.

# About
This program takes in inputs for `input file name`, `output file name` and whether to `compress or decompress`. It compresses standard text files into compressed binaries and decompresses compressed binaries to standard text file. This is uses an optimized LZW algorithm which resets its dectionary on approaching its limit. The LZW compression works by reading a sequence of characters, grouping the characters `(8-bit)` into strings, and converting the strings into codes `(16-bit in this case)`. Because the codes take up less space than the strings they replace, we get compression.

# Setup
```
# Clone the repo:
https://github.com/iamsdas/Text-Compression.git
# Open directory:
cd Text-Compression
# Compile the files:
g++ *.cpp -o lzw
```

# Examples:
## Compression
```
./lzw
c
demo.txt
compressed.bin
```
## Decompression
```
./lzw
d
compressed.bin
decompressed.txt
```
After successfull compression/decompression it will show number of characters read and number of characters written
