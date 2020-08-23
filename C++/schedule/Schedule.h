#pragma once
#include "PCB.h"
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <cmath>

using std::list;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;

class Schedule
{
private:
	//私有key类型
	class Key
	{
	public:
		uint16_t m_pid;
		clock_t m_remainingTime;
		Key(uint16_t pid = 0, clock_t remainingTime = 0) :
			m_pid(pid), m_remainingTime(remainingTime) { }

		//重载operator <
		friend bool operator<(const Key& left, const Key& right)
		{
			return left.m_remainingTime < right.m_remainingTime;
		}
	};
private:
	uint8_t m_cpuNums = 0;//逻辑处理器数目
	uint8_t m_resourceNums = 0; //资源数目
	uint8_t m_AvailableResourceNum = 0; //可使用资源数
	uint8_t m_AvailableCPUNum = 0; //可使用CPU资源数
	//就绪队列
	map<Key, pair<PCB, bool>> m_readyQueue;
	list<pair<PCB, bool>> m_runningProcess;
	//等待队列
	list<pair<PCB, bool>> m_waitQueue;
public:

	void clear(); //清空所有队列

	Schedule(uint8_t cpuNums = 1, uint8_t resourceNums = 1);
	Schedule(const Schedule& other) = delete;
	Schedule(Schedule&& other) = delete;
	Schedule& operator=(Schedule&& pcb) = delete;
	Schedule& operator=(const Schedule& pcb) = delete;

	void Running(uint8_t possibilityOfSeizingResources);
	//添加进程到就绪队列
	void AddProcessToReadyQueue(PCB&& process);

	//将进程从就绪队列移动到运行态
	void ReadyToRunning();
	//将进程从运行态移动到等待队列
	void RunningToWait(pair<PCB, bool>&& pcbInfo);
	//将进程从运行态移动到结束队列
	void RunningToEnd();
	//将进程从等待队列移动到就绪队列
	void WaitToReady();
	//终止当前运行进程
	bool KillRunning(uint16_t pid);

	//返回正在运行的进程信息
	inline const list<pair<PCB, bool>>& GetRunningProcess() const { return m_runningProcess; }
	//返回就绪队列信息
	inline const map<Key, pair<PCB, bool>>& GetReadyQueue() const { return m_readyQueue; }
	//返回等待队列信息
	inline const list<pair<PCB, bool>>& GetWaitQueue() const { return m_waitQueue; }
	inline int GetCPUNums() const { return m_cpuNums; }
	inline int GetAvailableCPUNums() const { return m_AvailableCPUNum; }
	inline int GetResourceNums() const { return m_resourceNums; }
	inline int GetAvailableResourceNums() const { return m_AvailableResourceNum; }
	//uint8_t m_cpuNums = 0;//逻辑处理器数目
	//uint8_t m_resourceNums = 0; //资源数目
	//uint8_t m_AvailableResourceNum = 0; //可使用资源数
	//uint8_t m_AvailableCPUNum = 0; //可使用CPU资源数
};
