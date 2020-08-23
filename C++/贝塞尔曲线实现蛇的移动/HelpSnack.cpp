#include "HelpSnack.h"

double HelpSnack::Simplify(int n, int m) const
{
	if (m > n)
	{
		return 0.0;
	}
	if (m < n / 2.0)
	{
		m = n - m;
	}
	double s1 = 0.0;
	for (int i = m + 1; i <= n; i++)
	{
		s1 += log((double)i);
	}
	double s2 = 0.0;
	int ub = n - m;
	for (int i = 2; i <= ub; i++)
	{
		s2 += log((double)i);
	}
	return s1 - s2;
}


inline double HelpSnack::CombinationNumber(int n, int m) const
{
	if (m > n)
	{
		return 0.0;
	}
	return exp(Simplify(n, m));
}

inline double HelpSnack::EachItem(int i, int n, double pi, double _t, double t) const
{
	return CombinationNumber(n, i) * pi * pow(_t, n - i) * pow(t, i);
}

void HelpSnack::CalculateBezierCurve(double incream)
{
	double  t = 0.0;//曲线参数t
	double _t = 0.0;
	HelpSnack::point pot = { 0 };
	for (t = 0; t < 1; t += incream)
	{
		_t = 1 - t;
		for (int i = 0; i != m_SnackBody.size(); ++i)
		{
			pot.x += (float)EachItem(i, (int)(m_SnackBody.size() - 1), m_SnackBody[i].x, _t, t);
			pot.y += (float)EachItem(i, (int)(m_SnackBody.size() - 1), m_SnackBody[i].y, _t, t);
		}
		m_BezierCurve.push_back(pot);
		pot.x = 0.0;
		pot.y = 0.0;
	}

}

inline double HelpSnack::IncludedAngle(const HelpSnack::line temp) const
{
	if (temp.tail.x == temp.head.x && temp.tail.y == temp.head.y)
	{
		return 0;
	}
	//正向x轴
	if (temp.tail.x > temp.head.x && temp.tail.y == temp.head.y)
	{
		return 0;
	}
	//负向x轴
	if (temp.tail.x < temp.head.x && temp.tail.y == temp.head.y)
	{
		return M_PI;
	}
	//正向y轴
	if (temp.tail.x == temp.head.x && temp.tail.y > temp.head.y)
	{
		return 90.0 * One;
	}
	//负向y轴
	if (temp.tail.x == temp.head.x && temp.tail.y < temp.head.y)
	{
		return -90.0 * One;
	}
	return atan2(temp.tail.y - temp.head.y, temp.tail.x - temp.head.x);
}

inline double HelpSnack::CurveFunction(double x) const
{
	return m_angleArg.A * sin(m_angleArg.W * (x * One) + m_angleArg.OFF) + m_angleArg.B;
	//	return 30 * sin(3 * (x * (One)));
//		return x;
}

const HelpSnack::point HelpSnack::GetOldOInNew(const HelpSnack::line temp) const
{
	double O = IncludedAngle(temp);
	if (fabs(O - 0) <= 0.000001)
	{
		HelpSnack::point result = { 0 };
		result.x = -temp.head.x;
		result.y = -temp.head.y;
		return result;
	}
	double r = temp.head.x - temp.head.y / tan(O);
	HelpSnack::point result = { 0 };
	result.y = (float)(r * sin(O));
	result.x = (float)(-r * cos(O) - temp.head.y / sin(O));
	return result;
}

const HelpSnack::point HelpSnack::TransformToNew(const HelpSnack::point temp, double O, const HelpSnack::point basePoint) const
{
	HelpSnack::point result = { 0 };
	result.x = (float)(temp.x * cos(O) + temp.y * sin(O) + basePoint.x);
	result.y = (float)(temp.y * cos(O) - temp.x * sin(O) + basePoint.y);
	return result;
}

const HelpSnack::point HelpSnack::TransformToOld(const HelpSnack::point temp, double O, const HelpSnack::point basePoint) const
{
	HelpSnack::point result = { 0 };
	result.x = float(temp.x * cos(O) - temp.y * sin(O) + basePoint.x);
	result.y = float(temp.x * sin(O) + temp.y * cos(O) + basePoint.y);
	return result;
}

const HelpSnack::line HelpSnack::ConstructLine(const HelpSnack::point head, const HelpSnack::point tail) const
{
	HelpSnack::line temp = { head, tail };
	return temp;
}


bool HelpSnack::SnackMove(float* pts, int n, float x, float y)
{
	this->m_SnackBody.clear();
	this->m_BezierCurve.clear();
//	this->m_SnackBody.resize(n / 2);
	HelpSnack::point temp;
	temp.x = pts[0];
	temp.y = pts[1];
	float xmin = x - range;
	float xmax = x + range;
	float ymin = y - range;
	float ymax = y + range;
	if (temp.x >= xmin && temp.x <= xmax && temp.y >= ymin && temp.y <= ymax)
	{
		return false;
	}
	//构造链表
	for (int i = 0; i < n; i += 2)
	{
		temp.x = pts[i];
		temp.y = pts[i + 1];
		m_SnackBody.push_back(temp);
	}
	newPos.x = x;
	newPos.y = y;
	//鼠标移动了
	if (newPos.x != oldPos.x && newPos.y != oldPos.y)
	{
			HelpSnack::point pTempHead;
			HelpSnack::point pTempTail;
			pTempHead.x = pts[0];
			pTempHead.y = pts[1];
			pTempTail.x = x;
			pTempTail.y = y;
			HelpSnack::line newX_Axis = ConstructLine(pTempHead, pTempTail);
			saveAngle = IncludedAngle(newX_Axis);
			saveO = GetOldOInNew(newX_Axis);
			HelpSnack::point newPoint = TransformToNew(pTempHead, saveAngle, saveO);
			newPoint.x += OffSet;
			newPoint.y = (float)CurveFunction(newPoint.x);
			saveN = pTempHead;
			HelpSnack::point oldPoint = TransformToOld(newPoint, saveAngle, saveN);
			//蛇尾部
			if (!m_SnackBody.empty())
				m_SnackBody.pop_back();
			m_SnackBody.push_front(oldPoint);
			oldPos.x = newPos.x;
			oldPos.y = oldPos.y;
	}
	//鼠标没有动
	else
	{
			HelpSnack::point pTempHead;
			pTempHead.x = pts[0];
			pTempHead.y = pts[1];
			HelpSnack::point newPoint = TransformToNew(pTempHead, saveAngle, saveO);
			newPoint.x += OffSet;
			newPoint.y = (float)CurveFunction(newPoint.x);
			HelpSnack::point oldPoint = TransformToOld(newPoint, saveAngle, saveN);
			//蛇尾部
			if (!m_SnackBody.empty())
				m_SnackBody.pop_back();
			m_SnackBody.push_front(oldPoint);
	}


	//原样
	//////int i = 0;
	//////for (auto&& it : m_SnackBody)
	//////{
	//////	pts[i] = it.x;
	//////	pts[i + 1] = it.y;
	//////	i += 2;
	//////}

	//全部贝塞尔
	//构造贝塞尔曲线
	CalculateBezierCurve(1 / (n / 2.0));
	//将贝塞尔曲线赋值
	int i = 0;
	for (auto&& it : m_BezierCurve)
	{
		pts[i] = it.x;
		pts[i + 1] = it.y;
		i += 2;
	}
	return true;
}
