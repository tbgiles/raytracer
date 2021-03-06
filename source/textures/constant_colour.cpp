#include "textures/constant_colour.hpp"

namespace poly::texture
{

	using Colour= atlas::math::Vector ;

	ConstantColour::ConstantColour(Colour const &c) : m_colour{c} {}
	Colour ConstantColour::get_colour([[maybe_unused]] poly::structures::SurfaceInteraction const &sr) const
	{
		return m_colour;
	}
	void ConstantColour::colour_set(Colour const &c)
	{
		m_colour = c;
	}
} // namespace poly::texture
