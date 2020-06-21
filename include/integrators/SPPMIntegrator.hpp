#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP


#include "structures/world.hpp"
#include "objects/object.hpp"
#include "structures/scene_slab.hpp"
#include "cameras/pinhole.hpp"
#include "materials/material.hpp"

namespace poly::integrators {

	class VisiblePoint : public poly::object::Object
	{
	public:
		VisiblePoint(int x_, int y_, math::Point const& point_, math::Vector const& incoming_ray_, std::shared_ptr<poly::material::Material> material_);
		// Provided to allow compatibility with Object type
		bool hit(math::Ray<math::Vector>const& R,
			poly::structures::SurfaceInteraction& sr) const;
		bool shadow_hit(math::Ray<math::Vector>const& R, float& t) const;

		// Originating Pixels
		int index_x; // Along the x axis
		int index_y; // Along the y axis

		// Point where the VisiblePoint was created
		math::Point point;

		// Direction of the incoming ray ( points toward the camera!)
		math::Vector w_i;

		// Material of the object that the VisiblePoint is on
		std::shared_ptr<poly::material::Material> material;
	};

	class SPPMIntegrator {
	public:
		SPPMIntegrator();
		void render(poly::structures::World const& world, poly::camera::PinholeCamera const& camera, poly::utils::BMP_info& output);
	private:

		std::vector<std::shared_ptr<poly::object::Object>> create_visible_points(std::shared_ptr<poly::structures::scene_slab> slab,
			poly::camera::PinholeCamera const& camera, 
			std::shared_ptr<poly::structures::World> world);

	};
}
/**
Steps:
the entire algorithm repeats for N iterations

1. Shoot out rays from camera. At every intersection with an object (1 ONLY), create a visiblePoint. Store these "Visible Points" in a KD-Tree, indexed based on location in the scene.

2. Shoot out rays from each light, intersection against the scenery. On each interstedtion, check nearby visible point KD-Tree. For each nearby visible point, add the photon's value to it's light contribution 

PSEUDOCODE FOR ALGORITHM

*/
#endif // !INTEGRATOR_HPP