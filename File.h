#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <vector>

using namespace std;

/****************************************************************
Parses text based on user defined delimiter and returns parsed
content through a vector
*****************************************************************/
class Parser {
private:
	std::string text;
	const char* delimiter;
public:
	std::vector<int> parse(std::string t, const char* d);
	const char* getDelimiter();
	void setDelimiter(const char*);
};

// parses text based on chosen delimiter
std::vector<int> Parser::parse(std::string t, const char* d) {
	std::vector<int> vlist;
	text = t;
	delimiter = d;
	std::string temp;
	// find delimiter in text
	int start = 0;
	int index = text.find(*delimiter);
	while (index != std::string::npos) {
		// put value between delimiter into temp
		temp.assign(text, start, index - start);
		// push number into vector
		vlist.push_back(stoi(temp));
		// find next delimiter
		start = index + 1;
		index = text.find(*delimiter, start);
	}
	return vlist;
}

// returns const char* delimiter
const char* Parser::getDelimiter() {
	return delimiter;
}

// sets delimiter
void Parser::setDelimiter(const char* d) {
	delimiter = d;
}



/****************************************************************
Object performs file operations
*****************************************************************/
class File {
protected:
	std::string directory;
public:
	File();
	File(std::string);
	std::string getDirectory();
	void setDirectory(std::string);
	void writeFile();
	bool readFile(std::string&);
	bool readFile(std::vector<int>&, const char*);
};


File::File() {
	directory = "Encrypted.txt";
}

File::File(std::string s) {
	directory = s;
}

// returns file directory
std::string File::getDirectory() {
	return directory;
}

// sets file directory
void File::setDirectory(std::string s) {
	directory = s;
}

// write to file
void File::writeFile() {
	std::ofstream myFile;
	myFile.open(directory);
	if (myFile.is_open()) {
		std::string text;
		getline(std::cin, text);
		myFile << text;
	}
	else {
		throw "No File to write to";
	}
	myFile.close();
}

// read from to string variable without delimiter
bool File::readFile(std::string& infile) {
	std::ifstream File;
	File.open(infile);
	getline(File, infile);
	if (File.eof()) {
		return true;
	}
	else
		return false;
}

// read from file
bool File::readFile(std::vector<int>& list, const char* delimiter) {

	std::ifstream myFile;
	myFile.open(directory);

	// open file
	if (!myFile.is_open()) {
		std::cout << "file not open" << std::endl;
		system("pause");
	}

	while (!myFile.eof()) {
		// get text from file
		std::string buffer = "";
		getline(myFile, buffer);
		// parse text into vector
		Parser decode;
		std::vector<int> newList = decode.parse(buffer, delimiter);
		// place vector into list passed into function
		list.insert(list.end(), newList.begin(), newList.end());
		// clear newList
		newList.clear();
	}
	if (myFile.eof()) {
		myFile.close();
		return true;
	}
	else {
		myFile.close();
		return false;
	}
}



/****************************************************************
Derived from File class.
Performs binary file operations
*****************************************************************/
class BinaryFiles : public File {
private:
	unsigned char* text;
public:
	BinaryFiles(std::string);
	void writeBFile();
	unsigned char* readBFile();
	unsigned char* getText();
	std::vector<std::bitset<8>> readBFilebit();
};

BinaryFiles::BinaryFiles(std::string d) : File(d) {}

// writes to binary file
void BinaryFiles::writeBFile() {
	std::string text;
	getline(cin, text);
	ofstream bout(directory, ios::binary);
	bout << text;
	bout.close();
}

// reads from binary file
// returns text as unsigned char*
unsigned char* BinaryFiles::readBFile() {
	streampos size;
	unsigned char* memblock;
	
	std::ifstream file(directory, ios::in | ios::binary);
	
	if (file.is_open()) {
		// go to end of file
		file.seekg(0, ios::end);
		// size is position of end of file
		size = file.tellg();
		// point to charecter away of size, size
		memblock = new unsigned char[size];
		// to beginning
		file.seekg(0, ios::beg);
		// read from begining to size(end) into memblock
		file.read((char*)memblock, size);
		// output memblock
		text = memblock;
		file.close();
		delete[] memblock;
		return text;
	}
}

// returns text from binary file
unsigned char* BinaryFiles::getText() {
	return text;
}

// reads each charected in binary file into bitsets
std::vector<std::bitset<8>> BinaryFiles::readBFilebit() {
	std::vector<std::bitset<8>> characters;

	streampos size;
	unsigned char* memblock;

	ifstream file(directory, ios::in | ios::binary);

	if (file.is_open()) {
		// go to end of file
		file.seekg(0, ios::end);
		// size is position of end of file
		size = file.tellg();
		memblock = new unsigned char[size];
		// go to beginning of file
		file.seekg(0, ios::beg);
		file.read((char*)memblock, size);

		// read each charecter and push bitset of charecter into vector
		for (int i = 0; i < size; i++) {
			characters.push_back(std::bitset<8>(memblock[i]));
		}
	}
	return characters;
}