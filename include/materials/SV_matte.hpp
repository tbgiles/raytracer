#pragma once
#ifndef SVMATTE_HPP
#define SVMATTE_HPP

#include <memory>

#include "structures/world.hpp"
#include "lights/light.hpp"
#include "textures/texture.hpp"
#include "BRDFs/lambertian.hpp"
#include "BRDFs/SV_lambertian.hpp"
#include "textures/constant_colour.hpp"
#include "textures/image_texture.hpp"

namespace poly::material
{

	class SV_Matte : public Material
	{
	public:
		SV_Matte(float f, std::shared_ptr<poly::texture::Texture> tex);

		SV_Matte(float f, Colour const &c);

		SV_Matte(float f, std::string const &s);
		virtual float get_diffuse_strength() const;
		virtual float get_specular_strength() const;
		virtual float get_reflective_strength() const;
		virtual float get_refractive_strength() const;
		virtual Colour get_hue([[maybe_unused]] atlas::math::Point& hp) const;

		void absorb_photon(structures::Photon &photon, poly::structures::KDTree& vp_tree, unsigned int max_depth,
						   std::vector<std::shared_ptr<poly::object::Object>> scene) const;
		virtual void handle_vision_point(std::shared_ptr<poly::object::Object>& visible_point,
										 poly::structures::SurfaceInteraction& si,
										 poly::structures::World& world) const;


	protected:
		std::shared_ptr<SV_LambertianBRDF> m_diffuse;

		Colour shade(poly::structures::SurfaceInteraction&sr, poly::structures::World& world) const;
	};
} // namespace poly::material
#endif // !SVMATTE_HPP