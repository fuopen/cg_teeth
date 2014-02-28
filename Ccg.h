#ifndef _CCG_H_
#define _CCG_H_

#include<GL/glut.h>
#include "CPoint.h"

class cdeal{
	private:
		CPoint* CP;
		int num_point;
	public:
		cdeal();
		cdeal(const Crwobj&);
		~cdeal();
		CPoint operator[](const unsigned int&)const;
		CPoint& operator[](const unsigned int&);
		void unify_vtx();
		void print_point();
		inline double max(const double&,const double&)const;
		inline double min(const double&,const double&)const;
};

#endif
