#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>
#include <atlas/math/math.hpp>

namespace poly::light { class Light; }
namespace poly::object { class Object; }
namespace poly::sampler { class Sampler; }
namespace poly::light { class Light; }

namespace poly::structures {

    class Tracer; // avoids non-declaration in circular dependancy
	class ViewPlane;

    class World {
    public:
        // Default pixel colour
        atlas::math::Vector m_background;

        // Section to be rendered
		int m_start_width, m_start_height, m_end_width, m_end_height;

         // The sampler for AA
        std::shared_ptr<poly::sampler::Sampler> m_sampler;

        // Objects in our scene
        std::vector<std::shared_ptr<poly::object::Object>> m_scene; 

        // Ambient light in our scene (gets handled specially)
        std::shared_ptr<poly::light::Light> m_ambient;
        
        // Lights in our scene
        std::vector<std::shared_ptr<poly::light::Light>> m_lights; 
        
        // Output as 1D array
        std::vector<atlas::math::Vector> m_image;

        // Information about the view plane
        std::shared_ptr<ViewPlane> m_vp;

        // Tracing Raycaster
        std::shared_ptr<Tracer> m_tracer;

        // Dimensions of each slab
        unsigned int m_slab_size;
    };
}

#endif // !WORLD_HPP