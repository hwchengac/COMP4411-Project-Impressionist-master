#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"

extern int irand(int max);
extern float frand();

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	radius = pDoc->getSize();
	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL)
	{
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	double alpha = pDoc->getAlpha();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int NumOfCircle = irand(2) + MIN_NUM_OF_CIRCLE;
	for (int i = 0; i < NumOfCircle; ++i)
	{
		double x_pos = static_cast<double>(frand()) * radius - radius / 2.0;
		double y_pos = static_cast<double>(frand()) * radius - radius / 2.0;
		Point RandTarget(target.x + x_pos, target.y + y_pos);
		Point RandSource(source.x + x_pos, source.y + y_pos);
		DrawCircle(RandSource, RandTarget, alpha);
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	//don't know what to put here.
}