#ifndef GROUP_H
#define GROUP_H

#include "Render.h"

class Group : public Figure, public Drawable {
private:
	Group* parent;
	std::vector<Drawable*> figures;
public:
	Group();
	~Group() override;

	void setParent(Group* parent);
	void addDrawable(Drawable* drawable);
	Group* getParent();
	const std::vector<Drawable*>& getFigures() const;
	void draw(Render_Window) override;
};

#endif // !GROUP_H

