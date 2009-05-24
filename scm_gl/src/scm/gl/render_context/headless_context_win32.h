
#ifndef SCM_GL_HEADLESS_CONTEXT_WIN32_H_INCLUDED
#define SCM_GL_HEADLESS_CONTEXT_WIN32_H_INCLUDED

#include <scm/gl/render_context/headless_context.h>

#include <scm/core/platform/platform.h>
#include <scm/core/utilities/platform_warning_disable.h>

namespace scm {
namespace gl {

class __scm_export(ogl) headless_context_win32 : public headless_context
{
public:
    headless_context_win32();
    virtual ~headless_context_win32();

    bool            setup(const context_format& desc,
                          const window_context& partent_ctx);
    void            cleanup();

    bool            make_current(bool current = true) const;

protected:
    handle          _pbuffer;

};

} // namespace gl
} // namespace scm

#include <scm/core/utilities/platform_warning_enable.h>

#endif // SCM_GL_HEADLESS_CONTEXT_WIN32_H_INCLUDED
