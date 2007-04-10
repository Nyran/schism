
#ifndef PROGRAM_OBJECT_H_INCLUDED
#define PROGRAM_OBJECT_H_INCLUDED

#include <string>

namespace gl
{

    class shader_object;

    class program_object
    {
    public:
        explicit program_object();
        virtual ~program_object();

        bool                attach_shader(const gl::shader_object&);
        bool                link();
        bool                validate();
        void                bind() const;
        void                unbind() const;

        const std::string&  get_linker_output() const { return (_linker_out); }
        const std::string&  get_valitation_output() const { return (_validate_out); }

        void                set_uniform_1f(const std::string&, float) const;
        void                set_uniform_2f(const std::string&, float, float) const;
        void                set_uniform_3f(const std::string&, float, float, float) const;
        void                set_uniform_4f(const std::string&, float, float, float, float) const;

        void                set_uniform_1fv(const std::string&, unsigned int, const float*) const;
        void                set_uniform_2fv(const std::string&, unsigned int, const float*) const;
        void                set_uniform_3fv(const std::string&, unsigned int, const float*) const;
        void                set_uniform_4fv(const std::string&, unsigned int, const float*) const;

        void                set_uniform_1i(const std::string&, int) const;
        void                set_uniform_2i(const std::string&, int, int) const;
        void                set_uniform_3i(const std::string&, int, int, int) const;
        void                set_uniform_4i(const std::string&, int, int, int, int) const;

        void                set_uniform_1iv(const std::string&, unsigned int, const int*) const;
        void                set_uniform_2iv(const std::string&, unsigned int, const int*) const;
        void                set_uniform_3iv(const std::string&, unsigned int, const int*) const;
        void                set_uniform_4iv(const std::string&, unsigned int, const int*) const;

        void                set_uniform_matrix_2fv(const std::string&, unsigned int, bool, const float*) const;
        void                set_uniform_matrix_3fv(const std::string&, unsigned int, bool, const float*) const;
        void                set_uniform_matrix_4fv(const std::string&, unsigned int, bool, const float*) const;

    protected:
    private:
        int                 get_uniform_location(const std::string&) const;

        unsigned int        _prog;
        std::string         _linker_out;
        std::string         _validate_out;
    };

} // namespace gl

#endif // PROGRAM_OBJECT_H_INCLUDED

