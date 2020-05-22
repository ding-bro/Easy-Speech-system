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

	this->Create_menu();  // ����Create_menu
}

void SpeechManager::show_menu()
{
	cout << "*****************************�ݽ��������̹���ϵͳ*****************************" << endl
		<<endl
		<< "  *******************************1.��ʼ�ݽ�����******************************" << endl
		<< endl
		<< "  *******************************2.�鿴�����¼******************************" << endl
		<< endl
		<< "  *******************************3.��ձ�����¼******************************" << endl
		<< endl
		<< "  *******************************4.�˳���������******************************" << endl
		<< endl;
}

void SpeechManager::exit_menu()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	cout << "��������˳�ϵͳ��" << endl;
	exit(0);
}

void SpeechManager::Init_menu()
{
	// ����Ϊ�գ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();

	// ��ʼ����������
	this->m_index = 1;
}

void SpeechManager::Create_menu()
{
	string nameseed = "ABCDEFGHIJKL";   // string ��������  12������
	for (int i = 0; i < nameseed.size(); i++)  // i<12  
	{
		string name = "ѡ��";
		name += nameseed[i];   // ���Ƶ�ƴ��

		Speaker s;
		s.m_name = name;
		for (int i = 0; i < 2; i++)   // ��2�ֱ���
		{
			s.m_score[i] = 0;
		}

		// ѡ�ֱ�ŷ��뵽V1������
		this->v1.push_back(i + 10001);

		// ѡ�ֵı���Լ���Ӧ��ѡ�ַ��뵽map������
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
	cout << "��" << this->m_index << "�ֱ������ڽ��г�ǩ��" << endl
		<<endl
		<< "-----------------------------------------"<<endl
		<<endl
		<< "��ǩ��ѡ�ְ�����ݽ�˳������: " << endl;

	if (this->m_index==1)  // ��һ�ֳ�ǩ   m_index һ��ʼ��Init_menu()�Ѿ���ʼ��Ϊ1
	{
		random_shuffle(v1.begin(), v1.end());  // �����ڽ�ϴ���㷨
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());  // �ڶ��ֳ�ǩ
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

// ���ģ�
void SpeechManager::SpeechStart()
{
	cout << endl
		<< "----------��" << this->m_index << "�ֱ�����ʽ��ʼ----------" << endl
		<< endl;
		
	multimap<double,int,greater<double>>group;  // ��Ϊ��ʱ����,��������

	int num = 0;  // ��¼��Ա����  6��һ��

	vector<int>v_match;   // ������ʽ����ѡ������
	if (this->m_index==1)
	{
		v_match = v1;    // �ڴ�֮ǰ�Ѿ���SpeechDraw���г�ǩ��ϣ���ǩ���֮��ȷ�ϱ�������
	}
	else
	{
		v_match = v2;
	}

	// ��������ѡ�ֽ��б���
	for (vector<int>::iterator it=v_match.begin();it!=v_match.end();it++)
	{
		num++;
		
		// ��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)  // 10����ί���
		{
			double score = (rand() % 401 + 600)/10.f;  // �����double�����ͣ������    (401+600)/10 ���ܴ���ʵõ�һ��С��
			//cout << score << " ";  //��ӡѡ�ַ���
			d.push_back(score);  // ����������
		}
		//cout << endl;

		sort(d.begin(), d.end(),greater1);   // ������������
		d.pop_front();  // ȥ����߷�
		d.pop_back();  // ȥ����ͷ�  

		double sum = accumulate(d.begin(), d.end(),0.0f);  // �ۼ��ܷ�
		double avg = sum / (double)d.size();   // ƽ��ֵ   ǿתΪdouble

	/*	cout << "��ţ� " << *it << "������ " << this->m_speaker[*it].m_name   // ��ӡƽ����
			<< "ƽ���֣� " << avg << endl;*/

		// ��ƽ���ַ��뵽map������
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		// ��������ݷ��뵽��ʱС��������
		group.insert(make_pair(avg, *it));

		// ÿ6��ȡ��ǰ����
		if (num%6==0)  // ȡģΪ0˵����6����12
		{
			cout << "��" << num / 6 << "�ֱ����������£� " << endl;
			for (multimap<double,int,greater<double>>::iterator it=group.begin();it!=group.end();it++)
			{
				cout << "��ţ� " << it->second << "������ " << this->m_speaker[it->second].m_name
					<< "�ɼ��� " << this->m_speaker[it->second].m_score[this->m_index-1] << endl;
			}
			cout << endl;

			// ȡ��ǰ����ѡ��
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
			group.clear();  // �ڶ��ֽ�������֮��Ҫ���ѡ��
		}
	}
	cout << "---------��" << this->m_index << "�ֱ������---------" << endl;
	system("pause");
}

void SpeechManager::ShowScore()
{
	cout << "----------��" << this->m_index << "�ֱ�������ѡ����Ϣ���£�----------" << endl;
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
		cout << "ѡ�ֱ�ţ�" << *it << endl
			<< "ѡ�������� " << this->m_speaker[*it].m_name << endl
			<< "ѡ�ֵ÷֣� " << this->m_speaker[*it].m_score[this->m_index - 1] << endl << endl;
	}
	system("pause");
	system("cls");
	this->show_menu();
}

void SpeechManager::ShowFinals()
{
	cout << "----------����ʤ��ѡ����Ϣ���£�----------"<< endl;
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
		cout << "ѡ�ֱ�ţ�" << *it << endl
			<< "ѡ�������� " << this->m_speaker[*it].m_name << endl
			<< "ѡ�ֵ÷֣� " << this->m_speaker[*it].m_score[this->m_index - 1] << endl << endl;
	}
	system("pause");
	system("cls");
	this->show_menu();
}

void SpeechManager::SaveFile()
{
	ofstream ding;
	ding.open("information.csv", ios::out|ios::app);   // app: append׷�ӷ�ʽ����д�ļ�,�����

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ding << "ѡ�ֱ�ţ� " << *it << endl;
		ding << "ѡ�������� " << this->m_speaker[*it].m_name << endl;
		ding << "ѡ�ֵ÷֣� " << this->m_speaker[*it].m_score[1] << endl;
	}ding << endl;

	ding.close();

	cout << "ѡ����Ϣ�ѱ���" << endl;
}

void SpeechManager::LoadFile()
{
	ifstream neng;
	neng.open("information.csv", ios::in);   // ���ļ�
	if (!neng.is_open())  // �ж��ļ��Ƿ����
	{
		this->FileIsEmpty = true;
		cout << "�ļ�������" << endl;
		neng.close();
		return;
	}

	char d;
	neng >> d;
	if (neng.eof())    // �����ļ�β ,�ж��ļ��Ƿ�Ϊ��
	{
		cout << "�ļ��ڲ�����Ϊ��" << endl;
		this->FileIsEmpty = true;
		neng.close();
		return;
	}

	this->FileIsEmpty = false;  // ��Ϊ��
	 
	neng.putback(d);  // putback �������ȡ�ĵ����ַ��Ż���

	string data;    

	while (neng>>data)   // ��ÿһ�����ݶ���ȡ
	{
		cout << data << " " << endl;
	}
	neng.close();
}

void SpeechManager::ClearFile()
{
	cout << "ȷ���Ƿ�Ҫ����ļ���ѡ����Ϣ��" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;
	int select = 0;
	cin >> select;
	if (select==1)
	{
		ofstream ofs("information.csv", ios::trunc);
		ofs.close();
		this->Init_menu();
		this->Create_menu();
		cout << "���ѡ����Ϣ�ɹ���" << endl;
		this->LoadFile();
	}
	else
	{
		cout << "�������˳�" << endl;
		return;
	}
}

SpeechManager::~SpeechManager()
{

}