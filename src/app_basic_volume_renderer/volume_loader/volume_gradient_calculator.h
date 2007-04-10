
#ifndef VOLUME_GRADIENT_CALCULATOR_H_INCLUDED
#define VOLUME_GRADIENT_CALCULATOR_H_INCLUDED

template<typename output_voxel_component_type, typename input_data_type>
class volume_gradient_calculator
{
public:
    bool generate_gradients(unsigned int width,
                            unsigned int height,
                            unsigned int depth,
                            const input_data_type*const src_data,
                            output_voxel_component_type*const dst_buffer);


protected:

private:
    unsigned int _width;
    unsigned int _height;
    unsigned int _depth;

    unsigned int   get_offset_clamp_to_edge( int x,
                                             int y,
                                             int z);
    unsigned int   get_output_offset( unsigned int x,
                                      unsigned int y,
                                      unsigned int z);
};

#include "volume_gradient_calculator.inl"

#endif // VOLUME_GRADIENT_CALCULATOR_H_INCLUDED