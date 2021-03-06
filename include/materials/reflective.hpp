#pragma once
#ifndef REFLECTIVEMAT_HPP
#define REFLECTIVEMAT_HPP

#include "BRDFs/perfect_specular.hpp"
#include "materials/phong.hpp"
#include "tracers/tracer.hpp"

namespace poly::material {

	class Reflective : public Phong {
	public:

		Reflective();

		Reflective(const float amount_refl,
			float f_diffuse,
			float f_spec,
			Colour const& _colour,
			float _exp);

		Colour shade(poly::structures::SurfaceInteraction& sr, poly::structures::World const& world) const;
		virtual float get_diffuse_strength() const;
		virtual float get_specular_strength() const;
		virtual float get_reflective_strength() const;
		virtual float get_refractive_strength() const;
		virtual Colour get_hue([[maybe_unused]] atlas::math::Point const& hp) const;

		void absorb_photon(structures::Photon& photon, poly::structures::KDTree& vp_tree, unsigned int max_depth,
			poly::structures::World& world) const;
		virtual void handle_vision_point(std::shared_ptr<poly::object::Object>& visible_point,
										 poly::structures::SurfaceInteraction& si,
										 poly::structures::World& world) const;

	protected:
		std::shared_ptr<PerfectSpecular> m_reflected_brdf;
	};

}

#endif // !REFLECTIVEMAT_HPP