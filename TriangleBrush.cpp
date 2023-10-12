#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "TriangleBrush.h"

void TriangleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	size = pDoc->getSize();
	BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target)
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
	DrawTriangle(source, target, alpha);
}

void TriangleBrush::BrushEnd(const Point source, const Point target)
{
	//nothing here
}