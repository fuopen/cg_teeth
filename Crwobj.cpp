#include "Crwobj.h"

Crwobj::Crwobj(const char* filename,const char* op_mode):CFile(filename,op_mode),num_vtx(0),renum_vtx(0),num_tri(0),num_comments(0),obj_vtx(NULL),obj_tri(NULL),comments(NULL){
	buffer_resolution();
	normlization();
	print_vertex();
}

Crwobj::~Crwobj(){
	if(obj_vtx!=NULL){
		free(obj_vtx);
		obj_vtx=NULL;
	}
	if(obj_tri!=NULL){
		free(obj_tri);
		obj_tri=NULL;
	}
	char_list* del=comments;
	while(true){
		if(comments!=NULL){
			if(comments->content!=NULL){
				free(comments->content);
			}
			if(comments->p_next!=NULL){
				comments= comments->p_next;
				free(del);
				del = comments;
				continue;
			}
			else{
				free(del);
				comments = del = NULL;
				break;
			}
		}
		else break;
	}
}

int Crwobj::confirm_elements(const char* begin,const char* end,const char* str,const int len){	
	int num=0;	
	char* tmp_ele = (char*) malloc(sizeof(char)*(len+1));
	for(const char* c_seek=begin;c_seek<end;c_seek++){
		if(isspace(*(c_seek-1))&& *c_seek==str[0] && isalpha(*(c_seek+1))){
			memcpy(tmp_ele,c_seek,sizeof(char)*len);
			tmp_ele[len]='\0';
			if(strcmp(tmp_ele,str)==0){
				free(tmp_ele);
				tmp_ele = NULL;
				const char* loc_num=c_seek;
				do{
					loc_num++;
				}while(isdigit(*loc_num)==0);
				c_seek=loc_num;
				do{
					loc_num++;
				}while(isdigit(*loc_num));
				tmp_ele =(char*)malloc(sizeof(char)*(loc_num-c_seek));
				memcpy(tmp_ele,c_seek,sizeof(char)*(loc_num-c_seek));
				num = atoi(tmp_ele);
				free(tmp_ele);
				return num;		
			}
			else continue;
		}
		else continue;
	}
	if(tmp_ele!=NULL) free(tmp_ele);
	return num;
}

void Crwobj::store_comments(const char* begin,const char* end){
	char* tmp = (char*) malloc(sizeof(char)*(end-begin+1));
	memcpy(tmp,begin,sizeof(char)*(end-begin));
	tmp[end-begin]='\0';
	if(comments==NULL){
		comments = (char_list*)malloc(sizeof(char_list));
		comments->content = tmp;
		comments->size = end-begin;
		comments->p_next=NULL;
	}
	else{
		char_list* conecp = comments;//->p_next;
		while(true){
			if(conecp->p_next==NULL) break;//conecp = conecp->p_next;
			else conecp = conecp->p_next;
		}
		char_list* conec = (char_list*)malloc(sizeof(char_list));
		conec->content = tmp;
		conec->size = end-begin;
		conec->p_next = NULL;
		conecp->p_next = conec;
	}
}

void Crwobj::store_vtx(const char* begin,const char* end){
	const char* l_seek = begin;
	const char* r_seek = begin;
	obj_vtx = (ovt*) malloc(sizeof(ovt)*num_vtx);
	int i=0;
	do{
		r_seek++;
		if(*(r_seek-2)=='v'&& isspace(*(r_seek-1)) && (isdigit(*(r_seek))|| *r_seek=='-')){//find the vetex row
			l_seek=r_seek;
			int j=0;
			while(*(r_seek)!='\n'){
				do{
					r_seek++;
				}while(isspace(*(r_seek))==0);
				char* f_tmp = (char*) malloc(sizeof(char)*(r_seek-l_seek));
				memcpy(f_tmp,l_seek,sizeof(char)*(r_seek-l_seek));
				obj_vtx[i].ordi[j]=atof(f_tmp);
				obj_vtx[i].vtx_nrm[j]=0.0;
				free(f_tmp);
				l_seek = r_seek;
				j++;
			}
			//obj_vtx[i].degree=0;
		}
		if(*r_seek=='\n'){
			obj_vtx[i].degree = 0;
			i++;
		}
	}while(r_seek!=end);
}

void Crwobj::store_tri(const char* begin,const char* end){
	const char* l_seek = begin;
	const char* r_seek = begin;
	obj_tri = (tri*) malloc(sizeof(tri)*num_tri);
	int i=0;
	do{
		r_seek++;
		if(*(r_seek-2)=='f'&& isspace(*(r_seek-1)) && isdigit(*(r_seek))){//find the vetex row
			l_seek=r_seek;
			int j=0;
			while(*(r_seek)!='\n'){
				do{
					r_seek++;
				}while(isspace(*(r_seek))==0);
				char* i_tmp = (char*) malloc(sizeof(char)*(r_seek-l_seek));
				memcpy(i_tmp,l_seek,sizeof(char)*(r_seek-l_seek));
				obj_tri[i].tri_vtx[j]=atoi(i_tmp);
				free(i_tmp);
				l_seek = r_seek;
				j++;
			}
			get_norm(&obj_tri[i]);
			get_vtx_nrm(i);
		}
		if(*r_seek=='\n')	i++;
	}while(r_seek!=end);
}

void Crwobj::print_vertex(){
	/*char_list* cl = comments;
	while(cl){
		printf("%s\n",cl->content);
		cl = cl->p_next;
	}*/
	/*for(unsigned int i=0;i<num_vtx;i++){
		printf("%d ",obj_vtx[i].degree);
	}*/
	printf("\nthe number of vertices is: %d\n", renum_vtx);
	/*for(unsigned int i=0;i<num_vtx;i++){
		printf("%g     %g       %g\n",obj_vtx[i].ordi[0],obj_vtx[i].ordi[1],obj_vtx[i].ordi[2]);
	}*/
	/*for(unsigned int i=0;i<renum_vtx;i++){
		printf("%f    %f    %f\n",obj_vtx[i].vtx_nrm[0],obj_vtx[i].vtx_nrm[1],obj_vtx[i].vtx_nrm[2]);
		//if(obj_vtx[i].degree ==0) printf("the %dth is NULL\n",i);
	}*/
}

void Crwobj::print_triangle(){
	printf("the number of triangle is:%d\n", num_tri);
	for(unsigned int i=0;i<num_tri;i++){
		printf("%f    %f     %f\n",obj_tri[i].tri_nrm[0],obj_tri[i].tri_nrm[1],obj_tri[i].tri_nrm[2]);
	}
}

void Crwobj::buffer_resolution(){
	char* buffer_begin = buffer;
	char* buffer_end = buffer;
	while(*buffer_begin!='\0'){
		if(*buffer_begin == '#'){
			while(true){
				if(*(buffer_end-1)=='\n'&& (*buffer_end=='v'||*buffer_end=='f')&& *(buffer_end+1)==' ') break;
				else if(*(buffer_end)=='\0')break;
				else buffer_end++;
			}
			store_comments(buffer_begin,buffer_end);
			if(num_vtx==0){
				num_vtx = confirm_elements(buffer_begin,buffer_end,"vertices",8);
				buffer_begin=buffer_end;
				continue;
			}
			else if(num_tri==0){
				num_tri = confirm_elements(buffer_begin,buffer_end,"triangles",9);
				buffer_begin=buffer_end;
				continue;
			}
			else{ 
				buffer_begin=buffer_end;
				continue;
			}					
		}
		else if(*buffer_begin=='v'&& (isspace(*(buffer_begin-1))||buffer_begin==buffer) && isspace(*(buffer_begin+1))){
			while(*buffer_end!='#'){
				buffer_end++;
			}
			store_vtx(buffer_begin,buffer_end);
			buffer_begin = buffer_end;
			continue;			
		}
		else if(*buffer_begin=='f'&& (isspace(*(buffer_begin-1))||buffer_begin==buffer) && isspace(*(buffer_begin+1))){
			while(*buffer_end!='#'){
				buffer_end++;
			}
			store_tri(buffer_begin,buffer_end);
			buffer_begin = buffer_end;
			continue;			
		}
		else{
			perror("Usage:The pointer error");
		}
	}
}

void Crwobj::get_norm(triangle* c_tri){
	double v1[3]={0.0,0.0,0.0};
	double v2[3]={0.0,0.0,0.0};
	for(unsigned int i=0;i<3;i++){
		v1[i] = obj_vtx[c_tri->tri_vtx[1]].ordi[i]-obj_vtx[c_tri->tri_vtx[0]].ordi[i];
		v2[i] = obj_vtx[c_tri->tri_vtx[2]].ordi[i]-obj_vtx[c_tri->tri_vtx[1]].ordi[i];
	}
	c_tri->tri_nrm[0]=v1[1]*v2[2]-v2[1]*v1[2];
	c_tri->tri_nrm[1]=v2[0]*v1[2]-v1[0]*v2[2];
	c_tri->tri_nrm[2]=v1[0]*v2[1]-v2[0]*v1[1];
	double sum=0.0;
	for(unsigned int i=0;i<3;i++){
		sum += c_tri->tri_nrm[i]*c_tri->tri_nrm[i];
	}
	sum = sqrt(sum);
	for(unsigned int i=0;i<3;i++){
		c_tri->tri_nrm[i] /= sum;
	}
}

void Crwobj::get_vtx_nrm(const int& index){
	for(unsigned int j=0;j<3;j++){
		obj_vtx[obj_tri[index].tri_vtx[j]-1].degree +=1;
		//printf("%f ",obj_vtx[obj_tri[index].tri_vtx[j]-1].ordi[0]);
		for(unsigned int k=0;k<3;k++){
			obj_vtx[obj_tri[index].tri_vtx[j]-1].vtx_nrm[k] += obj_tri[index].tri_nrm[k];
		}
	}
}

void Crwobj::normlization(){
	for(unsigned int i=0;i<num_vtx;i++){
		if(obj_vtx[i].degree==0){
			renum_vtx = i;
			break;
		}
		else{
			double sum = 0.0;
			for(unsigned int j=0;j<3;j++)
				sum += obj_vtx[i].vtx_nrm[j]*obj_vtx[i].vtx_nrm[j];
				sum = sqrt(sum);
			for(unsigned int j=0;j<3;j++)
				obj_vtx[i].vtx_nrm[j] /= sum;
		}	
	}
	if(renum_vtx==0) renum_vtx = num_vtx;
}

const ovt Crwobj::operator[](const unsigned int index)const{
	if(index<num_vtx){
		return obj_vtx[index];
	}
	else{
		return obj_vtx[0];
	}
}

const tri Crwobj::operator()(const unsigned int index)const{
	if(index<num_tri){
		return obj_tri[index];
	}
	else{
		return obj_tri[0];
	}
}

int Crwobj::GetVtxNum()const{
	return renum_vtx;
}

int Crwobj::GetTriNum()const{
	return num_tri;
}

/*int main(int argc,char** argv){
	if(argc!=3){
		perror("Usage:number of arguments error!");
	}
	Crwobj haha(argv[1],argv[2]);
	//haha.print_vertex();
	//haha.print_triangle();
	return 0;
}*/
