#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<functional>
#include"SpeechManager.h"
#include<ctime>

/*
演讲比赛规则：
	学校举行每一场演讲比赛，共有12个人参加，比赛共两轮，第一轮为淘汰赛，第二轮为决赛
	每名选手都有对应的编号，如10001-10012
	比赛方式：分组比赛，每组6个人
	第一轮分为两个小组，整体按照选手编号进行抽签之后顺序演讲
	十个评委分别给每名选手打分，去除最高分和最低分，求的平均分为本轮选手的成绩
	当小组演讲完后，将淘汰组内排名最后的三名选手，前三名选手晋级，进入下一轮的比赛
	第二轮为决赛，前三名胜出
	每轮比赛过后需要显示晋级选手的信息

*/

/*
程序功能：
	开始演讲比赛：完成整届比赛的流程，每个比赛阶段完成后需要给用户一个提示，用户按任意键后继续进行下一个阶段
	查看往届比赛记录：查看之前比赛的前三名结果，每次比赛都会记录到一个文件中，文件用.csv 后缀名进行保存
	清空比赛记录：将文件中的数据清空
	退出比赛程序：退出当前的程序

*/




int main()
{
	srand(time(NULL));
	while (true)
	{
		SpeechManager s;
		s.show_menu();

		 //测试Create_menu()
		//for (map<int,Speaker>::iterator it=s.m_speaker.begin();it!=s.m_speaker.end();it++)
		//{
		//	cout << "选手编号： " << it->first<<"	"
		//		<< "选手姓名： " << it->second.m_name<<"	"       // map中的自定义数据类型Speaker存放了name和score
		//		<< "选手分数： " << it->second.m_score[0] << endl;
		//}

		int select = 0;
		cin >> select;
		switch (select)
		{
		case 4:
			s.exit_menu();
			break;
		case 3:
			s.ClearFile();
			system("pause");
			system("cls");
			break;
		case 2:
			s.LoadFile();
			system("pause");
			system("cls");
			break;
		case 1:
			//s.Create_menu();
			s.StartSpeech();
			break;
		default:
			cout << "请输入有效的数字按键！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}



	system("pause");
	return 0;
}
