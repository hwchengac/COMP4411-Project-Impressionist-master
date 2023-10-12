#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "BlurringBrush.h"

void BlurringBrush::BrushBegin(const Point source, const Point target)
{
	glPointSize(1.0);
	BrushMove(source, target);
}

void BlurringBrush::BrushMove(const Point source, const Point target)
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

	int NumOfPoints = size * size;
	int x_counter = 0;
	int y_counter = 0;
	for (int i = 0; i < NumOfPoints; ++i)
	{
		double source_x_pos = source.x - size / 2.0 + x_counter;
		double source_y_pos = source.y - size / 2.0 + y_counter;
		double target_x_pos = target.x - size / 2.0 + x_counter;
		double target_y_pos = target.y - size / 2.0 + y_counter;

		glBegin(GL_POINTS);
			FilterColorAndApply(source_x_pos, source_y_pos, alpha);
			glVertex2d(target_x_pos, target_y_pos);
		glEnd();

		if (x_counter == size)
		{
			x_counter = 0;
			++y_counter;
		}
		else
		{
			++x_counter;
		}	
	}
}

void BlurringBrush::BrushEnd(const Point source, const Point target)
{

}