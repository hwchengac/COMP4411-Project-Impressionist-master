/*
	The header file for class Circle.
	This class will be the parent class for both circle brush and scattered circle.
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "ImpBrush.h"
#include <math.h>
using namespace std;

class Circle : public ImpBrush
{
	public:
		//constructor
		Circle(ImpressionistDoc* pDoc = NULL, char* name = NULL) : ImpBrush(pDoc, name) {}

	private:
		const int PARTITION = 20;
		const double ANGLE = 2 * M_PI / PARTITION;

	protected:
		double radius;
		//draw a circle
		void DrawCircle(const Point source, const Point target, const double alpha);
};

#endif
