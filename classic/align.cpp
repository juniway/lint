#include <iostream>
using namespace std;

struct s1 {
    char a;
    short a1;
    char b1;
    float b;
    int c;
    char e;
    double f;
};

// Size of Struct s1 = 32

struct s2 {
    double f;
    float b;
    int c;
    short a1;
    char a,b1,e;
};

// Size of Struct s2 = 24

struct s3 {
	char a;
	short b;
	double c;
	int d;
};

struct TimeStamp {
  uint32_t month  : 4;   // 1..12 [4 bits]
  uint32_t date   : 5;   // 1..31 [5 bits]
  uint32_t hour   : 5;   // 00..23 [5 bits]
  uint32_t minute : 6;   // 00..59 [6 bits]
  uint32_t second : 6;   // 00..59 [6 bits]
};

struct Date {
	unsigned short week :3; 	// 0..7 (3 bits)
	unsigned short monthDay :6; // 0..31 (6 bits)
	unsigned short month :5; 	// 0..12 (5 bits)
	unsigned short year :8; 	// 0..100 (8 bits)
};



int main() {
	std::cout << "s1: " << sizeof(s1) << std::endl;
	std::cout << "s2: " << sizeof(s2) << std::endl;
	std::cout << "s3: " << sizeof(s3) << std::endl;

	cout << "timestamp: " << sizeof(TimeStamp) << endl;
	cout << "short: " << sizeof(unsigned short) << endl;
	cout << "int: " << sizeof(unsigned int) << endl;
	cout << "Date: " << sizeof(Date) << endl;

	uint32_t ts = 0;
	uint8_t month = 8;
	uint8_t date = 30;
	uint8_t hour = 13;
	uint8_t minute = 27;
	uint8_t second = 55;

	ts = ts|month;
	ts = ts|(date << 5);
	ts = ts|(hour << 9);
	ts = ts|(minute << 14);
	ts = ts|(second << 20);
	cout << "ts: " << ts << endl;

	cout << "month: " << (ts & 0xF) << endl;
	cout << "date: " << ((ts & 0x1F0) >> 4) << endl;
	cout << "hour: " << ((ts & 0x3E00) >> 9) << endl;
	cout << "minute: " << ((ts & 0xFC000) >> 14) << endl;
	cout << "second: " << ((ts & 0x3F00000) >> 20) << endl;

	return 0;
}
