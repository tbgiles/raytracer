#pragma once

#include <atlas/math/math.hpp>
#include "lights/light.hpp"
#include "structures/surface_interaction.hpp"

namespace poly::light {

	class PointLight : public Light
	{
	public:

		PointLight();

		PointLight(math::Vector const& location);

		void location_set(atlas::math::Point const& location);

		atlas::math::Vector get_direction(poly::structures::SurfaceInteraction& sr);
		bool in_shadow(math::Ray<math::Vector> const& shadow_ray,
			poly::structures::World const& world);

		Colour L(poly::structures::SurfaceInteraction& sr, poly::structures::World const& world);

	protected:
		atlas::math::Point m_location;
	};

}