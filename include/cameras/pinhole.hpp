#ifndef PINHOLE_HPP
#define PINHOLE_HPP

#include <atlas/math/ray.hpp>
#include "cameras/camera.hpp"
#include "structures/world.hpp"
#include "structures/scene_slab.hpp"
#include "utilities/utilities.hpp"

namespace poly::camera {

    class PinholeCamera : public Camera {
    public:

        /*
        * Distance from eye to coordinate grid (larger means tighter rays)
        */
        float m_d;

        /*
        * Constructors
        */
        PinholeCamera();
        PinholeCamera(float d);

        /*
        * Out-of-gamut handling
        */
        Colour colour_validate(Colour const& colour) const;

        /*
        * Scene rendering loops
        */
        void multithread_render_scene(poly::structures::World& world, poly::utils::BMP_info& output);
        void render_scene(poly::structures::World& world) const;
        atlas::math::Ray<atlas::math::Vector> get_ray(int i, int j, poly::structures::World const& world) const;

    private:
        void render_slab(std::shared_ptr<poly::structures::scene_slab> slab) const;
    };
}

#endif // !PINHOLE_HPP