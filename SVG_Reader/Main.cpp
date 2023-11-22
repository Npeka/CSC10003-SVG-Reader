#include "src/SVGImage.h"
#include "src/Render.h"

int main() {
    SVGImage svgImage("sample.svg");
    sfml::render(svgImage);
    return 0;
}
