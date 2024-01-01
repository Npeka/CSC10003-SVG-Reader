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
	Transform_Type t = color.getTransform();

	/*if (isPercent) {
		p1.x = rect.GetLeft() + p1.x * (rect.GetRight() - rect.GetLeft()) / 100.0f;
		p1.y = rect.GetTop() + p1.y * (rect.GetBottom() - rect.GetTop()) / 100.0f;
		p2.x = rect.GetLeft() + p2.x * (rect.GetRight() - rect.GetLeft()) / 100.0f;
		p2.y = rect.GetTop() + p2.y * (rect.GetBottom() - rect.GetTop()) / 100.0f;
	}*/

	if (ColorOffset[0].getOffset() != 0) {
		RGB_Color first = ColorOffset[0].getColor();
		float offset = ColorOffset[0].getOffset();
		RGB_Color zero;
		zero.r = first.r * (1 - offset);
		zero.g = first.g * (1 - offset);
		zero.b = first.b * (1 - offset);
		zero.opacity = first.opacity * (1 - offset);
		Stop stop;
		stop.color = zero;
		stop.offset = 0;
		ColorOffset.insert(ColorOffset.begin(), stop);
		size++;
	}

	if (ColorOffset[size - 1].getOffset() != 1) {
		RGB_Color last = ColorOffset[size - 1].getColor();
		float offset = ColorOffset[size - 1].getOffset();
		RGB_Color one;
		one.r = last.r * (1 - offset);
		one.g = last.g * (1 - offset);
		one.b = last.b * (1 - offset);
		one.opacity = last.opacity * (1 - offset);
		one.balance();
		Stop stop;
		stop.color = one;
		stop.offset = 1;
		ColorOffset.push_back(stop);
		size++;
	}

	Gdiplus::LinearGradientBrush* linear;

	if (isPercent) {
		linear = new Gdiplus::LinearGradientBrush(
			rect,
			GDI_RGB(ColorOffset[0].getColor()),
			GDI_RGB(ColorOffset[size - 1].getColor()),
			0
		);
	}
	else {
		linear = new Gdiplus::LinearGradientBrush(
			Gdiplus::PointF(p1.x, p1.y),
			Gdiplus::PointF(p2.x, p2.y),
			GDI_RGB(ColorOffset[0].getColor()),
			GDI_RGB(ColorOffset[size - 1].getColor())
		);

		float scale1 = rect.Width / p1.x;
		float scale2 = rect.Height / p2.y;
		linear->ScaleTransform(scale1, scale2);
	}

	Gdiplus::Color* stopColors = new Gdiplus::Color[size];
	for (int i = 0; i < size; ++i) {
		stopColors[i] = GDI_RGB(ColorOffset[i].getColor());
	}

	Gdiplus::REAL* positions = new Gdiplus::REAL[size];
	for (int i = 0; i < size; ++i) {
		positions[i] = ColorOffset[i].getOffset();
	}

	linear->SetInterpolationColors(
		stopColors,
		positions,
		size
	);

	for (int i = 0; i < t.size(); i++) {
		if (t[i].first == SVG_Translate) {
			linear->TranslateTransform(t[i].second[0], t[i].second[1]);
		}
		else if (t[i].first == SVG_Rotate) {
			linear->RotateTransform(t[i].second[0]);
		}
		else if (t[i].first == SVG_Scale) {
			linear->ScaleTransform(t[i].second[0], t[i].second[1]);
		}
		else if (t[i].first == SVG_Matrix) {
			Gdiplus::Matrix matrix(
				t[i].second[0], t[i].second[1], t[i].second[2],
				t[i].second[3], t[i].second[4], t[i].second[5]
			);
			linear->SetTransform(&matrix);
		}
	}

	delete[] stopColors;
	delete[] positions;

	return linear;
}

Gdiplus::Brush* GDI_RadialGradient(const RadialGradient& color, const Gdiplus::RectF& rect) {
	float cx = color.getCX();
	float cy = color.getCY();
	float r = color.getR();
	/*float fx = color.getFX();
	float fy = color.getFY();*/
	vector<Stop> ColorOffset = color.getColorOffset();
	int size = ColorOffset.size();
	Transform_Type t = color.getTransform();

	Gdiplus::GraphicsPath path;
	path.AddEllipse(Gdiplus::RectF(cx - r, cy - r, r * 2, r * 2));

	Gdiplus::PathGradientBrush* radial = nullptr;
	radial = new Gdiplus::PathGradientBrush(&path);

	if (ColorOffset[0].getOffset() != 0) {
		RGB_Color first = ColorOffset[0].getColor();
		float offset = ColorOffset[0].getOffset();
		RGB_Color zero;
		zero.g = first.g; // * (1 - offset);
		zero.b = first.b; // * (1 - offset);
		zero.r = first.r; // * (1 - offset);
		zero.opacity = first.opacity; // *(1 - offset);
		Stop stop;
		stop.color = zero;
		stop.offset = 0;
		ColorOffset.insert(ColorOffset.begin(), stop);
		size++;
	}
	
	if (ColorOffset[size - 1].getOffset() != 1) {
		RGB_Color last = ColorOffset[size - 1].getColor();
		float offset = ColorOffset[size - 1].getOffset();
		RGB_Color one;
		one.r = last.r; // * (1 - offset);
		one.g = last.g; // * (1 - offset);
		one.b = last.b; // * (1 - offset);
		one.opacity = last.opacity; // *(1 - offset);
		one.balance();
		Stop stop;
		stop.color = one;
		stop.offset = 1;
		ColorOffset.push_back(stop);
		size++;
	}
	

	Gdiplus::Color* stopColors = new Gdiplus::Color[size];
	for (int i = 0; i < size; ++i) {
		stopColors[i] = GDI_RGB(ColorOffset[size - i - 1].getColor());
	}

	Gdiplus::REAL* positions = new Gdiplus::REAL[size];
	for (int i = 0; i < size; ++i) {
		positions[i] = 1 - ColorOffset[size - i - 1].getOffset();
	}

	radial->SetInterpolationColors(
		stopColors,
		positions,
		size
	);

	for (int i = 0; i < t.size(); ++i) {
		if (t[i].first == SVG_Translate) {
			radial->TranslateTransform(t[i].second[0], t[i].second[1]);
		}
		else if (t[i].first == SVG_Rotate) {
			radial->RotateTransform(t[i].second[0]);
		}
		else if (t[i].first == SVG_Scale) {
			radial->ScaleTransform(t[i].second[0], t[i].second[1]);
		}
		else if (t[i].first == SVG_Matrix) {
			float scale1 = rect.Width / r ;
			float scale2 = rect.Height / r;
			Gdiplus::Matrix matrix(
				t[i].second[0], t[i].second[1], t[i].second[2],
				t[i].second[3], t[i].second[4], t[i].second[5]
			);
			radial->SetTransform(&matrix);
			//radial->MultiplyTransform(&matrix);
		}
	}
	
	delete[] stopColors;
	delete[] positions;

	return radial;
}

Gdiplus::Brush* GDI_Brush(Color* color, const Gdiplus::RectF& rect) {
	if (auto it = dynamic_cast<RGB_Color*>(color)) {
		return new Gdiplus::SolidBrush(GDI_RGB(*it));
	}
	else if (auto it = dynamic_cast<LinearGradient*>(color)) {
		return GDI_LinearGradient(*it, rect);
	}
	else if (auto it = dynamic_cast<RadialGradient*>(color)) {
		return GDI_RadialGradient(*it, rect);
	}
	return nullptr;
}

Gdiplus::Pen* GDI_Pen(Color* color, const float& stroke_width, const Gdiplus::RectF& rect) {
	return new Gdiplus::Pen(GDI_Brush(color, rect), stroke_width);
}

void Transform_First(const Transform_Type& t, Render_Window) {
	for (int i = 0; i < t.size(); ++i) {
		if (t[i].first == SVG_Translate) {
			graphics.TranslateTransform(t[i].second[0], t[i].second[1]);
		}
		else if (t[i].first == SVG_Rotate) {
			graphics.RotateTransform(t[i].second[0]);
		}
		else if (t[i].first == SVG_Scale) {
			graphics.ScaleTransform(t[i].second[0], t[i].second[1]);
		}
		else if (t[i].first == SVG_Matrix) {
			Gdiplus::Matrix matrix(
				t[i].second[0], t[i].second[1], t[i].second[2],
				t[i].second[3], t[i].second[4], t[i].second[5]
			);
			//graphics.SetTransform(&matrix);
		}
	}
}

void Transform_Second(const Transform_Type& t, Render_Window) {
	for (int i = t.size() - 1; i >= 0; --i) {
		if (t[i].first == SVG_Translate) {
			graphics.TranslateTransform(-t[i].second[0], -t[i].second[1]);
		}
		else if (t[i].first == SVG_Rotate) {
			graphics.RotateTransform(-t[i].second[0]);
		}
		else if (t[i].first == SVG_Scale) {
			graphics.ScaleTransform(1 / t[i].second[0], 1 / t[i].second[1]);
		}
	}
}

// class Drawable
Drawable::Drawable() :
	brush(nullptr),
	pen(nullptr),
	solidBrush(nullptr)
{}

Drawable::~Drawable() {
	dealocate(brush);
	dealocate(pen);
	dealocate(solidBrush);
}
