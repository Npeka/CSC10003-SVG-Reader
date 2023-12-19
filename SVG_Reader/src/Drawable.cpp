#include "Drawable.h"

Gdiplus::Color GDI_RGB(const RGB_Color& color) {
	return Gdiplus::Color(color.opacity, color.r, color.g, color.b);
}

Gdiplus::Brush* GDI_LinearGradient(const LinearGradient& color, const Gdiplus::RectF& rect) {
	Point p1 = color.getP1();
	Point p2 = color.getP2();
	vector<Stop> ColorOffset = color.getColorOffset();
	int size = ColorOffset.size();
	bool isPercent = color.getIsPercent();

	if (isPercent) {
		p1.x = rect.GetLeft() + p1.x * (rect.GetRight() - rect.GetLeft()) / 100.0f;
		p1.y = rect.GetTop() + p1.y * (rect.GetBottom() - rect.GetTop()) / 100.0f;
		p2.x = rect.GetLeft() + p2.x * (rect.GetRight() - rect.GetLeft()) / 100.0f;
		p2.y = rect.GetTop() + p2.y * (rect.GetBottom() - rect.GetTop()) / 100.0f;
	}

	Gdiplus::LinearGradientBrush* linear;
	linear = new Gdiplus::LinearGradientBrush(
		Gdiplus::PointF(p1.x, p1.y),
		Gdiplus::PointF(p2.x, p2.y),
		GDI_RGB(ColorOffset[0].getColor()),
		GDI_RGB(ColorOffset[size - 1].getColor())
	);

	Gdiplus::Color* stopColors = new Gdiplus::Color[size];
	for (int i = 0; i < size; ++i) {
		stopColors[i] = GDI_RGB(ColorOffset[i].getColor());
	}

	Gdiplus::REAL* positions = new Gdiplus::REAL[size];
	for (int i = 0; i < size; ++i) {
		positions[i] = ColorOffset[i].getOffset() / 100;
	}

	linear->SetInterpolationColors(
		stopColors,
		positions,
		size
	);

	delete[] stopColors;
	delete[] positions;

	return linear;
}

Gdiplus::Brush* GDI_RadialGradient(const RadialGradient& color, const Gdiplus::RectF& rect) {
	int cx = color.getCX();
	int cy = color.getCY();
	int r = color.getR();
	vector<Stop> ColorOffset = color.getColorOffset();
	int size = ColorOffset.size();

	Gdiplus::GraphicsPath path;
	path.AddEllipse(cx - r, cy - r, 2 * r, 2 * r);

	Gdiplus::PathGradientBrush* radial = nullptr;
	radial = new Gdiplus::PathGradientBrush(&path);

	Gdiplus::Color* stopColors = new Gdiplus::Color[size];
	for (int i = size - 1; i >= 0; --i) {
		stopColors[i] = GDI_RGB(ColorOffset[i].getColor());
	}

	Gdiplus::Matrix matrix(0, -1.98198, 1.8439, 0, -1031.4, 454.004);
	radial->SetTransform(&matrix);

	Gdiplus::REAL* positions = new Gdiplus::REAL[size];
	for (int i = size - 1; i >= 0; --i) {
		positions[i] = 1 - ColorOffset[i].getOffset();
		std::cout << positions[i] << std::endl;
	}

	radial->SetInterpolationColors(
		stopColors,
		positions,
		size
	);

	delete[] stopColors;
	delete[] positions;

	return radial;
}

Gdiplus::Brush* GDI_Brush(Color* color, const Gdiplus::RectF& rect) {
	if (dynamic_cast<RGB_Color*>(color)) {
		return new Gdiplus::SolidBrush(GDI_RGB(*dynamic_cast<RGB_Color*>(color)));
	}
	else if (dynamic_cast<LinearGradient*>(color)) {
		return GDI_LinearGradient(*dynamic_cast<LinearGradient*>(color), rect);
	}
	else if (dynamic_cast<RadialGradient*>(color)) {
		return GDI_RadialGradient(*dynamic_cast<RadialGradient*>(color), rect);
	}
}

void Transform_First(const vector<pair<int, Point>>& t, Render_Window) {
	for (int i = 0; i < t.size(); ++i) {
		if (t[i].first == SVG_Translate) {
			graphics.TranslateTransform(t[i].second.x, t[i].second.y);
		}
		else if (t[i].first == SVG_Rotate) {
			graphics.RotateTransform(t[i].second.x);
		}
		else if (t[i].first == SVG_Scale) {
			graphics.ScaleTransform(t[i].second.x, t[i].second.y);
		}
	}
}

void Transform_Second(const vector<pair<int, Point>>& t, Render_Window) {
	for (int i = t.size() - 1; i >= 0; --i) {
		if (t[i].first == SVG_Translate) {
			graphics.TranslateTransform(-t[i].second.x, -t[i].second.y);
		}
		else if (t[i].first == SVG_Rotate) {
			graphics.RotateTransform(-t[i].second.x);
		}
		else if (t[i].first == SVG_Scale) {
			graphics.ScaleTransform(1 / t[i].second.x, 1 / t[i].second.y);
		}
	}
}

// class Drawable
Drawable::Drawable() :
	brush(nullptr),
	pen(nullptr)
{}

Drawable::~Drawable() {
	dealocate(brush);
	dealocate(pen);
}