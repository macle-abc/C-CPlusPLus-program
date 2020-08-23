#include "Schedule.h"
void Schedule::clear()
{
	m_readyQueue.clear();
	m_runningProcess.clear();
	m_waitQueue.clear();
}
Schedule::Schedule(uint8_t cpuNums, uint8_t resourceNums)
	:
	m_cpuNums(cpuNums),
	m_resourceNums(resourceNums)
{
	m_AvailableResourceNum = m_resourceNums;
	m_AvailableCPUNum = m_cpuNums;
}


void Schedule::Running(uint8_t possibilityOfSeizingResources)
{
	for (auto it = m_runningProcess.begin(); it != m_runningProcess.end(); )
	{
		//如果已经具有特殊资源
		if (it->second)
		{
			it->first.SetRunningTime(it->first.GetRunningTime() + 1);
			it->first.CalculateRemainingTime();
			++it;
		}
		else
		{
			bool result = (rand() % 100) < possibilityOfSeizingResources ?
				true : false;
			if (result)
			{
				if (m_AvailableResourceNum == 0)
				{
					it->second = false;
					RunningToWait(move(*it));
					it = m_runningProcess.erase(it);
				}
				else
				{
					--m_AvailableResourceNum;
					it->second = true;//占用资源
					it->first.SetRunningTime(it->first.GetRunningTime() + 1);
					it->first.CalculateRemainingTime();
					++it;
				}
			}
			else
			{
				it->first.SetRunningTime(it->first.GetRunningTime() + 1);
				it->first.CalculateRemainingTime();
				++it;
			}
		}
	}
}

void Schedule::AddProcessToReadyQueue(PCB&& process)
{
	Key temp(process.GetPid(), process.GetRemainingTime());
	process.SetStatus(PCB::ready);
	m_readyQueue[temp] = move(make_pair(move(process), false));
}

void Schedule::ReadyToRunning()
{
	if (m_readyQueue.empty())
		return;
	//只移动可使用的CPU资源数目的进程
	if (m_AvailableCPUNum == 0)
	{
		return;
	}
	for (uint8_t i = 0; i < m_AvailableCPUNum; ++i)
	{
		if (!m_readyQueue.empty())
		{
			m_readyQueue.begin()->second.first.SetStatus(PCB::run);
			m_runningProcess.push_back(move((m_readyQueue.begin()->second)));
			m_readyQueue.erase(m_readyQueue.begin());
			m_AvailableCPUNum--;
		}
	}
}

void Schedule::RunningToWait(pair<PCB, bool>&& pcbInfo)
{
	pcbInfo.first.SetStatus(PCB::wait);
	++m_AvailableCPUNum; 
	m_waitQueue.push_back(move(pcbInfo));
}

void Schedule::RunningToEnd()
{
	for (auto it = m_runningProcess.begin(); it != m_runningProcess.end();)
	{
		if (it->first.GetRemainingTime() == 0)
		{
			if (it->second) //进程结束资源释放
				++m_AvailableResourceNum;
			++m_AvailableCPUNum;
			it = m_runningProcess.erase(it);
		}
		else
			++it;
	}
}
static bool cmp(const pair<PCB, bool>& a, const pair<PCB, bool>& b)
{
	return a.first.GetEstimatedTime() > b.first.GetEstimatedTime();
}

void Schedule::WaitToReady()
{
	if (m_AvailableResourceNum > 0)
	{
		//唤醒可用资源数的进程数目
		for (uint8_t i = 0; i < m_AvailableResourceNum; ++i)
		{
			if (!m_waitQueue.empty())
			{
				m_waitQueue.sort(cmp);
				m_waitQueue.back().first.SetStatus(PCB::ready);
				Key temp(m_waitQueue.back().first.GetPid(), m_waitQueue.back().first.GetRemainingTime());
				m_readyQueue[temp] = move(m_waitQueue.back());
				m_waitQueue.pop_back();
			}
		}
	}
}

bool Schedule::KillRunning(uint16_t pid)
{
	for (auto it = m_runningProcess.begin(); it != m_runningProcess.end();)
	{
		if (it->first.GetPid() == pid)
		{
			if (it->second) //进程占用资源则释放
				++m_AvailableResourceNum;
			++m_AvailableCPUNum;
			it = m_runningProcess.erase(it);
			return true;
		}
		else
			++it;
	}
	return false;
}




