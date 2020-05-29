#pragma once

#include <atlas/math/math.hpp>
#include "lights/light.hpp"

namespace poly::light
{

	class AmbientOcclusion : public Light
	{
	public:
		AmbientOcclusion();

		void min_amount_set(float amount);

		void sampler_set(std::shared_ptr<poly::sampler::Sampler> s_ptr, float tightness);

		math::Vector direction_get([[maybe_unused]] poly::structures::ShadeRec &sr);

		// Specific to ambient occlusion, we need access to samples mapped to hemisphere
		math::Vector shadow_direction_get([[maybe_unused]] poly::structures::ShadeRec &sr, unsigned int sample_index);

		Colour L(poly::structures::ShadeRec &sr);

	protected:
		std::shared_ptr<poly::sampler::Sampler> m_sampler;
		Colour min_amount;
	};
} // namespace poly::light