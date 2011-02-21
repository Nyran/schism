
#ifndef SCM_GL_CORE_CONTEXT_H_INCLUDED
#define SCM_GL_CORE_CONTEXT_H_INCLUDED

#include <vector>
#include <utility>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <scm/core/math.h>
#include <scm/core/numeric_types.h>

#include <scm/gl_core/constants.h>
#include <scm/gl_core/data_types.h>
#include <scm/gl_core/data_formats.h>
#include <scm/gl_core/gl_core_fwd.h>
#include <scm/gl_core/frame_buffer_objects/viewport.h>
#include <scm/gl_core/render_device/device_child.h>

#include <scm/core/platform/platform.h>
#include <scm/core/utilities/platform_warning_disable.h>

namespace scm {
namespace gl {

namespace opengl {
class gl3_core;
} // namespace opengl

class __scm_export(gl_core) render_context : public render_device_child
{
////// types //////////////////////////////////////////////////////////////////////////////////////
public:
    struct index_buffer_binding {
        index_buffer_binding();
        bool                operator==(const index_buffer_binding& rhs) const; 
        bool                operator!=(const index_buffer_binding& rhs) const; 
        buffer_ptr          _index_buffer;
        primitive_topology  _primitive_topology;
        data_type           _index_data_type;
        scm::size_t         _index_data_offset;
    }; // struct index_buffer_binding
    struct texture_unit_binding {
        texture_ptr         _texture_image;
        sampler_state_ptr   _sampler_state;
    }; // struct texture_unit_binding
    struct image_unit_binding {
        image_unit_binding();
        bool                operator==(const image_unit_binding& rhs) const; 
        bool                operator!=(const image_unit_binding& rhs) const; 
        texture_ptr         _texture_image;
        data_format         _format;
        access_mode         _access;
        int                 _level;
        int                 _layer;
    }; // struct image_unit_binding
    struct buffer_binding {
        buffer_binding() : _offset(0), _size(0) {}
        bool                operator==(const buffer_binding& rhs) const; 
        bool                operator!=(const buffer_binding& rhs) const; 
        buffer_ptr          _buffer;
        scm::size_t         _offset;
        scm::size_t         _size;
    }; // struct uniform_buffer_binding
    typedef std::vector<texture_unit_binding>   texture_unit_array;
    typedef std::vector<image_unit_binding>     image_unit_array;
    typedef std::vector<buffer_binding>         buffer_binding_array;

private:
    struct binding_state_type {
        binding_state_type();
        // shader /////////////////////////////////////////////////////////////////////////////////
        program_ptr                         _program;
        // vertex specification ///////////////////////////////////////////////////////////////////
        vertex_array_ptr                    _vertex_array;
        index_buffer_binding                _index_buffer_binding;
        buffer_binding_array                _active_uniform_buffers;
        // state objects //////////////////////////////////////////////////////////////////////////
        // depth state
        depth_stencil_state_ptr             _depth_stencil_state;
        unsigned                            _stencil_ref_value;
        // rasterizer state
        rasterizer_state_ptr                _rasterizer_state;
        float                               _line_width;
        float                               _point_size;
        // blend state
        blend_state_ptr                     _blend_state;
        math::vec4f                         _blend_color;
        // texture units //////////////////////////////////////////////////////////////////////////
        texture_unit_array                  _texture_units;
        image_unit_array                    _image_units;
        // framebuffer control ////////////////////////////////////////////////////////////////////
        frame_buffer_ptr                    _draw_framebuffer;
        frame_buffer_ptr                    _read_framebuffer;
        frame_buffer_target                 _default_framebuffer_target;
        viewport_array                      _viewports;
    }; // struct binding_state_type

////// methods ////////////////////////////////////////////////////////////////////////////////////
public:
    virtual ~render_context();

    const opengl::gl3_core&     opengl_api() const;
    void                        apply();

    void                        reset();

    void                        flush();
    void                        sync();

    // debug api //////////////////////////////////////////////////////////////////////////////////
public:
    struct debug_output {
        virtual void operator()(debug_source, debug_type, debug_severity, const std::string&) const = 0;
    }; // struct debug_filter
    typedef shared_ptr<debug_output> debug_output_ptr;

    void                        register_debug_callback(const debug_output_ptr& f);
    void                        unregister_debug_callback(const debug_output_ptr& f);
    const std::string           retrieve_debug_log() const;
    void                        synchronous_reporting(bool e);
    bool                        synchronous_reporting() const;

protected:
    static void                 gl_debug_callback(unsigned src, unsigned type, unsigned id, unsigned severity,
                                                  int msg_length, const char* msg, void* user_param);
    void                        gl_debug_dispatch(unsigned src, unsigned type, unsigned severity, int msg_length, const char* msg);

    // buffer api /////////////////////////////////////////////////////////////////////////////////
public:
    void*                       map_buffer(const buffer_ptr& in_buffer, const access_mode in_access) const;
    void*                       map_buffer_range(const buffer_ptr& in_buffer, scm::size_t in_offset, scm::size_t in_size, const access_mode in_access) const;
    bool                        unmap_buffer(const buffer_ptr& in_buffer) const;
    bool                        orphane_buffer(const buffer_ptr& in_buffer) const;

    void                        bind_uniform_buffer(const buffer_ptr& in_buffer,
                                                    const unsigned    in_bind_point,
                                                    const scm::size_t in_offset = 0,
                                                    const scm::size_t in_size = 0);

    void                        set_uniform_buffers(const buffer_binding_array& in_buffers);
    const buffer_binding_array& current_uniform_buffers() const;

    void                        bind_unpack_buffer(const buffer_ptr& in_buffer);
    const buffer_ptr&           current_unpack_buffer() const;

    void                        reset_uniform_buffers();

    void                        bind_vertex_array(const vertex_array_ptr& in_vertex_array);
    const vertex_array_ptr&     current_vertex_array() const;

    void                        bind_index_buffer(const buffer_ptr& in_buffer, const primitive_topology in_topology, const data_type in_index_type, const scm::size_t in_offset = 0);
    void                        current_index_buffer(buffer_ptr& out_buffer, primitive_topology& out_topology, data_type& out_index_type, scm::size_t& out_offset) const;
    void                        set_index_buffer_binding(const index_buffer_binding& in_index_buffer_binding);
    const index_buffer_binding& current_index_buffer_binding() const;

    void                        reset_vertex_input();

    void                        begin_transform_feedback(const transform_feedback_ptr& in_transform_feedback, primitive_type in_topology_mode);
    void                        end_transform_feedback();
    const transform_feedback_ptr& active_transform_feedback() const;

    void                        draw_transform_feedback(const primitive_topology in_topology, const transform_feedback_ptr& in_transform_feedback, int stream = -1);

    void                        draw_arrays(const primitive_topology in_topology, const int in_first_index, const int in_count);
    void                        draw_elements(const int in_count, const int in_start_index = 0, const int in_base_vertex = 0);

protected:
    void                        pre_draw_setup();
    void                        post_draw_setup();

    void                        start_transform_feedback();

    void                        apply_vertex_input();
    void                        apply_uniform_buffer_bindings();

    // shader api /////////////////////////////////////////////////////////////////////////////////
public:
    void                        bind_program(const program_ptr& in_program);
    const program_ptr&          current_program() const;

    void                        reset_program();

protected:
    void                        apply_program();

protected:

    // texture api ////////////////////////////////////////////////////////////////////////////////
public:
    void                        bind_texture(const texture_ptr&       in_texture_image,
                                             const sampler_state_ptr& in_sampler_state,
                                             const unsigned           in_unit);
    void                        set_texture_unit_state(const texture_unit_array& in_texture_units);
    const texture_unit_array&   current_texture_unit_state() const;
    void                        reset_texture_units();

    void                        bind_image(const texture_ptr&       in_texture_image,
                                                 data_format        in_format,
                                                 access_mode        in_access,
                                                 unsigned           in_unit,
                                                 int                in_level = 0,
                                                 int                in_layer = -1);
    void                        set_image_unit_state(const image_unit_array& in_imageunits);
    const image_unit_array&     current_image_unit_state() const;
    void                        reset_image_units();

    bool                        update_sub_texture(const texture_image_ptr& in_texture,
                                                   const texture_region&    in_region,
                                                   const unsigned           in_level,
                                                   const data_format        in_data_format,
                                                   const size_t             in_offset);
    bool                        update_sub_texture(const texture_image_ptr& in_texture,
                                                   const texture_region&    in_region,
                                                   const unsigned           in_level,
                                                   const data_format        in_data_format,
                                                   const void*const         in_data);

protected:
    void                        apply_texture_units();
    void                        apply_image_units();

    // frame buffer api ///////////////////////////////////////////////////////////////////////////
public:
    void                        set_frame_buffer(const frame_buffer_ptr& in_frame_buffer);
    void                        set_default_frame_buffer(const frame_buffer_target in_target = FRAMEBUFFER_BACK);
    const frame_buffer_ptr&     current_frame_buffer() const;
    const frame_buffer_target   current_default_frame_buffer_target() const;

    void                        set_viewport(const viewport& in_vp);
    void                        set_viewports(const viewport_array& in_vp);
    const viewport_array&       current_viewports() const;

    void                        reset_framebuffer();

    void                        clear_color_buffer(const frame_buffer_ptr& in_frame_buffer,
                                                   const unsigned          in_buffer,
                                                   const math::vec4f&      in_clear_color   = math::vec4f(0.0f)) const;
    void                        clear_color_buffer(const frame_buffer_ptr& in_frame_buffer,
                                                   const unsigned          in_buffer,
                                                   const math::vec4i&      in_clear_color   = math::vec4i(0)) const;
    void                        clear_color_buffer(const frame_buffer_ptr& in_frame_buffer,
                                                   const unsigned          in_buffer,
                                                   const math::vec4ui&     in_clear_color   = math::vec4ui(0u)) const;
    void                        clear_color_buffers(const frame_buffer_ptr& in_frame_buffer,
                                                    const math::vec4f&      in_clear_color   = math::vec4f(0.0f)) const;
    void                        clear_depth_stencil_buffer(const frame_buffer_ptr& in_frame_buffer,
                                                           const float             in_clear_depth = 1.0f,
                                                           const int               in_clear_stencil = 0) const;
    void                        clear_default_color_buffer(const frame_buffer_target in_target = FRAMEBUFFER_BACK,
                                                           const math::vec4f&        in_clear_color   = math::vec4f(0.0f)) const;
    void                        clear_default_depth_stencil_buffer(const float            in_clear_depth = 1.0f,
                                                                   const int              in_clear_stencil = 0) const;

    void                        resolve_multi_sample_buffer(const frame_buffer_ptr& in_read_buffer,
                                                            const frame_buffer_ptr& in_draw_buffer) const;
    void                        generate_mipmaps(const texture_image_ptr& in_texture) const;

    void                        capture_color_buffer(const frame_buffer_ptr& in_frame_buffer,
                                                     const unsigned          in_buffer,
                                                     const texture_region&   in_region,
                                                     const data_format       in_data_format,
                                                     const buffer_ptr&       in_target_buffer,
                                                     const size_t            in_offset = 0);

protected:
    void                        apply_frame_buffer();


    // state api //////////////////////////////////////////////////////////////////////////////////
public:
    // depth stencil state
    void                            set_depth_stencil_state(const depth_stencil_state_ptr& in_ds_state, unsigned in_stencil_ref = 0);
    const depth_stencil_state_ptr&  current_depth_stencil_state() const;
    unsigned                        current_stencil_ref_value() const;

    // rasterizer state
    void                            set_rasterizer_state(const rasterizer_state_ptr& in_rs_state, float in_line_width = 1.0f, float in_point_size = 1.0f);
    const rasterizer_state_ptr&     current_rasterizer_state() const;
    float                           current_line_width() const;
    float                           current_point_size() const;

    // blend state
    void                            set_blend_state(const blend_state_ptr& in_bl_state, const math::vec4f& in_blend_color = math::vec4f(1.0f, 1.0f, 1.0f, 1.0f));
    const blend_state_ptr&          current_blend_state() const;
    const math::vec4f&              current_blend_color() const;

    void                            reset_state_objects();

protected:
    void                            apply_state_objects();
     
    // active queries /////////////////////////////////////////////////////////////////////////
public:
    void                            begin_query(const query_ptr& in_query);
    void                            end_query(const query_ptr& in_query);
    void                            collect_query_results(const query_ptr& in_query);

protected:
    render_context(render_device& in_device);

private:
    const opengl::gl3_core&     _opengl_api_core;

    binding_state_type          _current_state;
    binding_state_type          _applied_state;

    buffer_ptr                  _unpack_buffer;

    boost::unordered_set<debug_output_ptr>      _debug_outputs;
    bool                                        _debug_synchronous_reporting;

    typedef std::pair<unsigned, int>                    indexed_query_id;
    boost::unordered_map<indexed_query_id, query_ptr>   _active_queries;

    transform_feedback_ptr                      _active_transform_feedback;
    primitive_type                              _active_transform_feedback_topology_mode;

    // defaults
    // TODO
    //program_ptr                 _default_program;
    depth_stencil_state_ptr     _default_depth_stencil_state;
    rasterizer_state_ptr        _default_rasterizer_state;
    blend_state_ptr             _default_blend_state;

    friend class render_device;    
}; // class render_context

} // namespace gl
} // namespace scm

#include <scm/core/utilities/platform_warning_enable.h>

#endif // SCM_GL_CORE_CONTEXT_H_INCLUDED
