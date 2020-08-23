#pragma once

#include "BitMap.h"
#include <stdexcept>
#include <cstdint>
#include <string>
#include <ctime>
#include <iostream>
using std::string;
using std::move;
extern BitMap* bitMap;
class PCB
{
public:
	enum Status
	{
		ready,
		run,
		wait
	};
private:
	uint16_t m_pid = 0; //进程id
	string m_pName = ""; //进程名
	Status m_status = ready;//进程状态
	string m_owner = "";//进程拥有者
	clock_t m_estimatedTime = 0;//进程预估时间
	clock_t m_arriveTime = 0; //进程到达时间
	clock_t m_finishedTime = 0; //进程完成时间
	clock_t m_runningTime = 0;//进程运行时间
	clock_t m_remainingTime = 0;//进程剩余时间

public:
//	PCB() {}
	PCB(const string& pName = "sys", Status status = ready,
		const string& owner = "system", clock_t estimatedTime = 0,
		clock_t arriveTime = 0);
	PCB(const PCB& pcb) = delete;
	PCB(PCB&& pcb) noexcept;
	PCB& operator=(PCB&& pcb) noexcept;
	PCB& operator=(const PCB& pcb) = delete;
	~PCB();

	void CalculateRemainingTime();//计算进程剩余时间
	inline void SetPName(string&& pName);
	inline void SetStatus(PCB::Status status);
	inline void SetOwner(string&& owner);
	inline void SetEstimatedTime(const clock_t& estimatedTime);

	inline void SetRunningTime(const clock_t& runningTime);
	inline void SetArriveTime(const clock_t& arriveTime);
	inline void SetFinishedTime(const clock_t& finishedTime);

	inline const clock_t& GetArriveTime() const { return m_arriveTime; }
	inline const clock_t& GetFinishedTime() const { return m_finishedTime; }
	inline const uint16_t GetPid() const { return m_pid; }
	inline const string& GetPName() const { return m_pName; }
	inline const Status GetStatus() const { return m_status; }
	inline const string& GetOwner() const { return m_owner; }
	inline const clock_t& GetEstimatedTime() const { return m_estimatedTime; }
	inline const clock_t& GetRunningTime() const { return m_runningTime; }
	inline const clock_t& GetRemainingTime() const { return m_remainingTime; }
};

inline void PCB::SetPName(string&& pName)
{
	m_pName = move(pName);
}

inline void PCB::SetStatus(PCB::Status status)
{
	m_status = status;
}


inline void PCB::SetOwner(string&& owner)
{
	m_owner = move(owner);
}

inline void PCB::SetEstimatedTime(const clock_t& estimatedTime)
{
	m_estimatedTime = estimatedTime;
}

inline void PCB::SetRunningTime(const clock_t& runningTime)
{
	m_runningTime = runningTime;
}

inline void PCB::SetArriveTime(const clock_t& arriveTime)
{
	m_arriveTime = arriveTime;
}

inline void PCB::SetFinishedTime(const clock_t& finishedTime)
{
	m_finishedTime = finishedTime;
}
