
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



// decrypt and decode compressed binary file given the frequency of symbols
// use huffman coding algorythms to encrypt and decrypt binary file
int main()
{

	return 0;
}
