
#ifndef SCM_GL_CORE_SHADER_H_INCLUDED
#define SCM_GL_CORE_SHADER_H_INCLUDED

#include <string>

#include <scm/core/numeric_types.h>
#include <scm/core/pointer_types.h>

#include <scm/gl_core/constants.h>
#include <scm/gl_core/gl_core_fwd.h>
#include <scm/gl_core/render_device/device_child.h>

#include <scm/core/platform/platform.h>
#include <scm/core/utilities/platform_warning_disable.h>

namespace scm {
namespace gl {

class __scm_export(gl_core) shader : public render_device_child
{
public:
    virtual ~shader();

    shader_stage        type() const;
    const std::string&  info_log() const;

protected:
    shader(render_device&       ren_dev,
           shader_stage         in_type,
           const std::string&   in_src);

    bool   compile_source_string(      render_device&  ren_dev,
                                 const std::string&    in_src);

protected:
    shader_stage    _type;
    unsigned        _gl_shader_obj;
    std::string     _info_log;

    friend class scm::gl::program;
    friend class scm::gl::render_device;
    friend class scm::gl::render_context;
}; // class shader

} // namespace gl
} // namespace scm

#include <scm/core/utilities/platform_warning_enable.h>

#endif // SCM_GL_CORE_SHADER_H_INCLUDED
