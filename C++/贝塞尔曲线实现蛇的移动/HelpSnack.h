#pragma once

#include <cmath>
#include <list>
#include <deque>
using std::list;
using std::deque;

class HelpSnack
{
public:
	bool SnackMove(float* pts, int n, float x, float y);
	//默认已经设置好了曲线方程的各个参数
	HelpSnack() = default;
	//tempA设置摆动振幅
	//tempW设置摆动周期的倒数
	//tempOFF设置摆动初相
	//tempB设置摆动偏移量
	//tempOffSet点每次步进的距离
	//tempRange用于控制蛇停止移动距离 SnackMOve中(x,y)的范围 默认15.0f
	HelpSnack(double tempA, double tempW, double tempOFF, double tempB, float tempOffSet, float tempRange) 
		: OffSet(tempOffSet), range(tempRange)
	{
		m_angleArg.A = tempA;
		m_angleArg.W = tempW;
		m_angleArg.OFF = tempOFF;
		m_angleArg.B = tempB;
	}

private:
	struct point
	{
		float x;
		float y;
	};
	struct line
	{
		point head;
		point tail;
	};
	struct angleArg
	{
		//振幅
		double A;
		//周期:2 * M_PI / W
		double W;
		//初相
		double OFF;
		//上下偏移量
		double B;
	};

	//角度值转弧度的进制
	const double One = M_PI / 180.0;
	//每次步进的距离
	float OffSet = 6.0f;
	//拟合的贝塞尔曲线
	list<point> m_BezierCurve;
	//蛇真正的身体
	deque<point> m_SnackBody;
	//三角函数参数
	angleArg m_angleArg = { 3, 5, 6, 10 };
	//触碰点的范围
	float range = 15.0f;
	//新的xy
	point newPos = { 0 };
	//原始xy
	point oldPos = { 0 };

	double saveAngle;
	point saveO;
	point saveN;

private:
	//简化求组合数
	double Simplify(int n, int m) const;
	//求组合数
	inline double CombinationNumber(int n, int m) const;
	//贝塞尔曲线的每一项中的需要求和的项
	inline double EachItem(int i, int n, double pi, double _t, double t) const;
	//构造贝塞尔曲线
	void CalculateBezierCurve(double incream);

	//规定顺时针转为正角
	//负时针转为负角
	//该角度是由x轴到x1轴的角度
	//范围(-180, 180]
	//弧度制范围(-Pi,pi]
	inline double IncludedAngle(const HelpSnack::line temp) const;

	//y=f(x)
	inline double CurveFunction(double x) const;

	//获取旧坐标系原点在新坐标系的位置
	const HelpSnack::point GetOldOInNew(const HelpSnack::line temp) const;

	//temp是旧坐标系的坐标
	//O是x轴到x1轴的角度
	//basePoint为旧坐标系的原点在新坐标系的值
	const HelpSnack::point TransformToNew(const HelpSnack::point temp, double O, const HelpSnack::point basePoint) const;

	// temp为新坐标系的坐标
	//O为x1轴到x轴的角度
	//basePoint为新坐标系的原点在旧坐标系的值
	const HelpSnack::point TransformToOld(const HelpSnack::point temp, double O, const HelpSnack::point basePoint) const;

	const HelpSnack::line ConstructLine(const HelpSnack::point head, const HelpSnack::point tail) const;

};
