#pragma once

#include "lsRenderer.h"

#include <SFML/Graphics.hpp>

class lsSFMLRenderer : public lsRenderer
{
public:
	explicit lsSFMLRenderer(sf::RenderWindow& window)
		: m_window(window)
	{

	}

	void begin_frame(const lsRenderContext& ctx) override
	{
		m_window.clear(sf::Color::Black);
	}

	void end_frame(const lsRenderContext& ctx) override
	{
		m_window.display();
	}

	void draw_line(const lsVector2f& p1, const lsVector2f& p2,
		const lsColor& c, float r) override
	{
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(p1.x, p1.y), to_sfml_color(c)),
			sf::Vertex(sf::Vector2f(p2.x, p2.y), to_sfml_color(c))
		};
		m_window.draw(line, 2, sf::Lines);
	}

	void draw_circle(const lsVector2f& center, float radius,
		const lsColor& fill_color, const lsColor& stroke_color,
		float stroke_width) override
	{
		sf::CircleShape circle(radius);
		circle.setPosition(center.x - radius, center.y - radius);
		circle.setFillColor(to_sfml_color(fill_color));
		circle.setOutlineColor(to_sfml_color(stroke_color));
		circle.setOutlineThickness(stroke_width);
		m_window.draw(circle);
	}

private:
	sf::RenderWindow& m_window;

	static sf::Color to_sfml_color(const lsColor& color)
	{
		return sf::Color(
			static_cast<sf::Uint8>(color.r * 255),
			static_cast<sf::Uint8>(color.g * 255),
			static_cast<sf::Uint8>(color.b * 255),
			static_cast<sf::Uint8>(color.a * 255)
		);
	}
};
