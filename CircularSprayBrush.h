/*
	circle brush header file
*/
#ifndef CIRCULARSPRAYBRUSH_H
#define CIRCULARSPRAYBRUSH_H

#include "Circle.h"

class CircularSprayBrush : public Circle
{
public:
	//constructor
	CircularSprayBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : Circle(pDoc, name) {}

	//Brush realization
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
};

#endif
