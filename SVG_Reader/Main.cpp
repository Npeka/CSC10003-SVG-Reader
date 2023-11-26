#include "src/SVGImage.h"
#include "src/Render.h"

int main() {
    SVGImage svgImage("sample.svg");
    int a = 10;
    sfml::render(svgImage);
    return 0;
}
