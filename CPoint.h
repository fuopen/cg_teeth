#ifndef _CPOINT_H_
#define _CPOINT_H_
#include "Crwobj.h"

class CPoint{
	private:
		double point3d[3];
	public:
		CPoint();
		CPoint(const ovt&);
		CPoint(const CPoint&);
		~CPoint();
		CPoint& operator =(const CPoint&);
		CPoint& operator+=(const CPoint&);
		CPoint& operator-=(const CPoint&);
		CPoint& operator*=(const double&);
		CPoint  operator +(const CPoint&)const;
		CPoint  operator -(const CPoint&)const;
		double  operator[](const unsigned int&)const;
		double&  operator[](const unsigned int&);
};
#endif
