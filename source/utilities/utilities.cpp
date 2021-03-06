#include <iostream>
#include "utilities/utilities.hpp"
#include "stb_image_write.h"
#include "structures/world.hpp"

using namespace atlas;
using Colour = math::Vector;

namespace poly::utils
{
	BMP_info::BMP_info() :
		m_total_height{},
		m_total_width{},
		m_start_height{},
		m_start_width{},
		m_end_height{},
		m_end_width{},
		m_image{}
	{}

	void saveToBMP(nlohmann::json const& json,
				   poly::utils::BMP_info const& info)
	{
		std::string filename;
		try {
			filename = std::string(json["output_file"]);
		}
		catch (...) {
			std::clog
				<< "INFO: no output name specified, using default: 'output.bmp'"
				<< std::endl;
			filename = std::string("output.bmp");
		}

		saveToBMP(filename, info);
	}
	/**
	 * Saves a BMP image file based on the given array of pixels. All pixel
	 * values have to be in the range [0, 1].
	 *
	 * @param filename The name of the file to save to.
	 * @param width The width of the image.
	 * @param height The height of the image.
	 * @param image The array of pixels representing the image.
	 */
	void saveToBMP(std::string const& filename,
				   poly::utils::BMP_info const& info)
	{
		std::clog << "INFO: writing data to " << filename << std::endl;
		std::vector<unsigned char> data(info.m_image.size() * 3);
		int width  = info.m_total_width;
		int height = info.m_total_height;

		for (int i{height - info.m_end_height}, k{0};
			 i < height - info.m_start_height;
			 ++i) {
			for (int j{info.m_start_width}; j < info.m_end_width; ++j, k += 3) {
				Colour pixel = info.m_image[(i * width) + j];
				data[k + 0]	 = static_cast<unsigned char>(pixel.r * 255);
				data[k + 1]	 = static_cast<unsigned char>(pixel.g * 255);
				data[k + 2]	 = static_cast<unsigned char>(pixel.b * 255);
			}
		}

		stbi_write_bmp(
			filename.c_str(),
			static_cast<int>(info.m_end_width - info.m_start_width),
			static_cast<int>(info.m_end_height - info.m_start_height),
			3,
			data.data());
	}

	Colour random_colour_generate()
	{
		unsigned int granularity = 256;
		Colour colour;
		colour.x = (rand() % granularity) / (float)granularity;
		colour.y = (rand() % granularity) / (float)granularity;
		colour.z = (rand() % granularity) / (float)granularity;
		return colour;
	}

	Colour colour_validate(Colour const& colour)
	{
		if (colour.x > 1.0f || colour.y > 1.0f || colour.z > 1.0f ||
			colour.x < 0.0f || colour.y < 0.0f || colour.z < 0.0f) {
			// Out of gamut turns RED
			return Colour(1.0f, 0.0f, 0.0f);
		}
		else {
			return colour;
		}
	}

	Colour colour_average_max(Colour const& colour)
	{
		float max = std::max(colour.x, colour.y);
		max		  = std::max(max, colour.z);

		if (max > 1.0f) {
			return colour * (1 / max);
		}
		else {
			return colour;
		}
	}

	atlas::math::Vector reflect_over_normal(const math::Vector& wi,
											const atlas::math::Normal n)
	{
		float ndotwo = glm::dot(n, wi);
		return glm::normalize(-wi + (2.0f * n * ndotwo));
	}
} // namespace poly::utils
