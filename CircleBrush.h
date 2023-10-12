/*
	circle brush header file
*/
#ifndef CIRCLEBRUSH_H
#define CIRCLEBRUSH_H

#include "Circle.h"

class CircleBrush : public Circle
{
	public:
		//constructor
		CircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : Circle(pDoc, name) {}
		
		//Brush realization
		void BrushBegin(const Point source, const Point target);
		void BrushMove(const Point source, const Point target);
		void BrushEnd(const Point source, const Point target);
};

#endif

