#include "src/SVGImage.h"
#include "src/Render.h"

int main() {
    SVGImage svgImage("Ztest.svg");
    sfml::render(svgImage);
    return 0;
}
