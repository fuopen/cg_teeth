#include "CG.h"

void my_init(){
	if_draw = false;
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glMatrixMode(GL_MODELVIEW);

	GLfloat mat_ambient[4]     = {0.20,0.20,0.20,1.0};
	GLfloat diffuseMaterial[4] = {0.80,0.80,0.80,1.0};//{1.0,1.0,1.0,1.0};
	GLfloat mat_specular[4]    = {0.00,0.00,0.01,1.0};//{0.34,0.45,0.45,1.0};

	GLfloat light0_position[4]  = {1.0,1.0,1.0,0.0};
	GLfloat light0_ambient[4]   = {1.0,1.0,1.0,1.0};//{0.7,0.4,0.88,1.0};
	GLfloat light0_diffuse[4]   = {1.0,0.93,0.93,1.0};//{0.3,0.2,0.3,1.0};
	GLfloat light0_specular[4]  = {0.0,1.0,0.0,1.0};//{0.22,0.42,0.01,1.0};

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseMaterial);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,200.0);

	glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//glClearColor(1.0,1.0,1.0,1.0);
	//glColor3f(0.2,0.8,0.1);
	//glShadeModel(GL_FLAT);
}

void my_reshape(GLint w,GLint h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) gluOrtho2D(-0.5, 0.5, -0.5*(GLfloat)h/(GLfloat)w,0.5*(GLfloat)h/(GLfloat)w);
	else gluOrtho2D(-0.5*(GLfloat)w/(GLfloat)h,0.5*(GLfloat)w/(GLfloat)h, -0.5, 0.5);
	glMatrixMode(GL_MODELVIEW);
	winWidth = w;
	winHeight = h;
}

void my_draw(){
	for(unsigned int i=0;i<my_rwfile->GetTriNum();i++){
		glBegin(GL_TRIANGLES);
		for(unsigned int j=0;j<3;j++){
			glColor3f(0.0,0.2,0.5);
			glNormal3dv((*my_rwfile)[(*my_rwfile)(i).tri_vtx[j]-1].vtx_nrm);
			glVertex3d((*my_cg)[(*my_rwfile)(i).tri_vtx[j]-1][0],(*my_cg)[(*my_rwfile)(i).tri_vtx[j]-1][1],(*my_cg)[(*my_rwfile)(i).tri_vtx[j]-1][2]);
		}
		glEnd();
	}
}

void my_list(){
	list_id = glGenLists(1);
	glNewList(list_id,GL_COMPILE_AND_EXECUTE);
		my_draw();
	glEndList();
}

void my_display(){
	//if(!if_draw) return;
	glClearColor(0.5,0.2,0.5,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	/*glBegin(GL_POINTS);
	glVertex2f(0.0,0.0);
	glEnd();
	glFlush();*/
	//printf("%d \n",if_draw);
	if(trackballMove) glRotatef(angle,axis[0],axis[1],axis[2]);
	my_list();
	//glLoadIdentity();
	/*for(unsigned int i=0;i<my_rwfile->GetTriNum();i++){
		glBegin(GL_TRIANGLES);
		for(unsigned int j=0;j<3;j++){
			glColor3f(0.0,0.2,0.5);
			glNormal3dv((*my_rwfile)[(*my_rwfile)(i).tri_vtx[j]-1].vtx_nrm);
			glVertex3d((*my_cg)[(*my_rwfile)(i).tri_vtx[j]-1][0],(*my_cg)[(*my_rwfile)(i).tri_vtx[j]-1][1],(*my_cg)[(*my_rwfile)(i).tri_vtx[j]-1][2]);
		}
		glEnd();
	}*/
	//my_draw();
	glCallList(list_id);
	glutSwapBuffers();
	glFlush();
}

/*void my_display(){
	float** a;
	int num=81;
	double theta = 3.1415926*2/num;
	a = (float**) malloc(sizeof(float*)*num);
	for(int i=0;i<num;i++){
		a[i]=(float*)malloc(sizeof(float)*2);
		a[i][0]=0.7*cos(i*theta);
		a[i][1]=0.7*sin(i*theta);
	}
	glClearColor(0.5,0.2,0.1,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<num;i++){
		glColor3f(0.23,0.0,0.78);
		glVertex2f(a[i][0],a[i][1]);
	}   
    glEnd();
	glFlush();
	for(int i=0;i<num;i++){
		free(a[i]);
	}
	free(a);
}*/
void trackball_ptov(int x,int y,int width,int height,double v[3]){
	double d,a;
	v[0]=(2.0*x-width)/width;
	v[1]=(height-2.0*y)/height;
	d = sqrt(v[0]*v[0]+v[1]*v[1]);
	v[2]= cos((M_PI/2.0)*((d<1.0)? d:1.0));
	a = 1.0/ sqrt(v[0]*v[0]+v[1]*v[1]*v[1]+v[2]*v[2]);
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;
}

void mouseMotion(int x,int y){
	double curPos[3] , dx,dy,dz;
	trackball_ptov(x,y,winWidth,winHeight,curPos);
	if(trackingMouse){
		dx = curPos[0]-lastPos[0];
		dy = curPos[1]-lastPos[1];
		dz = curPos[2]-lastPos[2];
		if(dx||dy||dz){
			angle = 90.0*sqrt(dx*dx+dy*dy+dz*dz);

			axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
			axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
			axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];

			lastPos[0] = curPos[0];
			lastPos[1] = curPos[1];
			lastPos[2] = curPos[2];
		}
	}
	glutPostRedisplay();
}

void startMotion(int x, int y){
	trackingMouse = true;
	redrawContinue = false;
	startX = x;
	startY = y;
	curx = x;
	cury = y;
	trackball_ptov(x,y,winWidth,winHeight,lastPos);
	trackballMove = true;
}

void stopMotion(int x, int y){
	trackingMouse = false;
	if(startX != x||startY != y){
		redrawContinue = true;
	}
	else{
		angle = 0.0;
		redrawContinue = false;
		trackballMove = false;
	}
}

void mouseButton(int button,int state,int x,int y){
	if(button==GLUT_RIGHT_BUTTON) exit(0);
	if(button==GLUT_LEFT_BUTTON)
		switch(state){
			case GLUT_DOWN: y=winHeight-y;startMotion(x,y);break;
			case GLUT_UP  : stopMotion(x,y);break;
		}
}

/*void my_reshape(GLint w,GLint h){
	glViewport(0,0,w,h);
	winWidth = w;
	winHeight = h;
}*/

void spin_obj(){
	if(redrawContinue) glutPostRedisplay();
}

int main(int argc,char** argv){
	if(argc!=3){
		perror("Error arguments number!");
	}

	my_rwfile = new Crwobj(argv[1],argv[2]);
	my_cg = new cdeal(*my_rwfile);
	if_draw=true;
	//my_cg->print_point();
	//exit(0);
	glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(1500,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("FUCK");
	//my_init();
	GLfloat light1_position[]={-0.86,0.87,0.8,0.0};
	GLfloat light1_ambient[] ={0.98,0.91,0.97,1.0};
	GLfloat light1_diffuse[] ={0.12,0.94,0.14,1.0};
	GLfloat light1_specular[]={0.92,0.12,0.19,1.0};
	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
	glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.05);
	GLfloat spotdir[]={0.8,-0.87,-0.75};
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spotdir);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30);
	glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.7);
	glEnable(GL_LIGHT1);
	//glutReshapeFunc(my_reshape);
	glutDisplayFunc(my_display);
	glutReshapeFunc(my_reshape);
	//glEnable(GL_DEPTH_TEST);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(1.0,1.0,1.0,1.0);
	glutIdleFunc(spin_obj);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	my_init();
	glutMainLoop();
	delete my_rwfile;
	delete my_cg;
	return 0;
}
