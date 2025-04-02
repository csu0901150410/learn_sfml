#include "lsGeometry.h"
#include "lsRenderer.h"

void lsLine::render(lsRenderer& renderer) const
{
	renderer.draw_line(s, e, stroke_color, stroke_width);
}
