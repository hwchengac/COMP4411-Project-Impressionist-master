#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <iostream>

using namespace std;

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {

}

void LineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	previous_x = target.x;
	previous_y = target.y;

	int width = pDoc->getLineWidth();

	glLineWidth((float)width);
	BrushMove(source, target);

}

void LineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove document is NULL\n");
		return;
	}

	brushDown = true;
	if (brushDown) {

		int size = pDoc->getSize();
		int angle = 0, diff_x, diff_y;
		double alpha = pDoc->getAlpha();
		int half_size = size / 2;
		if (pDoc->m_CurrentStrokeDirection == 2) {
			diff_x = target.x - previous_x;
			diff_y = target.y - previous_y;
			angle = (int) round(atan2(diff_y, diff_x + 0.0001) * 180 / M_PI);
			if (angle < 0) {
				angle += 360;
			}
			previous_x = target.x;
			previous_y = target.y;
		}
		else {
			if (pDoc->m_CurrentStrokeDirection == 1)
			{
				angle = CalculateGradient(source);
				if (angle < 0) {
					angle += 360;
				}
			}
			else
				angle = pDoc->getLineAngle();
		}
		//cout << "angle: " << angle << endl;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();

		glTranslated(target.x, target.y, 0);
		glRotated(angle, 0, 0, 1);
		glTranslated(-target.x, -target.y, 0);

		glBegin(GL_LINES);
		SetColor(source, alpha);
		glVertex2d(target.x - half_size, target.y);
		glVertex2d(target.x + half_size, target.y);
		glEnd();

		glPopMatrix();
	}
}

void LineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far 
	brushDown = false;
}
