#ifndef DRAWABLE_H
#define DRAWABLE_H

// Include necessary libraries for rendering
#include <windows.h>
#include <gdiplus.h>

#include "Header.h"
#include "RGB_Color.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

// Define parameters needed for render lib
#define Render_Window Gdiplus::Graphics& graphics
#define Render_Parameters graphics

//********************************************//
// Function to convert from Color to Graphics library Colors
/**
 * @brief Converts RGB_Color to GDI+ Color.
 * @param color The RGB_Color object.
 * @return GDI+ Color equivalent.
 */
Gdiplus::Color GDI_RGB(const RGB_Color& color);

/**
 * @brief Creates a GDI+ LinearGradientBrush from a LinearGradient color.
 * @param color The LinearGradient object.
 * @param rect The bounding rectangle for the brush.
 * @return Pointer to the created LinearGradientBrush.
 */
Gdiplus::Brush* GDI_LinearGradient(const LinearGradient& color, const Gdiplus::RectF& rect = { 0,0,0,0 });

/**
 * @brief Creates a GDI+ RadialGradientBrush from a RadialGradient color.
 * @param color The RadialGradient object.
 * @param rect The bounding rectangle for the brush.
 * @return Pointer to the created RadialGradientBrush.
 */
Gdiplus::Brush* GDI_RadialGradient(const RadialGradient& color, const Gdiplus::RectF& rect = { 0,0,0,0 });

/**
 * @brief Creates a GDI+ Brush from a Color.
 * @param color The Color object.
 * @param rect The bounding rectangle for the brush.
 * @return Pointer to the created Brush.
 */
Gdiplus::Brush* GDI_Brush(Color* color, const Gdiplus::RectF& rect = { 0,0,0,0 });

/**
 * @brief Creates a GDI+ Pen from a Color.
 * @param color The Color object.
 * @param stroke_width The width of the pen.
 * @param rect The bounding rectangle for the pen.
 * @return Pointer to the created Pen.
 */
Gdiplus::Pen* GDI_Pen(Color* color, const float& stroke_width, const Gdiplus::RectF& rect = { 0,0,0,0 });

//********************************************//
//Function to apply transformations to render window
/**
 * @brief Applies the first transformation to the render window.
 * @param t The Transform_Type to apply.
 * @param graphics The GDI+ Graphics object.
 */
void Transform_First(const Transform_Type& t, Render_Window);

/**
 * @brief Applies the second transformation to the render window.
 * @param t The Transform_Type to apply.
 * @param graphics The GDI+ Graphics object.
 */
void Transform_Second(const Transform_Type& t, Render_Window);

/**
 * @brief Base class for drawable objects.
 *
 * This class provides basic functionality for drawable objects.
 * It includes brushes and pens for rendering and virtual functions
 * for setting attributes and drawing.
 */
class Drawable {
protected:
    Gdiplus::Brush* brush; /**< GDI+ Brush for filling shapes. */
    Gdiplus::Pen* pen;     /**< GDI+ Pen for outlining shapes. */
    Gdiplus::Brush* solidBrush; /**< GDI+ SolidBrush for solid color. */

public:
    /**
     * @brief Default constructor for Drawable.
     * Initializes brushes and pens to nullptr.
     */
    Drawable();

    /**
     * @brief Virtual function to draw the object.
     * To be implemented by derived classes.
     * @param graphics The GDI+ Graphics object.
     */
    virtual void draw(Render_Window) {};

    /**
     * @brief Virtual destructor for Drawable.
     * Frees allocated resources for brushes and pens.
     */
    virtual ~Drawable();

    /**
     * @brief Virtual function to set drawable attributes.
     * To be implemented by derived classes.
     */
    virtual void setDrawableAtrributes() {};
};

// Forward declarations for derived classes
class Drawable_Rectangle;
class Drawable_Ellipse;
class Drawable_Circle;
class Drawable_Line;
class Drawable_Polyline;
class Drawable_Polygon;
class Drawable_Text;
class Drawable_path;

#endif // !DRAWABLE_H
