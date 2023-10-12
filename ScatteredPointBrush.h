/*
	header file for scattered point brush
*/

#ifndef SCATTEREDPOINTBRUSH_H
#define SCATTEREDPOINTBRUSH_H

#include "ImpBrush.h"

class ScatteredPointBrush : public ImpBrush
{
	public:
		//constructor
		ScatteredPointBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : ImpBrush(pDoc, name) {}

		//Brush realization
		void BrushBegin(const Point source, const Point target);
		void BrushMove(const Point source, const Point target);
		void BrushEnd(const Point source, const Point target);
};

#endif
