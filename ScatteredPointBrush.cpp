#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"

extern float frand();

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	glPointSize(1.0);
	BrushMove(source, target);
}
void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	double alpha = pDoc->getAlpha();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int NumOfPoints = size * size * 0.5 + 1;
	for (int i = 0; i < NumOfPoints; ++i)
	{
		double x_pos = static_cast<double>(frand()) * size - size / 2.0;
		double y_pos = static_cast<double>(frand()) * size - size / 2.0;
		Point RandTarget(target.x + x_pos, target.y + y_pos);
		Point RandSource(source.x + x_pos, source.y + y_pos);

		glBegin(GL_POINTS);
			SetColor(RandSource, alpha);
			glVertex2d(RandTarget.x, RandTarget.y);
		glEnd();
	}
}
void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	//don't know what to put here
}