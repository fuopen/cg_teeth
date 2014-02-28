#ifndef _CFILE_H_
#define _CFILE_H_
/*****************************************************************
	This header defines the necessary classes for read and write *
	Last modify:2012-06-11										 *
	author:Hu sile												 *
*///**************************************************************
//Area of include files
#include<cstdio>
#include<cstdlib>
#include<cstring>

//class define

class CFile{
	protected:
		FILE* filept;
		long int filesize;
	public:
		CFile();
		CFile(const char*,const char*);
		~CFile();
		void sucide();
		char* buffer ;
};

#endif
