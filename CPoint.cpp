#include "CPoint.h"

CPoint::CPoint(){
	for(unsigned int i=0;i<3;i++)
		point3d[i]=0.0;
}

CPoint::CPoint(const ovt& ovtx){
	for(unsigned int i=0;i<3;i++)
		point3d[i]=ovtx.ordi[i];
}

CPoint::CPoint(const CPoint& cpt){
	for(unsigned int i=0;i<3;i++)
		point3d[i]=cpt.point3d[i];
}

CPoint::~CPoint(){}

CPoint& CPoint::operator =(const CPoint& ept){
	if(this==&ept) return *this;
	else for(unsigned int i=0;i<3;i++) point3d[i]=ept.point3d[i];
	return *this;
}

CPoint& CPoint::operator+=(const CPoint& apt){
	for(unsigned int i=0;i<3;i++) point3d[i]+=apt.point3d[i];
	return *this;
}

CPoint& CPoint::operator-=(const CPoint& spt){
	for(unsigned int i=0;i<3;i++) point3d[i]-=spt.point3d[i];
	return *this;
}

CPoint& CPoint::operator*=(const double& cof){
	for(unsigned int i=0;i<3;i++) point3d[i]*=cof;
	return *this;
}

CPoint CPoint::operator +(const CPoint& apt)const{
	CPoint* add = (CPoint*)malloc(sizeof(CPoint));
	for(unsigned int i=0;i<3;i++)
		add->point3d[i] = point3d[i]+apt.point3d[i];
	return *add;
}

CPoint CPoint::operator -(const CPoint& spt)const{
	CPoint* sub = (CPoint*)malloc(sizeof(CPoint));
	for(unsigned int i=0;i<3;i++)
		sub->point3d[i] = point3d[i]-spt.point3d[i];
	return *sub;
}

double CPoint::operator[](const unsigned int& index)const{
	return point3d[index];
}

double& CPoint::operator[](const unsigned int& index){
	return point3d[index];
}
