/*
 *  .file oglplus/enums/tess_gen_primitive_spacing_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/tess_gen_primitive_spacing.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	TessGenPrimitiveSpacing
> EnumValueRange(TessGenPrimitiveSpacing*)
OGLPLUS_NOEXCEPT(true)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVR_TESSGENPRIMITIVESPACING)
#define OGLPLUS_IMPL_EVR_TESSGENPRIMITIVESPACING
{
static const GLenum _values[] = {
#if defined GL_FRACTIONAL_EVEN
GL_FRACTIONAL_EVEN,
#endif
#if defined GL_FRACTIONAL_ODD
GL_FRACTIONAL_ODD,
#endif
#if defined GL_EQUAL
GL_EQUAL,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	TessGenPrimitiveSpacing
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif

