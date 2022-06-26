#include<iostream>

#include "wkSTL.h"


#pragma pack(1) 
struct T
{
	uint8_t a:1;
	uint16_t b:2;
	uint32_t c:4;
};
#pragma pack() 

int main()
{
	//int a, b;
	//std::cin >> a  >> b;
	//std::cout << a << std::endl;
	//std::cout << b << std::endl;
	size_t pushLen(0);
	wkSTL::Pipeline pipeline;

	std::vector<short> vec{ 1,2,3,4,5,6,7,8,9,10 };
	pushLen = pipeline.push(vec);
	std::cout << "push vector length:" << pushLen << std::endl;
	pipeline.push('\0');

	T tmp{ 0xa, 0xb, 0xc };
	pushLen = pipeline.push(tmp);
	std::cout << "push struct length:" << pushLen << std::endl;
	pipeline.push('\0');

	int in{ 0x12345678 };
	pushLen = pipeline.push(in);
	std::cout << "push int length:" << pushLen << std::endl;
	pipeline.push('\0');

	uint64_t i{ 0xF0F1F2F3F4F5F6F7 };
	pushLen = pipeline.push(i);
	std::cout << "push uint64_t length:" << pushLen << std::endl;
	pipeline.push('\0');

	double d{ 12.334 };
	pushLen = pipeline.push(d);
	std::cout << "push double length:" << pushLen << std::endl;
	pipeline.push('\0');

	long long l{ 0xA1A2A3A4A5A6A7A };
	pushLen = pipeline.push(l);
	std::cout << "push long long length:" << pushLen << std::endl;
	pipeline.push('\0');

	const char c1[] = "0123456789";
	pushLen = pipeline.push(c1);
	std::cout << "push char 1 length:" << pushLen << std::endl;
	pipeline.push('\0');

	const char* c2 = "abcdefghijklmn";
	pushLen = pipeline.push(c2, static_cast<int>(strlen(c2)+ 1));
	std::cout << "push char 2 length:" << pushLen << std::endl;
	pipeline.push('\0');


	std::string str{ "����һλC++������" };
	pushLen = pipeline.push(str);
	std::cout << "push string length:" << pushLen << std::endl;
	pipeline.push('\0');

	std::cout << "pipeline length:" << pipeline.length() << std::endl;
	std::cout << "pipeline content:" << pipeline << std::endl;

	//uint8_t f{ 0xbb };
	//std::cout << "f in pos:" << pipeline.at(pipeline.search(f)) << std::endl;
	std::cout << "s in pos:" << pipeline.at(pipeline.search(str)) << std::endl;

	//char pop[10] = {};

	//size_t popLen = pipeline.pop(pop, 10);
	//std::cout << popLen << std::endl;
	//std::cout << pop << std::endl;
	//std::cout << pipeline.size() << std::endl;
}

