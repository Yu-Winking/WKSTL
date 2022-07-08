#include<iostream>

#include "wkSTL.h"


//#pragma pack(1) 
struct struc
{
	uint8_t a : 1;
	uint16_t b : 2;
	uint32_t c : 4;
};


class A
{
public:
	A()
		:i_(0x0012), j_(0x0012)
	{}

	virtual ~A()
	{}

	uint64_t sum()
	{
		return i_+j_;
	}
private:
	int i_;
	uint64_t j_;
};
//#pragma pack()

int main()
{
	//int a, b;
	//std::cin >> a  >> b;
	//std::cout << a << std::endl;
	//std::cout << b << std::endl;
	size_t PushLen(0);
	wkSTL::Pipeline pipeline;

	struc tmp{ 0xa, 0xb, 0xc };
	PushLen = pipeline.Push(tmp);
	std::cout << "Push struct length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	A a;
	PushLen = pipeline.Push(std::move(a));
	std::cout << "Push class A length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	std::vector<int> vecInt{ 1,2,3,4,5,6,7,8,9,10 };
	PushLen = pipeline.Push(vecInt);
	std::cout << "Push int vector length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	std::vector<std::string> vecStr{ "abc", "efg", "hijk", "lmnopqrst" };
	PushLen = pipeline.Push(vecStr);
	std::cout << "Push string vector length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	int in{ 0x12345678 };
	PushLen = pipeline.Push(in);
	std::cout << "Push int length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	uint64_t i{ 0xF0F1F2F3F4F5F6F7 };
	PushLen = pipeline.Push(i);
	std::cout << "Push uint64_t length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	double d{ 12.334 };
	PushLen = pipeline.Push(d);
	std::cout << "Push double length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	long long l{ 0xA1A2A3A4A5A6A7A };
	PushLen = pipeline.Push(l);
	std::cout << "Push long long length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	const char c1[] = "0123456789";
	PushLen = pipeline.Push(c1);
	std::cout << "Push char 1 length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	const char* c2 = "abcdefghijklmn";
	PushLen = pipeline.Push(c2, static_cast<int>(strlen(c2)+1));
	std::cout << "Push char 2 length:" << PushLen << std::endl;
	//pipeline.Push('\0');


	std::string str{ "我是一位C++爱好者" };
	PushLen = pipeline.Push(str);
	std::cout << "Push string length:" << PushLen << std::endl;
	//pipeline.Push('\0');

	std::cout << "pipeline length:" << pipeline.Length() << std::endl;
	std::cout << "pipeline sumAll:" << pipeline.SumAll() << std::endl;
	std::cout << "pipeline content:" << pipeline << std::endl;

	uint8_t f{ 0xbb };
	std::cout << "0xbb in pos:" << pipeline.At(pipeline.Search(f)) << std::endl;
	std::cout << "s pos:" << pipeline.At(pipeline.Search(str)) << std::endl;
	std::cout << "in pos:" << pipeline.At(pipeline.Search(in)) << std::endl;
	std::cout << "c1 pos:" << pipeline.At(pipeline.Search(c1)) << std::endl;
 	std::cout << "c2 pos:" << pipeline.At(pipeline.Search(c2, static_cast<int>(strlen(c2)+1))) << std::endl;
	std::cout << "int vector pos:" << pipeline.At(pipeline.Search(vecInt)) << std::endl;
	std::cout << "string vector pos:" << pipeline.At(pipeline.Search(vecStr)) << std::endl;
	std::cout << "string pos:" << pipeline.At(pipeline.Search(str)) << std::endl;
 	std::cout << "class a pos:" << pipeline.At(pipeline.Search(a)) << std::endl;


	//char pop[10] = {};

	//size_t popLen = pipeline.pop(pop, 10);
	//std::cout << popLen << std::endl;
	//std::cout << pop << std::endl;
	//std::cout << pipeline.size() << std::endl;
}

