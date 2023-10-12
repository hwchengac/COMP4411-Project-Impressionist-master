//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Box.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Window*			m_colorScaleDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_strokeDirectionChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_lineWidthSlider;
	Fl_Slider*			m_lineAngleSlider;
	Fl_Slider*			m_alphaSlider;
	Fl_Slider*			m_spacingSlider;
	Fl_Slider*			m_edgeThresholdSlider;
	Fl_Button*          m_ClearCanvasButton;
	Fl_Button*			m_edgeClippingButton;
	Fl_Button*			m_anotherGradientButton;
	Fl_Button*			m_sizeRandomButton;
	Fl_Button*			m_paintButton;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);
	int					getLineWidth();
	int					getLineAngle();
	void				setLineAngle(int angle);
	double				getAlpha();
	double				getRedScale();
	double				getGreenScale();
	double				getBlueScale();

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_lineWidth;
	int		m_lineAngle;
	double	m_alpha;
	bool	m_edgeClipping;
	bool	m_anotherGradient;
	int		m_spacing;
	int		m_edgeThreshold;
	bool	m_sizeRandom;
	double	m_nRedScale;
	double	m_nGreenScale;
	double	m_nBlueScale;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE + 1];
	static Fl_Menu_Item		strokeDirectionMenu[NUM_STROKE_DIRECTION + 1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_color_scale(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void cb_swap_content(Fl_Menu_* o, void* v);
	static void cb_undo_content(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void cb_strokeDirectionChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void	cb_lineWidthSlides(Fl_Widget* o, void* v);
	static void	cb_lineAngleSlides(Fl_Widget* o, void* v);
	static void	cb_alphaSlides(Fl_Widget* o, void* v);
	static void	cb_spaceingSlides(Fl_Widget* o, void* v);
	static void	cb_edgeThresholdSlides(Fl_Widget* o, void* v);
	static void	cb_edgeClippingButton(Fl_Widget* o, void* v);
	static void	cb_anotherGradientButton(Fl_Widget* o, void* v);
	static void	cb_sizeRandom(Fl_Widget* o, void* v);
	static void	cb_paintButton(Fl_Widget* o, void* v);
	static void cb_drawEdge(Fl_Widget* o, void* v);
	static void cb_redScaleSlides(Fl_Widget* o, void* v);
	static void cb_greenScaleSlides(Fl_Widget* o, void* v);
	static void cb_blueScaleSlides(Fl_Widget* o, void* v);
};

#endif
