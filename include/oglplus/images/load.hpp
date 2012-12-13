/**
 *  @file oglplus/images/load.hpp
 *  @brief Image loader which finds and loads an image from its name
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_LOAD_1107121519_HPP
#define OGLPLUS_IMAGES_LOAD_1107121519_HPP

#include <oglplus/opt/application.hpp>
#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/images/png.hpp>

#include <string>
#include <fstream>
#include <stdexcept>

namespace oglplus {
namespace images {
namespace aux {

inline bool FindImageWithExts(
	std::ifstream& file,
	const std::string& path,
	const char** exts,
	unsigned& e,
	unsigned nexts
)
{
	for(e=0; e!= nexts; ++e)
	{
		file.open(path + exts[e], std::ios::binary);
		if(file.good()) return true;
	}
	return false;
}

inline bool FindImage(
	std::ifstream& file,
	std::string dirname,
	std::string name,
	const char** exts,
	unsigned& e,
	unsigned nexts
)
{
#if defined(WIN32) || defined(WIN64)
	const std::string dirsep("\\");
#else
	const std::string dirsep("/");
#endif
	const std::string pardir(".." + dirsep);
	const std::string path = dirname+dirsep+name;
	const std::string apppath = Application::RelativePath();
	std::string prefix;

	for(unsigned i=0; i!=3; ++i)
	{
		if(FindImageWithExts(file, apppath+prefix+path, exts, e, nexts))
			return true;
		prefix = pardir + prefix;
	}
	if(FindImageWithExts(file, apppath+name, exts, e, nexts))
		return true;
	return false;
}

} // namespace aux

inline Image<GLubyte> LoadByName(
	std::string dirname,
	std::string name,
	bool y_is_up,
	bool x_is_right
)
{
	std::ifstream file;
	const char* exts[] = {".png"};
	unsigned nexts = sizeof(exts)/sizeof(exts[0]);
	unsigned iext = nexts;
	aux::FindImage(file, dirname, name, exts, iext, nexts);

	if(!file.good())
		throw std::runtime_error("Unable to open image: "+name);
	// TODO switch on extension
	assert(iext == 0);
	return PNG(file, y_is_up, x_is_right);
}

/// Helper function for loading textures that come with @OGLplus in the examples
inline Image<GLubyte> LoadTexture(
	std::string name,
	bool y_is_up = true,
	bool x_is_right = true
)
{
	return LoadByName("textures", name, y_is_up, x_is_right);
}

} // images
} // oglplus

#endif // include guard
