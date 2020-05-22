#include"SpeechManager.h"
#include"Speaker.h"
#include<algorithm>
#include<deque>
#include<map>
#include<functional>
#include<numeric>
#include<fstream>


SpeechManager::SpeechManager()
{
	this->Init_menu();

	this->Create_menu();  // 测试Create_menu
}

void SpeechManager::show_menu()
{
	cout << "*****************************演讲比赛流程管理系统*****************************" << endl
		<<endl
		<< "  *******************************1.开始演讲比赛******************************" << endl
		<< endl
		<< "  *******************************2.查看往届记录******************************" << endl
		<< endl
		<< "  *******************************3.清空比赛记录******************************" << endl
		<< endl
		<< "  *******************************4.退出比赛程序******************************" << endl
		<< endl;
}

void SpeechManager::exit_menu()
{
	cout << "欢迎下次使用！" << endl;
	cout << "按任意键退出系统！" << endl;
	exit(0);
}

void SpeechManager::Init_menu()
{
	// 容器为空：
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();

	// 初始化比赛轮数
	this->m_index = 1;
}

void SpeechManager::Create_menu()
{
	string nameseed = "ABCDEFGHIJKL";   // string 名称种子  12个姓名
	for (int i = 0; i < nameseed.size(); i++)  // i<12  
	{
		string name = "选手";
		name += nameseed[i];   // 名称的拼接

		Speaker s;
		s.m_name = name;
		for (int i = 0; i < 2; i++)   // 有2轮比赛
		{
			s.m_score[i] = 0;
		}

		// 选手编号放入到V1容器中
		this->v1.push_back(i + 10001);

		// 选手的编号以及对应的选手放入到map容器中
		this->m_speaker.insert(make_pair(i + 10001, s));
	}
}

void SpeechManager::StartSpeech()
{
	for (m_index=1; m_index < 3; m_index++)
	{
		if (this->m_index==1)
		{
			this->SpeechDraw();

			this->SpeechStart();

			this->ShowScore();
		}
		if (this->m_index==2)
		{
			this->SpeechDraw();

			this->SpeechStart();

			this->ShowFinals();
		}
	}
	this->SaveFile();
	system("pause");
	system("cls");
	//this->m_index++;

	//this->SpeechDraw();

	//this->StartSpeech();

	//this->ShowFinals();
}

void SpeechManager::SpeechDraw()
{
	cout << "第" << this->m_index << "轮比赛正在进行抽签中" << endl
		<<endl
		<< "-----------------------------------------"<<endl
		<<endl
		<< "抽签后选手按编号演讲顺序如下: " << endl;

	if (this->m_index==1)  // 第一轮抽签   m_index 一开始在Init_menu()已经初始化为1
	{
		random_shuffle(v1.begin(), v1.end());  // 利用内建洗牌算法
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());  // 第二轮抽签
		for (vector<int>::iterator it= v2.begin(); it!= v2.end(); it++)
		{
			cout << *it << " ";
		}cout << endl;
	}
	cout << "-----------------------------------------" << endl;
	system("pause");
}

bool greater1(int a,int b)
{
	return a > b;
}

// 核心：
void SpeechManager::SpeechStart()
{
	cout << endl
		<< "----------第" << this->m_index << "轮比赛正式开始----------" << endl
		<< endl;
		
	multimap<double,int,greater<double>>group;  // 作为临时容器,降序排列

	int num = 0;  // 记录人员个数  6人一组

	vector<int>v_match;   // 创建正式比赛选手容器
	if (this->m_index==1)
	{
		v_match = v1;    // 在此之前已经有SpeechDraw进行抽签完毕，抽签完毕之后确认比赛轮数
	}
	else
	{
		v_match = v2;
	}

	// 遍历所有选手进行比赛
	for (vector<int>::iterator it=v_match.begin();it!=v_match.end();it++)
	{
		num++;
		
		// 评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)  // 10个评委打分
		{
			double score = (rand() % 401 + 600)/10.f;  // 打分用double浮点型，随机数    (401+600)/10 就能大概率得到一个小数
			//cout << score << " ";  //打印选手分数
			d.push_back(score);  // 放入容器中
		}
		//cout << endl;

		sort(d.begin(), d.end(),greater1);   // 分数进行排序
		d.pop_front();  // 去掉最高分
		d.pop_back();  // 去掉最低分  

		double sum = accumulate(d.begin(), d.end(),0.0f);  // 累加总分
		double avg = sum / (double)d.size();   // 平均值   强转为double

	/*	cout << "编号： " << *it << "姓名： " << this->m_speaker[*it].m_name   // 打印平均分
			<< "平均分： " << avg << endl;*/

		// 将平均分放入到map容器中
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		// 将打分数据放入到临时小组容器中
		group.insert(make_pair(avg, *it));

		// 每6人取出前三名
		if (num%6==0)  // 取模为0说明是6或者12
		{
			cout << "第" << num / 6 << "轮比赛名次如下： " << endl;
			for (multimap<double,int,greater<double>>::iterator it=group.begin();it!=group.end();it++)
			{
				cout << "编号： " << it->second << "姓名： " << this->m_speaker[it->second].m_name
					<< "成绩： " << this->m_speaker[it->second].m_score[this->m_index-1] << endl;
			}
			cout << endl;

			// 取走前三名选手
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it1 = group.begin(); it1 != group.end()&&count<3; it1++,count++)
			{
					if (this->m_index == 1)
					{
						v2.push_back((*it1).second);  
					}
					else
					{
						vVictory.push_back((*it1).second);
					}
			}
			group.clear();  // 第二轮降序排列之后，要清空选手
		}
	}
	cout << "---------第" << this->m_index << "轮比赛完毕---------" << endl;
	system("pause");
}

void SpeechManager::ShowScore()
{
	cout << "----------第" << this->m_index << "轮比赛晋级选手信息如下：----------" << endl;
	vector<int>v;
	if (this->m_index==1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}
	for (vector<int>::iterator it=v.begin();it!=v.end();it++)
	{
		cout << "选手编号：" << *it << endl
			<< "选手姓名： " << this->m_speaker[*it].m_name << endl
			<< "选手得分： " << this->m_speaker[*it].m_score[this->m_index - 1] << endl << endl;
	}
	system("pause");
	system("cls");
	this->show_menu();
}

void SpeechManager::ShowFinals()
{
	cout << "----------决赛胜出选手信息如下：----------"<< endl;
	vector<int>v;
	if (this->m_index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << endl
			<< "选手姓名： " << this->m_speaker[*it].m_name << endl
			<< "选手得分： " << this->m_speaker[*it].m_score[this->m_index - 1] << endl << endl;
	}
	system("pause");
	system("cls");
	this->show_menu();
}

void SpeechManager::SaveFile()
{
	ofstream ding;
	ding.open("information.csv", ios::out|ios::app);   // app: append追加方式继续写文件,不清空

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ding << "选手编号： " << *it << endl;
		ding << "选手姓名： " << this->m_speaker[*it].m_name << endl;
		ding << "选手得分： " << this->m_speaker[*it].m_score[1] << endl;
	}ding << endl;

	ding.close();

	cout << "选手信息已保存" << endl;
}

void SpeechManager::LoadFile()
{
	ifstream neng;
	neng.open("information.csv", ios::in);   // 打开文件
	if (!neng.is_open())  // 判断文件是否存在
	{
		this->FileIsEmpty = true;
		cout << "文件不存在" << endl;
		neng.close();
		return;
	}

	char d;
	neng >> d;
	if (neng.eof())    // 读到文件尾 ,判断文件是否为空
	{
		cout << "文件内部数据为空" << endl;
		this->FileIsEmpty = true;
		neng.close();
		return;
	}

	this->FileIsEmpty = false;  // 不为空
	 
	neng.putback(d);  // putback 将上面读取的单个字符放回来

	string data;    

	while (neng>>data)   // 把每一个数据都读取
	{
		cout << data << " " << endl;
	}
	neng.close();
}

void SpeechManager::ClearFile()
{
	cout << "确认是否要清空文件中选手信息？" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;
	int select = 0;
	cin >> select;
	if (select==1)
	{
		ofstream ofs("information.csv", ios::trunc);
		ofs.close();
		this->Init_menu();
		this->Create_menu();
		cout << "清空选手信息成功！" << endl;
		this->LoadFile();
	}
	else
	{
		cout << "按任意退出" << endl;
		return;
	}
}

SpeechManager::~SpeechManager()
{

}