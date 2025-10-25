#include <print>

#define UNK_ENABLE_PRINT_MACROS 1
#define UNK_ENABLE_ASSERT 1
#define UNK_ENABLE_FILE_CHECK 1

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    LOGGING    ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

#if UNK_ENABLE_PRINT_MACROS
#define UNK_CORE_LOG(formatedMessage, ...)\
        std::print("core log: ")\
        std::print(formatedMessage, __VA_ARGS__)\
        std::print("\n");
#define UNK_CORE_WARN(formatedMessage, ...)\
        std::print("core warn: ");\
        std::print(formatedMessage, __VA_ARGS__);\
        std::print("\n");
#define UNK_CORE_ERROR(formatedMessage, ...)\
        std::print("core error: ")\
        std::print(formatedMessage, __VA_ARGS__);\
        std::print("\n");
#define UNK_CORE_FATAL(formatedMessage, ...)\
        std::print("core fatal: ")\
        std::print(formatedMessage, __VA_ARGS__);\
        std::print("\n");

#define UNK_CLIENT_LOG(formatedMessage, ...)\
        std::print("client log: ")\
        std::print(formatedMessage, __VA_ARGS__);\
        std::print("\n");
#define UNK_CLIENT_WARN(formatedMessage, ...)\
        std::print("client warn: ");\
        std::print(formatedMessage, __VA_ARGS__);\
        std::print("\n");
#define UNK_CLIENT_ERROR(formatedMessage, ...)\
        std::print("client error: ")\
        std::print(formatedMessage, __VA_ARGS__);\
        std::print("\n");
#define UNK_CLIENT_FATAL(formatedMessage, ...)\
        std::print("client fatal: ")\
        std::print(formatedMessage, __VA_ARGS__);\
        std::print("\n");
#else
#define UNK_CORE_LOG(formatedMessage, ...)
#define UNK_CORE_WARN(formatedMessage, ...)
#define UNK_CORE_ERROR(formatedMessage, ...)
#define UNK_CORE_FATAL(formatedMessage, ...)

#define UNK_CLIENT_LOG(formatedMessage, ...)
#define UNK_CLIENT_WARN(formatedMessage, ...)
#define UNK_CLIENT_ERROR(formatedMessage, ...)
#define UNK_CLIENT_FATAL(formatedMessage, ...)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    ASSERTION    /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

#if UNK_ENABLE_ASSERT
#define UNK_CORE_ASSERT(message, expression)\
        if ((expression) == false)\
        {\
            std::println("core assert: {} {}", message, #expression);\
            assert(false);\
        }


#define UNK_CLIENT_ASSERT(message, expression)\
        if ((expression) == false)\
        {\
            std::println("client assert: {} {}", message, #expression);\
            assert(false);\
        }
#else
#define UNK_CORE_ASSERT(message, expression)
#define UNK_CLIENT_ASSERT(message, expression)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    FILE CHECK    ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

#if UNK_ENABLE_FILE_CHECK

#define UNK_CORE_CHECK_FILE_EXIST(filename) \
        if (!std::filesystem::exists(filname))\
        {\
	        std::println("core error: file not found {}", filename);\
        }

#define UNK_CLIENT_CHECK_FILE_EXIST(filename) \
        if (!std::filesystem::exists(filname))\
        {\
	        std::println("client error: file not found {}", filename);\
        }
#else
#define UNK_CORE_CHECK_FILE_EXIST(filename)
#define UNK_CLIENT_CHECK_FILE_EXIST(filename) 
#endif

// helpful for printing 

#define UNK_EXPAND_VEC2(vec) vec.x, vec.y
#define UNK_EXPAND_VEC3(vec) vec.x, vec.y, vec.z
#define UNK_EXPAND_VEC4(vec) vec.x, vec.y, vec.z, vec.w
