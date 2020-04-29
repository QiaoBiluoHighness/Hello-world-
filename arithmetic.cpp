// 生成.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include<stack>

#define MaxNumberCount 4
#define MinNumberCount 2
int OperatorCount = 5;
char Operator[5] = {};

std::ofstream question;

void DecideOperator() {
	int Operatorcount = 0;
	char temp;
	std::cout << "加减乘除(" << '+' << ',' << '-' << ',' << '*' << ',' << '/' << ',' << ")中至少选择两种运算符，";
	std::cout << "首先输入加减乘除你选择的个数:";
	std::cin >> Operatorcount;
	Operatorcount++;
	OperatorCount = Operatorcount;
	std::cout << "输入你选择的运算符(符号之间用空格隔开):";
	for (int i = 0; i < Operatorcount; i++) {
		if (i == Operatorcount - 1) {
			Operator[i] = '=';
		}
		else {
			std::cin >> temp;
			Operator[i] = temp;
		}
	}
	return;
}

int DecideCount() {
	int count = 0;
	std::cout << "输入你想要生成四则运算的数目:";
	std::cin >> count;
	return count;
}

bool DecideDecimal() {
	bool decOrint = false;
	std::cout << "决定是否有小数生成,";
	std::cout << "没有小数请输出0，";
	std::cout << "有小数请输出1:";
	std::cin >> decOrint;
	return decOrint;
}

bool DecideBracket() {
	bool bracket = false;
	std::cout << "决定是否有括号,";
	std::cout << "没有括号请输出0,";
	std::cout << "有括号请输出1:";
	std::cin >> bracket;
	return bracket;
}

bool DecideMaxRange() {
	bool max_range = false;
	std::cout << "决定最大数范围,";
	std::cout << "十位数请输出0,";
	std::cout << "百位数请输出1:";
	std::cin >> max_range;
	return max_range;
}

int Max_TwoDecimal() {
	return rand() % 3;
}

int Max_OneDecimal() {
	return rand() % 2;
}

//决定生成几位小数，or依旧整数
int DecimalOrInteger(float RandomNumber) {
	if (RandomNumber > 10)
		return Max_TwoDecimal();
	else
		return Max_OneDecimal();
	return 0;
}

//生成一个随机数
float GetRandomNumber(bool DecOrInt, bool max_range) {
	float RandomNumber = 0;
	if (max_range == false)
		RandomNumber = rand() % 10 + 1;
	if (max_range == true)
		RandomNumber = rand() % 100 + 1;

	if (DecOrInt == false)
		return RandomNumber;
	if (DecOrInt == true) {
		int temp = DecimalOrInteger(RandomNumber);
		while (temp--)
			RandomNumber /= 10.0;
	}
	return RandomNumber;
}

//返回运算数的个数
int GetNumberCount() {
	return rand() % (MaxNumberCount - MinNumberCount) + MinNumberCount;
}

//返回一个随机的运算符
char GetRandomOperator() {
	return Operator[rand() % (OperatorCount - 1)];
}


void NoBracket(int NumberCount, bool DecOrInt, bool max_range) {
	float tempRandomNumber = 0;
	char tempOperator;
	for (int i = 0; i < NumberCount; i++) {
		if (i == NumberCount - 1) {
			tempRandomNumber = GetRandomNumber(DecOrInt, max_range);
			tempOperator = Operator[OperatorCount - 1];
			std::cout << tempRandomNumber << tempOperator << std::endl;
			question << tempRandomNumber << tempOperator << std::endl;
		}
		else {
			tempRandomNumber = GetRandomNumber(DecOrInt, max_range);
			tempOperator = GetRandomOperator();
			std::cout << tempRandomNumber;
			question << tempRandomNumber;
			if (i != NumberCount - 1) {
				std::cout << tempOperator;
				question << tempOperator;
			}
		}
	}
	return;
}

int BracketDecide() {
	return rand() % 3;
}

void Bracket(int NumberCount, bool DecOrInt, bool max_range) {
	int method = 0;
	method = BracketDecide();
	float tempRandomNumber = 0;
	char tempOperator;
	switch (method) {
	case 0: NoBracket(NumberCount, DecOrInt, max_range); break;
	case 1:
		for (int i = 0; i < NumberCount; i++) {
			tempRandomNumber = GetRandomNumber(DecOrInt, max_range);
			tempOperator = Operator[OperatorCount - 1];
			if (i == NumberCount - 1) {
				std::cout << tempRandomNumber << tempOperator << std::endl;
				question << tempRandomNumber << tempOperator << std::endl;
			}
			else {
				tempRandomNumber = GetRandomNumber(DecOrInt, max_range);
				tempOperator = GetRandomOperator();
				if (i == 0) {
					std::cout << '(';
					question << '(';
				}
				std::cout << tempRandomNumber;
				question << tempRandomNumber;
				if (i == 1) {
					std::cout << ')';
					question << ')';
				}
				if (i != NumberCount - 1) {
					question << tempOperator;
					std::cout << tempOperator;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < NumberCount; i++) {
			if (i == NumberCount - 1) {
				tempRandomNumber = GetRandomNumber(DecOrInt, max_range);
				tempOperator = Operator[OperatorCount - 1];
				std::cout << tempRandomNumber << ')' << tempOperator << std::endl;
				question << tempRandomNumber << ')' << tempOperator << std::endl;
			}
			else {
				tempRandomNumber = GetRandomNumber(DecOrInt, max_range);
				tempOperator = GetRandomOperator();
				if (i == 1) {
					std::cout << '(';
					question << '(';
				}
				std::cout << tempRandomNumber;
				question << tempRandomNumber;
				if (i != NumberCount - 1) {
					std::cout << tempOperator;
					question << tempOperator;
				}
			}
		}
		break;
	}
	return;
}

//生成四则运算
void Arithmetic(bool DecOrInt, bool bracket, bool max_range) {
	int NumberCount = 0;//参与运算的数的个数
	NumberCount = GetNumberCount();

	if (bracket == false)
		NoBracket(NumberCount, DecOrInt, max_range);
	else {
		if (NumberCount == 2) //判断是否可添加括号
			NoBracket(NumberCount, DecOrInt, max_range);
		else
			Bracket(NumberCount, DecOrInt, max_range);
	}
	return;
}

int main()
{
	int count = 0;

	question.open("question.txt");

	bool DecOrInt = false;
	bool bracket = false;
	bool max_range = false;
	count = DecideCount();
	DecideOperator();
	DecOrInt = DecideDecimal();
	bracket = DecideBracket();
	max_range = DecideMaxRange();
	srand((unsigned int)time(NULL));
	for (int i = 0; i < count; i++)
		Arithmetic(DecOrInt, bracket, max_range);
	question.close();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
