#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Triangle.h"
#include <math.h>
using namespace std;

void Triangle::DrawTriangle(const Point source, const Point target, const double alpha)
{
	double AccumulatedAngle = 0.0;
	SetColor(source, alpha);
	glBegin(GL_POLYGON);
	if (size > 1)
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i < 3; ++i)
		{
			glVertex2d(target.x + size / 2.0 * cos(AccumulatedAngle), target.y + size / 2.0 * sin(AccumulatedAngle));
			AccumulatedAngle += 2 * M_PI / 3;
		}
		glEnd();
	}
	else
	{
		glBegin(GL_POINTS);
		glPointSize(size);
		glVertex2d(target.x, target.y);
		glEnd();
	}
}