/**
 *  @file oglplus/program_pipeline.hpp
 *  @brief ProgramPipeline object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PROGRAM_PIPELINE_1107121519_HPP
#define OGLPLUS_PROGRAM_PIPELINE_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/program.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/auxiliary/bitfield.hpp>
#include <oglplus/auxiliary/prog_pl_stages.hpp>

#include <cassert>

namespace oglplus {

// if program-pipeline is available
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects

/// ProgramPipeline operations wrapper class
/** This class implements OpenGL program pipeline operations.
 *  @note Do not use this class directly, use @c ProgramPipeline instead.
 *
 *  @see ProgramPipeline
 *
 *  @glsymbols
 *  @glfunref{GenProgramPipelines}
 *  @glfunref{DeleteProgramPipelines}
 *  @glfunref{IsProgramPipeline}
 */
class ProgramPipelineOps
 : public Named
 , public FriendOf<ProgramOps>
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		OGLPLUS_GLFUNC(GenProgramPipelines)(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenProgramPipelines));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(DeleteProgramPipelines)(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsProgramPipeline)(_name);
	}

	friend class FriendOf<ProgramPipelineOps>;
public:
	GLint GetIntParam(GLenum query) const
	{
		GLint result;
		OGLPLUS_GLFUNC(GetProgramPipelineiv)(_name, query, &result);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramPipelineiv,
			ProgramPipeline,
			_name
		));
		return result;
	}

	/// Bind this program pipeline
	/**
	 *  @glsymbols
	 *  @glfunref{BindProgramPipeline}
	 */
	void Bind(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindProgramPipeline)(_name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}

	/// Unbinds the current program pipeline object (if any)
	/**
	 *  @glsymbols
	 *  @glfunref{BindProgramPipeline}
	 */
	static void Unbind(void)
	{
		OGLPLUS_GLFUNC(BindProgramPipeline)(0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindProgramPipeline));
	}

	/// Program pipeline stage enumeration
	enum class Stage : GLbitfield {
#include <oglplus/enums/program_pipeline_stage.ipp>
	};

	/// Specifies program stages by calling functions of the returned object
	/** This function returns an object that allows to specify which stages
	 *  of @p program should by used when this pipeline is active by calling
	 *  the Vertex(), TessControl(), TessEvaluation(), Geometry(), Fragment()
	 *  and All() member functions of the object returned by UseStages.
	 *
	 *  example:
	 *  @code
	 *  Program prog;
	 *  ProgramPipeline pp;
	 *  ...
	 *  pp.UseStages(prog).Vertex();
	 *  pp.UseStages(prog).Vertex().Geometry();
	 *  pp.UseStages(prog).Vertex().TessControl().TessEvaluation().Geometry();
	 *  pp.UseStages(prog).Vertex().Geometry().Fragment();
	 *  pp.UseStages(prog).Geometry();
	 *  pp.UseStages(prog).All();
	 *  @endcode
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{UseProgramStages}
	 */
	aux::ProgPLUseStages UseStages(const ProgramOps& program) const
	{
		assert(_name != 0);
		return aux::ProgPLUseStages(
			_name,
			FriendOf<ProgramOps>::GetName(program),
			0
		);
	}

	/// Use the specified @p stages of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgramStages}
	 */
	void UseStages(
		std::initializer_list<Stage> stages,
		const ProgramOps& program
	) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(UseProgramStages)(
			_name,
			aux::MakeBitfield(stages),
			FriendOf<ProgramOps>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UseProgramStages));
	}

#if defined GL_ALL_SHADER_BITS
	/// Use all stages of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{UseProgramStages}
	 */
	void UseAllStages(const ProgramOps& program) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(UseProgramStages)(
			_name,
			GL_ALL_SHADER_BITS,
			FriendOf<ProgramOps>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UseProgramStages));
	}
#endif

	/// Returns the validation process output
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 *  @glfunref{GetProgramPipelineInfoLog}
	 */
	String GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, OGLPLUS_GLFUNC(GetProgramPipelineiv),
			OGLPLUS_GLFUNC(GetProgramPipelineInfoLog),
			"GetProgramPipelineiv",
			"GetProgramPipelineInfoLog"
		);
	}

	/// Returns true if the pipeline is validated, false otherwise
	/**
	 *  @see Validate
	 *
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 */
	bool IsValid(void) const
	{
		return GetIntParam(GL_VALIDATE_STATUS) == GL_TRUE;
	}

	/// Validates this program pipeline
	/**
	 *  @throws Error ValidationError
	 *  @see Link
	 *
	 *  @glsymbols
	 *  @glfunref{ValidateProgramPipeline}
	 */
	void Validate(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ValidateProgramPipeline)(_name);
		ThrowOnError(OGLPLUS_OBJECT_ERROR_INFO(
			ValidateProgramPipeline,
			ProgramPipeline,
			_name
		));
		if(!IsValid())
			throw ValidationError(
				GetInfoLog(),
				OGLPLUS_OBJECT_ERROR_INFO(
					ValidateProgramPipeline,
					ProgramPipeline,
					_name
				)
			);
	}

	/// Make the @p program active for this program pipeline
	/**
	 *  @glsymbols
	 *  @glfunref{ActiveShaderProgram}
	 */
	void ActiveShaderProgram(const ProgramOps& program) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ActiveShaderProgram)(
			_name,
			FriendOf<ProgramOps>::GetName(program)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ActiveShaderProgram));
	}

	/// Returns the current active shader program
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 *  @gldefref{ACTIVE_PROGRAM}
	 */
	Managed<ProgramOps> ActiveShaderProgram(void) const
	{
		return Managed<ProgramOps>(GetIntParam(GL_ACTIVE_PROGRAM));
	}

	/// Returns true if this pipeline contains a shader of a particular kind
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 */
	bool HasShader(Shader::Kind shader_kind) const
	{
		return GetIntParam(GLenum(shader_kind)) != 0;
	}

	/// Returns the program from which the @p shader_kind is used
	/**
	 *  @glsymbols
	 *  @glfunref{GetProgramPipeline}
	 */
	Managed<ProgramOps> ShaderProgram(Shader::Kind shader_kind) const
	{
		return Managed<ProgramOps>(GetIntParam(GLenum(shader_kind)));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating  OpenGL program pipeline functionality
/**
 *  @ingroup objects
 */
class ProgramPipeline
 : public ProgramPipelineOps
{ };
#else
typedef Object<ProgramPipelineOps, true> ProgramPipeline;
#endif

#endif // program pipeline

} // namespace oglplus

#endif // include guard
