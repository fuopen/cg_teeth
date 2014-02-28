#ifndef _CG_H_
#define _CG_H_
/**********************************************************
this header file defined some basic plot function		   *
author:husile											   *
last modified:2012-07-10								   *
														   *
*///********************************************************
#include"Ccg.h"

#define TEETH 1

Crwobj* my_rwfile;
cdeal* my_cg;
GLuint list_id;
int winWidth,winHeight;
float angle= 0.0,axis[3],trans[3];
bool trackingMouse = false;
bool redrawContinue = false;
bool trackballMove = false;

double lastPos[3]={0.0,0.0,0.0};

int curx,cury;
int startX,startY;

bool if_rwfile;
bool if_draw;
void my_init();
void my_reshape(GLint,GLint);
void my_display();
void my_draw();
void my_list();
void trackball_ptov(int,int,int,int,double[]);
void mouseMotion(int,int);
void startMotion(int,int);
void stopMotion(int,int);
void mouseButton(int,int,int,int);
void spin_obj();
#endif
