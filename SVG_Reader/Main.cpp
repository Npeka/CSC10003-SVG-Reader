#include "src/SVGImage.h"
#include "src/Render.h"

int main() {
    SVGImage svgImage("svg-01.svg");
    svgImage.render();
    return 0;
}
