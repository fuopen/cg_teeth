#include"Ccg.h"

cdeal::cdeal():CP(NULL),num_point(0){}

cdeal::cdeal(const Crwobj& obj):CP(NULL),num_point(0){
	if(obj.GetVtxNum()!=0){
		num_point = obj.GetVtxNum();
		CP = (CPoint*)malloc(sizeof(CPoint)*num_point);
		for(unsigned int i=0;i<num_point;i++){
			for(unsigned int j=0;j<3;j++){
				CP[i][j] = obj[i].ordi[j];
			}
		}
	}
	unify_vtx();
}

cdeal::~cdeal(){
	if(CP!=NULL) free(CP);
}

double cdeal::max(const double& a,const double& b)const{
	return (a>=b)? a:b;
}

double cdeal::min(const double& a,const double& b)const{
	return (a<=b)? a:b;
}

void cdeal::unify_vtx(){
	double max0,min0,max1,min1,max2,min2;
	max0 = max0 = CP[0][0];
	max1 = max1 = CP[0][1];
	max2 = max2 = CP[0][2];

	for(unsigned int i=0;i<num_point;i++){
		max0 = max(max0,CP[i][0]);
		min0 = min(min0,CP[i][0]);
		max1 = max(max1,CP[i][1]);
		min1 = min(min1,CP[i][1]);
		max2 = max(max2,CP[i][2]);
		min2 = max(min2,CP[i][2]);
	}

	CPoint* mid_pt = (CPoint*)malloc(sizeof(CPoint));
	(*mid_pt)[0]= (min0+max0)/2.0;
	(*mid_pt)[1]= (min1+max1)/2.0;
	(*mid_pt)[2]= (min2+max2)/2.0;

	for(unsigned int i=0;i<num_point;i++){
		CP[i] -= (*mid_pt);
	}

	free(mid_pt);
	
	double dis_pt[3];
	dis_pt[0]= (max0-min0);
	dis_pt[1]= (max1-min1);
	dis_pt[2]= (max2-min2);
	
	double _width = max(dis_pt[0],max(dis_pt[1],dis_pt[2]));
	for(unsigned int i=0;i<num_point;i++)
		CP[i] *= 1.0/_width;
}

void cdeal::print_point(){
	for(unsigned int i=0;i<num_point;i++)
		printf("%f	%f	%f\n",CP[i][0],CP[i][1],CP[i][2]);
}

CPoint cdeal::operator[](const unsigned int& index)const{
	return CP[index];
}

CPoint& cdeal::operator[](const unsigned int& index){
	return CP[index];
}

/*int main(int argc,char** argv){
	if(argc!=3){
		perror("Usage:number of arguments error!");
	}
	Crwobj haha(argv[1],argv[2]);
	cdeal test(haha);
	//test.print_point();
	return 0;
}*/
