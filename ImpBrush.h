#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>

// Each brush type has an associated constant.
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES,
	BRUSH_CIRCLES,
	BRUSH_SCATTERED_POINTS,
	BRUSH_SCATTERED_LINES,
	BRUSH_SCATTERED_CIRCLES,
	BRUSH_CIRCULAR_SPRAY,
	BRUSH_SPRAY,
	BRUSH_TRIANGLE,
	BRUSH_SCATTERED_TRIANGLE,
	BRUSH_BLURRING,
	NUM_BRUSH_TYPE // Make sure this stays at the end!
};


// Not sure where to put this
enum
{
	DIRECTION_SLIDER_RIGHT_MOUSE = 0,
	DIRECTION_GRADIENT,
	DIRECTION_BRUSH_DIRECTION,
	NUM_STROKE_DIRECTION // Make sure this stays at the end!
};


class ImpressionistDoc; // Pre-declaring class

class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };

	int x, y;
};

class ImpBrush 
{
protected:
	ImpBrush::ImpBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	//filter
	const int FILTER[3][3] = { {1, 1, 1},
							   {1, 1, 1},
							   {1, 1, 1} };

	const int FILTER_FACTOR = 9;

	//Sobel operator
	const int SOBEL_X[3][3] = { {-1, 0, 1},
								{-2, 0, 2},
								{-1, 0, 1} };

	const int SOBEL_Y[3][3] = { {1,  2,  1},
								{0,  0,  0},
								{-1, -2, -1} };

	//Apply filter
	GLdouble Filtering(const int source_x, const int source_y);

	//filter for each colour and apply it in gl
	void FilterColorAndApply(const int source_x, const int source_y, const double alpha);

	//Calculate the gradient
	int CalculateGradient(const Point source);

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const Point source, const Point target ) = 0;
	virtual void BrushMove( const Point source, const Point target ) = 0;
	virtual void BrushEnd( const Point source, const Point target ) = 0;

	// according to the source image and the position, determine the draw color
	void SetColor( const Point source, const double alpha );

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	char* BrushName( void );

	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	char*				m_pBrushName;

	
};

#endif