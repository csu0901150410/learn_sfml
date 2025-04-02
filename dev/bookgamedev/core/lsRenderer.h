#pragma once

#include "lsGeometry.h"

// ��Ⱦ������
struct lsRenderContext
{
	void* window_ptr;
};

// ��Ⱦ�ӿ�
class lsRenderer
{
public:
	virtual ~lsRenderer() = default;

	virtual void begin_frame(const lsRenderContext& ctx) = 0;
	virtual void end_frame(const lsRenderContext& ctx) = 0;

	virtual void draw_line(const lsVector2f& p1, const lsVector2f& p2,
		const lsColor& c, float r) = 0;

	virtual void draw_circle(const lsVector2f& center, float radius,
		const lsColor& fill_color, const lsColor& stroke_color,
		float stroke_width) = 0;
};
