//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <iostream>					// For debugging
#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

using namespace std;				// For debugging

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

void ImpressionistUI::cb_color_scale(Fl_Menu_* o, void* v)
{
	whoami(o)->m_colorScaleDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

void ImpressionistUI::cb_swap_content(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->swapContent();
}

void ImpressionistUI::cb_undo_content(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->undoContent();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
	whoami(o)->m_colorScaleDialog->hide();
}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	if (type == 1 || type == 4) {
		pUI->m_strokeDirectionChoice->activate();
		pUI->m_lineWidthSlider->activate();
		pUI->m_lineAngleSlider->activate();
		pUI->m_edgeClippingButton->activate();
		pUI->m_anotherGradientButton->activate();
	} else {
		pUI->m_strokeDirectionChoice->deactivate();
		pUI->m_lineWidthSlider->deactivate();
		pUI->m_lineAngleSlider->deactivate();
		pUI->m_edgeClippingButton->deactivate();
		pUI->m_anotherGradientButton->deactivate();
	}


	pDoc->setBrushType(type);
}

void ImpressionistUI::cb_strokeDirectionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;

	pDoc->setStrokeDirectionType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

void ImpressionistUI::cb_paintButton(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->paintCanvas();
}

void ImpressionistUI::cb_drawEdge(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	cout << "draw edge\n";
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize = int(((Fl_Slider *)o)->value() ) ;
}


// Updates line width
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_lineWidth = int(((Fl_Slider*)o)->value());
}

// Updates line angle
void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_lineAngle = int(((Fl_Slider*)o)->value());
}

// Updates alpha
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_alpha = double(((Fl_Slider*)o)->value());
}

// Updates spacing
void ImpressionistUI::cb_spaceingSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_spacing = int(((Fl_Slider*)o)->value());
}

// Updates edgeThreshold
void ImpressionistUI::cb_edgeThresholdSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_edgeThreshold = int(((Fl_Slider*)o)->value());
}

// Updates edge clipping
void ImpressionistUI::cb_edgeClippingButton(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->m_edgeClipping == TRUE) pUI->m_edgeClipping = FALSE;
	else pUI->m_edgeClipping = TRUE;
}

// Updates another gradient
void ImpressionistUI::cb_anotherGradientButton(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->m_anotherGradient == TRUE) pUI->m_anotherGradient = FALSE;
	else pUI->m_anotherGradient = TRUE;
}

// Updates size random
void ImpressionistUI::cb_sizeRandom(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->m_sizeRandom == TRUE) pUI->m_sizeRandom = FALSE;
	else pUI->m_sizeRandom = TRUE;
}

// Updates red
void ImpressionistUI::cb_redScaleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nRedScale = double(((Fl_Slider*)o)->value());
}

// Updates green
void ImpressionistUI::cb_greenScaleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nGreenScale = double(((Fl_Slider*)o)->value());
}

// Updates blue
void ImpressionistUI::cb_blueScaleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nBlueScale = double(((Fl_Slider*)o)->value());
}

//---------------------------------- per instance functions --------------------------------------
//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

//------------------------------------------------
// Return the line width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_lineWidth;
}

//------------------------------------------------
// Return the line angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_lineAngle;
}

//-------------------------------------------------
// Set the line angle
//-------------------------------------------------
void ImpressionistUI::setLineAngle(int angle)
{
	m_lineAngle = angle;
	m_lineAngleSlider->value(m_lineAngle);
}

//------------------------------------------------
// Return the alpha
//------------------------------------------------
double ImpressionistUI::getAlpha()
{
	return m_alpha;
}

double ImpressionistUI::getRedScale()
{
	return m_nRedScale;
}

double ImpressionistUI::getGreenScale()
{
	return m_nGreenScale;
}

double ImpressionistUI::getBlueScale()
{
	return m_nBlueScale;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes },
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas },
		{ "&Color Scale...",	FL_ALT + 'o', (Fl_Callback*)ImpressionistUI::cb_color_scale },
		{ "&Swap", FL_ALT + 'p', (Fl_Callback*)ImpressionistUI::cb_swap_content },
		{ "&Undo", FL_ALT + 'u', (Fl_Callback*)ImpressionistUI::cb_undo_content, 0, FL_MENU_DIVIDER },

		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Circular Spray",	FL_ALT+'e', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCULAR_SPRAY},
  {"Spray",				FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SPRAY},
  {"YouTube",			FL_ALT+'t', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_TRIANGLE},
  {"Scattered YouTube", FL_ALT+'y', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_TRIANGLE},
  {"Blurring",			FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_BLURRING},
  {0}
};

// Stroke direction choice menu defination
Fl_Menu_Item ImpressionistUI::strokeDirectionMenu[NUM_STROKE_DIRECTION + 1] = {
  {"Slider/Right Mouse",FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)DIRECTION_SLIDER_RIGHT_MOUSE},
  {"Gradient",			FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)DIRECTION_GRADIENT},
  {"Brush Direction",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)DIRECTION_BRUSH_DIRECTION},
  {0}
};


//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_lineWidth = 1;
	m_lineAngle = 0;
	m_alpha = 1.00;
	m_spacing = 1;
	m_edgeThreshold = 0;
	m_nRedScale = 1.0;
	m_nGreenScale = 1.0;
	m_nBlueScale = 1.0;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_strokeDirectionChoice = new Fl_Choice(115, 45, 160, 25, "&Stroke Direction");
		m_strokeDirectionChoice->user_data((void*)(this));	 // record self to be used by static callback functions
		m_strokeDirectionChoice->menu(strokeDirectionMenu);
		m_strokeDirectionChoice->callback(cb_strokeDirectionChoice);
		m_strokeDirectionChoice->deactivate();

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line width slider to the dialog 
		m_lineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_lineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_lineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_lineWidthSlider->labelfont(FL_COURIER);
		m_lineWidthSlider->labelsize(12);
		m_lineWidthSlider->minimum(1);
		m_lineWidthSlider->maximum(40);
		m_lineWidthSlider->step(1);
		m_lineWidthSlider->value(m_lineWidth);
		m_lineWidthSlider->align(FL_ALIGN_RIGHT);
		m_lineWidthSlider->callback(cb_lineWidthSlides);
		m_lineWidthSlider->deactivate();

		// Add line angle slider to the dialog 
		m_lineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_lineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_lineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_lineAngleSlider->labelfont(FL_COURIER);
		m_lineAngleSlider->labelsize(12);
		m_lineAngleSlider->minimum(0);
		m_lineAngleSlider->maximum(359);
		m_lineAngleSlider->step(1);
		m_lineAngleSlider->value(m_lineAngle);
		m_lineAngleSlider->align(FL_ALIGN_RIGHT);
		m_lineAngleSlider->callback(cb_lineAngleSlides);
		m_lineAngleSlider->deactivate();

		// Add alpha slider to the dialog 
		m_alphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_alphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_alphaSlider->type(FL_HOR_NICE_SLIDER);
		m_alphaSlider->labelfont(FL_COURIER);
		m_alphaSlider->labelsize(12);
		m_alphaSlider->minimum(0.00);
		m_alphaSlider->maximum(1.00);
		m_alphaSlider->step(0.01);
		m_alphaSlider->value(m_alpha);
		m_alphaSlider->align(FL_ALIGN_RIGHT);
		m_alphaSlider->callback(cb_alphaSlides);


		// Add edge clipping button to the dialog
		m_edgeClippingButton = new Fl_Light_Button(10, 200, 120, 25, "&Edge Clipping");
		m_edgeClippingButton->user_data((void*)(this));
		m_edgeClippingButton->callback(cb_edgeClippingButton);
		m_edgeClippingButton->deactivate();

		// Add another gradient button to the dialog
		m_anotherGradientButton = new Fl_Light_Button(240, 200, 150, 25, "&Another Gradient");
		m_anotherGradientButton->user_data((void*)(this));
		m_anotherGradientButton->callback(cb_anotherGradientButton);
		m_anotherGradientButton->deactivate();

		// Add box and spacing slider to dialog
		Fl_Box* box1 = new Fl_Box(10, 230, 380, 40);
		box1->box(FL_UP_BOX);
		m_spacingSlider = new Fl_Value_Slider(20, 239, 130, 22, "Spacing");
		m_spacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_spacingSlider->type(FL_HOR_NICE_SLIDER);
		m_spacingSlider->labelfont(FL_COURIER);
		m_spacingSlider->labelsize(12);
		m_spacingSlider->minimum(1);
		m_spacingSlider->maximum(16);
		m_spacingSlider->step(1);
		m_spacingSlider->value(m_spacing);
		m_spacingSlider->align(FL_ALIGN_RIGHT);
		m_spacingSlider->callback(cb_spaceingSlides);

		m_sizeRandomButton = new Fl_Light_Button(220, 239, 100, 22, "&Size Rand.");
		m_sizeRandomButton->user_data((void*)(this));
		m_sizeRandomButton->callback(cb_sizeRandom);

		m_paintButton = new Fl_Button(330, 239, 50, 22, "&Paint");
		m_paintButton->user_data((void*)(this));
		m_paintButton->callback(cb_paintButton);


		// Add box and edge threshold slider to dialog
		Fl_Box* box2 = new Fl_Box(10, 275, 380, 40);
		box2->box(FL_UP_BOX);
		m_edgeThresholdSlider = new Fl_Value_Slider(20, 285, 200, 20, "Edge Threshold");
		m_edgeThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_edgeThresholdSlider->type(FL_HOR_NICE_SLIDER);
		m_edgeThresholdSlider->labelfont(FL_COURIER);
		m_edgeThresholdSlider->labelsize(12);
		m_edgeThresholdSlider->minimum(0);
		m_edgeThresholdSlider->maximum(500);
		m_edgeThresholdSlider->step(1);
		m_edgeThresholdSlider->value(m_edgeThreshold);
		m_edgeThresholdSlider->align(FL_ALIGN_RIGHT);
		m_edgeThresholdSlider->callback(cb_edgeThresholdSlides);

		m_paintButton = new Fl_Button(330, 285, 50, 20, "&Do it");
		m_paintButton->user_data((void*)(this));
		m_paintButton->callback(cb_drawEdge);

    m_brushDialog->end();	


	m_colorScaleDialog = new Fl_Window(400, 325, "Color Scale Dialog");
		// Add red slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 50, 300, 20, "Red");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
		m_BrushSizeSlider->labelfont(FL_COURIER);
		m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(0.0);
		m_BrushSizeSlider->maximum(3.0);
		m_BrushSizeSlider->step(0.1);
		m_BrushSizeSlider->value(m_nRedScale);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_redScaleSlides);

		// Add green slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 100, 300, 20, "Green");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
		m_BrushSizeSlider->labelfont(FL_COURIER);
		m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(0.0);
		m_BrushSizeSlider->maximum(3.0);
		m_BrushSizeSlider->step(0.1);
		m_BrushSizeSlider->value(m_nGreenScale);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_greenScaleSlides);

		// Add blue slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 150, 300, 20, "Blue");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
		m_BrushSizeSlider->labelfont(FL_COURIER);
		m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(0.0);
		m_BrushSizeSlider->maximum(3.0);
		m_BrushSizeSlider->step(0.1);
		m_BrushSizeSlider->value(m_nBlueScale);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_blueScaleSlides);

	m_colorScaleDialog->end();

}
