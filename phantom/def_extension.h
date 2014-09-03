#ifndef o_phantom_extension_h__
#define o_phantom_extension_h__

o_namespace_begin(phantom)

template<typename t_Target, typename t_Source>
inline t_Target lexical_cast(const t_Source &arg)
{
    return boost::lexical_cast<t_Target>(arg);
}

// float
template<>
inline float lexical_cast<float, phantom::string>(const phantom::string& arg)
{
    static float zero = 0.f;
    if(arg == "-1.#IND") return -zero/zero;
    else if(arg == "1.#IND") return zero/zero;
    else if(arg == "-1.#INF") return -1.f/zero;
    else if(arg == "1.#INF") return 1.f/zero;
    else return boost::lexical_cast<float>(arg);
}

// double
template<>
inline double lexical_cast<double, phantom::string>(const phantom::string& arg)
{
    static double zero = 0;
    if(arg == "-1.#IND") return -zero/zero;
    else if(arg == "1.#IND") return zero/zero;
    else if(arg == "-1.#INF") return -1./zero;
    else if(arg == "1.#INF") return 1./zero;
    else return boost::lexical_cast<double>(arg);
}

// long double
template<>
inline long double lexical_cast<long double, phantom::string>(const phantom::string& arg)
{
    static long double zero = 0;
    if(arg == "-1.#IND") return -zero/zero;
    else if(arg == "1.#IND") return zero/zero;
    else if(arg == "-1.#INF") return -1./zero;
    else if(arg == "1.#INF") return 1./zero;
    else return boost::lexical_cast<long double>(arg);
}

// long long
template<>
inline long long lexical_cast<long long, phantom::string>(const phantom::string& arg)
{
    return (long long)phantom::lexical_cast<long double>(arg);
}

template<>
inline unsigned long long lexical_cast<unsigned long long, phantom::string>(const phantom::string& arg)
{
    return (unsigned long long)phantom::lexical_cast<long double>(arg);
}

// long
template<>
inline long lexical_cast<long, phantom::string>(const phantom::string& arg)
{
    return (long)phantom::lexical_cast<float>(arg);
}

template<>
inline unsigned long lexical_cast<unsigned long, phantom::string>(const phantom::string& arg)
{
    return (unsigned long)phantom::lexical_cast<double>(arg);
}


// int
template<>
inline int lexical_cast<int, phantom::string>(const phantom::string& arg)
{
    return (int)phantom::lexical_cast<double>(arg);
}

template<>
inline unsigned int lexical_cast<unsigned int, phantom::string>(const phantom::string& arg)
{
    return (unsigned int)phantom::lexical_cast<double>(arg);
}


// short
template<>
inline short lexical_cast<short, phantom::string>(const phantom::string& arg)
{
    return (short)phantom::lexical_cast<float>(arg);
}

template<>
inline unsigned short lexical_cast<unsigned short, phantom::string>(const phantom::string& arg)
{
    return (unsigned short)phantom::lexical_cast<float>(arg);
}

// char
template<>
inline char lexical_cast<char, phantom::string>(const phantom::string &arg)
{
    return (char)phantom::lexical_cast<int>(arg);
}

template<>
inline phantom::string lexical_cast<phantom::string, char>(const char& arg)
{
    return phantom::lexical_cast<phantom::string>((int)arg);
}

// char
template<>
inline bool lexical_cast<bool, phantom::string>(const phantom::string &arg)
{
#pragma warning(disable:4800)
    return (bool)phantom::lexical_cast<int>(arg);
#pragma warning(default:4800)
}

template<>
inline phantom::string lexical_cast<phantom::string, bool>(const bool& arg)
{
    return phantom::lexical_cast<phantom::string>((int)arg);
}

template<>
inline unsigned char lexical_cast<unsigned char, phantom::string>(const phantom::string &arg)
{
    return (unsigned char)phantom::lexical_cast<unsigned int>(arg);
}

template<>
inline phantom::string lexical_cast<phantom::string, unsigned char>(const unsigned char& arg)
{
    return phantom::lexical_cast<phantom::string>((unsigned int)arg);
}

template<>
inline std::nullptr_t lexical_cast<std::nullptr_t, phantom::string>(const phantom::string &arg)
{
    if(arg != "nullptr")
    {
        o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
    }
    return nullptr;
}

template<>
inline phantom::string lexical_cast<phantom::string, std::nullptr_t>(const std::nullptr_t& arg)
{
    if(arg != nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
    }
    return "nullptr";
}

template<>
inline void* lexical_cast<void*, phantom::string>(const phantom::string &arg)
{
    void* ptr;
#pragma warning(disable:4996)
    sscanf(arg.c_str(), "%X", &ptr);
#pragma warning(default:4996)
    return ptr;
}

typedef void* msvc_bug_lexical_cast_void_ptr; // WTF ??? why do i need this typedef to make the specialization work ? o�
template<>
inline phantom::string lexical_cast<phantom::string, msvc_bug_lexical_cast_void_ptr>(const msvc_bug_lexical_cast_void_ptr& arg)
{
    char buffer[32] = "";
#pragma warning(disable:4996)

#if o_ARCHITECTURE == o_ARCHITECTURE_X86
    sprintf(buffer, "%08X", (size_t)arg);
#elif o_ARCHITECTURE == o_ARCHITECTURE_X64
    sprintf(buffer, "%016X", (size_t)arg);
#else
    sprintf(buffer, "%016X", (size_t)arg);
#endif
#pragma warning(default:4996)
    return buffer;
}

template<typename t_Ty, bool is_class, bool is_enum>
struct string_converter_helper
{
    static void to(const reflection::Type* a_pType, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_strOut += phantom::lexical_cast<string>(*a_pSrc);
    }
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const t_Ty* a_pSrc)
    {
        a_strOut += phantom::lexical_cast<string>(*a_pSrc);
    }
    static void from(const reflection::Type* a_pType, const string& input, t_Ty* a_pDest)
    {
        *a_pDest = phantom::lexical_cast<t_Ty>(input);
    }
};

template<typename t_Ty>
struct string_converter : public string_converter_helper<t_Ty, boost::is_class<t_Ty>::value, boost::is_enum<t_Ty>::value>
{

};

template<>
struct string_converter<void>
{
    static void to(const reflection::Type* a_pType, string& a_strOut, const void* a_pSrc)
    {
    }
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const void* a_pSrc)
    {
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, void* a_pDest)
    {
    }
};

template<>
struct string_converter<std::nullptr_t> 
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const std::nullptr_t* a_pSrc)
    {
        if(*a_pSrc != nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
        }
        a_strOut = "nullptr";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const std::nullptr_t* a_pSrc)
    {
        if(*a_pSrc != nullptr)
        {
            o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
        }
        a_strOut = "nullptr";
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, std::nullptr_t* a_pDest)
    {
        if(a_strIn != "nullptr")
        {
            o_exception(exception::reflection_runtime_exception, "parsing nullptr value failed");
        }
        *a_pDest = nullptr;
    }
};

template<>
struct string_converter<char>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const char* a_pSrc)
    {
        a_strOut += "'";
        switch(*a_pSrc)
        {
        case '\'':  a_strOut += "\\'"; break;
        case '\\': a_strOut += "\\\\"; break;
        case '\n': a_strOut += "\\n" ; break;
        case '\r': a_strOut += "\\r" ; break;
        case '\t': a_strOut += "\\t" ; break;
        case '\0': a_strOut += "\\0" ; break;
        default:
            a_strOut += *a_pSrc;
        }
        a_strOut += "'";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const char* a_pSrc)
    {
        a_strOut += *a_pSrc;
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, char* a_pDest)
    {
        *a_pDest = a_strIn[0];
    }
};

template<>
struct string_converter<bool>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const bool* a_pSrc)
    {
        a_strOut += *a_pSrc ? "true" : "false";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const bool* a_pSrc)
    {
        a_strOut += *a_pSrc ? "true" : "false";
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, bool* a_pDest)
    {
        if(a_strIn == "true")
        {
            *a_pDest = true;
        }
        else 
        {
            *a_pDest = false;
        }
    }
};

template<>
struct string_converter<wchar_t>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const wchar_t* a_pSrc)
    {
        a_strOut += *((const char*)a_pSrc);
        a_strOut += *(((const char*)a_pSrc)+1);
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const wchar_t* a_pSrc)
    {
        a_strOut += *((const char*)a_pSrc);
        a_strOut += *(((const char*)a_pSrc)+1);
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, wchar_t* a_pDest)
    {
        *((char*)a_pDest) = a_strIn[0];
        *(((char*)a_pDest)+1) = a_strIn[1];
    }
};

template<>
struct string_converter<signal_t>
{
    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const signal_t* a_pSrc)
    {
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const signal_t* a_pSrc)
    {
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, signal_t* a_pDest)
    {
    }
};

template<typename t_Alloc>
struct string_converter<std::basic_string<char, std::char_traits<char>, t_Alloc>>
{
    typedef std::basic_string<char, std::char_traits<char>, t_Alloc> self_type;

    static void toLiteral(const reflection::Type* a_pType, string& a_strOut, const self_type* a_pSrc)
    {
        a_strOut += "\"";
        for(auto it = a_pSrc->begin(); it != a_pSrc->end(); ++it)
        {
            switch(*it)
            {
            case '"':  a_strOut += "\\\""; break;
            case '\\': a_strOut += "\\\\"; break;
            case '\n': a_strOut += "\\n" ; break;
            case '\r': a_strOut += "\\r" ; break;
            case '\t': a_strOut += "\\t" ; break;
            case '\0': a_strOut += "\\0" ; break;
            default:
                a_strOut += *it;
            }
        }
        a_strOut += "\"";
    }
    static void to(const reflection::Type* a_pType, string& a_strOut, const self_type* a_pSrc)
    {
        a_strOut.insert(a_strOut.end(), a_pSrc->begin(), a_pSrc->end());
    }
    static void from(const reflection::Type* a_pType, const string& a_strIn, self_type* a_pDest)
    {
        a_pDest->insert(a_pDest->end(), a_strIn.begin(), a_strIn.end());
    }
};

o_forceinline restore_state   combine_restore_states(restore_state s0, restore_state s1)
{
    return s0 > s1 ? s0 : s1;
}


namespace extension
{
    template< typename >
    struct constructor;
    template< typename >
    struct allocator;
    template< typename >
    struct serializer;
    template< typename >
    struct resetter;
    template< typename >
    struct initializer;
    template< typename >
    struct installer;
    template<typename t_Ty>
    struct rtti_data_registrer;
    template<typename t_Ty>
    struct dynamic_deleter;
}

namespace state
{
    namespace detail
    {
        template<typename t_Ty>
        struct state_machine_serializer;
        template<typename t_Ty>
        struct root_class_state_machine_serializer;
        template<typename t_Ty>
        struct state_machine_resetter;
        template<typename t_Ty>
        struct root_class_state_machine_resetter;
    }
}

o_namespace_end(phantom)

o_namespace_begin(phantom, extension)
template<typename t_Ty>
struct allocator;
o_namespace_end(phantom, extension)

o_namespace_begin(phantom, extension, detail)

/* constructor */

enum default_constructor_id
{
    default_constructor_placement_new,
    default_constructor_default_construction_forbidden,
    default_constructor_all_default_forbidden,
    default_constructor_none,
};

template<typename t_Ty, default_constructor_id t_default_constructor_id>
struct default_constructor_helper;

template<typename t_Ty>
struct default_constructor_helper<t_Ty, default_constructor_all_default_forbidden>
{
public:
    o_forceinline static void construct(t_Ty* a_pInstance) { o_unused(a_pInstance); o_exception(exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
    o_forceinline static void destroy(t_Ty* a_pInstance) { o_unused(a_pInstance); o_exception( exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
    o_forceinline static void construct(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pInstance); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); o_exception( exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
    o_forceinline static void destroy(t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pInstance); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); o_exception( exception::unsupported_member_function_exception, "type is abstract and cannot be constructed/destroyed"); }
};

template<typename t_Ty>
struct default_constructor_helper<t_Ty, default_constructor_none>
{
public:
    o_forceinline static void construct(t_Ty* a_pInstance) {o_unused(a_pInstance);  }
    o_forceinline static void destroy(t_Ty* a_pInstance) {o_unused(a_pInstance);  }
    o_forceinline static void construct(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pChunk); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); }
    o_forceinline static void destroy(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) {o_unused(a_pChunk); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize);  }
};

template<typename t_Ty>
struct default_constructor_helper<t_Ty, default_constructor_default_construction_forbidden>
{
public:
    o_forceinline static void construct(t_Ty* a_pInstance) { o_unused(a_pInstance); o_exception(exception::unsupported_member_function_exception, "type hasn't default constructor and cannot be constructed"); }
    o_forceinline static void destroy(t_Ty* a_pInstance) { a_pInstance->~t_Ty(); }
    o_forceinline static void construct(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize) { o_unused(a_pChunk); o_unused(a_uiCount); o_unused(a_uiChunkSectionSize); o_exception(exception::unsupported_member_function_exception, "type hasn't default constructor and cannot be constructed"); }
    o_forceinline static void destroy(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            reinterpret_cast<t_Ty*>(pChunk)->~t_Ty();
    }
};

template<typename t_Ty>
struct default_constructor_helper<t_Ty, default_constructor_placement_new>
{
public:
    o_forceinline static void construct(t_Ty* a_pInstance) { new (a_pInstance) t_Ty; }
    o_forceinline static void destroy(t_Ty* a_pInstance) { static_cast<t_Ty*>(a_pInstance)->~t_Ty(); }
    o_forceinline static void construct(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            reinterpret_cast<t_Ty*>(pChunk)->~t_Ty();
    }
    o_forceinline static void destroy(t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
            reinterpret_cast<t_Ty*>(pChunk)->~t_Ty();
    }
};


/* installation */

enum default_installer_id
{
    default_installer_none,
    default_installer_static_rtti_registration,
    default_installer_static_rtti_registration_and_statechart,
    no_installer,
};

template<typename t_Ty, default_installer_id t_default_installer_id>
struct default_installer_helper;

template<typename t_Ty>
struct default_installer_helper<t_Ty, default_installer_static_rtti_registration>
{
public:
    o_forceinline static void install(reflection::Class* a_pClass, t_Ty* a_pInstance, size_t a_uiLevel)
    {
        reflection::Class* pBaseClass = a_pClass;
        o_assert(!connection::slot_pool::hasAllocationController(a_pInstance, pBaseClass));
        connection::slot_pool& ac = connection::slot_pool::allocationController(a_pInstance, pBaseClass);
        phantom::addRttiData(a_pInstance, phantom::rtti_data(pBaseClass, pBaseClass, a_pInstance, &ac, &phantom::extension::dynamic_deleter<t_Ty>::dynamicDelete, a_uiLevel));
        phantom::extension::rtti_data_registrer<t_Ty>::registerInfo(a_pInstance, a_pInstance, pBaseClass, &ac, &phantom::extension::dynamic_deleter<t_Ty>::dynamicDelete, a_uiLevel);
        pBaseClass->installInstanceDataMembersCascade(a_pInstance, a_uiLevel);
        pBaseClass->registerInstance(a_pInstance);
    }
     
    o_forceinline static void uninstall(reflection::Class* a_pClass, t_Ty* a_pInstance, size_t a_uiLevel)
    {
        reflection::Class* pBaseClass = a_pClass;
        pBaseClass->unregisterInstance(a_pInstance);
        pBaseClass->uninstallInstanceDataMembersCascade(a_pInstance, a_uiLevel);
        removeRttiData(a_pInstance, a_uiLevel);
        phantom::extension::rtti_data_registrer<t_Ty>::unregisterInfo(a_pInstance, a_uiLevel);
        connection::slot_pool::eraseAllocationController(a_pInstance, pBaseClass);
    }
    o_forceinline static void install(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel)
    {
        reflection::Class* pBaseClass = a_pClass;
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            o_assert(!connection::slot_pool::hasAllocationController(pChunk, pBaseClass));
            connection::slot_pool& ac = connection::slot_pool::allocationController(pChunk, pBaseClass);
            phantom::addRttiData(pChunk, phantom::rtti_data(pBaseClass, pBaseClass, pChunk, &ac, &phantom::extension::dynamic_deleter<t_Ty>::dynamicDelete, a_uiLevel));
            phantom::extension::rtti_data_registrer<t_Ty>::registerInfo(reinterpret_cast<t_Ty*>(pChunk), pChunk, pBaseClass, &ac, &phantom::extension::dynamic_deleter<t_Ty>::dynamicDelete, a_uiLevel) ;
            pBaseClass->installInstanceDataMembersCascade(pChunk, a_uiLevel);
            pBaseClass->registerInstance(pChunk);
        }
    }
    o_forceinline static void uninstall(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel)
    {
        reflection::Class* pBaseClass = a_pClass;
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            pBaseClass->unregisterInstance(pChunk);
            pBaseClass->uninstallInstanceDataMembersCascade(pChunk, a_uiLevel);
            removeRttiData(pChunk, a_uiLevel);
            phantom::extension::rtti_data_registrer<t_Ty>::unregisterInfo(reinterpret_cast<t_Ty*>(pChunk), a_uiLevel) ;
            connection::slot_pool::eraseAllocationController(pChunk, pBaseClass);
        }
    }
};

template<typename t_Ty, uint t_super_class_count_of, boolean t_has_smdataptr>
struct smdata_installer_of_helper ;

template<typename t_Ty, uint t_superclasscount>
struct smdata_installer_of_helper_super;

template<typename t_Ty>
struct smdata_installer_of
    : public smdata_installer_of_helper<t_Ty
    , phantom::super_class_count_of<t_Ty>::value
    , has_smdataptr<t_Ty>::value>
{
    template<typename t_Ty2, uint t_superclasscount>
    friend struct smdata_installer_of_helper_super;
};

template<typename t_Ty, uint t_super_class_count_of, boolean t_has_smdataptr>
struct smdata_installer_of_helper
    : public smdata_installer_of_helper_super<t_Ty, t_super_class_count_of>
{
    template<typename t_Ty2, uint t_superclasscount>
    friend struct smdata_installer_of_helper_super;
};

template<typename t_Ty, uint t_superclasscount>
struct smdata_installer_of_helper_super
{
    template<typename t_Ty2, uint t_superclasscount2>
    friend struct smdata_installer_of_helper_super;

    template<typename,default_installer_id> friend struct default_installer_helper;
    o_forceinline static void install(t_Ty* a_pThis, phantom::state::base_state_machine_data* a_pSmdataptr)
    {
        smdata_installer_of<o_NESTED_TYPE super_class_of<t_Ty,t_superclasscount-1>::type>::install(a_pThis, a_pSmdataptr);
        smdata_installer_of_helper_super<t_Ty, t_superclasscount-1>::install(a_pThis, a_pSmdataptr);
    }
    o_forceinline static void uninstall(t_Ty* a_pThis)
    {
        smdata_installer_of<o_NESTED_TYPE super_class_of<t_Ty,t_superclasscount-1>::type>::uninstall(a_pThis);
        smdata_installer_of_helper_super<t_Ty, t_superclasscount-1>::uninstall(a_pThis);
    }
};

template<typename t_Ty>
struct smdata_installer_of_helper_super<t_Ty, 0>
{
    template<typename t_Ty2, uint t_superclasscount>
    friend struct smdata_installer_of_helper_super;
    template<typename,default_installer_id>
    friend struct default_installer_helper;
    o_forceinline static void install(t_Ty* a_pThis, phantom::state::base_state_machine_data* a_pSmdataptr) {}
    o_forceinline static void uninstall(t_Ty* a_pThis) {}
};

template<typename t_Ty, uint t_superclasscount>
struct smdata_installer_of_helper<t_Ty, t_superclasscount, true>
{
    template<typename,default_installer_id> friend struct default_installer_helper;
    template<typename t_Ty2, uint t_superclasscount2>
    friend struct smdata_installer_of_helper_super;
    o_forceinline static void install(t_Ty* a_pThis, phantom::state::base_state_machine_data* a_pSmdataptr)
    {
        *((phantom::state::base_state_machine_data**)(&(a_pThis->PHANTOM_CODEGEN_m_smdataptr))) = a_pSmdataptr;
    }
    o_forceinline static void uninstall(t_Ty* a_pThis)
    {
        *((phantom::state::base_state_machine_data**)(&(a_pThis->PHANTOM_CODEGEN_m_smdataptr))) = NULL;
    }
};

template<typename t_Ty>
struct default_installer_helper<t_Ty, default_installer_static_rtti_registration_and_statechart>
{
    typedef phantom::state::native::state_machine_data<t_Ty> state_machine_data;
public:
    inline static void        install(reflection::Class* a_pClass,  t_Ty* a_pInstance, size_t a_uiLevel )
    {
        default_installer_helper<t_Ty, default_installer_static_rtti_registration>::install(a_pClass, a_pInstance, a_uiLevel);
        phantom::state::base_state_machine_data* smdataptr = new (phantom::extension::allocator<state_machine_data>::allocate(o_memory_stat_insert_arguments)) state_machine_data(a_pInstance);
        smdata_installer_of<t_Ty>::install(a_pInstance, smdataptr);
    }
    inline static void        uninstall(reflection::Class* a_pClass,  t_Ty* a_pInstance, size_t a_uiLevel )
    {
        phantom::extension::allocator<state_machine_data>::deallocate(
            (state_machine_data*)(
                static_cast<o_NESTED_TYPE first_super_statechart_class_of<t_Ty>::type*>(a_pInstance)->PHANTOM_CODEGEN_m_smdataptr
            ) o_memory_stat_append_arguments
        );
        default_installer_helper<t_Ty, default_installer_static_rtti_registration>::uninstall(a_pClass, a_pInstance, a_uiLevel);

    }
    inline static void        install(reflection::Class* a_pClass,  t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel )
    {
        default_installer_helper<t_Ty, default_installer_static_rtti_registration>::install(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_uiLevel);
        // new (phantom::allocate<state_machine_data>(a_uiCount)) state_machine_data[a_uiCount];
        o_assert(false, "TODO : implement smdataptr installation for chunks");
    }
    inline static void        uninstall(reflection::Class* a_pClass,  t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel )
    {
        phantom::deallocate<state_machine_data>(
            (state_machine_data*)(
                static_cast<o_NESTED_TYPE first_super_statechart_class_of<t_Ty>::type*>(a_pChunk)->PHANTOM_CODEGEN_m_smdataptr
            )
            , a_uiCount o_memory_stat_append_arguments
        );
        default_installer_helper<t_Ty, default_installer_static_rtti_registration>::uninstall(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_uiLevel);
    }
};

template<typename t_Ty>
struct default_installer_helper<t_Ty, default_installer_none>
{
public:
    o_forceinline static void install(reflection::Type* , t_Ty* a_pInstance, size_t a_uiLevel) {  }
    o_forceinline static void uninstall(reflection::Type* , t_Ty* a_pInstance, size_t a_uiLevel) {  }
    o_forceinline static void install(reflection::Type* , t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel) {  }
    o_forceinline static void uninstall(reflection::Type* , t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel) {  }
};

/* initialization */

enum default_initializer_id
{
    default_initializer_member_function_and_instanciation_notification,
    default_initializer_instanciation_notification_only,
    default_initializer_member_function_only,
    default_initializer_none,
};

template<typename t_Ty, default_initializer_id t_Id>
struct default_initializer_helper;

template<typename t_Ty>
struct default_initializer_helper<t_Ty, default_initializer_none>
{
    o_forceinline static void initialize(reflection::Type*, t_Ty* a_pInstance) {  }
    o_forceinline static void terminate(reflection::Type*, t_Ty* a_pInstance) {  }
    o_forceinline static void initialize(reflection::Type*, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) {  }
    o_forceinline static void terminate(reflection::Type*, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize) {  }
    o_forceinline static restore_state restore(reflection::Type*, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass) { return restore_complete; }
    o_forceinline static restore_state restore(reflection::Type*, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize) { return restore_complete; }
};


// INITIALIZER METHODS (RECURSIVE) CALLERS

template<typename t_Ty>
struct initialize_member_function_caller;
template<typename t_Ty>
struct terminate_member_function_caller;
template<typename t_Ty>
struct restore_member_function_caller;
template<typename t_Ty>
struct destroyed_signal_emitter;


// INITIALIZE CALLER

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct initialize_member_function_caller_super_
{
    typedef typename super_class_of<t_Ty,t_super_class_count_of-1>::type super_class;
    static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
    {
        // Call super first
        initialize_member_function_caller<super_class>::apply(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance);

        // Then the current class
        initialize_member_function_caller_super_<t_Ty, t_super_class_count_of-1, t_declared>::apply(a_pClass, a_pInstance);
    }
};

template<typename t_Ty>
struct initialize_member_function_caller_super_<t_Ty, 0, false>
{
    inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance) 
    { 
        a_pClass->initializeInstanceDataMembers(a_pInstance); 
    }
};

template<typename t_Ty>
struct initialize_member_function_caller_super_<t_Ty, 0, true>
{
    inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance) 
    { 
        a_pClass->initializeInstanceDataMembers(a_pInstance);
        static_cast<initialize_member_function_caller_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_initialize(); 
    }
};

template<typename t_Ty>
struct initialize_member_function_caller_friend_breaker : public t_Ty
{
    template<typename t_Ty2, int t_super_class_count_of, bool t_has_initialize_member_function, bool t_declared>
    friend struct initialize_member_function_caller_helper_;
};

template<typename t_Ty, int t_super_class_count_of, bool t_has_initialize_member_function, bool t_declared>
struct initialize_member_function_caller_helper_ 
    : public initialize_member_function_caller_super_<t_Ty, t_super_class_count_of, t_declared> 
{

};

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct initialize_member_function_caller_helper_<t_Ty, t_super_class_count_of, false, t_declared>
{
    inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance) 
    {
        a_pClass->initializeInstanceDataMembers(a_pInstance);
    }
};

template<typename t_Ty>
struct initialize_member_function_caller
    : public initialize_member_function_caller_helper_<t_Ty
    , super_class_count_of<t_Ty>::value
    , has_initializer_member_function_initialize<t_Ty>::value
    , has_initializer_member_function_initialize_declared<t_Ty>::value>
{
};

// RESTORE CALLER

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct restore_member_function_caller_super_
{
    typedef typename super_class_of<t_Ty,t_super_class_count_of-1>::type super_class;

    static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint filter, uint pass)
    {
        // Call super first
        restore_state result = restore_member_function_caller<super_class>::apply(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance, filter, pass);
        // Then the current class
        return combine_restore_states(result, restore_member_function_caller_super_<t_Ty, t_super_class_count_of-1, t_declared>::apply(a_pClass, a_pInstance, filter, pass)); 
    }
};

template<typename t_Ty>
struct restore_member_function_caller_super_<t_Ty, 0, true>
{
    inline static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass) 
    {        
        restore_state result = a_pClass->restoreInstanceDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass);
        return combine_restore_states(result, static_cast<restore_member_function_caller_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_restore(a_uiSerializationFlag, a_uiPass)); 
    }
};

template<typename t_Ty>
struct restore_member_function_caller_super_<t_Ty, 0, false>
{
    inline static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass) 
    { 
        return a_pClass->restoreInstanceDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass); 
    }
};

template<typename t_Ty>
struct restore_member_function_caller_friend_breaker : public t_Ty
{
    template<typename t_Ty2, int t_super_class_count_of, bool t_has_restore_member_function, bool t_declared>
    friend struct restore_member_function_caller_helper_;
};

template<typename t_Ty, int t_super_class_count_of, bool t_has_restore_member_function, bool t_declared>
struct restore_member_function_caller_helper_ : public restore_member_function_caller_super_<t_Ty, t_super_class_count_of, t_declared> 
{

};

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct restore_member_function_caller_helper_<t_Ty, t_super_class_count_of, false, t_declared>
{
    inline static restore_state apply(reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass) 
    { 
        return a_pClass->restoreInstanceDataMembers(a_pInstance, a_uiSerializationFlag, a_uiPass); 
    }
};

template<typename t_Ty>
struct restore_member_function_caller
    : public restore_member_function_caller_helper_<t_Ty
        , super_class_count_of<t_Ty>::value
        , has_initializer_member_function_restore<t_Ty>::value
        , has_initializer_member_function_restore_declared<t_Ty>::value>
{

};

// TERMINATE CALLER

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct terminate_member_function_caller_super_
{
    typedef typename super_class_of<t_Ty,t_super_class_count_of-1>::type super_class;
    static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance)
    {
        // Current class first
        terminate_member_function_caller_super_<t_Ty, t_super_class_count_of-1, t_declared>::apply(a_pClass, a_pInstance);
        // Then super classes
        terminate_member_function_caller<super_class>::apply(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance);
    }
};

template<typename t_Ty>
struct terminate_member_function_caller_super_<t_Ty, 0, true>
{
    inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance) 
    {
        static_cast<terminate_member_function_caller_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_terminate(); 
        a_pClass->terminateInstanceDataMembers(a_pInstance); 
    }
};

template<typename t_Ty>
struct terminate_member_function_caller_super_<t_Ty, 0, false>
{
    inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance) { a_pClass->terminateInstanceDataMembers(a_pInstance); }
};

template<typename t_Ty>
struct terminate_member_function_caller_friend_breaker : public t_Ty
{
    template<typename t_Ty2, int t_super_class_count_of, bool t_has_terminate_member_function, bool t_declared>
    friend struct terminate_member_function_caller_helper_;
};

template<typename t_Ty, int t_super_class_count_of, bool t_has_terminate_member_function, bool t_declared>
struct terminate_member_function_caller_helper_ : public terminate_member_function_caller_super_<t_Ty, t_super_class_count_of, t_declared> 
{

};

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct terminate_member_function_caller_helper_<t_Ty, t_super_class_count_of, false, t_declared>
{
    inline static void apply(reflection::Class* a_pClass, t_Ty* a_pInstance) { a_pClass->terminateInstanceDataMembers(a_pInstance); }
};

template<typename t_Ty>
struct terminate_member_function_caller
    : public terminate_member_function_caller_helper_<t_Ty
    , super_class_count_of<t_Ty>::value
    , has_initializer_member_function_terminate<t_Ty>::value
    , has_initializer_member_function_terminate_declared<t_Ty>::value>
{
};

// INITIALIZE CALLER

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct destroyed_signal_emitter_super_
{
    static void apply(t_Ty* a_pInstance)
    {
        // Call super first
        destroyed_signal_emitter<typename super_class_of<t_Ty,t_super_class_count_of-1>::type>::apply(a_pInstance);

        // Then the current class
        destroyed_signal_emitter_super_<t_Ty, t_super_class_count_of-1, t_declared>::apply(a_pInstance);
    }
};

template<typename t_Ty>
struct destroyed_signal_emitter_super_<t_Ty, 0, true>
{
    inline static void apply(t_Ty* a_pInstance) 
    { 
        static_cast<destroyed_signal_emitter_friend_breaker<t_Ty>*>(a_pInstance)->PHANTOM_CODEGEN_destroyed(); 
    }
};

template<typename t_Ty>
struct destroyed_signal_emitter_super_<t_Ty, 0, false>
{
    inline static void apply(t_Ty* a_pInstance) {}
};

template<typename t_Ty>
struct destroyed_signal_emitter_friend_breaker : public t_Ty
{
    template<typename t_Ty2, int t_super_class_count_of, bool t_has_initialize_member_function, bool t_declared>
    friend struct destroyed_signal_emitter_helper_;
};

template<typename t_Ty, int t_super_class_count_of, bool t_has_initialize_member_function, bool t_declared>
struct destroyed_signal_emitter_helper_ 
    : public destroyed_signal_emitter_super_<t_Ty, t_super_class_count_of, t_declared> {};

template<typename t_Ty, int t_super_class_count_of, bool t_declared>
struct destroyed_signal_emitter_helper_<t_Ty, t_super_class_count_of, false, t_declared>
{
    inline static void apply(t_Ty* a_pInstance) {}
};

template<typename t_Ty>
struct destroyed_signal_emitter
    : public destroyed_signal_emitter_helper_<t_Ty
    , super_class_count_of<t_Ty>::value
    , has_destroyed_signal<t_Ty>::value
    , has_destroyed_signal_declared<t_Ty>::value>
{
};



template<typename t_Ty>
struct default_initializer_helper<t_Ty, default_initializer_member_function_and_instanciation_notification>
{
    inline static void      initialize( reflection::Class* a_pClass, t_Ty* a_pInstance )
    {
        initialize_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance);
#if o__bool__use_kind_creation_signal
        a_pClass->fireKindCreated(a_pInstance);
#endif
    }
    inline static restore_state   restore( reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass )
    {
        restore_state result = restore_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance, a_uiSerializationFlag, a_uiPass); 
#if o__bool__use_kind_creation_signal
        a_pClass->fireKindCreated(a_pInstance);
#endif
        return result;
    }
    inline static void      terminate( reflection::Class* a_pClass, t_Ty* a_pInstance )
    {
#if o__bool__use_kind_destruction_signal
        a_pClass->fireKindDestroyed(static_cast<t_Ty*>(a_pInstance));
#endif
#if o__bool__use_destroyed_signal
        destroyed_signal_emitter<t_Ty>::apply(a_pInstance);
#endif
        terminate_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance);
    }
    inline static void        initialize( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            initialize_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk));
#if o__bool__use_kind_creation_signal
            a_pClass->fireKindCreated(reinterpret_cast<t_Ty*>(pChunk));
#endif
        }
    }
    inline static void        terminate( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
#if o__bool__use_kind_destruction_signal
            a_pClass->fireKindDestroyed(reinterpret_cast<t_Ty*>(pChunk));
#endif
#if o__bool__use_destroyed_signal
            destroyed_signal_emitter<t_Ty>::apply(reinterpret_cast<t_Ty*>(pChunk));
#endif
            terminate_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk));
        }
    }
    inline static restore_state   restore( reflection::Class* a_pClass, t_Ty* a_pChunk, uint a_uiSerializationFlag, uint a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize  )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        restore_state result = restore_complete;
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            result = combine_restore_states(result, restore_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk), a_uiSerializationFlag, a_uiPass)); 
#if o__bool__use_kind_creation_signal
            a_pClass->fireKindCreated(reinterpret_cast<t_Ty*>(pChunk));
#endif
        }
        return result;
    }
};


template<typename t_Ty>
struct default_initializer_helper<t_Ty, default_initializer_member_function_only>
{
    inline static void        initialize( reflection::Class* a_pClass, t_Ty* a_pInstance )
    {
        initialize_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance);
    }
    inline static void        terminate( reflection::Class* a_pClass, t_Ty* a_pInstance )
    {
#if o__bool__use_destroyed_signal
        destroyed_signal_emitter<t_Ty>::apply(a_pInstance);
#endif
        terminate_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance);
    }
    inline static restore_state   restore( reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass )
    {
        return restore_member_function_caller<t_Ty>::apply(a_pClass, a_pInstance, a_uiSerializationFlag, a_uiPass); 
    }
    inline static void        initialize( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            initialize_member_function_caller<t_Ty>::apply(pClass, reinterpret_cast<t_Ty*>(pChunk));
        }
    }
    inline static void        terminate( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
#if o__bool__use_destroyed_signal
            destroyed_signal_emitter<t_Ty>::apply(reinterpret_cast<t_Ty*>(pChunk));
#endif
            terminate_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk));
        }
    }
    inline static restore_state   restore( reflection::Class* a_pClass, t_Ty* a_pChunk, uint a_uiSerializationFlag, uint a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize  )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        restore_state result = restore_complete;
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            result = combine_restore_states(result, restore_member_function_caller<t_Ty>::apply(a_pClass, reinterpret_cast<t_Ty*>(pChunk), a_uiSerializationFlag, a_uiPass)); 
        }
        return result;
    }
};

template<typename t_Ty>
struct default_initializer_helper<t_Ty, default_initializer_instanciation_notification_only>
{
    inline static void        initialize( reflection::Class* a_pClass, t_Ty* a_pInstance )
    {
#if o__bool__use_kind_creation_signal
        a_pClass->fireKindCreated(a_pInstance);
#endif
    }
    inline static restore_state     restore( reflection::Class* a_pClass, t_Ty* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass )
    {
#if o__bool__use_kind_creation_signal
        a_pClass->fireKindCreated(a_pInstance);
#endif
        return restore_complete;
    }
    inline static void        terminate( reflection::Class* a_pClass, t_Ty* a_pInstance )
    {
#if o__bool__use_kind_destruction_signal
        a_pClass->fireKindDestroyed(a_pInstance);
#endif
#if o__bool__use_destroyed_signal
        destroyed_signal_emitter<t_Ty>::apply(a_pInstance);
#endif
    }
    inline static void        initialize( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
#if o__bool__use_kind_creation_signal
            a_pClass->fireKindCreated(reinterpret_cast<t_Ty*>(pChunk));
#endif
        }
    }
    inline static void        terminate( reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
#if o__bool__use_kind_destruction_signal
            a_pClass->fireKindDestroyed(reinterpret_cast<t_Ty*>(pChunk));
#endif
#if o__bool__use_destroyed_signal
            destroyed_signal_emitter<t_Ty>::apply(reinterpret_cast<t_Ty*>(pChunk));
#endif
        }
    }
    inline static restore_state   restore( reflection::Class* a_pClass, t_Ty* a_pChunk, uint a_uiSerializationFlag, uint a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize  )
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
#if o__bool__use_kind_creation_signal
            a_pClass->fireKindCreated(reinterpret_cast<t_Ty*>(pChunk));
#endif
        }
        return restore_complete;
    }

};

enum default_serializer_id
{
    default_serializer_not_serializable,
    default_serializer_not_supported_and_must_be_customized,
    default_serializer_canonical,
    default_serializer_enum,
    default_serializer_podclass,
    default_serializer_class,
    default_serializer_class_with_root_statechart,
    default_serializer_pointer,
    default_serializer_array,
    default_serializer_container,
    default_serializer_basic_string_char,
    default_serializer_basic_string_wchar_t,
};

enum default_resetter_id
{
    default_resetter_not_resettable,
    default_resetter_not_supported_and_must_be_customized,
    default_resetter_canonical,
    default_resetter_class,
    default_resetter_class_with_root_statechart,
    default_resetter_default,
};

template<typename t_Ty, default_serializer_id t_default_serializer_id>
struct default_serializer_helper;

template<typename t_Ty, default_resetter_id t_default_resetter_id>
struct default_resetter_helper;

template<typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_not_serializable>
{
    static void throw_exception() { o_exception(exception::unsupported_member_function_exception, "This type is not serializable"); }
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
       throw_exception();
    }
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        throw_exception();
    }
};

template<typename t_Ty>
struct default_resetter_helper<t_Ty, default_resetter_not_resettable>
{
    static void throw_exception() { o_exception(exception::unsupported_member_function_exception, "This type is not resettable"); }
    o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
    {
        throw_exception();
    }
    o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
    {
        throw_exception();
    }
    o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        throw_exception();
    }
    o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        throw_exception();
    }
};
template <typename t_Ty>
struct default_serializer;

template <typename t_Ty>
struct default_resetter;

template<typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_not_supported_and_must_be_customized>
{
    o_static_assert_msg(sizeof(t_Ty) == sizeof(t_Ty),
        "no serializer defined for the given class, \
        you must define it by yourself and declare it \
        using template specialization or 'o_Serializer' macro-variable \
        in the classdef.h" );

};

template<typename t_Ty>
struct default_resetter_helper<t_Ty, default_resetter_not_supported_and_must_be_customized>
{
    o_static_assert_msg(sizeof(t_Ty) == sizeof(t_Ty),
        "no resetter defined for the given class, \
        you must define it by yourself and declare it \
        using template specialization or 'o_Resetter' macro-variable \
        in the classdef.h" );

};

template<typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_canonical>
{
public:
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        *reinterpret_cast<t_Ty*>(a_pOutBuffer) = *a_pInstance;
        a_pOutBuffer += sizeof(t_Ty);
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        *a_pInstance = *reinterpret_cast<t_Ty const*>(a_pInBuffer);
        a_pInBuffer += sizeof(t_Ty);
    }
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            *reinterpret_cast<t_Ty*>(a_pOutBuffer) = *reinterpret_cast<t_Ty const*>(pChunk);
            a_pOutBuffer += sizeof(t_Ty);
        }
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        for(;a_uiCount--;pChunk += a_uiChunkSectionSize)
        {
            *reinterpret_cast<t_Ty*>(pChunk) = *reinterpret_cast<t_Ty const*>(a_pInBuffer);
            a_pInBuffer += sizeof(t_Ty);
        }
    }
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        a_OutBranch.put_value(phantom::lexical_cast<string>(*a_pInstance));
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        const boost::optional<string>& value = a_InBranch.get_value_optional<string>();
        if(value.is_initialized())
        {
            *reinterpret_cast<t_Ty*>(a_pInstance) = phantom::lexical_cast<t_Ty>(*value);
        }
    }
    o_forceinline static void serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            t_Ty value = *reinterpret_cast<t_Ty const*>(pChunk);
            a_OutBranch.put<string>(index_buffer, phantom::lexical_cast<string>(value));
            pChunk += a_uiChunkSectionSize;
        }
    }
    o_forceinline static void deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            const boost::optional<string>& value = a_InBranch.get_optional<string>(index_buffer);
            if(value.is_initialized())
            {
                *reinterpret_cast<t_Ty*>(pChunk) = phantom::lexical_cast<t_Ty>(*value);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
};


template<typename t_Ty>
struct default_resetter_helper<t_Ty, default_resetter_canonical>
{
    o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
    {
        default_serializer_helper<t_Ty, default_serializer_canonical>::serialize(a_pType, a_pInstance, a_pOutBuffer, 0, NULL);
    }
    o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
    {
        default_serializer_helper<t_Ty, default_serializer_canonical>::deserialize(a_pType, a_pInstance, a_pInBuffer, 0, NULL);
    }
    o_forceinline static void remember(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        default_serializer_helper<t_Ty, default_serializer_canonical>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, 0, NULL);
    }
    o_forceinline static void reset(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        default_serializer_helper<t_Ty, default_serializer_canonical>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, 0, NULL);
    }
};


template<typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_array>
{
    o_static_assert_msg(boost::extent<t_Ty>::value, "t_Ty is not an array type, weird...");
    enum {extent = boost::extent<t_Ty>::value};
    typedef o_NESTED_TYPE boost::remove_extent<t_Ty>::type content_type;

    typedef o_NESTED_TYPE reflection::canonical_meta_class_type_of<content_type>::type meta_content_type;

    static void serialize(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        phantom::extension::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type const*>(a_pInstance), extent, sizeof(content_type), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::ArrayType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        phantom::extension::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type*>(a_pInstance), extent, sizeof(content_type), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
    {
        phantom::extension::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type const*>(a_pInstance), extent, sizeof(content_type), a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::ArrayType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
    {
        phantom::extension::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type*>(a_pInstance), extent, sizeof(content_type), a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void        serialize(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            phantom::extension::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type const*>(pChunk), extent, sizeof(content_type), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    static void        deserialize(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            phantom::extension::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type*>(pChunk), extent, sizeof(content_type), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            pChunk += a_uiChunkSectionSize;
        }
    }

    static void        serialize(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            property_tree index_tree;
            phantom::extension::serializer<content_type>::serialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type const*>(pChunk), extent, sizeof(content_type), index_tree, a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(index_buffer, index_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }

    static void        deserialize(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            boost::optional<const property_tree&> index_tree_opt = a_InBranch.get_child_optional(index_buffer);
            if(index_tree_opt.is_initialized())
            {
                phantom::extension::serializer<content_type>::deserialize(static_cast<meta_content_type*>(a_pType->getElementType()), reinterpret_cast<content_type*>(pChunk), extent, sizeof(content_type), *index_tree_opt, a_uiSerializationMask, a_pDataBase);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::ArrayType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ArrayType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }

};

template<typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_pointer>
{
    static void        serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        void* ptr = *reinterpret_cast<void* const*>(a_pInstance);
        const rtti_data& rttiData = phantom::rttiDataOf(ptr);
        o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
        void* ptr_base = rttiData.base;
        // save the offset from the base address to restore the correct inheritance layout address later
        size_t offset = reinterpret_cast<size_t>(ptr)-reinterpret_cast<size_t>(ptr_base);
        uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
        *reinterpret_cast<uint*>(a_pOutBuffer) = guid;
        a_pOutBuffer += sizeof(uint);
        *reinterpret_cast<size_t*>(a_pOutBuffer) = offset;
        a_pOutBuffer += sizeof(size_t);
        if(guid == 0xffffffff) // Object not stored in database, we try to save it
        {
            if(ptr_base)
            {
                // we "inline" it if it's a class instance and we know the said class
                reflection::Class*  pClass = rttiData.object_class;
                o_assert(pClass, "The object is not stored in the data base and its type is unknown"
                    ", we cannot save it, ensure the pointer valueMember you are trying to serialize is transient or "
                    "that the internal types are either serializable class instances installed with phantom (o_classN.. + o_new)"
                    " either data stored in database ");

                *reinterpret_cast<uint*>(a_pOutBuffer) = pClass->getGuid(); // Save the class guid ; TODO : little/big endian managment
                a_pOutBuffer += sizeof(uint);
                pClass->serialize(ptr_base, a_pOutBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance
            }
            else
            {
                *reinterpret_cast<uint*>(a_pOutBuffer) = 0; // Ptr null => we save a null guid
                a_pOutBuffer += sizeof(uint);
            }
        }
    }

    static void        deserialize(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        uint guid = *reinterpret_cast<uint const*>(a_pInBuffer);
        a_pInBuffer += sizeof(uint);
        // read the offset from the base address to restore the correct inheritance layout address
        size_t offset = *reinterpret_cast<size_t const*>(a_pInBuffer);
        a_pInBuffer += sizeof(size_t);

        if(guid == 0xffffffff) // Object not stored in database, we try to rebuild it
        {
            // We find the instance class thanks to the stored guid 
            uint classGuid = *reinterpret_cast<uint const*>(a_pInBuffer);
            a_pInBuffer += sizeof(uint);
            if(classGuid != 0)
            {
                // we "uninline" it if it's a class instance and we know the said class
                reflection::Type*  pType = phantom::typeByGuid(classGuid);
                o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                    "ensure all the class are registered correctly before deserializing data");

                reflection::Class* pClass = static_cast<reflection::Class*>(pType);
                void* newInstance = pClass->allocate();
                pClass->build(newInstance);
                pClass->deserialize(newInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance

                // we restore all the pass here, because we can't do it later, 
                // we won't have any pointer to this object after this member_function
                uint pass = 0;
                restore_state restored = restore_incomplete;
                while(restored == restore_incomplete)
                {
                    // be sure for this kind of objects that you don't have dependencies 
                    // with other stored object which couln't be totally restored at this point
                    restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
                }
                if(restored == restore_failed)
                {
                    pClass->deleteInstance(newInstance);
                    *reinterpret_cast<void**>(a_pInstance) = NULL;
                }
                else
                {
                    *reinterpret_cast<void**>(a_pInstance) = reinterpret_cast<byte*>(newInstance)+offset; // restore the correct layout
                }
            }
            else
            {
                *reinterpret_cast<void**>(a_pInstance) = NULL; // restore the null pointer (if classGuid == 0)
            }
        }
        else 
        {
            *reinterpret_cast<void**>(a_pInstance) = reinterpret_cast<byte*>(a_pDataBase ? a_pDataBase->getDataAddress(guid) : (void*)guid)+offset; // restore the correct layout
        }
    }

    static void serialize(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
    {
        void* ptr = *reinterpret_cast<void* const*>(a_pInstance);
        const rtti_data& rttiData = phantom::rttiDataOf(ptr);
        o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
        void* ptr_base = rttiData.base;
        size_t offset = reinterpret_cast<size_t>(ptr)-reinterpret_cast<size_t>(ptr_base);
        uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
        a_OutBranch.put<string>("guid", phantom::lexical_cast<string>(guid));
        a_OutBranch.put<string>("offset", phantom::lexical_cast<string>(offset));
        if((guid == 0xffffffff) AND (ptr_base != NULL))
        {
            a_OutBranch.put<string>("type", rttiData.object_class->getQualifiedDecoratedName()); 
            property_tree data_tree;
            rttiData.object_class->serialize(ptr_base, data_tree, a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child("data", data_tree);
        }
    }

    static void deserialize( reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase )
    {
        string guid_str = a_InBranch.get<string>("guid");
        string offset_str = a_InBranch.get<string>("offset");
        uint guid = phantom::lexical_cast<uint>(guid_str);
        size_t offset = phantom::lexical_cast<size_t>(offset_str);
        if(guid == 0xffffffff)
        {
            boost::optional<string> typeName_opt = a_InBranch.get_optional<string>("type"); 
            if(typeName_opt.is_initialized())
            {
                reflection::Type* pType = a_pDataBase ? a_pDataBase->solveTypeByName(/*decodeQualifiedDecoratedNameFromIdentifierName*/(*typeName_opt)) : phantom::typeByName(decodeQualifiedDecoratedNameFromIdentifierName(*typeName_opt));
                o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                    "ensure all the class are registered correctly before deserializing data");
                reflection::Class* pClass = static_cast<reflection::Class*>(pType);
                void* newInstance = pClass->allocate();
                pClass->build(newInstance);
                const property_tree& data_tree = a_InBranch.get_child("data");
                pClass->deserialize(newInstance, data_tree, a_uiSerializationMask, a_pDataBase);
                    
                // we restore all the pass here, because we can't do it later, 
                // we won't have any pointer to this object after this member_function
                uint pass = 0;
                restore_state restored = restore_incomplete;
                while(restored == restore_incomplete)
                {
                    // be sure for this kind of objects that you don't have dependencies 
                    // with other stored object which couln't be totally restored at this point
                    restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
                }
                if(restored == restore_failed)
                {
                    pClass->deleteInstance(newInstance);
                    *reinterpret_cast<void**>(a_pInstance) = NULL;
                }
                else
                {
                    *reinterpret_cast<void**>(a_pInstance) = reinterpret_cast<byte*>(newInstance)+offset; // restore the correct layout
                }
            }
            else
            {
                *reinterpret_cast<void**>(a_pInstance) = NULL;
            }
        }
        else 
        {
            *reinterpret_cast<void**>(a_pInstance) = reinterpret_cast<byte*>(a_pDataBase ? a_pDataBase->getDataAddress(guid) : (void*)guid)+offset;
        }
    }

    static void        serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            void* ptr = *reinterpret_cast<void* const*>(pChunk);
            const rtti_data& rttiData = phantom::rttiDataOf(ptr);
            o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
            void* ptr_base = rttiData.base;
            // save the offset from the base address to restore the correct inheritance layout address later
            size_t offset = reinterpret_cast<size_t>(ptr)-reinterpret_cast<size_t>(ptr_base);
            uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
            *reinterpret_cast<uint*>(a_pOutBuffer) = guid; // TODO : little/big endian managment
            a_pOutBuffer += sizeof(uint);
            *reinterpret_cast<size_t*>(a_pOutBuffer) = offset; // TODO : little/big endian managment
            a_pOutBuffer += sizeof(size_t);
            if(guid == 0xffffffff) // Object not stored in database, we try to save it
            {
                if(ptr_base)
                {
                    // we "inline" it if it's a class instance and we know the said class
                    reflection::Class*  pClass = rttiData.object_class;
                    o_assert(pClass, "The object is not stored in the data base and its type is unknown"
                        ", we cannot save it, ensure the pointer valueMember you are trying to serialize is transient or "
                        "that the internal types are either serializable class instances installed with phantom (o_classN.. + o_new)"
                        " either data stored in database ");

                    *reinterpret_cast<uint*>(a_pOutBuffer) = pClass->getGuid(); // Save the class guid ; TODO : little/big endian managment
                    a_pOutBuffer += sizeof(uint);
                    pClass->serialize(ptr_base, a_pOutBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance
                }
                else
                {
                    *reinterpret_cast<uint*>(a_pOutBuffer) = 0; // Ptr null => we save a null guid
                    a_pOutBuffer += sizeof(uint);
                }
            }
            pChunk += a_uiChunkSectionSize;
        }
    }

    static void        deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            uint guid = *reinterpret_cast<uint const*>(a_pInBuffer);
            a_pInBuffer += sizeof(uint);
            // read the offset from the base address to restore the correct inheritance layout address
            size_t offset = *reinterpret_cast<size_t const*>(a_pInBuffer);
            a_pInBuffer += sizeof(size_t);

            if(guid == 0xffffffff) // Object not stored in database, we try to rebuild it
            {
                // We find the instance class thanks to the stored guid 
                uint classGuid = *reinterpret_cast<uint const*>(a_pInBuffer);
                a_pInBuffer += sizeof(uint);

                if(classGuid != 0)
                {
                    // we "uninline" it if it's a class instance and we know the said class
                    reflection::Type*  pType = phantom::typeByGuid(classGuid);
                    o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                        "ensure all the class are registered correctly before deserializing data");

                    reflection::Class* pClass = static_cast<reflection::Class*>(pType);
                    void* newInstance = pClass->allocate();
                    pClass->build(newInstance);
                    pClass->deserialize(newInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase); // Save the instance

                    // we restore all the pass here, because we can't do it later, 
                    // we won't have any pointer to this object after this member_function
                    uint pass = 0;
                    restore_state restored = restore_incomplete;
                    while(restored == restore_incomplete)
                    {
                        // be sure for this kind of objects that you don't have dependencies 
                        // with other stored object which couln't be totally restored at this point
                        restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
                    }
                    if(restored == restore_failed)
                    {
                        pClass->deleteInstance(newInstance);
                        *reinterpret_cast<void**>(pChunk) = NULL;
                    }
                    else
                    {
                        *reinterpret_cast<void**>(pChunk) = reinterpret_cast<byte*>(newInstance)+offset; // restore the correct layout
                    }
                }
                else
                {
                    *reinterpret_cast<void**>(pChunk) = NULL;
                }
            }
            else
            {
                *reinterpret_cast<void**>(pChunk) = reinterpret_cast<byte*>(a_pDataBase ? a_pDataBase->getDataAddress(guid) : (void*)guid)+offset; // TODO : little/big endian managment
            }
            pChunk += a_uiChunkSectionSize;
        }
    }

    static void        serialize(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            void* ptr = *reinterpret_cast<void* const*>(pChunk);
            const rtti_data& rttiData = phantom::rttiDataOf(ptr);
            o_assert(ptr == nullptr OR NOT(rttiData.isNull()));
            void* ptr_base = rttiData.base;
            uint guid = a_pDataBase ? a_pDataBase->getGuid(ptr_base) : (uint)ptr_base;
            // save the offset from the base address to restore the correct inheritance layout address later
            size_t offset = reinterpret_cast<size_t>(ptr)-reinterpret_cast<size_t>(ptr_base);
            property_tree index_tree;
            index_tree.put<string>("guid", phantom::lexical_cast<string>(guid));
            index_tree.put<string>("offset", phantom::lexical_cast<string>(offset));
            if((guid == 0xffffffff) AND (ptr_base != NULL))
            {
                index_tree.put<string>("type", rttiData.object_class->getQualifiedDecoratedName()); 
                property_tree data_tree; 
                rttiData.object_class->serialize(ptr_base, data_tree, a_uiSerializationMask, a_pDataBase);
                index_tree.add_child("data", data_tree);
            }
            a_OutBranch.add_child(index_buffer, index_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }

    static void        deserialize(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            boost::optional<const property_tree&> index_tree_opt = a_InBranch.get_child_optional(index_buffer);
            if(index_tree_opt.is_initialized())
            {
                const property_tree& index_tree = *index_tree_opt;
                const string& guid_str = index_tree.get<string>("guid");
                const string& offset_str = index_tree.get<string>("offset");
                uint guid = phantom::lexical_cast<uint>(guid_str);
                size_t offset = phantom::lexical_cast<size_t>(offset_str);
                if(guid == 0xffffffff)
                {
                    boost::optional<string> typeName_opt = index_tree.get_optional<string>("type"); 
                    if(typeName_opt.is_initialized())
                    {
                        const string& typeName = *typeName_opt;
                        reflection::Type* pType = a_pDataBase ? a_pDataBase->solveTypeByName(/*decodeQualifiedDecoratedNameFromIdentifierName*/(typeName)) : phantom::typeByName(decodeQualifiedDecoratedNameFromIdentifierName(typeName));
                        o_assert(pType AND pType->asClass(), "The class associated with the given serialized data cannot be found, "
                            "ensure all the class are registered correctly before deserializing data");
                        reflection::Class* pClass = static_cast<reflection::Class*>(pType);
                        void* newInstance = pClass->allocate();
                        pClass->build(newInstance);
                        const property_tree& data_tree = index_tree.get_child("data"); 
                        pClass->deserialize(newInstance, data_tree, a_uiSerializationMask, a_pDataBase);
                        // we restore all the pass here, because we can't do it later, 
                        // we won't have any pointer to this object after this member_function
                        uint pass = 0;
                        restore_state restored = restore_incomplete;
                        while(restored == restore_incomplete)
                        {   // be sure for this kind of objects that you don't have dependencies 
                            // with other stored object which couln't be totally restored at this point
                            restored = pClass->restore(newInstance, a_uiSerializationMask, pass++);
                        }
                        if(restored == restore_failed)
                        {
                            pClass->deleteInstance(newInstance);
                            *reinterpret_cast<void**>(pChunk) = NULL;
                        }
                        else
                        {
                            *reinterpret_cast<void**>(pChunk) = reinterpret_cast<byte*>(newInstance)+offset; // restore the correct layout
                        }
                    }
                    else
                    {
                        *reinterpret_cast<void**>(pChunk) = reinterpret_cast<byte*>(a_pDataBase ? a_pDataBase->getDataAddress(guid) : (void*)guid)+offset;
                    }
                }
                else
                {
                    *reinterpret_cast<void**>(pChunk) = reinterpret_cast<byte*>(a_pDataBase ? a_pDataBase->getDataAddress(guid) : (void*)guid)+offset;
                }
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
};



template<typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_enum>
{
    typedef o_NESTED_TYPE phantom::enum_integral_type<t_Ty>::type proxy_type;
    o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serialize(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserialize(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }



    o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serializeLayout(reflection::Enum* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::serializeLayout(a_pType, (proxy_type const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::Enum* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<proxy_type>::deserializeLayout(a_pType, (proxy_type*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
};


template<typename t_Ty>
struct default_resetter_helper<t_Ty, default_resetter_default>
{
    template<typename t_MetaTy>
    o_forceinline static void remember(t_MetaTy* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
    {
        serializer<t_Ty>::serialize(a_pType, a_pInstance, a_pOutBuffer, 0, NULL);
    }
    template<typename t_MetaTy>
    o_forceinline static void reset(t_MetaTy* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
    {
        serializer<t_Ty>::deserialize(a_pType, a_pInstance, a_pInBuffer, 0, NULL);
    }
    template<typename t_MetaTy>
    o_forceinline static void remember(t_MetaTy* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        serializer<t_Ty>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, 0, NULL);
    }
    template<typename t_MetaTy>
    o_forceinline static void reset(t_MetaTy* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        serializer<t_Ty>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, 0, NULL);
    }
};



template <typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_class_with_root_statechart>
{
public:
    o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::serialize(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }



    o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::serialize(a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::serialize(a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::deserialize(a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::serializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::serialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer_helper<t_Ty, default_serializer_class>::deserializeLayout(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        state::detail::root_class_state_machine_serializer<t_Ty>::deserialize(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }

};

template <typename t_Ty>
struct default_resetter_helper<t_Ty, default_resetter_class_with_root_statechart>
{
public:
    o_forceinline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
    {
        default_resetter_helper<t_Ty, default_resetter_class>::remember(a_pType, a_pInstance, a_pOutBuffer);
        state::detail::state_machine_resetter<t_Ty>::remember(a_pInstance, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer)
    {
        default_resetter_helper<t_Ty, default_resetter_class>::reset(a_pType, a_pInstance, a_pInBuffer);
        state::detail::state_machine_resetter<t_Ty>::reset(a_pInstance, a_pInBuffer);
    }
    o_forceinline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        default_resetter_helper<t_Ty, default_resetter_class>::remember(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
        state::detail::state_machine_resetter<t_Ty>::remember(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        default_resetter_helper<t_Ty, default_resetter_class>::reset(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
        state::detail::state_machine_resetter<t_Ty>::reset(a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }
};


template<typename t_Ty, size_t t_super_class_count_of>
struct super_class_serializer_helper
{
    o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::serialize(a_pClass, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::serialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::deserialize(a_pClass, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::deserialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::serialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::serialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::deserialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::deserialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::serialize(a_pClass, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::serialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::deserialize(a_pClass, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::deserialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void serialize(reflection::Class* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::serialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::serialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    o_forceinline static void deserialize(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer_helper<t_Ty, t_super_class_count_of-1>::deserialize(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
        phantom::extension::serializer<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::deserialize(a_pClass->getSuperClass(t_super_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
};


template<typename t_Ty, size_t t_super_class_count_of>
struct super_class_resetter_helper
{
    o_forceinline static void remember(reflection::Class* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer)
    {
        super_class_resetter_helper<t_Ty, t_super_class_count_of-1>::remember(a_pClass, a_pInstance, a_pOutBuffer);
        phantom::extension::resetter<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::remember(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::Class* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer)
    {
        super_class_resetter_helper<t_Ty, t_super_class_count_of-1>::reset(a_pClass, a_pInstance, a_pInBuffer);
        phantom::extension::resetter<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::reset(a_pClass->getSuperClass(t_super_class_count_of-1), a_pInstance, a_pInBuffer);
    }
    o_forceinline static void remember(reflection::Class* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        super_class_resetter_helper<t_Ty, t_super_class_count_of-1>::remember(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
        phantom::extension::resetter<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::remember(a_pClass->getSuperClass(t_super_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::Class* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        super_class_resetter_helper<t_Ty, t_super_class_count_of-1>::reset(a_pClass, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
        phantom::extension::resetter<o_traits_t_Ty_super_class(t_super_class_count_of-1)>::reset(a_pClass->getSuperClass(t_super_class_count_of-1), a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }
    
};

template<typename t_Ty>
struct super_class_serializer_helper<t_Ty, 0> // recursion stop 
{
    o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
    o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
    o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void serialize(reflection::Type* a_pClass, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)     {    }
    o_forceinline static void deserialize(reflection::Type* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)    {    }
};

template<typename t_Ty>
struct super_class_resetter_helper<t_Ty, 0> // recursion stop 
{
    o_forceinline static void remember(reflection::Type* a_pClass, t_Ty const* a_pInstance, byte*& a_pOutBuffer) {    }
    o_forceinline static void reset(reflection::Type* a_pClass, t_Ty* a_pInstance, byte const*& a_pInBuffer) {    }
    o_forceinline static void remember(reflection::Type* a_pClass, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) {    }
    o_forceinline static void reset(reflection::Type* a_pClass, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) {    }
};

template <typename t_Ty>
struct super_class_serializer : public super_class_serializer_helper<t_Ty, phantom::super_class_count_of<t_Ty>::value>
{

};

template <typename t_Ty>
struct super_class_resetter : public super_class_resetter_helper<t_Ty, phantom::super_class_count_of<t_Ty>::value>
{

};

template <typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_class>
{
public:
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer<t_Ty>::serialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        serializeLayout(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer<t_Ty>::deserialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        deserializeLayout(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer<t_Ty>::serialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        serializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        super_class_serializer<t_Ty>::deserialize(static_cast<reflection::Class*>(a_pType), a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        deserializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
};

template <typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_podclass>
{
public:
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serializeLayout(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserializeLayout(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserializeLayout(a_pType, a_pInstance, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase);
};

template <typename t_Ty>
struct default_resetter_helper<t_Ty, default_resetter_class>
{
    o_forceinline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer);
    o_forceinline static void reset(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer);
    o_forceinline static void remember(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer);
    o_forceinline static void reset(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer);
};

template <typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_container>
{
    typedef o_NESTED_TYPE t_Ty::value_type value_type;
    typedef o_NESTED_TYPE t_Ty::size_type size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator const_iterator;

    typedef o_NESTED_TYPE reflection::canonical_meta_class_type_of<t_Ty>::type meta_type;
    typedef o_NESTED_TYPE reflection::canonical_meta_class_type_of<value_type>::type meta_value_type;

public:
    static void serialize(meta_type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type   size = a_pInstance->size();
        serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        const_iterator it = a_pInstance->begin();
        const_iterator end = a_pInstance->end();
        for(;it!=end;++it)
        {
            serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        }
    }
    static void deserialize(meta_type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type   size = 0;
        serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        phantom::container::reserver<t_Ty>::apply(a_pInstance, size);
        size_type i = 0;
        for(;i<size;++i)
        {
            value_type deserialized;
            serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &deserialized, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            phantom::container::adder<t_Ty>::apply(a_pInstance, deserialized);
        }
    }
    static void serialize(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
            size_type   size = pInstance->size();
            serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            const_iterator it = pInstance->begin();
            const_iterator end = pInstance->end();
            for(;it!=end;++it)
            {
                serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void deserialize(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
            size_type   size = 0;
            serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            phantom::container::reserver<t_Ty>::apply(pInstance, size);
            size_type i = 0;
            for(;i<size;++i)
            {
                value_type deserialized;
                serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &deserialized, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
                phantom::container::adder<t_Ty>::apply(pInstance, deserialized);
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serialize(meta_type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type   size = a_pInstance->size();
        a_OutBranch.put<string>("size", phantom::lexical_cast<string>(size));
        const_iterator it = a_pInstance->begin();
        const_iterator end = a_pInstance->end();
        int i = 0;
        for(;it!=end;++it)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            property_tree index_tree;
            serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), index_tree, a_uiSerializationMask, a_pDataBase);
            a_OutBranch.add_child(index_buffer, index_tree);
        }
    }
    static void deserialize(meta_type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        boost::optional<string> size_str_opt = a_InBranch.get_optional<string>("size");
        if(size_str_opt.is_initialized())
        {
            size_type   size = phantom::lexical_cast<size_type>(*size_str_opt);
            phantom::container::reserver<t_Ty>::apply(a_pInstance, size);
            size_type i = 0;
            for(;i<size;++i)
            {
                char index_buffer[32]="";
                o_secured_sprintf(index_buffer, 32, "_%d", i);
                boost::optional<const property_tree&> index_tree_opt = a_InBranch.get_child_optional(index_buffer);
                if(index_tree_opt.is_initialized())
                {
                    value_type pDeserialized;
                    serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &pDeserialized, *index_tree_opt, a_uiSerializationMask, a_pDataBase);
                    phantom::container::adder<t_Ty>::apply(a_pInstance, pDeserialized);
                }
            }
        }
    }
    static void serialize(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
            size_type   size = pInstance->size();
            property_tree container_tree;
            container_tree.put<string>("size", phantom::lexical_cast<string>(size));
            const_iterator it = pInstance->begin();
            const_iterator end = pInstance->end();
            {
                size_t i = 0;
                for(;it!=end;++it)
                {
                    char index_buffer[32]="";
                    o_secured_sprintf(index_buffer, 32, "_%d", i++);
                    property_tree index_tree;
                    serializer<value_type>::serialize(static_cast<meta_value_type*>(a_pType->getValueType()), &(*it), index_tree, a_uiSerializationMask, a_pDataBase);
                    container_tree.add_child(index_buffer, index_tree);
                }
            }
            a_OutBranch.add_child(index_buffer, container_tree);
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void deserialize(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
            boost::optional<const property_tree&> container_tree_opt = a_InBranch.get_child_optional(index_buffer);
            if(container_tree_opt.is_initialized())
            {
                const property_tree& container_tree = *container_tree_opt;
                size_type size = phantom::lexical_cast<size_type>(container_tree.get<string>("size"));
                phantom::container::reserver<t_Ty>::apply(pInstance, size);
                {
                    size_type i = 0;
                    for(;i<size;++i)
                    {
                        char index_buffer[32]="";
                        o_secured_sprintf(index_buffer, 32, "_%d", i);
                        boost::optional<const property_tree&> index_tree_opt = container_tree.get_child_optional(index_buffer);
                        if(index_tree_opt.is_initialized())
                        {
                            value_type deserialized;
                            serializer<value_type>::deserialize(static_cast<meta_value_type*>(a_pType->getValueType()), &deserialized, *index_tree_opt, a_uiSerializationMask, a_pDataBase);
                            phantom::container::adder<t_Ty>::apply(pInstance, deserialized);
                        }
                    }
                }
            }
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serializeLayout(meta_type* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(meta_type* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(meta_type* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(meta_type* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(meta_type* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(meta_type* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
};


// some util template functions
template<typename t_Ty2>
struct to_property_branch_value
{
    static const char* apply(t_Ty2 const* a_pInstance) { return a_pInstance->c_str(); }
};
template<>
struct to_property_branch_value<phantom::string>
{
    static phantom::string const & apply(phantom::string const* a_pInstance) { return *a_pInstance; }
};
template<typename t_Ty2>
struct from_property_branch_value
{
    static const char* apply(phantom::string const& a_pInstance) { return a_pInstance.c_str(); }
};
template<>
struct from_property_branch_value<phantom::string>
{
    static phantom::string const & apply(phantom::string const& a_pInstance)
    {
        return a_pInstance;
    }
};

template <typename t_Ty>
struct default_serializer_helper<t_Ty, default_serializer_basic_string_char>
{

    typedef o_NESTED_TYPE t_Ty::value_type      value_type;
    typedef o_NESTED_TYPE t_Ty::size_type       size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator  const_iterator;

public:
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type size = a_pInstance->size();
        serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
        memcpy(a_pOutBuffer, a_pInstance->c_str(), size);
        a_pOutBuffer += size;
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        size_type   size = 0;
        serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
        a_pInstance->assign((char const*)a_pInBuffer, size);
        a_pInBuffer += size;
    }
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        while(a_uiCount--)
        {
            t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
            size_type size = pInstance->size();
            serializer<size_type>::serialize(typeOf<size_type>(), &size, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
            memcpy(a_pOutBuffer, pInstance->c_str(), size);
            a_pOutBuffer += size;
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        while(a_uiCount--)
        {
            t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
            size_type   size = 0;
            serializer<size_type>::deserialize(typeOf<size_type>(), &size, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
            pInstance->assign((char const*)a_pInBuffer, size);
            a_pInBuffer += size;
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        a_OutBranch.put_value(to_property_branch_value<t_Ty>::apply(a_pInstance));
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        boost::optional<string> opt = a_InBranch.get_value_optional<string>();
        if(opt.is_initialized())
        {
            a_pInstance->assign(from_property_branch_value<t_Ty>::apply(*opt));
        }
        else a_pInstance->clear();
    }
    static void serialize(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte const* pChunk = reinterpret_cast<byte const*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            t_Ty const* pInstance = reinterpret_cast<t_Ty const*>(pChunk);
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            a_OutBranch.put<string>(index_buffer, to_property_branch_value<t_Ty>::apply(pInstance));
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void deserialize(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        byte* pChunk = reinterpret_cast<byte*>(a_pChunk);
        int i = 0;
        while(a_uiCount--)
        {
            t_Ty* pInstance = reinterpret_cast<t_Ty*>(pChunk);
            char index_buffer[32]="";
            o_secured_sprintf(index_buffer, 32, "_%d", i++);
            boost::optional<string> opt = a_InBranch.get_optional<string>(index_buffer);
            if(opt.is_initialized())
            {
                pInstance->assign(from_property_branch_value<t_Ty>::apply(*opt));
            }
            else pInstance->clear();
            pChunk += a_uiChunkSectionSize;
        }
    }
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::ClassType* a_pType, t_Ty const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        serialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::ClassType* a_pType, t_Ty* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        deserialize(a_pType, a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
};


template<typename t_Ty>
struct default_allocator : public o__t1_class__default_class_allocator(t_Ty)
{
    o_rebind(default_allocator)
};

template<typename t_Ty>
struct default_constructor : public default_constructor_helper<t_Ty,
    boost::is_abstract<t_Ty>::value
    ? phantom::has_virtual_destructor_cascade<t_Ty>::value
        ? detail::default_constructor_default_construction_forbidden
        : detail::default_constructor_all_default_forbidden // abstract
    : boost::is_class<t_Ty>::value
        ? boost::is_pod<t_Ty>::value
            ? detail::default_constructor_none
            : NOT(phantom::is_default_constructible_and_not_abstract<t_Ty>::value)
                ? detail::default_constructor_default_construction_forbidden // no default constructor
                : detail::default_constructor_placement_new
        : detail::default_constructor_none
>
{
    o_rebind(default_constructor)
};


template<typename t_Ty>
struct default_installer : public default_installer_helper<t_Ty,
    (boost::is_fundamental<t_Ty>::value
        OR phantom::is_signal_t<t_Ty>::value
        OR phantom::is_nullptr_t<t_Ty>::value
        OR boost::is_pod<t_Ty>::value 
        OR has_meta_specifier<t_Ty, o_pod>::value
        OR has_meta_specifier<t_Ty, o_no_rtti>::value)
        ? default_installer_none
        : (has_reflection_cascade<t_Ty>::value || is_meta_type<t_Ty>::value)
            ? has_statechart_cascade<t_Ty>::value
                ? default_installer_static_rtti_registration_and_statechart
                : default_installer_static_rtti_registration
            :  default_installer_none

>
{
    o_rebind(default_installer)
};

template <typename t_Ty>
struct default_serializer : public default_serializer_helper<t_Ty,
    (boost::is_void<t_Ty>::value OR phantom::is_signal_t<t_Ty>::value)
    ? default_serializer_not_serializable
    : boost::is_array<t_Ty>::value
    ? default_serializer_array
    : phantom::is_data_pointer<t_Ty>::value
        ? default_serializer_pointer
        : boost::is_enum<t_Ty>::value
        ? default_serializer_enum
        : boost::is_class<t_Ty>::value
            ? is_basic_string_char<t_Ty>::value
                ? default_serializer_basic_string_char
                : (is_map_container<t_Ty>::value OR is_sequential_container<t_Ty>::value OR is_set_container<t_Ty>::value)
                    ? detail::default_serializer_container
                    : /*has_reflection<t_Ty>::value
                        ? */has_root_statechart<t_Ty>::value
                            ? detail::default_serializer_class_with_root_statechart
                            : has_meta_specifier<t_Ty, o_pod>::value
                                ? detail::default_serializer_podclass
                                : detail::default_serializer_class
                        //: detail::default_serializer_not_supported_and_must_be_customized
        : detail::default_serializer_canonical>

{
    o_rebind(default_serializer)
};

template<typename t_Ty>
struct default_initializer : public default_initializer_helper<t_Ty,
    (is_signal_t<t_Ty>::value 
    OR boost::is_void<t_Ty>::value 
    OR is_meta_type<t_Ty>::value 
    OR boost::is_abstract<t_Ty>::value
    OR boost::is_pod<t_Ty>::value 
    OR has_meta_specifier<t_Ty, o_pod>::value
    OR NOT(has_reflection_cascade<t_Ty>::value))
    ? detail::default_initializer_none
    : boost::is_class<t_Ty>::value 
    ? detail::default_initializer_member_function_and_instanciation_notification
    : detail::default_initializer_instanciation_notification_only
>
{
    o_rebind(default_initializer)
};

template <typename t_Ty>
struct default_resetter : public default_resetter_helper<t_Ty,
    NOT(phantom::is_serializable<t_Ty>::value)
    ? default_resetter_not_resettable
    : boost::is_array<t_Ty>::value
    ? default_resetter_default
    : phantom::is_data_pointer<t_Ty>::value
        ? default_resetter_canonical
        : boost::is_enum<t_Ty>::value
        ? default_resetter_default
        : boost::is_class<t_Ty>::value
            ? is_basic_string_char<t_Ty>::value
                ? default_resetter_default
                : is_container<t_Ty>::value
                    ? detail::default_resetter_default
                    : /*has_reflection<t_Ty>::value
                        ? */has_root_statechart<t_Ty>::value
                            ? detail::default_resetter_class_with_root_statechart
                            : detail::default_resetter_class
                        //: detail::default_serializer_not_supported_and_must_be_customized
        : detail::default_resetter_canonical>

{
    o_rebind(default_resetter)
};

/**
 * \struct allocator_inheritance_super_index
 *
 * \brief Allocator inheritance super index. You can specialize it to specify from which super class a class must inherit its allocator.
 * 		  By default it's the first super class (index 0)
 */

template<typename t_Ty>
struct allocator_inheritance_super_index
{
    BOOST_STATIC_CONSTANT(size_t, value = 0);
};

template<typename t_Ty, bool t_inherits_allocator>
struct allocator_inheritance_helper
    : public
    phantom::extension::allocator<
     o_traits_t_Ty_super_class(allocator_inheritance_super_index<t_Ty>::value)
    >
    ::o_NESTED_TEMPLATE rebind<t_Ty>::other
{
///< We inherits allocator thanks to type template rebinding.
};

template<typename t_Ty>
struct allocator_inheritance_helper <t_Ty, false>
    : public default_allocator<t_Ty>
{
///< If we don't inherit from a super allocator, we use default one.
};

template<typename t_Ty>
struct inherited_allocator : public allocator_inheritance_helper<
    t_Ty
    , super_class_count_of<t_Ty>::value != 0 AND ((meta_specifiers<t_Ty>::value & o_inherits_allocator) == o_inherits_allocator)
>
{
    typedef allocator_inheritance_helper<
        t_Ty
        , super_class_count_of<t_Ty>::value != 0 AND ((meta_specifiers<t_Ty>::value & o_inherits_allocator) == o_inherits_allocator)
    >  super_type;
    o_forceinline static t_Ty* allocate() { return super_type::allocate(); }
    o_forceinline static void deallocate(t_Ty* a_pInstance) { super_type::deallocate(a_pInstance); }
    o_forceinline static t_Ty* allocate(size_t a_uiCount) { return super_type::allocate(a_uiCount); }
    o_forceinline static void deallocate(t_Ty* a_pInstance, size_t a_uiCount) { super_type::deallocate(a_pInstance,a_uiCount);  }
};

template<>
struct default_allocator<void>
{
//#pragma message(o_PP_QUOTE(o_exception(unsupported_member_function_exception)))
    o_forceinline static void* allocate() { o_exception(unsupported_member_function_exception); return NULL;  }
    o_forceinline static void deallocate(void* a_pInstance) { o_exception(unsupported_member_function_exception); }
    o_forceinline static void* allocate(size_t a_uiCount) { o_exception(unsupported_member_function_exception); return NULL; }
    o_forceinline static void deallocate(void* a_pInstance, size_t a_uiCount) { o_exception(unsupported_member_function_exception); }
};



template <>
class default_serializer<phantom::signal_t>
{
public:
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(phantom::exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serialize(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserialize(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }


    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void serializeLayout(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }
    static void deserializeLayout(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be serialized");
    }

};



template <>
class default_resetter<phantom::signal_t>
{
public:
    o_forceinline static void remember(reflection::Type* a_pType, phantom::signal_t const* a_pInstance, byte*& a_pOutBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
    o_forceinline static void reset(reflection::Type* a_pType, phantom::signal_t* a_pInstance, byte const*& a_pInBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
    o_forceinline static void remember(reflection::Type* a_pType, phantom::signal_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
    o_forceinline static void reset(reflection::Type* a_pType, phantom::signal_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        o_exception(exception::unsupported_member_function_exception, "signal_t is not supposed to be reset");
    }
};

#if o_BUILT_IN_WCHAR_T
template <>
struct default_serializer<wchar_t>
{
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serialize(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserialize(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserialize(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }



    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pInstance, byte* a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pInstance, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pInstance, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pInstance, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pInstance, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    static void serializeLayout(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::serializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    static void deserializeLayout(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase)
    {
        default_serializer<short>::deserializeLayout(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }

};
template <>
class default_resetter<wchar_t>
{
public:
    o_forceinline static void remember(reflection::Type* a_pType, wchar_t const* a_pInstance, byte*& a_pOutBuffer)
    {
        default_resetter<short>::remember(a_pType, (short const*)a_pInstance, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::Type* a_pType, wchar_t* a_pInstance, byte const*& a_pInBuffer)
    {
        default_resetter<short>::reset(a_pType, (short*)a_pInstance, a_pInBuffer);
    }
    o_forceinline static void remember(reflection::Type* a_pType, wchar_t const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer)
    {
        default_resetter<short>::remember(a_pType, (short const*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
    o_forceinline static void reset(reflection::Type* a_pType, wchar_t* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer)
    {
        default_resetter<short>::reset(a_pType, (short*)a_pChunk, a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }
};
#endif



#include "phantom/def_interpolator.inl"
#include "phantom/def_copier.inl"
#include "phantom/def_converter.inl"

template<typename t_Ty>
struct safe_constructor_ 
{
    static void safeConstruct(void* a_pInstance) { constructor<t_Ty>::construct((t_Ty*)a_pInstance); }
};

#include "phantom/def_new_delete.inl"

o_namespace_end(phantom, extension, detail)

o_namespace_begin(phantom, extension)

template<typename t_Ty>
struct dynamic_deleter
{
    o_forceinline static void dynamicDelete(void* a_pBase o_memory_stat_append_parameters)
    {
        phantom::extension::detail::delete_helper<t_Ty>(o_memory_stat_insert_parameters_use) >> a_pBase;
    }
};

o_namespace_end(phantom, extension)
    
o_namespace_begin(phantom, extension, detail)

template<typename t_Ty, uint t_superclasscount>
struct rtti_data_registrer_helper_
{
    template <typename> friend struct rtti_data_registrer;
    static void registerInfo(t_Ty* a_pThis, void* a_pBase, phantom::reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, size_t a_uiLevel) {}
    static void unregisterInfo(t_Ty* a_pThis, size_t a_uiLevel) {}
};

template<typename t_Ty>
struct rtti_data_registrer_helper_<t_Ty, 0>
{
    template <typename, uint > friend struct rtti_data_registrer_helper_;
    template <typename > friend struct rtti_data_registrer;
    inline static void registerInfo(t_Ty* a_pThis, void* a_pBase, phantom::reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, size_t a_uiLevel);
    inline static void unregisterInfo(t_Ty* a_pThis, size_t a_uiLevel);
};

#define o_rtti_data_registrer_helper_register_0() 
#define o_rtti_data_registrer_helper_register_1()  o_rtti_data_registrer_helper_register_0() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(0), phantom::super_class_count_of<o_traits_t_Ty_super_class(0)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_2()  o_rtti_data_registrer_helper_register_1() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(1), phantom::super_class_count_of<o_traits_t_Ty_super_class(1)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_3()  o_rtti_data_registrer_helper_register_2() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(2), phantom::super_class_count_of<o_traits_t_Ty_super_class(2)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_4()  o_rtti_data_registrer_helper_register_3() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(3), phantom::super_class_count_of<o_traits_t_Ty_super_class(3)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_5()  o_rtti_data_registrer_helper_register_4() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(4), phantom::super_class_count_of<o_traits_t_Ty_super_class(4)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_6()  o_rtti_data_registrer_helper_register_5() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(5), phantom::super_class_count_of<o_traits_t_Ty_super_class(5)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_7()  o_rtti_data_registrer_helper_register_6() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(6), phantom::super_class_count_of<o_traits_t_Ty_super_class(6)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_8()  o_rtti_data_registrer_helper_register_7() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(7), phantom::super_class_count_of<o_traits_t_Ty_super_class(7)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_9()  o_rtti_data_registrer_helper_register_8() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(8), phantom::super_class_count_of<o_traits_t_Ty_super_class(8)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
#define o_rtti_data_registrer_helper_register_10() o_rtti_data_registrer_helper_register_9() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(9), phantom::super_class_count_of<o_traits_t_Ty_super_class(9)>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);

#define o_rtti_data_registrer_helper_unregister_0() 
#define o_rtti_data_registrer_helper_unregister_1()  o_rtti_data_registrer_helper_unregister_0() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(0), phantom::super_class_count_of<o_traits_t_Ty_super_class(0)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_2()  o_rtti_data_registrer_helper_unregister_1() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(1), phantom::super_class_count_of<o_traits_t_Ty_super_class(1)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_3()  o_rtti_data_registrer_helper_unregister_2() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(2), phantom::super_class_count_of<o_traits_t_Ty_super_class(2)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_4()  o_rtti_data_registrer_helper_unregister_3() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(3), phantom::super_class_count_of<o_traits_t_Ty_super_class(3)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_5()  o_rtti_data_registrer_helper_unregister_4() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(4), phantom::super_class_count_of<o_traits_t_Ty_super_class(4)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_6()  o_rtti_data_registrer_helper_unregister_5() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(5), phantom::super_class_count_of<o_traits_t_Ty_super_class(5)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_7()  o_rtti_data_registrer_helper_unregister_6() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(6), phantom::super_class_count_of<o_traits_t_Ty_super_class(6)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_8()  o_rtti_data_registrer_helper_unregister_7() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(7), phantom::super_class_count_of<o_traits_t_Ty_super_class(7)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_9()  o_rtti_data_registrer_helper_unregister_8() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(8), phantom::super_class_count_of<o_traits_t_Ty_super_class(8)>::value>::unregisterInfo(a_pThis, a_uiLevel);
#define o_rtti_data_registrer_helper_unregister_10() o_rtti_data_registrer_helper_unregister_9() phantom::extension::detail::rtti_data_registrer_helper_<o_traits_t_Ty_super_class(9), phantom::super_class_count_of<o_traits_t_Ty_super_class(9)>::value>::unregisterInfo(a_pThis, a_uiLevel);

#define o_specialize_rtti_data_registrer_helper(_super_class_count_of_) \
    template<typename t_Ty>\
struct rtti_data_registrer_helper_<t_Ty, _super_class_count_of_>\
{\
    template <typename, phantom::uint > friend struct rtti_data_registrer_helper_;\
    template <typename > friend struct rtti_data_registrer;\
    static void registerInfo(t_Ty* a_pThis, void* a_pBase, phantom::reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, size_t a_uiLevel) \
{\
    o_rtti_data_registrer_helper_register_##_super_class_count_of_() \
}\
    static void unregisterInfo(t_Ty* a_pThis, size_t a_uiLevel) \
{\
    o_rtti_data_registrer_helper_unregister_##_super_class_count_of_() \
}\
};

o_specialize_rtti_data_registrer_helper(1)
o_specialize_rtti_data_registrer_helper(2)
o_specialize_rtti_data_registrer_helper(3)
o_specialize_rtti_data_registrer_helper(4)
o_specialize_rtti_data_registrer_helper(5)
o_specialize_rtti_data_registrer_helper(6)
o_specialize_rtti_data_registrer_helper(7)
o_specialize_rtti_data_registrer_helper(8)
o_specialize_rtti_data_registrer_helper(9)

o_namespace_end(phantom, extension, detail)

o_namespace_begin(phantom, extension)

/* these versions are the stable ones which are never specialized but inherits from the specilized/customized ones */

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct allocator
///
/// \brief  Allocator. (see instance creation process)
/// 		Allocation / Deallocation : by default phantom uses boost::fast_pool_allocator to allocate instance memory.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct allocator : public o_memory_stat_allocator(t_Ty, detail::inherited_allocator<t_Ty>)
{
};

template<>
struct allocator<void> 
{
    o_forceinline static void* allocate(o_memory_stat_insert_parameters) { o_error(false, "cannot allocate void"); return nullptr; }
    o_forceinline static void deallocate(void* a_pInstance o_memory_stat_append_parameters) { o_error(false, "cannot deallocate void");  }
    o_forceinline static void* allocate(size_t a_uiCount o_memory_stat_append_parameters) { o_error(false, "cannot allocate void"); return nullptr;}
    o_forceinline static void deallocate(void* a_pInstance, size_t a_uiCount o_memory_stat_append_parameters) { o_error(false, "cannot deallocate void"); }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct constructor
///
/// \brief  Constructor. (see instance creation process)
/// 		Construction : By default Phantom uses C++ placement new for instanciable classes
/// 		Destruction : By default Phantom uses C++ destructor call for instanciable classes
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct constructor : public detail::default_constructor<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct installer
///
/// \brief  Installer. (see instance creation process)
/// 		Installation is applied just after construction
/// 		Uninstallation is applied just before destruction
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct installer : public detail::default_installer<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct serializer
///
/// \brief  Serializer. (see instance creation process)
/// 		Serialization is applied when the users wants it. It's used inside the high-level serialization system provided with phantom.
/// 		Deserialization is applied just after installation (see instance creation process)
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct serializer : public detail::default_serializer<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct resetter
///
/// \brief  Resetter. (see instance creation process)
/// 		Used to remember the state of an object at a time 'T' and reset it when desired
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct resetter : public detail::default_resetter<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct initializer
///
/// \brief  Initializer. (see instance creation process)
/// 		Initialization is applied just after installation if deserialization doesn't occur
/// 		termination is the first step applied in the instance deletion process.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct initializer : public detail::default_initializer<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct interpolator
///
/// \brief  interpolator.
/// 		Provides interpolation from a start value to and end value
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct interpolator : public detail::default_interpolator<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct copier
///
/// \brief  copier.
/// 		Provides copy of type instances
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct copier : public detail::default_copier<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct converter
///
/// \brief  converter.
/// 		Provides conversion of type instances
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct converter : public detail::default_converter<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct converter
///
/// \brief  converter.
/// 		Provides conversion of type instances
///
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace detail 
{
    template<typename t_Ty, bool t_is_fundamental>
    struct default_promoter_helper
    {
        static reflection::Type* apply(reflection::Type*)
        {
            return typeOf<o_NESTED_TYPE boost::promote<t_Ty>::type>();
        }
    };
    template<typename t_Ty>
    struct default_promoter_helper<t_Ty, false>
    {
        static reflection::Type* apply(reflection::Type* a_pType)
        {
            return a_pType;
        }
    };
}

template<typename t_Ty>
struct promoter : public detail::default_promoter_helper<t_Ty, boost::is_fundamental<t_Ty>::value>
{
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \struct safe_constructor
///
/// \brief  safe_constructor.
/// 		Provides safe construction of type instances
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct safe_constructor : public detail::safe_constructor_<t_Ty>
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class rtti_data_registrer
///
/// \brief This helper registers/unregisters RTTI info of any class instance to the phantom system.
/// 	   You shouldn't use this unless you decide to customize installation from scratch.
/// 	   Remark : It's recommanded to make your installer inherits/call the default_installer member_functions
/// 	   instead of making a new one from scratch
///
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename t_Ty>
struct rtti_data_registrer
{
    template<typename, detail::default_installer_id> friend struct detail::default_installer_helper;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn static void rtti_data_registrer::registerInfo(t_Ty* a_pThis, void* a_pBase,
    ///     phantom::reflection::Class* a_pBaseClass, connection::slot::allocator* a_csac)
    ///
    /// \brief Registers RTTI instance info of a_pThis.
    ///
    /// \author Vivien MILLET
    /// \date 26/11/2011
    ///
    /// \param [in,out] a_pThis      If non-null, instance pointer.
    /// \param [in,out] a_pBase      If non-null, base address (for multiple inheritance).
    /// \param [in,out] a_pBaseClass If non-null, the base class.
    /// \param [in,out] a_csac       If non-null, the slot allocator.
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    static void registerInfo(t_Ty* a_pThis, void* a_pBase, phantom::reflection::Class* a_pBaseClass, connection::slot_pool* a_csac, dynamic_delete_func_t a_dynamic_delete_func, size_t a_uiLevel)
    {
        detail::rtti_data_registrer_helper_<t_Ty, phantom::super_class_count_of<t_Ty>::value>::registerInfo(a_pThis, a_pBase, a_pBaseClass, a_csac, a_dynamic_delete_func, a_uiLevel);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn static void rtti_data_registrer::unregisterInfo(t_Ty* a_pThis)
    ///
    /// \brief Unregisters RTTI instance info of a_pThis.
    ///
    /// \author Vivien MILLET
    /// \date 26/11/2011
    ///
    /// \param [in,out] a_pThis If non-null, instance pointer.
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    static void unregisterInfo(t_Ty* a_pThis, size_t a_uiLevel)
    {
        detail::rtti_data_registrer_helper_<t_Ty, phantom::super_class_count_of<t_Ty>::value>::unregisterInfo(a_pThis, a_uiLevel);
    }
};


#define o_begin_extension(_extension_, ...)\
    o_namespace_begin(phantom, extension, detail)\
    template<>\
    struct _extension_##_ \
    {

#define o_end_extension()\
    };\
    o_namespace_end(phantom, extension, detail)\

o_namespace_end(phantom, extension)


#endif // o_phantom_extension_h__
