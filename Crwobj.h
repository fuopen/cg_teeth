#ifndef _CRWOBJ_W_
#define _CRWOBJ_H_
/******************************************
	This header file inherit the class    *
	defined in CFile.h,for read the obj   *
	file.								  *
	Last modify:2012-06-11                *
	author:Hu sile						  *
*///***************************************
//Area of include files
#include "CFile.h"
#include<cctype>
#include<cmath>

//class define
typedef struct objvertex{
	double ordi[3];
	double vtx_nrm[3];
	int degree;
}ovt;

typedef struct triangle{
	int tri_vtx[3];
	double tri_nrm[3];
}tri;

typedef struct charlist{
	char* content;
	int size;
	struct charlist* p_next;
}char_list;

class Crwobj:public CFile{
	private:
		ovt* obj_vtx;
		tri* obj_tri;
		char_list* comments;
		int num_vtx;
		int renum_vtx;
		int num_tri;
		int num_comments;
		void buffer_resolution();
		int confirm_elements(const char*,const char*,const char*,const int);
		void store_comments(const char*,const char*);
		void store_vtx(const char*,const char*);
		void store_tri(const char*,const char*);
		inline void get_norm(triangle*);
		inline void get_vtx_nrm(const int&);
		void normlization();
	public:
		Crwobj(const char*,const char*);
		~Crwobj();
		const ovt  operator [](const unsigned int)const;//return vertex
		const tri  operator ()(const unsigned int)const;//return triangle
		void print_vertex();
		void print_triangle();
		int GetVtxNum()const;
		int GetTriNum()const;
};
#endif
