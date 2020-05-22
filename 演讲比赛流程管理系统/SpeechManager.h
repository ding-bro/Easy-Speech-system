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

	void show_menu();  // ��ʾ�˵�����

	void exit_menu(); // �˳�����

	~SpeechManager();

	vector<int>v1;  // ����������  12��

	vector<int>v2;  // ��һ�ֱ���  6��

	vector<int>vVictory;  // ʤ��ǰ����   3��

	map<int, Speaker>m_speaker;  // ��ű�ţ��Լ���Ӧ�ľ���ѡ��

	int m_index; // ��¼��������

	void Init_menu(); // ��ʼ����������

	void Create_menu(); // ����ѡ��

	void StartSpeech();  // �ᴩ������������:   ��ʼ����

	void SpeechDraw();  // ������ǩ

	void SpeechStart(); // ��ʽ��ʼ����

	void ShowScore();  // ��ʾ��������

	void ShowFinals(); // ��ʾ����

	void SaveFile();   // �����ļ�����.csv ������excel��

	bool FileIsEmpty;   // �ļ��Ƿ�Ϊ��

	void LoadFile();  //��ȡ�ļ�

	void ClearFile();

};