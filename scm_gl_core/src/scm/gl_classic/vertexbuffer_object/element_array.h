
#ifndef SCM_OGL_ELEMENT_ARRAY_H_INCLUDED
#define SCM_OGL_ELEMENT_ARRAY_H_INCLUDED

#include <scm/gl_classic/buffer_object/buffer_object.h>

#include <scm/core/platform/platform.h>

namespace scm {
namespace gl_classic {

class __scm_export(gl_core) element_array : public buffer_object
{
public:
    element_array();
    virtual ~element_array();

}; // class element_array

} // namespace gl_classic
} // namespace scm

#endif // SCM_OGL_ELEMENT_ARRAY_H_INCLUDED
