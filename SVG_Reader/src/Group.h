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
	void setParentAttributes();
	Group* getParent();
	const std::vector<Drawable*>& getFigures() const;

	void addDrawable(Drawable* drawable);
	void draw(Render_Window) override;
};

#endif // !GROUP_H

