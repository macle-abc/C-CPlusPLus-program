#include "PCB.h"
void PCB::CalculateRemainingTime()
{
	if (m_estimatedTime - m_runningTime >= 0)
		m_remainingTime = m_estimatedTime - m_runningTime;
}

PCB::PCB(const string& pName, Status status, const string& owner, clock_t estimatedTime, clock_t arriveTime)
	:	
		m_pName(pName),
		m_status(status),
		m_owner(owner),
		m_estimatedTime(estimatedTime),
		m_remainingTime(estimatedTime),
		m_arriveTime(arriveTime)
{
	bool isOk = false;
	m_pid = BitMapFindFirst(bitMap, &isOk);
	if (!isOk)
	{
		throw std::length_error("pid过大!无法创建进程!");
	}
	else
	{
		BitMapSet(bitMap, m_pid);
	}
}

PCB::PCB(PCB&& pcb) noexcept:
	m_pid(pcb.m_pid),
	m_pName(move(pcb.m_pName)),
	m_status(pcb.m_status),
	m_owner(move(pcb.m_owner)),
	m_estimatedTime(pcb.m_estimatedTime),
	m_runningTime(pcb.m_runningTime),
	m_remainingTime(pcb.m_remainingTime),
	m_arriveTime(pcb.m_arriveTime),
	m_finishedTime(pcb.m_finishedTime)
{
	pcb.m_pid = 0; //复原
}

PCB& PCB::operator=(PCB&& pcb) noexcept
{
	if (this == &pcb)
		return *this;
	if (pcb.m_pid != 0)
		BitMapReset(bitMap, m_pid);
	m_pid = pcb.m_pid;
	pcb.m_pid = 0; //复原

	m_pName = move(pcb.m_pName);
	m_status = pcb.m_status;
	m_owner = move(pcb.m_owner);
	m_estimatedTime = pcb.m_estimatedTime;
	m_runningTime = pcb.m_runningTime;
	m_remainingTime = pcb.m_remainingTime;
	m_arriveTime = pcb.m_arriveTime;
	m_finishedTime = pcb.m_finishedTime;

	return *this;
}

PCB::~PCB()
{
	if (m_pid != 0)
		BitMapReset(bitMap, m_pid);
}






