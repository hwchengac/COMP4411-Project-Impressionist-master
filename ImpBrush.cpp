//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"
#include <iostream>				// for debugging
#include <math.h>

using namespace std;				// for debugging

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source, const double alpha)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[3];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );

	GLfloat colorR, colorG, colorB, GLalpha;
	//cout << "impbusgh" << alpha << endl;
	colorR = (GLfloat) min(color[0] / 255.0 * pDoc->m_pUI->getRedScale(), 1.0);
	colorG = (GLfloat) min(color[1] / 255.0 * pDoc->m_pUI->getGreenScale(), 1.0);
	colorB = (GLfloat) min(color[2] / 255.0 * pDoc->m_pUI->getBlueScale(), 1.0);
	GLalpha = (GLfloat)alpha;

	glColor4f(colorR, colorG, colorB, GLalpha);

}

GLdouble ImpBrush::Filtering(const int source_x, const int source_y)
{
	ImpressionistDoc* pDoc = GetDocument();
	GLdouble filtered_color = 0.0;

	//convert to grey

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int pos_x = source_x + i - 1;
			int pos_y = source_y + j - 1;
			GLubyte color[3];
			GLdouble grey_color;

			//get original colour pixel
			memcpy(color, pDoc->GetOriginalPixel(pos_x, pos_y), 3);
			//convert to grey
			grey_color = 0.299 * color[0] + 0.587 * color[1] + 0.114 * color[2];
			//cout << grey_color << endl; //debug
			//apply filter
			filtered_color += grey_color * FILTER[i][j];
		}
	}
	filtered_color /= FILTER_FACTOR;
	return filtered_color;
}

void ImpBrush::FilterColorAndApply(const int source_x, const int source_y, const double alpha)
{
	ImpressionistDoc* pDoc = GetDocument();
	GLubyte color[3];
	GLfloat colorR = 0.0;
	GLfloat colorG = 0.0;
	GLfloat	colorB = 0.0;
	GLfloat GLalpha = (GLfloat)alpha;
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int pos_x = source_x + i - 1;
			int pos_y = source_y + j - 1;
			GLubyte color[3];

			//get original colour pixel
			memcpy(color, pDoc->GetOriginalPixel(pos_x, pos_y), 3);
			//apply filter
			colorR += color[0] * FILTER[i][j];
			colorG += color[1] * FILTER[i][j];
			colorB += color[2] * FILTER[i][j];
		}
	}
	//colorR = colorR / (FILTER_FACTOR * 255.0);
	colorR = (GLfloat)min(colorR / (FILTER_FACTOR * 255.0) * pDoc->m_pUI->getRedScale(), 1.0);
	//colorG = colorG / (FILTER_FACTOR * 255.0);
	colorG = (GLfloat)min(colorG / (FILTER_FACTOR * 255.0) * pDoc->m_pUI->getGreenScale(), 1.0);
	//colorB = colorB / (FILTER_FACTOR * 255.0);
	colorB = (GLfloat)min(colorB / (FILTER_FACTOR * 255.0) * pDoc->m_pUI->getBlueScale(), 1.0);
	glColor4f(colorR, colorG, colorB, GLalpha);
}


int ImpBrush::CalculateGradient(const Point source)
{
	GLdouble filtered_color;
	GLdouble gradient_x = 0;
	GLdouble gradient_y = 0;
	int angle = 0;
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			filtered_color = Filtering(source.x + i -1, source.y + j - 1);
			gradient_x += filtered_color * SOBEL_X[i][j];
			gradient_y += filtered_color * SOBEL_Y[i][j];
			//cout << "debug" << endl; //debug
		}
	}
	
	double y_value = static_cast<double>(gradient_y);
	double x_value = static_cast<double>(gradient_x);
	angle = (int)round(atan2(y_value, x_value + 0.0001) * 180 / M_PI);
	//cout << "x: " << x_value << "y: " << y_value << endl;	//debug
	return angle;
}