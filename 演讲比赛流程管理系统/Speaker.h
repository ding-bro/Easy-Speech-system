#pragma once
#include<iostream>
using namespace std;

class Speaker
{
public:
	string m_name;
	double m_score[2];   // 利用浮点型，让分数不容易相等，并且利用数组表示有2轮比赛
	//int m_number;

};