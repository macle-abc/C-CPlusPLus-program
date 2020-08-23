#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "Employee.h"

using std::stringstream;
using std::ostream;
using std::istream;
using std::cout;
using std::cin;
using std::string;
using std::ios;
using std::ofstream;
using std::ifstream;
using std::endl;

//****************判断字符串str能否为工号或电话数****************//
inline bool Employee::AsIdOrTel(string str)//判断字符串str能否为工号或电话号码
{
	for (int i = 0; i < str.size(); ++i)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}

//****************判断字符串str能否作为工资数****************//
inline bool Employee::AsSalary(string str)
{
	int numPointSign = 0;
	if (str[0] == '-' || str[0] == '.' || str[0] < '0' || str[0] > '9')
		return false;
	for (int i = 1; i < str.size(); ++i)
	{
		if (str[i] == '.')
			++numPointSign;
		else if (str[i] < '0' || str[i] > '9')
			return false;
		if (numPointSign > 1)
			return false;
	}
	return true;
}

//****************重载输入运算符****************//
inline istream & operator >> (istream & is, Employee & e)
{
	e.rsetName();
	e.rsetSex();
	e.rsetDepartment();
	e.rsetID();
	e.rsetSalary();
	e.rsetTel();
	return is;
}

//****************重载输出运算符****************//
inline ostream & operator << (ostream & os, Employee & e)
{
	os << "姓名: " << e.m_Name
		<< "	性别: " << e.m_Sex << "\n"
		<< "科室: " << e.m_Department
		<< "	工号: " << e.m_ID << "\n"
		<< "工资: " << e.m_Salary
		<< "	电话: " << e.m_Tel << endl;
	return os;
}

//****************重设职工姓名****************//
inline void Employee::rsetName()
{
	cout << "请输入职工姓名: ";
	getline(cin, m_Name);
}

//****************重设职工性别****************//
inline void Employee::rsetSex()
{
	cout << "请输入职工性别: ";
	getline(cin, m_Sex);
}

//****************重设职工工号****************//
inline void Employee::rsetID()
{
	cout << "请输入职工工号(工号为6位数字): ";
	getline(cin, m_ID);
	while (!AsIdOrTel(m_ID) || m_ID.size() != (unsigned)6)//判断输入是否正确
	{
		cout << "输入错误!请重新输入: ";
		getline(cin, m_ID);
	}
}

//****************重设职工电话****************//
inline void Employee::rsetTel()
{
	cout << "请输入职工电话: ";
	getline(cin, m_Tel);
	while (!AsIdOrTel(m_Tel))
	{
		cout << "输入错误!电话数不合理!请重新输入: ";
		getline(cin, m_Tel);
	}
}

//****************重设职工科室****************//
inline void Employee::rsetDepartment()
{
	cout << "请输入职工科室: ";
	getline(cin, m_Department);
}

//****************重设职工工资****************//
inline void Employee::rsetSalary()
{
	cout << "请输入职工工资: ";
	getline(cin, m_Salary);
	while (!AsSalary(m_Salary))
	{
		cout << "输入错误!工资数不合理!请重新输入: ";
		getline(cin, m_Salary);
	}
}

//*****************判断链表中是否存在str数据******************//
inline int Node::isRepeat(struct Node * p, string str)
{
	int flag = 0;
	if (p->m_department == str)
		flag = 1;
	else
	{
		while (p->next)
		{
			p = p->next;
			if (p->m_department == str)
			{
				flag = 1;
				break;
			}
		}
		if (p->m_department == str)
		{
			flag = 1;
		}
	}
	return flag;
}

//*****************交换a b数据******************//
inline void Employee::swap(Employee * a, Employee * b) {
	Employee * temp = new Employee;
	temp->m_Department = a->m_Department;
	temp->m_ID = a->m_ID;
	temp->m_Name = a->m_Name;
	temp->m_Salary = a->m_Salary;
	temp->m_Sex = a->m_Sex;
	temp->m_Tel = a->m_Tel;
	a->m_Department = b->m_Department;
	a->m_ID = b->m_ID;
	a->m_Name = b->m_Name;
	a->m_Salary = b->m_Salary;
	a->m_Sex = b->m_Sex;
	a->m_Tel = b->m_Tel;
	b->m_Department = temp->m_Department;
	b->m_ID = temp->m_ID;
	b->m_Name = temp->m_Name;
	b->m_Salary = temp->m_Salary;
	b->m_Sex = temp->m_Sex;
	b->m_Tel = temp->m_Tel;
}

//*****************链表拆分******************//
inline Employee * Employee::partion(Employee *pBegin, Employee *pEnd) {
	if (pBegin == pEnd || pBegin->next == pEnd)    return pBegin;
	string key = pBegin->m_Salary;    //选择pBegin作为基准元素
	Employee *p = pBegin, *q = pBegin;
	double keynumber = 0.0;
	double qsalary = 0.0;
	stringstream translate;
	while (q != pEnd) {   //从pBegin开始向后进行一次遍历
		translate << q->m_Salary;
		translate >> qsalary;
		translate.clear();
		translate << key;
		translate >> keynumber;
		translate.clear();
		if (qsalary > keynumber) {
			p = p->next;
			swap(p, q);
		}
		q = q->next;
	}
	swap(p, pBegin);
	return p;
}

//*****************链表快速排序******************//
inline void Employee::quick_sort(Employee *pBegin, Employee *pEnd) {
	if (pBegin == pEnd || pBegin->next == pEnd)    return;
	Employee *mid = partion(pBegin, pEnd);
	quick_sort(pBegin, mid);
	quick_sort(mid->next, pEnd);
}

//*****************排序链表******************//
inline Employee* Employee::sortList(Employee* head) {
	if (head == NULL || head->next == NULL)    return head;
	quick_sort(head, NULL);
	return head;
}

//****************依据工号精确查找职工信息******************//
void Employee::QueryByID()
{
	ifstream ifile;
	int finish = 0;
	string ID;
	cout << "请输入查询的职工工号(工号为6位数字): ";
	getline(cin, ID);
	while (!AsIdOrTel(ID) || ID.size() != (unsigned)6)//判断输入是否正确
	{
		cout << "输入错误!请重新输入: ";
		getline(cin, ID);
	}
	ifile.open("职工信息表.txt", ios::in);
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	//****************读取文件信息操作****************//
	while (ifile.peek() != EOF)
	{
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		this->m_Name = name;
		this->m_Sex = sex;
		this->m_Department = department;
		this->m_ID = Id;
		this->m_Salary = salary;
		this->m_Tel = Tel;
		if (ID == this->m_ID)//工号相同则输出
		{
			++finish;
			cout << *this;
			break;
		}
	}
	if (!finish)
		cout << "查询失败!可能该工号没有录入!" << endl;
	ifile.close();
	cout << "即将返回查询菜单" << endl;
}

//****************依据姓名模糊查找职工信息******************//
void Employee::QueryByName()
{
	ifstream ifile;
	int finish = 0;
	string name;
	cout << "请输入职工姓名: ";
	getline(cin, name);
	ifile.open("职工信息表.txt", ios::in);
	char tname[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	//****************读取文件信息操作****************//
	while (ifile.peek() != EOF)
	{
		ifile.getline(tname, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		this->m_Name = tname;
		this->m_Sex = sex;
		this->m_Department = department;
		this->m_ID = Id;
		this->m_Salary = salary;
		this->m_Tel = Tel;
		if (this->m_Name.find(name) != string::npos)//存在相同姓名关键字则输出
		{
			++finish;
			cout << *this << endl;
		}
	}
	if (!finish)
		cout << "查询失败!可能该姓名没有录入!" << endl;
	ifile.close();
	cout << "即将返回查询菜单" << endl;
}

//*****************依据部门模糊查找职工信息******************//
void Employee::QueryByDepartment()
{
	ifstream ifile;
	int finish = 0;
	string department;
	cout << "请输入职工科室: ";
	getline(cin, department);
	ifile.open("职工信息表.txt", ios::in);
	char name[80];
	char tdepartment[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	//****************读取文件信息操作****************//
	while (ifile.peek() != EOF)
	{
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(tdepartment, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		this->m_Name = name;
		this->m_Sex = sex;
		this->m_Department = tdepartment;
		this->m_ID = Id;
		this->m_Salary = salary;
		this->m_Tel = Tel;
		if (this->m_Department.find(department) != string::npos)//存在科室相同关键字则输出
		{
			++finish;
			cout << *this << endl;
		}
	}
	if (!finish)
		cout << "查询失败!可能该科室没有录入!" << endl;
	ifile.close();
	cout << "即将返回查询菜单" << endl;
}

//*****************将职工信息写入文件******************//
void Employee::InputToFile()
{
	ofstream ofile;
	string select = "y";
	ofile.open("职工信息表.txt", ios::app);
	cout << "开始输入职工信息!" << endl;
	ifstream ifile;
	Employee * pte = new Employee;
	char name[80];	
	char tdepartment[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	while (toupper(select[0]) == 'Y')
	{
		trans : cin >> *this;
		Employee * head;
		Employee * temp = new Employee;
		head = temp;
		//****************读取文件信息操作****************//
		ifile.open("职工信息表.txt", ios::in);
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(tdepartment, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = tdepartment;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
		while (ifile.peek() != EOF)
		{
			temp->next = new Employee;
			temp = temp->next;
			ifile.getline(name, 80);
			ifile.getline(sex, 80);
			ifile.getline(tdepartment, 80);
			ifile.getline(Id, 80);
			ifile.getline(salary, 80);
			ifile.getline(Tel, 80);
			temp->m_Name = name;
			temp->m_Sex = sex;
			temp->m_Department = tdepartment;
			temp->m_ID = Id;
			temp->m_Salary = salary;
			temp->m_Tel = Tel;
		}
		temp->next = nullptr;
		ifile.close();
		temp = head;
		//****************判断是否存在相同工号，保证输入工号唯一****************//
		while (temp->next)
		{
			if (temp->m_ID == this->m_ID)
			{
				cout << "存在相同工号,请重新输入职工信息: " << endl;
				goto trans;
				}
			temp = temp->next;
		}
		if (temp->m_ID == this->m_ID)
		{
			cout << "存在相同工号,请重新输入职工信息: " << endl;
			
			goto trans;
		}

		//*****************写入文件操作*****************//
		ofile << this->m_Name << endl;
		ofile << this->m_Sex << endl;
		ofile << this->m_Department << endl;
		ofile << this->m_ID << endl;
		ofile << this->m_Salary << endl;
		ofile << this->m_Tel << endl;
		cout << "是否继续?(是请输入y或Y,否则输入n或N) ";
		getline(cin, select);
		//****************输入检测*****************//
		while (select.size() != (unsigned)1 || (select[0] != 'n' && select[0] != 'N' && select[0] != 'y' && select[0] != 'Y'))
		{
			cout << "输入错误!请重新输入: ";
			getline(cin, select);
		}
	}
	ofile.close();
	cout << "即将返回主菜单" << endl << endl;
}

//*****************查找菜单******************//
void Employee::Query()
{
	cout << "1).根据职工工号精确查找职工信息\n"
		<< "2).根据职工姓名模糊查找职工信息\n"
		<< "3).根据职工科室模糊查找职工信息\n"
		<< "4).返回主菜单" << endl;
	char select[80] = { 0 };
	cout << "请输入您的选择: ";
	cin.getline(select, 80);
	//*****************输入检测****************//
	while (select[1] != '\0' || select[0] < '1' || select[0] > '4')
	{
		cout << "输入错误!请重新输入: ";
		cin.getline(select, 80);
	}
	while (select[0] > '0' && select[0] < '4')
	{
		switch (select[0])
		{
		case '1':
			QueryByID();
			break;
		case '2':
			QueryByName();
			break;
		case '3':
			QueryByDepartment();
			break;
		default:
			break;
		}
		cout << "\n1).根据职工工号精确查找职工信息\n"
			<< "2).根据职工姓名模糊查找职工信息\n"
			<< "3).根据职工科室模糊查找职工信息\n"
			<< "4).返回主菜单" << endl;
		cout << "请输入您的选择: ";
		cin.getline(select, 80);
		while (select[1] != '\0' || select[0] < '1' || select[0] > '4')
		{
			cout << "输入错误!请重新输入: ";
			cin.getline(select, 80);
		}
	}
	cout << "即将返回主菜单" << endl << endl;
}

//*****************通过姓名查找职工信息并删除*****************//
void Employee::DeleteByName()
{
	ifstream ifile;
	ifile.open("职工信息表.txt", ios::in);
	string Name;
	cout << "请输入需要删除的职工姓名: ";
	getline(cin, Name);
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	//*****************读取文件操作***************//
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	temp->next = nullptr;
	temp = head;
	ifile.close();
	//*****************写入文件前判断是否删除信息是否有效****************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
		return;
	}
	int number = 0;//记录与用户输入的姓名相同的职工数
	Employee * tempToSave = new Employee;//记录相同姓名的职工信息
	Employee * HeadTempSave = tempToSave;
	//*****************记录相同姓名的职工信息*****************//
	while (temp->next)
	{
		if (temp->m_Name == Name)
		{
			++number;
			*tempToSave = *temp;
			tempToSave->next = new Employee;
			tempToSave = tempToSave->next;
		}
		temp = temp->next;
	}
	if (temp->m_Name == Name)
	{
		++number;
		*tempToSave = *temp;
		tempToSave->next = new Employee;
		tempToSave = tempToSave->next;
	}
	tempToSave->next = nullptr;
	tempToSave = HeadTempSave;
	temp = head;
	//*****************判断用户输入的姓名是否有效****************//
	if (number == 0)//不存在用户输入的姓名
		cout << "没有输入该姓名的职工信息!" << endl << "即将返回删除菜单" << endl << endl;
	else if (number == 1)//仅存在一个与用户输入的姓名相同的职工
	{
		//*****************写入文件前判断是否删除信息是否有效****************//
		if (temp->m_Department == "Null" || temp->m_Department == "")
		{
			cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
			return;
		}
		Employee * ptemp = nullptr;
		//*****************删除职工信息****************//
		if (temp->m_Name == Name)
		{
			head = temp->next;
			delete temp;
			++finish;
		}
		else
		{
			while (temp->next)
			{
				if (temp->next->m_Name == Name)
				{
					ptemp = temp->next;
					temp->next = temp->next->next;
					delete ptemp;
					++finish;
					break;
				}
				temp = temp->next;
			}
			if (temp->m_Name == Name)
			{
				temp->next = nullptr;
			}
		}
		temp = head;
		ofstream ofile;
		//*****************写入文件****************//
		ofile.open("职工信息表.txt", ios::out);
		if (!finish)
		{
			cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
			return;
		}
		if (!head)
		{
			cout << "信息删除成功!" << endl;
			cout << "即将返回删除菜单" << endl << endl;
			return;
		}
		while (temp->next)
		{
			ofile << temp->m_Name << endl;
			ofile << temp->m_Sex << endl;
			ofile << temp->m_Department << endl;
			ofile << temp->m_ID << endl;
			ofile << temp->m_Salary << endl;
			ofile << temp->m_Tel << endl;
			temp = temp->next;
		}
		ofile << temp->m_Name << endl;
		ofile << temp->m_Sex << endl;
		ofile << temp->m_Department << endl;
		ofile << temp->m_ID << endl;
		ofile << temp->m_Salary << endl;
		ofile << temp->m_Tel << endl;
		ofile.close();
		cout << "信息删除成功!" << endl << "即将返回删除菜单" << endl << endl;
	}
	else//存在多个与用户输入的姓名相同的职工
	{
		cout << "存在" << number << "个相同姓名的职工!" << endl;
		//打印相同姓名的职工信息
		while (tempToSave->next)
		{
			cout << *tempToSave << endl;
			tempToSave = tempToSave->next;
		}
		tempToSave = HeadTempSave;
		cout <<	"1).删除该姓名全部职工信息\n2).输入工号精确删除该姓名的职工信息" << endl;
		cout << "请输入您的选择: ";
		char select[80];
		string SelectId;
		cin.getline(select, 80);
		//*****************输入检测****************//
		while (select[1] != '\0' || select[0] < '1' || select[0] > '2')
		{
			cout << "输入错误!请重新输入: ";
			cin.getline(select, 80);
		}
		switch (select[0])
		{
			case '1':
			{
				//*****************写入文件前判断是否删除信息是否有效****************//
				if (temp->m_Department == "Null" || temp->m_Department == "")
				{
					cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
					return;
				}
				Employee * ptemp = new Employee;//储存删除姓名后的职工信息
				Employee * HeadPtemp = ptemp;
				//*****************删除职工信息****************//
				while (temp->next)
				{
					if (temp->m_Name != Name)
					{
						++finish;
						*ptemp = *temp;
						ptemp->next = new Employee;
						ptemp = ptemp->next;
					}
					temp = temp->next;
				}
				if (temp->m_Name != Name)
				{
					++finish;
					*ptemp = *temp;
					ptemp->next = new Employee;
					ptemp = ptemp->next;
				}
				ptemp->next = nullptr;
				ptemp = HeadPtemp;
				temp = head;
				ofstream ofile;
				//*****************写入文件****************//
				ofile.open("职工信息表.txt", ios::out);
				if (!finish)
				{
					cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
					return;
				}
				if (!HeadPtemp)
				{
					cout << "信息删除成功!" << endl;
					cout << "即将返回查询菜单" << endl << endl;
					return;
				}

				while (ptemp->next)
				{
					ofile << ptemp->m_Name << endl;
					ofile << ptemp->m_Sex << endl;
					ofile << ptemp->m_Department << endl;
					ofile << ptemp->m_ID << endl;
					ofile << ptemp->m_Salary << endl;
					ofile << ptemp->m_Tel << endl;
					ptemp = ptemp->next;
				}
				ofile.close();
				cout << "信息删除成功!" << endl;
				cout << "即将返回删除菜单" << endl << endl;
			}
				break;
			case '2':
			{
				cout << "请输入工号精确删除该姓名的职工信息" << endl;
				string ID;
				cout << "请输入需要删除职工信息的职工工号(工号为6位数字) ";
				l:getline(cin, ID);
				int Idnumber = 0;//记录符合输入工号的职工数
				//*****************输入检测****************//
				while (!AsIdOrTel(ID) || ID.size() != (unsigned)6)
				{
					cout << "输入错误!请重新输入: ";
					getline(cin, ID);
				}
				while (tempToSave->next)
				{
					if (tempToSave->m_ID == ID)
					{
						++Idnumber;
					}
					tempToSave = tempToSave->next;
				}
				tempToSave = HeadTempSave;
				if (Idnumber)
					DeleteByID(ID);
				else//提示工号不为上述姓名相同的任意一名职工工号
				{
					cout << "所输入的工号不为上述姓名相同的任意一名职工工号!" << endl;
					cout << "请重新输入:";
					goto l;//跳转至重新输入工号
				}
			}
				break;
			default:
				break;
		}
		
	}
}

//****************通过工号查找职工信息并删除****************//
void Employee::DeleteByID(string ID)//重载版本:接收删除菜单中传递进来的工号
{
	ifstream ifile;
	ifile.open("职工信息表.txt", ios::in);
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	//*****************读取文件操作***************//
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	temp->next = nullptr;
	temp = head;
	//*****************写入文件前判断是否删除信息是否有效****************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
		return;
	}
	Employee * ptemp = nullptr;
	//*****************删除职工信息****************//
	if (temp->m_ID == ID)
	{
		head = temp->next;
		delete temp;
		++finish;
	}
	else
	{
		while (temp->next)
		{
			if (temp->next->m_ID == ID)
			{
				ptemp = temp->next;
				temp->next = temp->next->next;
				delete ptemp;
				++finish;
				break;
			}
			temp = temp->next;
		}
		if (temp->m_ID == ID)
		{
			temp->next = nullptr;
		}
	}
	temp = head;
	ifile.close();
	ofstream ofile;
	//*****************写入文件****************//
	ofile.open("职工信息表.txt", ios::out);
	if (!finish)
	{
		cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
		return;
	}
	if (!head)
	{
		cout << "信息删除成功!" << endl;
		cout << "即将返回删除菜单" << endl << endl;
		return;
	}

	while (temp->next)
	{
		ofile << temp->m_Name << endl;
		ofile << temp->m_Sex << endl;
		ofile << temp->m_Department << endl;
		ofile << temp->m_ID << endl;
		ofile << temp->m_Salary << endl;
		ofile << temp->m_Tel << endl;
		temp = temp->next;
	}
	ofile << temp->m_Name << endl;
	ofile << temp->m_Sex << endl;
	ofile << temp->m_Department << endl;
	ofile << temp->m_ID << endl;
	ofile << temp->m_Salary << endl;
	ofile << temp->m_Tel << endl;
	ofile.close();
	cout << "信息删除成功!" << endl;
	cout << "即将返回删除菜单" << endl << endl;
}
//********通过工号查找职工信息并删除********//
void Employee::DeleteByID()
{
	ifstream ifile;
	ifile.open("职工信息表.txt", ios::in);
	string ID;
	cout << "请输入需要删除的职工工号(工号为6位数字): ";
	getline(cin, ID);
	//*****************输入检测****************//
	while (!AsIdOrTel(ID) || ID.size() != (unsigned)6)
	{
		cout << "输入错误!请重新输入: ";
		getline(cin, ID);
	}
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	//*****************读取文件操作***************//
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	temp->next = nullptr;
	temp = head;
	//*****************写入文件前判断是否删除信息是否有效****************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
		return;
	}
	Employee * ptemp = nullptr;
	//*****************删除职工信息****************//
	if (temp->m_ID == ID)
	{
		head = temp->next;
		delete temp;
		++finish;
	}
	else
	{
		while (temp->next)
		{
			if (temp->next->m_ID == ID)
			{
				ptemp = temp->next;
				temp->next = temp->next->next;
				delete ptemp;
				++finish;
				break;
			}
			temp = temp->next;
		}
		if (temp->m_ID == ID)
		{
			temp->next = nullptr;
		}
	}
	temp = head;
	ifile.close();
	ofstream ofile;
	//*****************写入文件****************//
	ofile.open("职工信息表.txt", ios::out);
	if (!finish)
	{
		cout << "没有输入职工信息无法删除!" << endl << "即将返回删除菜单" << endl << endl;
		return;
	}
	if (!head)
	{
		cout << "信息删除成功!" << endl;
		cout << "即将返回删除菜单" << endl << endl;
		return;
	}

	while (temp->next)
	{
		ofile << temp->m_Name << endl;
		ofile << temp->m_Sex << endl;
		ofile << temp->m_Department << endl;
		ofile << temp->m_ID << endl;
		ofile << temp->m_Salary << endl;
		ofile << temp->m_Tel << endl;
		temp = temp->next;
	}
	ofile << temp->m_Name << endl;
	ofile << temp->m_Sex << endl;
	ofile << temp->m_Department << endl;
	ofile << temp->m_ID << endl;
	ofile << temp->m_Salary << endl;
	ofile << temp->m_Tel << endl;
	ofile.close();
	cout << "信息删除成功!" << endl ;
	cout << "即将返回删除菜单" << endl << endl;
}

//*****************删除全部职工信息******************//
void Employee::DeleteAllInfo()
{
	if (!remove("职工信息表.txt"))
		cout << "文件删除成功!" << endl;
	else
		cout << "文件删除失败!(可能没有输入职工信息!)" << endl;
	cout << "即将返回主菜单" << endl << endl;
}

//***************输入工号查找职工信息并修改****************//
void Employee::ChangeByID()
{
	ifstream ifile;
	ifile.open("职工信息表.txt", ios::in);
	string ID;
	cout << "请输入需要修改职工信息的职工工号(工号为6位数字) ";
	getline(cin, ID);
	//*****************输入检测****************//
	while (!AsIdOrTel(ID) || ID.size() != (unsigned)6)
	{
		cout << "输入错误!请重新输入: ";
		getline(cin, ID);
	}
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	//*****************读取文件操作****************//
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	ifile.close();
	temp->next = nullptr;
	temp = head;
	int finishnum = 0;
	//*****************判断写入文件前修改信息是否有效****************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法修改!" << endl << "即将返回修改菜单" << endl << endl;
		return;
	}
	cout << "请输入所需修改的职工信息\n";	
	this->rsetName();
	this->rsetSex();
	this->rsetDepartment();
	this->m_ID = ID;
	this->rsetSalary();
	this->rsetTel();
	//*****************修改操作****************//
	if (this->m_ID == temp->m_ID)
	{
		temp->m_ID = this->m_ID;
		temp->m_Department = this->m_Department;
		temp->m_Name = this->m_Name;
		temp->m_Salary = this->m_Salary;
		temp->m_Sex = this->m_Sex;
		temp->m_Tel = this->m_Tel;
		++finishnum;
	}
	else
	{
		while (temp->next)
		{

			if (this->m_ID == temp->m_ID)
			{
				temp->m_ID = this->m_ID;
				temp->m_Department = this->m_Department;
				temp->m_Name = this->m_Name;
				temp->m_Salary = this->m_Salary;
				temp->m_Sex = this->m_Sex;
				temp->m_Tel = this->m_Tel;
				++finishnum;
				break;
			}
			temp = temp->next;
		}
		if (this->m_ID == temp->m_ID)
		{
			temp->m_ID = this->m_ID;
			temp->m_Department = this->m_Department;
			temp->m_Name = this->m_Name;
			temp->m_Salary = this->m_Salary;
			temp->m_Sex = this->m_Sex;
			temp->m_Tel = this->m_Tel;
			++finishnum;
		}
	}
	temp = head;
	if (!finishnum)
	{
		cout << "没有输入职工信息无法修改!" << endl << "即将返回修改菜单" << endl << endl;
		return;
	}
	ofstream ofile;
	//*****************写入文件****************//
	ofile.open("职工信息表.txt", ios::out);
	while (temp->next)
	{
		ofile << temp->m_Name << endl;
		ofile << temp->m_Sex << endl;
		ofile << temp->m_Department << endl;
		ofile << temp->m_ID << endl;
		ofile << temp->m_Salary << endl;
		ofile << temp->m_Tel << endl;
		temp = temp->next;
	}
	ofile << temp->m_Name << endl;
	ofile << temp->m_Sex << endl;
	ofile << temp->m_Department << endl;
	ofile << temp->m_ID << endl;
	ofile << temp->m_Salary << endl;
	ofile << temp->m_Tel << endl;
	ofile.close();
	cout << "信息修改成功!" << endl;
	cout << "即将返回修改菜单" << endl << endl;
}

//*****************通过姓名查找职工信息并修改****************//
void Employee::ChangeByName()
{
	ifstream ifile;
	ifile.open("职工信息表.txt", ios::in);
	string Name;
	cout << "请输入需要修改的职工姓名: ";
	getline(cin, Name);
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	//*****************读取文件操作***************//
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	temp->next = nullptr;
	temp = head;
	ifile.close();
	//*****************写入文件前判断是否删除信息是否有效****************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法修改!" << endl << "即将返回修改菜单" << endl << endl;
		return;
	}
	int number = 0;//记录姓名与用户输入姓名相同的职工数
	Employee * tempToSave = new Employee;//记录姓名相同的职工信息
	Employee * HeadTempSave = tempToSave;
	//记录姓名相同的职工信息
	while (temp->next)
	{
		if (temp->m_Name == Name)
		{
			++number;
			*tempToSave = *temp;
			tempToSave->next = new Employee;
			tempToSave = tempToSave->next;
		}
		temp = temp->next;
	}
	if (temp->m_Name == Name)
	{
		++number;
		*tempToSave = *temp;
		tempToSave->next = new Employee;
		tempToSave = tempToSave->next;
	}
	tempToSave->next = nullptr;
	tempToSave = HeadTempSave;
	temp = head;
	if (number == 0)//不存在与用户输入的姓名相同的职工信息
		cout << "没有输入该姓名的职工信息!" << endl << "即将返回修改菜单" << endl << endl;
	else if (number == 1)//仅存在一名与用户输入的姓名相同的职工
	{
		cout << "请输入所需修改的职工信息\n";
		this->rsetName();
		this->rsetSex();
		this->rsetDepartment();
		this->rsetSalary();
		this->rsetTel();
		//*****************写入文件前判断是否删除信息是否有效****************//
		if (temp->m_Department == "Null" || temp->m_Department == "")
		{
			cout << "没有输入职工信息无法修改!" << endl << "即将返回修改菜单" << endl << endl;
			return;
		}
		Employee * ptemp = nullptr;
		//*****************修改职工信息****************//
		if (temp->m_Name == Name)
		{
			temp->m_Department = this->m_Department;
			temp->m_Name = this->m_Name;
			temp->m_Salary = this->m_Salary;
			temp->m_Sex = this->m_Sex;
			temp->m_Tel = this->m_Tel;
			++finish;
		}
		else
		{
			while (temp->next)
			{
				if (temp->m_Name == Name)
				{
					temp->m_Department = this->m_Department;
					temp->m_Name =  this->m_Name;
					temp->m_Salary = this->m_Salary;
					temp->m_Sex = this->m_Sex;
					temp->m_Tel = this->m_Tel;
					++finish;
					break;
				}
				temp = temp->next;
			}
			if (temp->m_Name == Name)
			{
				temp->m_Department = this->m_Department;
				temp->m_Name = this->m_Name;
				temp->m_Salary = this->m_Salary;
				temp->m_Sex = this->m_Sex;
				temp->m_Tel = this->m_Tel;
				++finish;
			}
		}
		temp = head;
		ofstream ofile;
		//*****************写入文件****************//
		ofile.open("职工信息表.txt", ios::out);
		if (!finish)
		{
			cout << "没有输入职工信息无法修改!" << endl << "即将返回修改菜单" << endl << endl;
			return;
		}
		if (!head)
		{
			cout << "信息修改成功!" << endl;
			cout << "即将返回修改菜单" << endl << endl;
			return;
		}
		while (temp->next)
		{
			ofile << temp->m_Name << endl;
			ofile << temp->m_Sex << endl;
			ofile << temp->m_Department << endl;
			ofile << temp->m_ID << endl;
			ofile << temp->m_Salary << endl;
			ofile << temp->m_Tel << endl;
			temp = temp->next;
		}
		ofile << temp->m_Name << endl;
		ofile << temp->m_Sex << endl;
		ofile << temp->m_Department << endl;
		ofile << temp->m_ID << endl;
		ofile << temp->m_Salary << endl;
		ofile << temp->m_Tel << endl;
		ofile.close();
		cout << "信息修改成功!" << endl << "即将返回修改菜单" << endl << endl;
	}
	else//存在多名与用户输入的姓名相同的职工信息
	{
		cout << "存在" << number << "个相同姓名的职工!" << endl;
		while (tempToSave->next)
		{
			cout << *tempToSave << endl;
			tempToSave = tempToSave->next;
		}
		tempToSave = HeadTempSave;
		cout << "请输入工号精确修改该姓名的职工信息" << endl;
		string ID;
		cout << "请输入需要修改职工信息的职工工号(工号为6位数字) ";
		l:getline(cin, ID);
		int Idnumber = 0;
		//*****************输入检测****************//
		while (!AsIdOrTel(ID) || ID.size() != (unsigned)6)
		{
			cout << "输入错误!请重新输入: ";
			getline(cin, ID);
		}
		while (tempToSave->next)
		{
			if (tempToSave->m_ID == ID)
			{
				++Idnumber;
			}
			tempToSave = tempToSave->next;
		}
		tempToSave = HeadTempSave;
		if (Idnumber)
			ChangeByID(ID);
		else
		{
			cout << "所输入的工号不为上述姓名相同的任意一名职工工号!" << endl;
			cout << "请重新输入:";
			goto l;//跳转至重新输入
		}
	}
}

//****************通过姓名查找职工信息并修改****************//
void Employee::ChangeByID(string ID)//重载版本:接收修改菜单中传递的工号
{
	ifstream ifile;
	ifile.open("职工信息表.txt", ios::in);
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	//*****************读取文件操作****************//
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	ifile.close();
	temp->next = nullptr;
	temp = head;
	int finishnum = 0;
	cout << "请输入所需修改的职工信息\n";
	this->rsetName();
	this->rsetSex();
	this->rsetDepartment();
	this->m_ID = ID;
	this->rsetSalary();
	this->rsetTel();
	//*****************判断写入文件前修改信息是否有效****************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法修改!" << endl << "即将返回修改菜单" << endl << endl;
		return;
	}
	//*****************修改操作****************//
	if (this->m_ID == temp->m_ID)
	{
		temp->m_ID = this->m_ID;
		temp->m_Department = this->m_Department;
		temp->m_Name = this->m_Name;
		temp->m_Salary = this->m_Salary;
		temp->m_Sex = this->m_Sex;
		temp->m_Tel = this->m_Tel;
		++finishnum;
	}
	else
	{
		while (temp->next)
		{

			if (this->m_ID == temp->m_ID)
			{
				temp->m_ID = this->m_ID;
				temp->m_Department = this->m_Department;
				temp->m_Name = this->m_Name;
				temp->m_Salary = this->m_Salary;
				temp->m_Sex = this->m_Sex;
				temp->m_Tel = this->m_Tel;
				++finishnum;
				break;
			}
			temp = temp->next;
		}
		if (this->m_ID == temp->m_ID)
		{
			temp->m_ID = this->m_ID;
			temp->m_Department = this->m_Department;
			temp->m_Name = this->m_Name;
			temp->m_Salary = this->m_Salary;
			temp->m_Sex = this->m_Sex;
			temp->m_Tel = this->m_Tel;
			++finishnum;
		}
	}
	temp = head;
	if (!finishnum)
	{
		cout << "没有输入职工信息无法修改!" << endl << "即将返回修改菜单" << endl << endl;
		return;
	}
	ofstream ofile;
	//*****************写入文件****************//
	ofile.open("职工信息表.txt", ios::out);
	while (temp->next)
	{
		ofile << temp->m_Name << endl;
		ofile << temp->m_Sex << endl;
		ofile << temp->m_Department << endl;
		ofile << temp->m_ID << endl;
		ofile << temp->m_Salary << endl;
		ofile << temp->m_Tel << endl;
		temp = temp->next;
	}
	ofile << temp->m_Name << endl;
	ofile << temp->m_Sex << endl;
	ofile << temp->m_Department << endl;
	ofile << temp->m_ID << endl;
	ofile << temp->m_Salary << endl;
	ofile << temp->m_Tel << endl;
	ofile.close();
	cout << "信息修改成功!" << endl;
	cout << "即将返回修改菜单" << endl << endl;
}

//*****************修改职工信息菜单******************//
void Employee::ChangeInfo()
{
	cout << "1).输入职工工号修改职工信息\n"
		<< "2).输入职工姓名修改职工信息\n"
		<< "3).返回主菜单" << endl;
	char select[80] = { 0 };
	cout << "请输入您的选择: ";
	cin.getline(select, 80);
	//*****************输入检测****************//
	while (select[1] != '\0' || select[0] < '1' || select[0] > '3')
	{
		cout << "输入错误!请重新输入: ";
		cin.getline(select, 80);
	}
	while (select[0] > '0' && select[0] < '3')
	{
		switch (select[0])
		{
		case '1':
			ChangeByID();
			break;
		case '2':
			ChangeByName();
			break;
		default:
			break;
		}
		cout << "1).输入职工工号修改职工信息\n"
			<< "2).输入职工姓名修改职工信息\n"
			<< "3).返回主菜单" << endl;
		cout << "请输入您的选择: ";
		cin.getline(select, 80);
		while (select[1] != '\0' || select[0] < '1' || select[0] > '3')
		{
			cout << "输入错误!请重新输入: ";
			cin.getline(select, 80);
		}
	}
	cout << "即将返回主菜单" << endl << endl;
}

//*****************删除职工信息菜单******************//
void Employee::DeleteInfo()
{
	cout << "1).输入职工工号删除职工信息\n"
		<< "2).输入职工姓名删除职工信息\n"
		<< "3).返回主菜单" << endl;
	char select[80] = { 0 };
	cout << "请输入您的选择: ";
	cin.getline(select, 80);
	//*****************输入检测****************//
	while (select[1] != '\0' || select[0] < '1' || select[0] > '3')
	{
		cout << "输入错误!请重新输入: ";
		cin.getline(select, 80);
	}
	while (select[0] > '0' && select[0] < '3')
	{
		switch (select[0])
		{
		case '1':
			DeleteByID();
			break;
		case '2':
			DeleteByName();
			break;
		default:
			break;
		}
		cout << "1).输入职工工号删除职工信息\n"
			<< "2).输入职工姓名删除职工信息\n"
			<< "3).返回主菜单" << endl;
		cout << "请输入您的选择: ";
		cin.getline(select, 80);
		while (select[1] != '\0' || select[0] < '1' || select[0] > '3')
		{
			cout << "输入错误!请重新输入: ";
			cin.getline(select, 80);
		}
	}
	cout << "即将返回主菜单" << endl << endl;
}

//*****************依据工资排序输出******************//
void Employee::SortAndOutput()
{
	ifstream ifile;
	//*****************读取文件操作****************//
	ifile.open("职工信息表.txt", ios::in);
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	temp->next = nullptr;
	ifile.close();
	temp = head;
	head = sortList(temp);//排序职工信息
	temp = head;
	//*****************输出前判断排序是否有效******************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法排序!" << endl << "即将返回主菜单" << endl << endl;
		return;
	}
	cout << "排序结果为: \n";
	while (temp->next)
	{
		cout << *temp << endl;
		temp = temp->next;
	}
	if (temp->m_Department == "Null" || temp->m_Department == "")
		return;
	cout << *temp;
	cout << "即将返回主菜单" << endl << endl;
}

//*****************依据科室输出各科室工资平均值******************//
void Employee::StatisticAndAverage()
{
	ifstream ifile;
	//******************读取文件操作*****************//
	ifile.open("职工信息表.txt", ios::in);
	char name[80];
	char department[80];
	char sex[80];
	char Id[80];
	char salary[80];
	char Tel[80];
	int finish = 0;
	Employee * head;
	Employee * temp = new Employee;
	head = temp;
	ifile.getline(name, 80);
	ifile.getline(sex, 80);
	ifile.getline(department, 80);
	ifile.getline(Id, 80);
	ifile.getline(salary, 80);
	ifile.getline(Tel, 80);
	temp->m_Name = name;
	temp->m_Sex = sex;
	temp->m_Department = department;
	temp->m_ID = Id;
	temp->m_Salary = salary;
	temp->m_Tel = Tel;
	while (ifile.peek() != EOF)
	{
		temp->next = new Employee;
		temp = temp->next;
		ifile.getline(name, 80);
		ifile.getline(sex, 80);
		ifile.getline(department, 80);
		ifile.getline(Id, 80);
		ifile.getline(salary, 80);
		ifile.getline(Tel, 80);
		temp->m_Name = name;
		temp->m_Sex = sex;
		temp->m_Department = department;
		temp->m_ID = Id;
		temp->m_Salary = salary;
		temp->m_Tel = Tel;
	}
	temp->next = nullptr;
	ifile.close();
	temp = head;
	Node * p = new Node;
	Node * nhead = p;
	double number = 0.0;
	double psum = 0.0;
	double tsum = 0.0;
	stringstream translate;
	//******************统计各科室人数及工资总和*****************//
	while (temp->next)
	{
		if (p->isRepeat(p, temp->m_Department))//存在相同科室时
		{
			//******************string类型与double类型互相转换*****************//
			translate << p->m_number;
			translate >> number;
			++number;//该科室职工人数增加
			translate.clear();
			translate << number;
			translate >> p->m_number;
			translate.clear();
			translate << p->m_sum;
			translate >> psum;
			translate.clear();
			translate << temp->m_Salary;
			translate >> tsum;
			translate.clear();
			psum += tsum;//统计该科室工资总计
			translate << psum;
			translate >> p->m_sum;
			translate.clear();
		}
		else
		{
			p->m_department = temp->m_Department;//创建新科室
			translate << p->m_number;
			translate >> number;
			++number;
			translate.clear();
			translate << number;
			translate >> p->m_number;
			translate.clear();
			translate << p->m_sum;
			translate >> psum;
			translate.clear();
			translate << temp->m_Salary;
			translate >> tsum;
			translate.clear();
			psum += tsum;
			translate << psum;
			translate >> p->m_sum;
			translate.clear();
			p->next = new Node;
			p = p->next;
		}
		temp = temp->next;
	}
	//*****************对链表末尾未处理的数据进行相同操作******************//
	if (p->isRepeat(p, temp->m_Department))
	{
		translate << p->m_number;
		translate >> number;
		translate.clear();
		++number;
		translate << number;
		translate >> p->m_number;
		translate.clear();
		translate << p->m_sum;
		translate >> psum;
		translate.clear();
		translate << temp->m_Salary;
		translate >> tsum;
		translate.clear();
		psum += tsum;
		translate << psum;
		translate >> p->m_sum;
		translate.clear();
	}
	else
	{
		p->m_department = temp->m_Department;
		translate << p->m_number;
		translate >> number;
		translate.clear();
		++number;
		translate << number;
		translate >> p->m_number;
		translate.clear();
		translate << p->m_sum;
		translate >> psum;
		translate.clear();
		translate << temp->m_Salary;
		translate >> tsum;
		translate.clear();
		psum += tsum;
		translate << psum;
		translate >> p->m_sum;
		translate.clear();
		p->next = new Node;
		p = p->next;
	}
	p = nhead;
	//*****************输出前判断是否存在职工信息******************//
	if (temp->m_Department == "Null" || temp->m_Department == "")
	{
		cout << "没有输入职工信息无法输出!" << endl << "即将返回主菜单" << endl << endl;
		return;
	}
	while (p->next)
	{
		translate << p->m_sum;
		translate >> psum;
		translate.clear();
		translate << p->m_number;
		translate >> number;
		translate.clear();
		cout << p->m_department << "科室的平均工资为: " << (double)psum / number << endl;
		p = p->next;
	}
	cout << "即将返回主菜单" << endl << endl;
}