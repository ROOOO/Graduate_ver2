//
//  main.cpp
//  Graduate_Ver2
//
//  Created by King on 15/4/25.
//  Copyright (c) 2015年 King. All rights reserved.
//

#include <iostream>

#include "macro.h"

vector<dots> posVector;
deque<dots> posDeque;


struct sun {
  GLdouble x;
  GLdouble y;
  int n;
  GLdouble size;
}sun;

struct pos {        // 用于3D交互，纪录鼠标位移、缩放
  float tx, ty, tz;
  float rx, ry, rz;
  float s;
  float angle;
}pos;

typedef struct {
  GLint x, y;
}GLintPoint;
GLintPoint mousePos[2];

void mouseMotion(int x, int y) {
  mousePos[1].x = x;
  mousePos[1].y = windowHeight - y;
  pos.ry += (mousePos[1].x - mousePos[0].x);
  pos.rx += (mousePos[1].y - mousePos[0].y);
  mousePos[0] = mousePos[1];
}

void mouse(int button, int state, int x, int y) {
  if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    mousePos[0].x = x;
    mousePos[0].y = windowHeight - y;
  }
}



void init() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("DLA Model");
  
  glClearColor(0.0, 0.0, 0.0, 0.0);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
  
  srand((unsigned)time(0));
  
//  dots d = dots();
//  d.init(windowWidth / 2, windowHeight / 2);
//  posVector.push_back(d);
//  posDeque.push_back(d);
  
  for (int i = 0; i < 10; i++) {
    dots d2 = dots();
    d2.init(0, windowHeight / 2 + (rand() % 10 - 5));
    posVector.push_back(d2);
    posDeque.push_back(d2);
  }
  
  
  sun = { windowWidth * 0.5, windowHeight * 0.5, 20, 20.0 };
}

void growth (int sunX, int sunY) {
//  long size = posDeque.size();
////  cout << size << endl;
//  for (long i = 0; i < size; i++) {
//    cout << i << endl;
    dots curDot = posDeque.at(0);
    curDot.grow(sunX, sunY);
    
    dots nextDot = dots();
    nextDot.init(curDot.nextDotPosX, curDot.nextDotPosY);
    posVector.push_back(nextDot);
    posDeque.push_back(nextDot);
    
    posDeque.pop_front();
//  }
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  sun = { double(mousePos->x), double(mousePos->y), 20, 20.0 };
  
//  sun = { double(100 * cos(i)), double(rand() % windowHeight), 20, 20.0 };

  glBegin(GL_TRIANGLE_FAN);
  glColor3f(255, 255, 0);
  for (int t = 0; t < 1000; t++) {
    glVertex2d(sun.size * cos(2 * PI / sun.n * t) + sun.x, sun.size * sin(2 * PI / sun.n * t) + sun.y);
  }
  glEnd();
  
//  sun.x = rand() % windowWidth;
  
  growth(sun.x, sun.y);
  
  glBegin(GL_POINTS);
  glColor3f(255, 0, 0);
  for (vector<dots>::iterator it = posVector.begin(); it != posVector.end(); it++) {
    glVertex2i(it->getPositionX(), it->getPositionY());
  }
  glEnd();
  
  glutSwapBuffers();
  glutPostRedisplay();
}




void init3D() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(600, 150);
  glutCreateWindow("3D DLA Model");
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClearDepth(10.0f);                   // Set background depth to farthest
  glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
  
  glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
  glShadeModel(GL_SMOOTH);   // Enable smooth shading
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //    glOrtho(-8.0 * 64 / 48.0, 8.0 * 64 / 48.0, -8.0, 8.0, 0.1, 100);
  gluPerspective(60.0f, 1.0f, .01f, 2000.0f);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(150.0, 150.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
  srand((unsigned int)time(0));
  
  static int a = 0;
  
  pos.rx = pos.ry = pos.tx = pos.ry = pos.rz = pos.tz = 0;
  pos.s = 1;
  pos.angle = 0;
}

void axis(double length) {
  glLineWidth(5.0);
  glBegin(GL_LINES);
  {
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, length);
  }
  glEnd();
  
  glPushMatrix();
  glTranslated(0, 0, length - 0.2);
  glutWireCone(4, 0.2, 12, 9);
  
  glLineWidth(2.0);
  glutWireCone(4, 10, 10, 10);
  
  glPopMatrix();
}

void drawAxis(double length)
{
  glPushMatrix();
  glRotatef(pos.ry, 0, 1, 0);
  glRotatef(pos.rx, 0, 0, 1);
  glScalef(pos.s, pos.s, pos.s);
  
  glColor3d(0, 0, 1);
  axis(length);
  
  glPushMatrix();
  glRotated(90, 0, 1.0, 0);
  glColor3d(1, 0, 0);
  axis(length);
  glPopMatrix();
  
  glPushMatrix();
  glRotated(-90.0, 1, 0, 0);
  glColor3d(0, 1, 0);
  axis(length);
  glPopMatrix();
  
  glPopMatrix();
}

void Grid(int gridLength) {
  glBegin(GL_LINES);
  {
    glColor3f(0.5, 0.5, 0.5);
    glVertex3d(-gridLength, 0, 0);
    glVertex3d(gridLength, 0, 0);
  }
  glEnd();
}
void drawGrid(int gridLength) {
  for (int i = -gridLength; i <= gridLength; i += 5) {
    glLineWidth(1.0);
    glPushMatrix();
    glRotatef(pos.ry, 0, 1, 0);
    glRotatef(pos.rx, 0, 0, 1);
    glScalef(pos.s, pos.s, pos.s);
    
    glPushMatrix();
    glTranslated(0, 0, i);
    Grid(gridLength);
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(0, 0, i);
    Grid(gridLength);
    glPopMatrix();
    
    glPopMatrix();
  }
}

void display3D() {
  //glClearColor(1, 1, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //    glEnable(GL_POINT_SMOOTH);
  
  drawGrid(100);
  drawAxis(50);
  
  
  glutSwapBuffers();
  glutPostRedisplay();
}

void keyBoard(unsigned char key, int x, int y) {
  //DLA();
  if (key == '+') {
    pos.s += 0.1;
  } else if (key == '-') {
    pos.s -= 0.1;
  }
  
  glutPostRedisplay();
}

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  
  if (!is3D) {
    init();
    glutDisplayFunc(Display);
  } else {
    init3D();
    glutDisplayFunc(display3D);
  }
  glutKeyboardFunc(keyBoard);
  
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  
  glutMainLoop();
}

