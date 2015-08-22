/**
 *  @file oglplus/texgen/newton_node.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_NEWTON_NODE_HPP
#define OGLPLUS_TEXGEN_NEWTON_NODE_HPP

#include <oglplus/texgen/base_node.hpp>
#include <oglplus/texgen/sibling_input.hpp>
#include <oglplus/texgen/constant_output.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <iosfwd>

namespace oglplus {
namespace texgen {

class NewtonNode;

enum class NewtonFunction
{
	Xe3minus1,
	Xe4minus1
};

class NewtonOutputSlot
 : public BaseOutputSlot
{
private:
	friend class NewtonNode;

	FallbackInputSlot<GlobalCoordinateSlot, true> _coord;
	FallbackInputSlot<ConstantOutputSlot<Vec3f>> _offset;
	FallbackInputSlot<ConstantOutputSlot<Vec3f>> _scale;

	NewtonFunction _function;
public:
	NewtonOutputSlot(Node& parent, NewtonFunction function);

	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE;

	std::ostream& Definitions(std::ostream&, CompileContext&)
	OGLPLUS_OVERRIDE;
};

class NewtonNode
 : public SingleBaseOutputNode
{
private:
	NewtonOutputSlot _output;

public:
	NewtonNode(NewtonFunction function);

	std::size_t InputCount(void)
	OGLPLUS_OVERRIDE;

	InputSlot& Input(std::size_t i)
	OGLPLUS_OVERRIDE;

	BaseOutputSlot& SingleOutput(void)
	OGLPLUS_OVERRIDE;
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/newton_node.ipp>
//#endif

#endif // include guard