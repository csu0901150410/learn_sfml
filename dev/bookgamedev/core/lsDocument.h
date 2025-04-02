#pragma once

#include <memory>

#include "lsGeometry.h"
#include "lsRenderer.h"

class lsDocument
{
public:
	void add_shape(std::unique_ptr<lsGeometryObject> shape)
	{
		m_shapes.push_back(std::move(shape));
	}

	void render(lsRenderer& renderer, const lsRenderContext& ctx) const
	{
		renderer.begin_frame(ctx);
		for (const auto& shape : m_shapes)
		{
			shape->render(renderer);
		}
		renderer.end_frame(ctx);
	}

	const std::vector<std::unique_ptr<lsGeometryObject>>& get_shapes() const
	{
		return m_shapes;
	}

private:
	std::vector<std::unique_ptr<lsGeometryObject>> m_shapes;
};
