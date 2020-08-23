#ifndef SALARYMANAGEMENTSYSTEM_H_
#define SALARYMANAGEMENTSYSTEM_H_

#include "Employee.h"

//工资管理系统类
class SalaryManagementSystem
{
private:
	Employee person;
public:
	SalaryManagementSystem(string name = "Null", string sex = "Null", string ID = "0", string Tel = "0", string department = "Null", string salary = "0");
	~SalaryManagementSystem() {}
};

#endif