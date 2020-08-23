#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <string>
using std::string;

class Employee
{
private:
	string m_Name;//职工姓名
	string m_Sex;//职工性别
	string m_Department;//职工科室
	string m_Salary;//职工工资
	string m_ID;//职工工号
	string m_Tel;//职工电话
	Employee * next;

	void rsetName();//重设姓名
	void rsetSex();//重设性别
	void rsetID();//重设工号
	void rsetTel();//重设电话
	void rsetDepartment();//重设科室
	void rsetSalary();//重设工资

	void QueryByID();//通过工号查找职工信息
	void QueryByName();//通过姓名查找职工信息
	void QueryByDepartment();//通过科室查找职工信息

	void DeleteByID(string ID);//通过工号查找职工信息并删除
	void DeleteByID();//通过工号查找职工信息并删除
	void DeleteByName();//通过姓名查找职工信息并删除

	void ChangeByID(string ID); //通过工号查找职工信息并修改
	void ChangeByID();//通过工号查找职工信息并修改
	void ChangeByName();//通过姓名查找职工信息并修改

	void swap(Employee * a, Employee * b);//交换a，b信息
	Employee *partion(Employee *pBegin, Employee *pEnd);//拆分链表
	void quick_sort(Employee *pBegin, Employee *pEnd);//快速排序
	Employee* sortList(Employee* head);//链表排序
	friend std::istream & operator >> (std::istream & is, Employee & e);//重载输入运算符
	friend std::ostream & operator << (std::ostream & os, Employee & e);//重载输出运算符
	bool AsIdOrTel(string str);//判断字符串str能否为工号或电话号码
	bool AsSalary(string str);//判断字符串str能否为工资数

public:
	Employee(string name = "Null", string sex = "Null", string ID = "0", string Tel = "0", string department = "Null", string salary = "0") :
		m_Name(name), m_Sex(sex), m_ID(ID), m_Tel(Tel), m_Department(department), m_Salary(salary) {}
	~Employee() {}

	void InputToFile();//输入职工信息至文件
	void Query();//查询职工信息
	void ChangeInfo();//修改职工信息
	void DeleteInfo();//删除职工信息
	void DeleteAllInfo();//删除全体信息
	void SortAndOutput();//排序并输出
	void StatisticAndAverage();//分科室进行统计，计算各科室的平均值
};

//**************员工部分信息结构******************
class Node
{
public:
	string m_department;
	string m_number;
	string m_sum;
	Node * next;
	int isRepeat(Node * p, string department);//判断是否已存在相同的部门
	Node(string department = "Null", string number = "0", string sum = "0", Node * n = nullptr) : m_department(department), m_number(number), m_sum(sum), next(n) {}
};

#endif