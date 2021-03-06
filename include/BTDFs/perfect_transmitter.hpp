#pragma once

#include <atlas/math/math.hpp>
#include "BTDFs/BTDF.hpp"
#include "structures/surface_interaction.hpp"

namespace poly::material {

	class PerfectTransmitter : public BTDF {
	public:
		PerfectTransmitter();
		PerfectTransmitter(float kt, float _ior);

		bool tot_int_refl(poly::structures::SurfaceInteraction const& sr) const;
		Colour f([[maybe_unused]] poly::structures::SurfaceInteraction const& sr,
			[[maybe_unused]] atlas::math::Vector& w_o,
			[[maybe_unused]] atlas::math::Vector& w_i) const;

		Colour sample_f(poly::structures::SurfaceInteraction const& sr,
			atlas::math::Vector& w_o,
			atlas::math::Vector& w_t) const;

		Colour rho([[maybe_unused]] poly::structures::SurfaceInteraction const& sr,
			[[maybe_unused]] atlas::math::Vector& w_o) const;

		float kt() const;

		float ior() const;
	};
}