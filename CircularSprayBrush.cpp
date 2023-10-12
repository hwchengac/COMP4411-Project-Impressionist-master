#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircularSprayBrush.h"
#include <iostream>

using namespace std;

void CircularSprayBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	radius = pDoc->getSize();
	//cout << "begin" << endl;
	BrushMove(source, target);
}

void CircularSprayBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL)
	{
		printf("CircularSprayBrush::BrushMove  document is NULL\n");
		return;
	}

	double alpha = pDoc->getAlpha();
	//cout << "draw" << endl;
	int inner_radius = pDoc->getSize();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 10; i > 0; i--) {
		radius = inner_radius * i / 10;
		DrawCircle(source, target, alpha / 10);
	}
}

void CircularSprayBrush::BrushEnd(const Point source, const Point target)
{
	//don't know what to put here.
}
