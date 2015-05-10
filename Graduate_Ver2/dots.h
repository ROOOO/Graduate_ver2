//
//  dots.h
//  Graduate_Ver2
//
//  Created by King on 15/4/25.
//  Copyright (c) 2015年 King. All rights reserved.
//

#ifndef __Graduate_Ver2__dots__
#define __Graduate_Ver2__dots__

#include <stdio.h>
#include "macro.h"
#include <vector>

class position;

class dots {
public:
  dots();
  ~dots();
  
  void init(GLint x, GLint y);
  
  GLint getPositionX();
  GLint getPositionY();
  GLint getPositionZ();
  
  GLint nextDotPosX;
  GLint nextDotPosY;
  
  void grow(GLint lightX, GLint lightY);
  
  bool isOnTree;
  
private:
  struct m_pos {
    GLint x, y, z;
  }m_pos;
  struct m_nextPos {
    GLint x, y;
    GLint distance;
  };
  std::vector<m_nextPos> m_nextPosVec;
  
  int m_minIndex;
  
public:
  
};

#endif /* defined(__Graduate_Ver2__dots__) */
