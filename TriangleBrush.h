/*
	Triangular brush
*/

#ifndef TRIANGLEBRUSH_H
#define TRIANGLEBRUSH_H

#include "Triangle.h"

class TriangleBrush : public Triangle
{
	public:
		//constructor
		TriangleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : Triangle(pDoc, name) {}

		//Brush realization
		void BrushBegin(const Point source, const Point target);
		void BrushMove(const Point source, const Point target);
		void BrushEnd(const Point source, const Point target);
};

#endif