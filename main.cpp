#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "File.h"

using namespace std;

/****************************************************************
Frequency Object holds symbol and frequency
*****************************************************************/
struct frequency
{
	char _c;
	float _f;
	frequency(char c, float f) { _c = c; _f = f; }
};


// A preinitialized vector of Frequencies
vector<frequency> vfrequency = {
	// given values
	frequency(' ',8.0),
	frequency('!',0.0306942),
	frequency('"',0.000183067),
	frequency('#',0.00854313),
	frequency('$',0.00970255),
	frequency('%',0.00170863),
	frequency('&',0.00134249),
	frequency('\'',0.000122045),
	frequency('(',0.000427156),
	frequency(')',0.00115942),
	frequency('*',0.0241648),
	frequency('+',0.00231885),
	frequency(',',0.00323418),
	frequency('-',0.0197712),
	frequency('.',0.0316706),
	frequency('/',0.00311214),
	frequency('0',2.74381),
	frequency('1',4.35053),
	frequency('2',3.12312),
	frequency('3',2.43339),
	frequency('4',1.94265),
	frequency('5',1.88577),
	frequency('6',1.75647),
	frequency('7',1.621),
	frequency('8',1.66225),
	frequency('9',1.79558),
	frequency(':',0.00189169),
	frequency(';',0.00207476),
	frequency('<',0.000427156),
	frequency('=',0.00140351),
	frequency('>',0.000183067),
	frequency('?',0.00207476),
	frequency('@',0.0238597),
	frequency('A',0.130466),
	frequency('B',0.0806715),
	frequency('C',0.0660872),
	frequency('D',0.0698096),
	frequency('E',0.0970865),
	frequency('F',0.0417393),
	frequency('G',0.0497332),
	frequency('H',0.0544319),
	frequency('I',0.070908),
	frequency('J',0.0363083),
	frequency('K',0.0460719),
	frequency('L',0.0775594),
	frequency('M',0.0782306),
	frequency('N',0.0748134),
	frequency('O',0.0729217),
	frequency('P',0.073715),
	frequency('Q',0.0147064),
	frequency('R',0.08476),
	frequency('S',0.108132),
	frequency('T',0.0801223),
	frequency('U',0.0350268),
	frequency('V',0.0235546),
	frequency('W',0.0320367),
	frequency('X',0.0142182),
	frequency('Y',0.0255073),
	frequency('Z',0.0170252),
	frequency('[',0.0010984),
	frequency('\\',0.00115942),
	frequency(']',0.0010984),
	frequency('^',0.00195272),
	frequency('_',0.0122655),
	frequency('\'',0.00115942),
	frequency('a',7.52766),
	frequency('b',2.29145),
	frequency('c',2.57276),
	frequency('d',2.76401),
	frequency('e',7.0925),
	frequency('f',1.2476),
	frequency('g',1.85331),
	frequency('h',2.41319),
	frequency('i',4.69732),
	frequency('j',0.836677),
	frequency('k',1.96828),
	frequency('l',3.77728),
	frequency('m',2.99913),
	frequency('n',4.56899),
	frequency('o',5.17),
	frequency('p',2.45578),
	frequency('q',0.346119),
	frequency('r',4.96032),
	frequency('s',4.61079),
	frequency('t',3.87388),
	frequency('u',2.10191),
	frequency('v',0.833626),
	frequency('w',1.24492),
	frequency('x',0.573305),
	frequency('y',1.52483),
	frequency('z',0.632558),
	frequency('{',0.000122045),
	frequency('|',0.000122045),
	frequency('}',0.000122045),
	frequency('~',0.00152556)
};



/****************************************************************
Pure virtual objects acts as base class for branch and leaf nodes
*****************************************************************/
class Node {
public: 
	virtual float Freq() = 0;
	virtual string Symbol() = 0;
};



/****************************************************************
Derived from Node class. 
Holds a left node and right node
used in huffman tree as non-end nodes
*****************************************************************/
class Branch : public Node {
protected:
	Node* left;
	Node* right;
public:
	Branch(Node*, Node*);
	Node* getLeft();
	Node* getRight();
	float Freq();
	string Symbol();
	
	void operator = (const Branch& B) {
		left = B.left;
		right = B.right;
	}
};


Branch::Branch(Node* n1, Node* n2) {
	left = n1;
	right = n2;
}


// returns left node
Node* Branch::getLeft() {
	return left;
}


// returns right node
Node* Branch::getRight() {
	return right;
}


// returns frequency of symbol
float Branch::Freq() {
	float amount = left->Freq() + right->Freq();
	return amount;
}


// returns symbol
string Branch::Symbol() {
	return string(left->Symbol() + right->Symbol());
}



/****************************************************************
Derived from Node class
Leaf object holds symbol and frequency. 
Used as the end nodes of the huffman tree
******************************************************************/
class Leaf : public Node {
protected: 
	float freq;
	string symbol;
public:
	Leaf(string, float);
	float Freq();
	string Symbol();
};


Leaf::Leaf(string s = "", float f=0) {
	freq = f;
	symbol = s;
}


// returns frequency
float Leaf::Freq() {
	return freq;
}


// returns symbol
string Leaf::Symbol() {
	return symbol;
}



/****************************************************************
structure used to sort Nodes in priority queue
*****************************************************************/
struct compare {
	bool operator () (Node* n1, Node* n2) {
		return (n1->Freq() > n2->Freq());
	}
};



// reads symbol and frequency from frequency vector
// reads pair into node 
// pushes nodes into priority queue
priority_queue<Node*, vector<Node*>, compare> readFrequencyVector(vector<frequency> freqTable) {
	priority_queue<Node*, vector<Node*>, compare> pQueue;
	for (auto& x : freqTable) {
		Node* freq = new Leaf(string(1, x._c), x._f);
		pQueue.push(freq);
	}
	return pQueue;
}



/****************************************************************
Interfaces for huffman coding.
Huffman coding is an efficient method of compressing data without
losing information. Huffman coding works by using a
frequency-sorted binary tree to encode symbols.
*****************************************************************/
class Huffman {
private:
	priority_queue<Node*, vector<Node*>, compare> FreqQueue;
public:
	Huffman() {}
	Huffman(priority_queue<Node*, vector<Node*>, compare>);
	priority_queue<Node*, vector<Node*>, compare> getQueue();
	void setQueue(priority_queue<Node*, vector<Node*>, compare>);
	priority_queue<Node*, vector<Node*>, compare> Tree();
	void Encode(Node*, string);
	string Decode(Node*, string);

};


Huffman::Huffman(priority_queue<Node*, vector<Node*>, compare> f) {
	FreqQueue = f;
}

// returns priority queue
priority_queue<Node*, vector<Node*>, compare> Huffman::getQueue() {
	return FreqQueue;
}


// sets priority queue
void Huffman::setQueue(priority_queue<Node*, vector<Node*>, compare> f) {
	FreqQueue = f;
}


// constructs frequency sorted binary tree
priority_queue<Node*, vector<Node*>, compare> Huffman::Tree() {
	while (FreqQueue.size() > 1) {
		// get lowest frequency assign it left
		Node* left = FreqQueue.top();
		FreqQueue.pop();
		// get next lowest frequency assign it right
		Node* right = FreqQueue.top();
		FreqQueue.pop();
		// create branch node and initialize with left and right nodes
		Node* branchNode = new Branch(left, right);
		// push branch node back to  queue
		FreqQueue.push(branchNode);
	}
	return FreqQueue;
}


// encodes charecters into binary 
// traverses tree and records binary path to each leaf/symbol
void Huffman::Encode(Node* root, string str) {
	vector<Node*> code;
	if (dynamic_cast<Branch*>(root) != nullptr) {
		Encode(dynamic_cast<Branch*>(root)->getLeft(), str + "0");
		Encode(dynamic_cast<Branch*>(root)->getRight(), str + "1");
	}
	if (dynamic_cast<Leaf*>(root) != nullptr) {
		Node* leaf = dynamic_cast<Leaf*>(root);
		cout << "Symbol: " << leaf->Symbol() << endl
			<< "Frequency: " << leaf->Freq() << endl
			<< "Binary Code: " << str << endl << endl;
	}
}


// decodes binary text to ascii text
// returns decoded text
string Huffman::Decode(Node* root, string fileName) {
	string decodedText = "";
	BinaryFiles file(fileName);
	vector<bitset<8>> encryptedBinary = file.readBFilebit();
	Node* current = root;

	// for each index in the vector
	for (auto x : encryptedBinary) {
		// for each bit in the byte (read bitset backwards)
		for (int i = x.size() - 1; i >= 0; i--) {
			// if 0 and branch, traverse left. if 1 and branch traverse right
			if (x[i] == 0 && dynamic_cast<Branch*>(current) != nullptr)
				current = dynamic_cast<Branch*>(current)->getLeft();
			if (x[i] == 1 && dynamic_cast<Branch*>(current) != nullptr)
				current = dynamic_cast<Branch*>(current)->getRight();

			// if leaf, get symbol
			if (dynamic_cast<Leaf*>(current) != nullptr) {
				decodedText += dynamic_cast<Leaf*>(current)->Symbol();
				current = root;
			}
		}
	}
	return decodedText;
}

// decrypt and decode compressed binary file given the frequency of symbols
// use huffman coding algorythms to encrypt and decrypt binary file
int main() {
	priority_queue<Node*, vector<Node*>, compare> s = readFrequencyVector(vfrequency);
	Huffman HT(s);
	s = HT.Tree();
	string code = "";
	BinaryFiles binaryFile("Compress.bin");
	cout << endl << "Decrypted Binary File: " << endl << endl;
	cout << HT.Decode(s.top(), binaryFile.getDirectory()) << endl << endl;
	cout << "=====================================================================" << endl;
	cout << endl << "Encoded Ascii to Binary: " << endl << endl;
	HT.Encode(s.top(), code);
	cout << "=====================================================================" << endl;
	cout << endl << "Encrypted Text: " << endl << endl;
	int index = 0;
	for (auto& x : binaryFile.readBFilebit()) {
		cout << x;
		index++;
		if (index == 10) {
			cout << endl;
			index = 0;
		}
	}
	cout << endl;
	return 0;
}



// Program Output //
/*
Decrypted Binary File:

Stay Hungry, Stay Foolish.  I am honored to be with you today at your 
commencement from one of the finest universities in the world. I never 
graduated from college. Truth be told, this is the closest I've ever 
gotten to a college graduation. Today I want to tell you three stories 
from my life. That's it. No big deal. Just three stories... When I was 
young, there was an amazing publication called The Whole Earth Catalog, 
which was one of the bibles of my generation. It was created by a fellow 
named Stewart Brand not far from here in Menlo Park, and he brought it 
to life with his poetic touch. This was in the late 1960s, before personal
computers and desktop publishing, so it was all made with typewriters, 
scissors, and polaroid cameras. It was sort of like Google in paperback 
form, 35 years before Google came along it was idealistic, and overflowing
with neat tools and great notions.  Stewart and his team put out several 
issues of The Whole Earth Catalog, and then when it had run its course, they 
put out a final issue. It was the mid 1970s, and I was your age. On the back 
cover of their final issue was a photograph of an early morning country road, 
the kind you might find yourself hitchhiking on if you were so adventurous. 
Beneath it were the words "Stay Hungry. Stay Foolish." It was their farewell 
message as they signed off. Stay Hungry. Stay Foolish. And I have always 
wished that for myself. And now, as you graduate to begin anew, I wish that 
for you. Steve Jobs  h

=====================================================================

Encoded Ascii to Binary:

Symbol: h
Frequency: 2.41319
Binary Code: 00000

Symbol: 3
Frequency: 2.43339
Binary Code: 00001

Symbol: p
Frequency: 2.45578
Binary Code: 00010

Symbol: w
Frequency: 1.24492
Binary Code: 000110

Symbol: f
Frequency: 1.2476
Binary Code: 000111

Symbol: r
Frequency: 4.96032
Binary Code: 0010

Symbol: o
Frequency: 5.17
Binary Code: 0011

Symbol: c
Frequency: 2.57276
Binary Code: 01000

Symbol: 0
Frequency: 2.74381
Binary Code: 01001

Symbol: d
Frequency: 2.76401
Binary Code: 01010

Symbol: z
Frequency: 0.632558
Binary Code: 0101100

Symbol: M
Frequency: 0.0782306
Binary Code: 0101101000

Symbol: T
Frequency: 0.0801223
Binary Code: 0101101001

Symbol: [
Frequency: 0.0010984
Binary Code: 0101101010000000

Symbol: ]
Frequency: 0.0010984
Binary Code: 0101101010000001

Symbol: \
Frequency: 0.00115942
Binary Code: 0101101010000010

Symbol: )
Frequency: 0.00115942
Binary Code: 0101101010000011

Symbol: +
Frequency: 0.00231885
Binary Code: 010110101000010

Symbol: '
Frequency: 0.00115942
Binary Code: 0101101010000110

Symbol: &
Frequency: 0.00134249
Binary Code: 0101101010000111

Symbol: $
Frequency: 0.00970255
Binary Code: 0101101010001

Symbol: -
Frequency: 0.0197712
Binary Code: 010110101001

Symbol: F
Frequency: 0.0417393
Binary Code: 01011010101

Symbol: B
Frequency: 0.0806715
Binary Code: 0101101011

Symbol: q
Frequency: 0.346119
Binary Code: 01011011

Symbol: y
Frequency: 1.52483
Binary Code: 010111

Symbol: m
Frequency: 2.99913
Binary Code: 01100

Symbol: 2
Frequency: 3.12312
Binary Code: 01101

Symbol: 7
Frequency: 1.621
Binary Code: 011100

Symbol: 8
Frequency: 1.66225
Binary Code: 011101

Symbol: v
Frequency: 0.833626
Binary Code: 0111100

Symbol: j
Frequency: 0.836677
Binary Code: 0111101

Symbol: 6
Frequency: 1.75647
Binary Code: 011111

Symbol: e
Frequency: 7.0925
Binary Code: 1000

Symbol: 9
Frequency: 1.79558
Binary Code: 100100

Symbol: g
Frequency: 1.85331
Binary Code: 100101

Symbol: l
Frequency: 3.77728
Binary Code: 10011

Symbol: a
Frequency: 7.52766
Binary Code: 1010

Symbol: 5
Frequency: 1.88577
Binary Code: 101100

Symbol: 4
Frequency: 1.94265
Binary Code: 101101

Symbol: t
Frequency: 3.87388
Binary Code: 10111

Symbol:
Frequency: 8
Binary Code: 1100

Symbol: k
Frequency: 1.96828
Binary Code: 110100

Symbol: R
Frequency: 0.08476
Binary Code: 1101010000

Symbol: K
Frequency: 0.0460719
Binary Code: 11010100010

Symbol: V
Frequency: 0.0235546
Binary Code: 110101000110

Symbol: @
Frequency: 0.0238597
Binary Code: 110101000111

Symbol: E
Frequency: 0.0970865
Binary Code: 1101010010

Symbol: *
Frequency: 0.0241648
Binary Code: 110101001100

Symbol: _
Frequency: 0.0122655
Binary Code: 1101010011010

Symbol: =
Frequency: 0.00140351
Binary Code: 1101010011011000

Symbol: ~
Frequency: 0.00152556
Binary Code: 1101010011011001

Symbol: /
Frequency: 0.00311214
Binary Code: 110101001101101

Symbol: ,
Frequency: 0.00323418
Binary Code: 110101001101110

Symbol: >
Frequency: 0.000183067
Binary Code: 1101010011011110000

Symbol: "
Frequency: 0.000183067
Binary Code: 1101010011011110001

Symbol: <
Frequency: 0.000427156
Binary Code: 110101001101111001

Symbol: (
Frequency: 0.000427156
Binary Code: 110101001101111010

Symbol: '
Frequency: 0.000122045
Binary Code: 11010100110111101100

Symbol: {
Frequency: 0.000122045
Binary Code: 11010100110111101101

Symbol: |
Frequency: 0.000122045
Binary Code: 11010100110111101110

Symbol: }
Frequency: 0.000122045
Binary Code: 11010100110111101111

Symbol: %
Frequency: 0.00170863
Binary Code: 1101010011011111

Symbol: G
Frequency: 0.0497332
Binary Code: 11010100111

Symbol: S
Frequency: 0.108132
Binary Code: 1101010100

Symbol: H
Frequency: 0.0544319
Binary Code: 11010101010

Symbol: Y
Frequency: 0.0255073
Binary Code: 110101010110

Symbol: X
Frequency: 0.0142182
Binary Code: 1101010101110

Symbol: Q
Frequency: 0.0147064
Binary Code: 1101010101111

Symbol: !
Frequency: 0.0306942
Binary Code: 110101011000

Symbol: .
Frequency: 0.0316706
Binary Code: 110101011001

Symbol: W
Frequency: 0.0320367
Binary Code: 110101011010

Symbol: :
Frequency: 0.00189169
Binary Code: 1101010110110000

Symbol: ^
Frequency: 0.00195272
Binary Code: 1101010110110001

Symbol: ;
Frequency: 0.00207476
Binary Code: 1101010110110010

Symbol: ?
Frequency: 0.00207476
Binary Code: 1101010110110011

Symbol: #
Frequency: 0.00854313
Binary Code: 11010101101101

Symbol: Z
Frequency: 0.0170252
Binary Code: 1101010110111

Symbol: A
Frequency: 0.130466
Binary Code: 1101010111

Symbol: x
Frequency: 0.573305
Binary Code: 11010110

Symbol: C
Frequency: 0.0660872
Binary Code: 11010111000

Symbol: D
Frequency: 0.0698096
Binary Code: 11010111001

Symbol: I
Frequency: 0.070908
Binary Code: 11010111010

Symbol: U
Frequency: 0.0350268
Binary Code: 110101110110

Symbol: J
Frequency: 0.0363083
Binary Code: 110101110111

Symbol: O
Frequency: 0.0729217
Binary Code: 11010111100

Symbol: P
Frequency: 0.073715
Binary Code: 11010111101

Symbol: N
Frequency: 0.0748134
Binary Code: 11010111110

Symbol: L
Frequency: 0.0775594
Binary Code: 11010111111

Symbol: 1
Frequency: 4.35053
Binary Code: 11011

Symbol: u
Frequency: 2.10191
Binary Code: 111000

Symbol: b
Frequency: 2.29145
Binary Code: 111001

Symbol: n
Frequency: 4.56899
Binary Code: 11101

Symbol: s
Frequency: 4.61079
Binary Code: 11110

Symbol: i
Frequency: 4.69732
Binary Code: 11111

=====================================================================

Encrypted Text:

11010101001011110100101111100110101010101110001110110010100100101111101010011011
10110011010101001011110100101111100010110101010011001110011111111111000000110101
01100111001100110101110101100101001100110000000001111101001100101000010101100101
11001111001110011000110000011011111101110000011000101110011111000110010111001101
01010100101111100101010111110001011100111110000010110001000001101100011001000111
01010001000011001000111011011111000001110010001101100110000111110110001100001100
01111100101110000010001100000111111111110110001111010111110011100011101111110111
10010000010111101111110111111111000111101100111111110111001011100000100011000001
10001100101001101010110101011001110011010111010110011101100001111001000001011001
00101001010100101011100010101011110000101011000001110010001101100110001000001110
01110011100010010110001101010110011100010110100100101110001011100000110011100110
00110010111001110011010101101010011011101100101110000011111111101100111111111011
00101110000010001100010001001100111111010001111010111110011010111010110101001101
11101100011110010001100100001111001000001011001001010011101111011110001110111001
01110011110010101100010000011100111001110001001011000110010010100101010010101110
00101010111111110011111011101010110011100010110100100110101010100101111100110101
11010110000011010101110110111110010111001111001011110001001110011110001011100111
11000110010111000000010100010001100111101011100110010111111000111101100000111001
00011011001100011000101111100100111111100011110001101010110011100010110100100000
10101011111010100110111101100111101100111111011111010101100111001101011111000111
10011100111111100101110001010100010101001111010101100111001101011101111110001111
01011111001011100000001010001000110011110101110011001011111100011110110101011001
11010101100111010101100111001101010110100000010001110111001101011101011000001101
01011110110001011100111110001110110010111010100110111011001011100000100000101000
11000001101010111101100101011101110010100110010100101100111111110110010111000001
01110001110011001111111010001010101111111100111110111000100010101001110011100001
01011000101101001000001000110011010101101000000001110011100011001101010010101000
10101110000011001101011100010101011110101001100111001011101010011011101100000110
00000111110100000000110000011010101111011000011111011000110000110001111100101110
00001000110011100111111111001100111000111101100001100011111000110001011111001001
01100011101100000101010101111111100111110111010101100111001101011101010111110000
01101010111101100010000010100010101011110000101011001110010101111100101011000001
11100010011100110011000110110011101101001100100001010110011010101001011110000001
10101000101011111000101101011001010101110101010110011101001110111110000011110100
01011000001110010001101100110000000100000101000110011111111011100010110100010001
11011001100111100110101111011010001011010011010100110111011001010111010101011000
00001000110011100100100011111000100101000001011111001111110111110010111001111001
00111111100011110001100000110111111011100000110000000111111111011000001000111000
10111111110100011001011100111110000100000000110101011001110001011010010000011111
11110110000011010101111011001111111101110010111000001000110010011101010111100011
00110111001000111110100111110110101001101110110011100110000001110011001010001100
00010100000101111000111110110101001111000100000110110000010111000101111000001011
11011001010111010101011000101010001111011010010111001100010110000010111000111001
10011111111111000000111111110110010111010100110111011001111000111100111111011111
00000110101011110110010101001110011110001100101001010100011000001101111110111000
00110010111010111000101000000110001011111101111000001011110110101001101110110011
11001000111111111011110001100101111011010100110111011001010111010101011000001000
11100111010001000111111101010110001000101001100100000101010111101101010110011100
11010111010101111100000110101011110110011110001100101011111000011000111110010011
11111110100100011001101010011100110011100101100111000110011111111011100000101010
00010100000101110011010010001101001100000111001100100110011010100110111011000000
11011001100010111100010100010111101100111001100000011100110010100011001101010011
10011001110010110011100011000100010100110010001100101010011001111101100101110011
11110111110000011010101111011001111101010100010101001111111111101011111111010001
10101001101110110010101110101010110000110111100100000100001111001100110001101111
11110110010111000001101111110111000001100111011000101010111110010111001100111001
11111011001010111010101011001001010010100010101011111001110100111011111111001111
10111110110101011001110011001101010100101111000000110101000101011111001010111010
10101100000001111111110110010111100010100110011000001011100010111110000111110001
01111100111101000011110010000010101010011110011111111101111011100010001111011000
01100011111000101101001000001000110011010101101000000001110011100011001101010010
10100010101110000011001101011100010101011110101001100111001011101010011011101100
10101110101010110010111000001000111011100000110000001000111011100111111011111000
00001010010101100001011100011101110011111101111111011000100000111110000010111101
00011010100110111011001011100000100001011111000001011100010111110000111110001011
11100101011000001111111111101101010011110011111111101111011100010001101010110011
10011010111010101111100000110101011110110010111000001000110001100111110101011001
10111001000111000100111110110101001101110110010101110101010110011010111010110000
01101010111101100010111001111100000101100101010010110001101010110011100110101111
00111011100101110000010001100111001101001000110100110001000001101111001000001011
00001100011111001011100000100011111001011000001111111111101101010011110011111111
10111101110001000110000011010101111011001010110000010000000011101110011100101001
01010000100000011000011000111110010101110111001000101000101001101011111000110000
11001011101111111110110010111000100000111110001110110111001001011111000010001110
10010101101010011011101100101110000010001100110100111111110101010110001011100111
11000110001100111111001010000010111110000011111111111010101011000101110011111000
00101111010001001100011111000000011111101110100000000000001111111010011111111011
00101110000111110111001111100011111000101110011111000110000011010000010100011001
11100011110010100101001111001000111011011111100000100011111000111101101010110011
10001011010111000111011000101010111000001100111111011111000001101000001010001100
10111000001000110000011000110010010101111011001101010011011110001110101010010111
10100101111100110101010101110001110110010100100101111101010110011100110101010010
11110100101111100010110101010011001110011111111111000000110101011001110101001101
11100011100110101110101011111000001101010111101100101110000010001111100101100000
11110100010100000011010001001110011110001100100011110111101010100101100011001010
11110110010111000001000010111110011110111111001011110110000101011000011000111000
11111010101100111001101010100101111010010111110011010101010111000111011001010010
01011111010101100111001101010100101111010010111110001011010101001100111001111111
11110000001101010110011100110101011111101010101100110101110101100000001010011110
01000110010101001100011010100101111111011000001101111111110000001000010101100101
11000001010101111100000111001100101100011000101111111010001001100011111010101100
11100110101011111101010101100111010011000110110101001101110110010101111011000101
11001111100011001001010010101001010111000101010111100011001011100111100111001100
01001011111111101110010101110110000001101101010011011101100110101110101100000110
11111111100000011001011100000101010111110000011100110010110001011100111110001101
01011001110011010101001011110000111100100011001101011101110011111001111101100110
00000000

C:\Users\yusuf\Desktop\lab1\Debug\lab1.exe (process 26148) exited with code 0.
Press any key to close this window . . .

*/
