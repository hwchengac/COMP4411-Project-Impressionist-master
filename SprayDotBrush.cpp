#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SprayDotBrush.h"
#include <math.h>

extern float frand();

void SprayDotBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	glPointSize(1.0);
	BrushMove(source, target);
}
void SprayDotBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("SprayDotBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	double alpha = pDoc->getAlpha();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (size > 1) {
		int NumOfPoints = size;
		for (int i = 0; i < NumOfPoints; i++)
		{
			double angle = frand() * 360;
			double rand_x = (frand() * size - size / 2.0) * cos(angle);
			double rand_y = (frand() * size - size / 2.0) * sin(angle);
			glBegin(GL_POINTS);
			SetColor(Point(source.x + rand_x, source.y + rand_y), alpha);
			glVertex2d(target.x + rand_x, target.y + rand_y);
			glEnd();
		}
		for (int i = 0; i < NumOfPoints / 2; i++) {
			double angle = frand() * 360;
			double rand_x = (frand() * size - size / 2.0) * cos(angle);
			double rand_y = (frand() * size - size / 2.0) * sin(angle);
			glBegin(GL_POINTS);
			SetColor(Point(source.x + rand_x / 2, source.y + rand_y / 2), alpha);
			glVertex2d(target.x + rand_x / 2, target.y + rand_y / 2);
			glEnd();
		}
	}
	else {
		glBegin(GL_POINTS);
		glPointSize(size);
		glVertex2d(target.x, target.y);
		glEnd();
	}
}
void SprayDotBrush::BrushEnd(const Point source, const Point target)
{
	//don't know what to put here
}