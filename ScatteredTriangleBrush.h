/*
	Scattered Triangular brush
*/

#ifndef SCATTEREDTRIANGLEBRUSH_H
#define SCATTEREDTRIANGLEBRUSH_H

#include "Triangle.h"

class ScatteredTriangleBrush : public Triangle
{
	public:
		//constructor
		ScatteredTriangleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : Triangle(pDoc, name) {}

		//Brush realization
		void BrushBegin(const Point source, const Point target);
		void BrushMove(const Point source, const Point target);
		void BrushEnd(const Point source, const Point target);

	private:
		const int MIN_NUM_OF_TRIANGLE = 3;	//the min num of triangle by random
};

#endif
