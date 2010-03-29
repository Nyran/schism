
#include "render_device_resource.h"

#include <scm/gl_core/render_device.h>

namespace scm {
namespace gl {

render_device_resource::render_device_resource(render_device& dev)
  : render_device_child(dev)
{
}

render_device_resource::~render_device_resource()
{
}

} // namespace gl
} // namespace scm
