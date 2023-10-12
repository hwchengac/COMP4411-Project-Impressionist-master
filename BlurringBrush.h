/*
	The brush which will blur the image by a 3 * 3 box filter
*/

#ifndef BLURRINGBRUSH_H
#define BLURRINGBRUSH_H

#include "ImpBrush.h"

class BlurringBrush : public ImpBrush
{
	public:
		//constuctor
		BlurringBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : ImpBrush(pDoc, name) {}

		//Brush realization
		void BrushBegin(const Point source, const Point target);
		void BrushMove(const Point source, const Point target);
		void BrushEnd(const Point source, const Point target);
};

#endif
