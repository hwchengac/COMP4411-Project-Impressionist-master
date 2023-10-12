#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Circle.h"
#include <math.h>
#include <iostream>
using namespace std;

void Circle::DrawCircle(const Point source, const Point target, const double alpha)
{
	double AccumulatedAngle = 0.0;
	//cout << alpha << endl;

	SetColor(source, alpha);
	if (radius > 1)
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i < PARTITION; ++i)
		{
			glVertex2d(target.x + radius / 2.0 * cos(AccumulatedAngle), target.y + radius / 2.0 * sin(AccumulatedAngle));
			AccumulatedAngle += ANGLE;
		}
		glEnd();
	}
	else
	{
		glBegin(GL_POINTS);
			glPointSize(radius);
			glVertex2d(target.x, target.y);
		glEnd();
	}
}