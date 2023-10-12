#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredTriangleBrush.h"

extern int irand(int max);
extern float frand();

void ScatteredTriangleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	size = pDoc->getSize();
	BrushMove(source, target);
}

void ScatteredTriangleBrush::BrushMove(const Point source, const Point target)
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

	int NumOfTriangle = irand(2) + MIN_NUM_OF_TRIANGLE;
	for (int i = 0; i < NumOfTriangle; ++i)
	{
		double x_pos = static_cast<double>(frand()) * size - size / 2.0;
		double y_pos = static_cast<double>(frand()) * size - size / 2.0;
		Point RandTarget(target.x + x_pos, target.y + y_pos);
		Point RandSource(source.x + x_pos, source.y + y_pos);
		DrawTriangle(RandSource, RandTarget, alpha);
	}
}

void ScatteredTriangleBrush::BrushEnd(const Point source, const Point target)
{
	//nothing
}