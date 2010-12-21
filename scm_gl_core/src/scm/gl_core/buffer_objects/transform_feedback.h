
#ifndef SCM_GL_CORE_TRANSFORM_FEEDBACK_H_INCLUDED
#define SCM_GL_CORE_TRANSFORM_FEEDBACK_H_INCLUDED

#include <utility>
#include <vector>

#include <scm/core/numeric_types.h>
#include <scm/core/pointer_types.h>

#include <scm/gl_core/constants.h>
#include <scm/gl_core/gl_core_fwd.h>
#include <scm/gl_core/render_device/context_bindable_object.h>
#include <scm/gl_core/render_device/device_child.h>

#include <scm/core/platform/platform.h>
#include <scm/core/utilities/platform_warning_disable.h>

namespace scm {
namespace gl {

class __scm_export(gl_core) stream_output_setup
{
public:
    typedef std::pair<buffer_ptr, size_t>   element;
    typedef std::vector<element>            element_array;

public:
    stream_output_setup(const element_array& in_elements);
    stream_output_setup(const element& in_element);
    stream_output_setup(const buffer_ptr& out_buffer, const size_t out_buffer_offset = 0);

    /*virtual*/ ~stream_output_setup();

    stream_output_setup&    operator()(const element& in_element);
    stream_output_setup&    operator()(const buffer_ptr& out_buffer, const size_t out_buffer_offset = 0);

    const element&          operator[](const size_t i) const;
    const element_array&    elements() const;

    bool                    operator==(const stream_output_setup& rhs) const;
    bool                    operator!=(const stream_output_setup& rhs) const;

protected:
    element_array           _elements;

}; // class stream_output_setup

class __scm_export(gl_core) transform_feedback : public context_bindable_object, public render_device_child
{
public:
    virtual ~transform_feedback();

    const buffer_ptr&           stream_out_buffer(const size_t i) const;
    const buffer_ptr&           operator[](const size_t i) const;
    const stream_output_setup&  stream_out_setup() const;

protected:
    transform_feedback(      render_device&         in_device,
                       const stream_output_setup&   in_vert_format);

    void                        bind(render_context& in_context) const;
    void                        unbind(render_context& in_context) const;

    bool                        initialize_transform_feedback_object(const render_device& in_device);
    void                        bind_stream_out_buffers(render_context& in_context) const;
    void                        unbind_stream_out_buffers(render_context& in_context) const;

protected:
    stream_output_setup         _stream_out_setup;

    friend class scm::gl::render_device;
    friend class scm::gl::render_context;

}; // class transform_feedback

} // namespace gl
} // namespace scm

#include <scm/core/utilities/platform_warning_enable.h>

#endif // SCM_GL_CORE_TRANSFORM_FEEDBACK_H_INCLUDED
