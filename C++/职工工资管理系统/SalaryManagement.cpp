#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include "Employee.h"
#include "SalaryManagementSystem.h"

using std::ostream;
using std::istream;
using std::cout;
using std::cin;
using std::string;
using std::ios;
using std::ofstream;
using std::ifstream;
using std::endl;

SalaryManagementSystem::SalaryManagementSystem(string name, string sex, string ID, string Tel, string department, string salary) : person(name, sex, ID, Tel, department, salary)
{
	cout << "******************欢迎来到职工工资管理系统**********************\n"
		<< "*1).输入职工信息				2).查询职工信息*\n"
		<< "*3).修改职工信息				4).删除职工信息*\n"
		<< "*5).依据工资对职工信息排序输出		        6).删除全体信息*\n"
		<< "*7).输出各科室的平均工资			8).退出管理系统*\n"
		<< "****************************************************************\n"
		<< "请输入您的选择: ";

	char select[80] = { 0 };
	cin.getline(select, 80);
	while (select[1] != '\0' || select[0] < '1' || select[0] > '8')//检测输入是否正确
	{
		cout << "输入错误!请重新输入: ";
		cin.getline(select, 80);
	}
	while (select[0] > '0' && select[0] < '8')
	{
		switch (select[0])
		{
		case '1':
			person.InputToFile();
			break;
		case '2':
			person.Query();
			break;
		case '3':
			person.ChangeInfo();
			break;
		case '4':
			person.DeleteInfo();
			break;
		case '5':
			person.SortAndOutput();
			break;
		case '6':
			person.DeleteAllInfo();
			break;
		case '7':
			person.StatisticAndAverage();
			break;
		default:
			break;
		}
		cout << "****************************************************************\n"
			<< "*1).输入职工信息				2).查询职工信息*\n"
			<< "*3).修改职工信息				4).删除职工信息*\n"
			<< "*5).依据工资对职工信息排序输出		        6).删除全体信息*\n"
			<< "*7).输出各科室的平均工资			8).退出管理系统*\n"
			<< "****************************************************************\n"
			<< "请输入您的选择: ";
		cin.getline(select, 80);
		while (select[1] != '\0' || select[0] < '1' || select[0] > '8')
		{
			cout << "输入错误!请重新输入: ";
			cin.getline(select, 80);
		}
	}
	cout << "再见!(职工工资管理系统将在3秒种后关闭！)";
	Sleep(3000);//延迟退出时间
}