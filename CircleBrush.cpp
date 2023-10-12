#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <iostream>

using namespace std;

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	radius = pDoc->getSize();
	//cout << "begin" << endl;
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) 
	{
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	double alpha = pDoc->getAlpha();
	//cout << "draw" << endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	DrawCircle(source, target, alpha);
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	//don't know what to put here.
}
