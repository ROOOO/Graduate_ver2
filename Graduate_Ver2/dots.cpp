//
//  dots.cpp
//  Graduate_Ver2
//
//  Created by King on 15/4/25.
//  Copyright (c) 2015年 King. All rights reserved.
//

#include "dots.h"

dots::dots() {
  isOnTree = false;
}

dots::~dots() { }

void dots::init(GLint inX, GLint inY) {
  m_pos.x = inX;
  m_pos.y = inY;
}

void dots::grow(GLint lightX, GLint lightY) {
  if (isOnTree) {
    return;
  }
  
  for (GLint j = -1; j < 2; j++) {
    for (GLint i  = -1; i < 2; i++) {
      if (!(i == 0 && j == 0)) {
        m_nextPosVec.push_back({ m_pos.x + i,
          m_pos.y + j,
          (lightX - (m_pos.x + i)) * (lightX - (m_pos.x + i)) + (lightY - (m_pos.y + j)) * (lightY - (m_pos.y + j))} );
      }
    }
  }
  
  m_minIndex = 0;
  GLdouble minDistance = m_nextPosVec.at(m_minIndex).distance;
  for (int i = 1; i < m_nextPosVec.size(); i++) {
    if (m_nextPosVec.at(i).distance < minDistance) {
      minDistance = m_nextPosVec.at(i).distance;
      m_minIndex = i;
    }
  }
  
  int probability = rand() % 100;
  
  switch (m_minIndex) {
    case 0:
      if (probability < 10) {
        m_minIndex = 5;
      } else if (probability < 30) {
        m_minIndex = 3;
      } else if (probability < 70) {
        m_minIndex = 0;
      } else if (probability < 90) {
        m_minIndex = 1;
      } else {
        m_minIndex = 2;
      }
      break;
      
    case 1:
      if (probability < 10) {
        m_minIndex = 3;
      } else if (probability < 30) {
        m_minIndex = 0;
      } else if (probability < 70) {
        m_minIndex = 1;
      } else if (probability < 90) {
        m_minIndex = 2;
      } else {
        m_minIndex = 4;
      }
      break;
      
    case 2:
      if (probability < 10) {
        m_minIndex = 0;
      } else if (probability < 30) {
        m_minIndex = 1;
      } else if (probability < 70) {
        m_minIndex = 2;
      } else if (probability < 90) {
        m_minIndex = 4;
      } else {
        m_minIndex = 7;
      }
      break;
      
    case 3:
      if (probability < 10) {
        m_minIndex = 6;
      } else if (probability < 30) {
        m_minIndex = 5;
      } else if (probability < 70) {
        m_minIndex = 3;
      } else if (probability < 90) {
        m_minIndex = 0;
      } else {
        m_minIndex = 1;
      }
      break;
      
    case 4:
      if (probability < 10) {
        m_minIndex = 1;
      } else if (probability < 30) {
        m_minIndex = 2;
      } else if (probability < 70) {
        m_minIndex = 4;
      } else if (probability < 90) {
        m_minIndex = 7;
      } else {
        m_minIndex = 6;
      }
      break;
      
    case 5:
      if (probability < 10) {
        m_minIndex = 7;
      } else if (probability < 30) {
        m_minIndex = 6;
      } else if (probability < 70) {
        m_minIndex = 5;
      } else if (probability < 90) {
        m_minIndex = 3;
      } else {
        m_minIndex = 0;
      }
      break;
      
    case 6:
      if (probability < 10) {
        m_minIndex = 3;
      } else if (probability < 30) {
        m_minIndex = 5;
      } else if (probability < 70) {
        m_minIndex = 6;
      } else if (probability < 90) {
        m_minIndex = 7;
      } else {
        m_minIndex = 4;
      }
      break;
      
    case 7:
      if (probability < 10) {
        m_minIndex = 5;
      } else if (probability < 30) {
        m_minIndex = 6;
      } else if (probability < 70) {
        m_minIndex = 7;
      } else if (probability < 90) {
        m_minIndex = 4;
      } else {
        m_minIndex = 2;
      }
      break;
//      
//    case 8:
//      cout << "8" << endl;
//      if (probability < 10) {
//        m_minIndex = 5;
//      } else if (probability < 30) {
//        m_minIndex = 3;
//      } else if (probability < 70) {
//        m_minIndex = 0;
//      } else if (probability < 90) {
//        m_minIndex = 1;
//      } else {
//        m_minIndex = 2;
//      }
//      break;
      
    default:
      break;
  }
  
//  cout << m_minIndex << endl;
  
  nextDotPosX = m_nextPosVec.at(m_minIndex).x;
  nextDotPosY = m_nextPosVec.at(m_minIndex).y;
  
//  cout << m_minIndex << endl;
  
  isOnTree = true;
}

GLint dots::getPositionX() {
  return m_pos.x;
}
GLint dots::getPositionY() {
  return m_pos.y;
}
GLint dots::getPositionZ() {
  return m_pos.z;
}
