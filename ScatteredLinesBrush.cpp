#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLinesBrush.h"
#include "LineBrush.h"

#include <iostream>				// for debugging

extern float frand();
extern int irand(int);

using namespace std;				// for debugging

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {

}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	previous_x = target.x;
	previous_y = target.y;

	int width = pDoc->getLineWidth();

	glLineWidth((float)width);
	BrushMove(source, target);

}

void ScatteredLineBrush::BrushMove(const Point source, const Point target) {
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
			angle = (int)round(atan2(diff_y, diff_x + 0.0001) * 180 / M_PI);
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

		for (int i = 0; i < irand(3) + 2; i++) {

			double rand_dx = frand() * size - half_size;
			double rand_dy = frand() * size - half_size;
			double new_target_x = target.x + rand_dx;
			double new_target_y = target.y + rand_dy;

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPushMatrix();

			glTranslated(new_target_x, new_target_y, 0);
			glRotated(angle, 0, 0, 1);
			glTranslated(-new_target_x, -new_target_y, 0);

			glBegin(GL_LINES);
			SetColor(Point(source.x + rand_dx, source.y + rand_dy), alpha);
			glVertex2d(new_target_x - half_size, new_target_y);
			glVertex2d(new_target_x + half_size, new_target_y);
			glEnd();

			glPopMatrix();
	}
	}
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
	brushDown = false;
}
