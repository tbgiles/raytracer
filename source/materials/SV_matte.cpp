#include "materials/SV_matte.hpp"

namespace poly::material {

	SV_Matte::SV_Matte(float f, std::shared_ptr<poly::texture::Texture> tex)
	{
		m_diffuse = std::make_shared<SV_LambertianBRDF>(f, tex);
	}

	SV_Matte::SV_Matte(float f, Colour const& c)
	{
		m_diffuse = std::make_shared<SV_LambertianBRDF>(f, std::make_shared<poly::texture::ConstantColour>(c));
	}

	SV_Matte::SV_Matte(float f, std::string const& s)
	{
		m_diffuse = std::make_shared<SV_LambertianBRDF>(f, std::make_shared<poly::texture::ImageTexture>(s));
	}

	Colour SV_Matte::shade(poly::structures::SurfaceInteraction& sr, poly::structures::World& world) const {
		// Render loop
		Colour r = Colour(0.0f, 0.0f, 0.0f);
		Colour a = {0.0f, 0.0f, 0.0f};
		atlas::math::Vector nullVec(0.0f, 0.0f, 0.0f);

		if (world.m_ambient) {
			a = m_diffuse->rho(sr, nullVec)
				* world.m_ambient->L(sr, world);
		}

		for (std::shared_ptr<poly::light::Light> light : world.m_lights) {
			Colour brdf = m_diffuse->f(sr, nullVec, nullVec);
			Colour L = light->L(sr, world);
			float angle = glm::dot(sr.m_normal,
								   light->get_direction(sr));
			if (angle >= 0) {
				r += (brdf
					* L
					* angle);
			}
		}

		return (a + r);
	}
}
