#include "CFile.h"

CFile::CFile():filept(NULL),filesize(0),buffer(NULL){
}

CFile::CFile(const char* filename,const char* op_mode){
	//printf("CFile constructor\n");//*********
	if((filept=fopen(filename,op_mode))==NULL) 
		perror("Usage:Error opening file");
	printf("open file success!\n");//*************
	if(strcmp("r",op_mode)==0){
		fseek(filept,0,SEEK_END);
		filesize = ftell(filept);
		rewind(filept);
		buffer  = (char*) malloc(sizeof(char)*(filesize+1));
		if(buffer==NULL){
			perror("Usage:memory error");
		}
		int result=0;
		if(result=fread(buffer,1,filesize,filept)!=filesize){
			perror("Usage:read error");
		}
		fclose(filept);
		buffer[filesize]='\0';
	}
	//printf("%s\n",buffer);exit(0);//**********
}

CFile::~CFile(){
	/*if(buffer!=NULL){
		free(buffer);
		buffer= NULL;
	}*/
	sucide();
}

void CFile::sucide(){
	if(buffer!=NULL){
		free(buffer);
		buffer= NULL;
	}
}

/*int main(int argc,char** argv){
	if(argc!=3){
		perror("Usage:Number of arguments error!");
	}
	CFile testfile(argv[1],argv[2]);
	printf("Test result is: %s",testfile.buffer);
	return 0;
}*/
