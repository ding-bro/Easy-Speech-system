#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"Speaker.h"

class SpeechManager
{
public:
	SpeechManager();

	void show_menu();  // 显示菜单功能

	void exit_menu(); // 退出功能

	~SpeechManager();

	vector<int>v1;  // 比赛总人数  12人

	vector<int>v2;  // 第一轮比赛  6人

	vector<int>vVictory;  // 胜利前三名   3人

	map<int, Speaker>m_speaker;  // 存放编号，以及对应的具体选手

	int m_index; // 记录比赛轮数

	void Init_menu(); // 初始化容器属性

	void Create_menu(); // 创建选手

	void StartSpeech();  // 贯穿整个比赛流程:   开始比赛

	void SpeechDraw();  // 比赛抽签

	void SpeechStart(); // 正式开始比赛

	void ShowScore();  // 显示比赛分数

	void ShowFinals(); // 显示决赛

	void SaveFile();   // 保存文件，用.csv ，可用excel打开

	bool FileIsEmpty;   // 文件是否为空

	void LoadFile();  //读取文件

	void ClearFile();

};