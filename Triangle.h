/*
	The header file for class Triangle.
	This class will be the parent class for both triangle brush and scattered triangle.
*/
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "ImpBrush.h"

class Triangle : public ImpBrush
{
	public:
		//contructor
		Triangle(ImpressionistDoc* pDoc = NULL, char* name = NULL) : ImpBrush(pDoc, name) {}

	protected:
		double size;
		void DrawTriangle(const Point source, const Point target, const double alpha);
};

#endif