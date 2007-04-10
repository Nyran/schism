
#ifndef SCRIPT_SYSTEM_LUA_H_INCLUDED
#define SCRIPT_SYSTEM_LUA_H_INCLUDED


extern "C"
{
    #include <lua.h>
}

#include <scm_core/platform/platform.h>
#include <scm_core/script/script_system.h>

namespace scm
{
    namespace core
    {
        namespace detail
        {
            class __scm_export script_system_lua : public scm::core::script_system_interface
            {
            public:
        	    script_system_lua();
        	    virtual ~script_system_lua();
                    
                bool                            initialize();
                bool                            shutdown();

            protected:
                script_result_t                 process_script  (std::istream& in_stream,
                                                                 const std::string& input_source_name);
                script_result_t                 process_script  (const std::string& in_string,
                                                                 const std::string& input_source_name);

                script_result_t                 int_process_script(lua_Reader input_reader,
                                                                   void *in_data,
                                                                   const std::string& input_source_name);


            private:
                lua_State*                      _l_state;

                const std::string               _l_incomplete_input_msg;

            }; // class script_system_lua

        } // namespace detail
    } // namespace core
} // namespace scm

#endif // namespace SCRIPT_SYSTEM_LUA_H_INCLUDED