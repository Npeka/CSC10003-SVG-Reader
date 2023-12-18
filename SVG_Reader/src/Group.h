#ifndef GROUP_H
#define GROUP_H

#include "Drawable.h"
#include "Figure.h"

class Group : public Figure, public Drawable {
private:
    Group* parent; 
    vector<Drawable*> figures; 
    vector<pair<string, string>> childAttributes; 

public:
    
    Group();
    ~Group() override;
    void setParent(Group* parent);
    void setParentAttributes();
    void setFigureAttributes(const string& attribute, string& value) override;
    void setChildAttributes(Figure* figure);

    Group* getParent();
    const vector<Drawable*>& getFigures() const;
    void addDrawable(Drawable* drawable);

    void draw(Render_Window) override;
};

#endif // !GROUP_H