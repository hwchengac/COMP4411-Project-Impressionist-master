/*
	header file for scattered point brush
*/

#ifndef SPRAYDOTBRUSH_H
#define SPRAYDOTBRUSH_H

#include "ImpBrush.h"

class SprayDotBrush : public ImpBrush
{
	public:
		//constructor
		SprayDotBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : ImpBrush(pDoc, name) {}

		//Brush realization
		void BrushBegin(const Point source, const Point target);
		void BrushMove(const Point source, const Point target);
		void BrushEnd(const Point source, const Point target);
};

#endif
