
#include "quad.h"

#include <cassert>

#include <boost/assign/list_of.hpp>

#include <scm/core/pointer_types.h>

#include <scm/gl_core/render_device/device.h>
#include <scm/gl_core/buffer_objects/buffer.h>
#include <scm/gl_core/render_device/context.h>
#include <scm/gl_core/buffer_objects/vertex_array.h>
#include <scm/gl_core/buffer_objects/vertex_format.h>

namespace scm {
namespace gl {

quad_geometry::quad_geometry(const render_device_ptr& in_device,
                             const math::vec2f& in_min_vertex,
                             const math::vec2f& in_max_vertex)
  : geometry(in_device),
    _min_vertex(in_min_vertex),
    _max_vertex(in_max_vertex)
{
    using namespace scm::math;

    int num_vertices            = 4;

    struct vertex {
        vec3f pos;
        vec2f tex;
    };

    scoped_array<vertex>            vert(new vertex[num_vertices]);
    scoped_array<unsigned short>    ind_s(new unsigned short[4]);

    _vertices = in_device->create_buffer(BIND_VERTEX_BUFFER, USAGE_STREAM_DRAW, num_vertices * sizeof(vertex), 0);

    render_context_ptr ctx = in_device->main_context();
    vertex* data = static_cast<vertex*>(ctx->map_buffer(_vertices, ACCESS_WRITE_INVALIDATE_BUFFER));
     
    const vec2f& o = in_min_vertex;
    const vec2f& l = in_max_vertex;

    data[0].pos = vec3f(o.x, o.y, 0.0f); data[0].tex = vec2f(0.0f, 0.0f);
    data[1].pos = vec3f(l.x, o.y, 0.0f); data[1].tex = vec2f(1.0f, 0.0f);
    data[2].pos = vec3f(o.x, l.y, 0.0f); data[2].tex = vec2f(0.0f, 1.0f);
    data[3].pos = vec3f(l.x, l.y, 0.0f); data[3].tex = vec2f(1.0f, 1.0f);
    
    ctx->unmap_buffer(_vertices);

    // wire indices
    ind_s[0]  =  0;
    ind_s[1]  =  1;
    ind_s[2]  =  2;
    ind_s[3]  =  3;

    using namespace scm::gl;
    using boost::assign::list_of;

    _solid_indices = in_device->create_buffer(BIND_INDEX_BUFFER, USAGE_STATIC_DRAW, num_vertices * sizeof(unsigned short), ind_s.get());

    _vertex_array = in_device->create_vertex_array(vertex_format(0, 0, TYPE_VEC3F, sizeof(vertex))
                                                                (0, 2, TYPE_VEC2F, sizeof(vertex)),
                                                   list_of(_vertices));
}

quad_geometry::~quad_geometry()
{
    _vertex_array.reset();
    _solid_indices.reset();
    _vertices.reset();
}

void
quad_geometry::draw(const render_context_ptr& in_context,
                    const draw_mode in_draw_mode) const
{
    in_context->bind_vertex_array(_vertex_array);
    in_context->bind_index_buffer(_solid_indices, PRIMITIVE_TRIANGLE_STRIP, TYPE_USHORT);
    in_context->apply();

    in_context->draw_elements(4);
}

} // namespace gl
} // namespace scm