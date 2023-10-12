/*
	scattered circle brush header file
*/

#ifndef SCATTEREDCIRCLE_H
#define SCATTEREDCIRCLE_H

#include "Circle.h"

class ScatteredCircleBrush : public Circle
{
	public:
		//constructor
		ScatteredCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : Circle(pDoc, name) {}

		//Brush realization
		void BrushBegin(const Point source, const Point target);
		void BrushMove(const Point source, const Point target);
		void BrushEnd(const Point source, const Point target);

	private:
		const int MIN_NUM_OF_CIRCLE = 4;	//the min num of circle by random
};

#endif
