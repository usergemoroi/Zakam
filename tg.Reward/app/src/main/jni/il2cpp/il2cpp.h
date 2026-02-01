#pragma once

#include <cmath>
#include <codecvt>
#include <fstream>
#include <functional>
#include <locale>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "il2cpp_defines.h"
#include "il2cpp_string.h"

static Map il2cpp { };
static Map unity { };
static Map shared { };

#define LOGIR(...) __android_log_print(ANDROID_LOG_INFO, "logs", __VA_ARGS__)
#define LOGER(...) __android_log_print(ANDROID_LOG_ERROR, "logs", __VA_ARGS__)

namespace il2cpp_api
{
	struct api_func
	{
	
	void * object_unbox (Il2CppObject * obj )
	{
		static auto fn = reinterpret_cast < void * ( * ) ( Il2CppObject * ) > ( il2cpp_base + oxorany (0x21256D8) );
		
		return fn ( obj );
	}
	
    Il2CppDomain * domain_get ( )
	{
		static auto fn = reinterpret_cast < Il2CppDomain * ( * ) ( ) > ( il2cpp_base + oxorany(0x765E85C) );
		
		return fn ( );
	}
	
    Il2CppAssembly * domain_assembly_open ( Il2CppDomain * domain , const char * usable )
	{
		static auto fn = reinterpret_cast < Il2CppAssembly * ( * ) ( Il2CppDomain * , const char * ) > ( il2cpp_base + oxorany(0x46C4F7C) );
		
		return fn ( domain , usable );
	}
	
    Il2CppImage * assembly_get_image (Il2CppAssembly * assembly )
	{
		static auto fn = reinterpret_cast <Il2CppImage * ( * ) (Il2CppAssembly * ) > ( il2cpp_base + oxorany(0x46DEFF8) );
		
		return fn ( assembly );
	}
	
    Il2CppClass * class_from_name ( Il2CppImage * im , const char * n1 , const char * n2 )
	{
		static auto fn = reinterpret_cast < Il2CppClass * ( * ) ( Il2CppImage * , const char * , const char * ) > ( il2cpp_base + oxorany(0x766C6D4) );
		
		return fn ( im , n1 , n2 );
	}
	
    FieldInfo * class_get_field_from_name ( Il2CppClass* cl , const char * n )
	{
		static auto fn = reinterpret_cast < FieldInfo * ( * ) (Il2CppClass* , const char * ) > ( il2cpp_base + oxorany(0x762F928) );
		
		return fn ( cl , n );
	}
	
    MethodInfo* class_get_method_from_name ( Il2CppClass* cl , const char * n , int a )
	{
		static auto fn = reinterpret_cast < MethodInfo * ( * ) ( Il2CppClass* , const char * , int ) > ( il2cpp_base + oxorany(0x20C7178) );
		
		return fn ( cl , n , a );
	}
	
    MethodInfo* class_get_methods ( Il2CppClass* clas , void ** iter )
	{
		static auto fn = reinterpret_cast < MethodInfo * ( * ) ( Il2CppClass* , void ** ) > ( il2cpp_base + oxorany(0x762FAAC) );
		
		return fn ( clas , iter );
	}
	
    Il2CppClass* class_from_type ( const Il2CppType* type )
	{
		static auto fn = reinterpret_cast < Il2CppClass * ( * ) ( const Il2CppType * ) > ( il2cpp_base + oxorany(0x762F208) ); // 0x2124BEC
		
		return fn ( type );
	}
	
    Il2CppObject * object_new ( Il2CppClass* cl )
	{
		static auto fn = reinterpret_cast < Il2CppObject * ( * ) ( Il2CppClass* ) > ( il2cpp_base + oxorany(0x46C55C4) );
		
		return fn ( cl );
	}
	
	const char * method_get_name ( MethodInfo* info )
	{
		static auto fn = reinterpret_cast < const char * ( * ) ( MethodInfo* ) > ( il2cpp_base + oxorany(0x2124F98) );
		
		return fn ( info );
	}
	
	uint32_t method_get_param_count ( MethodInfo* info )
	{
		static auto fn = reinterpret_cast < uint32_t ( * ) ( MethodInfo* ) > ( il2cpp_base + oxorany(0x2124FA8) );
		
		return fn ( info );
	}
	
	const Il2CppType* method_get_return_type ( MethodInfo* info )
	{
		static auto fn = reinterpret_cast < const Il2CppType * ( * ) ( MethodInfo * info ) > ( il2cpp_base + oxorany(0x2124F88) );
		
		return fn ( info );
	}
	
	void field_static_get_value ( FieldInfo * f , void * n )
	{
		static auto fn = reinterpret_cast < void ( * ) ( FieldInfo* , void * ) > ( il2cpp_base + oxorany(0x46DF7A4) );
		
		return fn ( f , n );
	}
	
    Il2CppString* string_new ( const char * t )
	{
		static auto fn = reinterpret_cast < Il2CppString * ( * ) ( const char * ) > ( il2cpp_base + oxorany(0x46DD100) );
		
		return fn ( t );
	}
	
    Il2CppImage* get_img_to_asm ( const char* assembly )
{
    Il2CppDomain* domain = domain_get ( );
	
    Il2CppAssembly* domain_asm = domain_assembly_open ( domain , assembly );
	
    Il2CppImage* asm_img = assembly_get_image ( domain_asm );
	
    return asm_img;
}
	
	};
	
	class il2cpp_data
	{
	public:
		api_func functions;
		
	};
	
	std :: unique_ptr < il2cpp_data > g_data = std :: make_unique < il2cpp_data > ( );

	il2cpp_data * get ( )
	{
		return g_data.get( );
	}
}

namespace il2cpp_ray
{
	template < typename T >
    struct array
    {
        void* klass;
        void* monitor;
        void* bounds;
        int32_t capacity;
        T m_items[ 0 ];

        [[maybe_unused]] int32_t get_capacity( )
        {
            if ( !this )
                return 0;

            return capacity;
        }

        T* get_ptr( )
        {
            if ( !this )
                return nullptr;

            return m_items;
        }

        std::vector< T > to_cpp_array( )
        {
            if ( !this )
                return { };

            std::vector< T > ret;

            for ( int i = 0; i < capacity; i++ )
                ret.push_back( m_items[ i ] );

            return std::move( ret );
        }

        bool copy_from( const std::vector< T >& vec )
        {
            if ( !this )
                return false;

            return copy_from( ( T* ) vec.data( ), ( int ) vec.size( ) );
        }

        [[maybe_unused]] bool copy_from( T* arr, int size )
        {
            if ( !this )
                return false;

            if ( size < capacity )
                return false;

            memcpy( m_items, arr, size * sizeof( T ) );

            return true;
        }

        [[maybe_unused]] void copy_to( T* arr )
        {
            if ( !this || !check_obj( m_items ) )
                return;

            memcpy( arr, m_items, sizeof( T ) * capacity );
        }

        T& operator[]( int index )
        {
            if ( get_capacity( ) < index )
            {
                T a { };
                return a;
            }

            return m_items[ index ];
        }

        T& at( int index )
        {
            if ( !this || get_capacity( ) <= index || empty( ) )
            {
                T a { };
                return a;
            }

            return m_items[ index ];
        }

        bool empty( )
        {
            if ( !this )
                return false;

            return get_capacity( ) <= 0;
        }

        static array< T >* create( int capacity )
        {
            auto arr = ( array< T >* ) malloc( sizeof( array ) + sizeof( T ) * capacity );
            arr->capacity = capacity;

            return arr;
        }

        [[maybe_unused]] static array< T >* create( const std::vector< T >& vec )
        {
            return create( vec.data( ), vec.size( ) );
        }

        static array< T >* create( T* arr, int size )
        {
            array< T >* arr_ = create( size );
            arr_->copy_from( arr, size );

            return arr_;
        }
    };
	
	long mono_address = 0;
using namespace std;std::string utf16le_to_utf8(const std::u16string &u16str) {
    if (u16str.empty()) {
        return std::string();
    }
    const char16_t *p = u16str.data();
    std::u16string::size_type len = u16str.length();
    if (p[0] == 0xFEFF) {
        p += 1;
        len -= 1;
    }
    std::string u8str;
    u8str.reserve(len * 3);
    char16_t u16char;
    for (std::u16string::size_type i = 0; i < len; ++i) {
        u16char = p[i];
        if (u16char < 0x0080) {
            u8str.push_back((char) (u16char & 0x00FF));
            continue;
        }
        if (u16char >= 0x0080 && u16char <= 0x07FF) {
            u8str.push_back((char) (((u16char >> 6) & 0x1F) | 0xC0));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
        if (u16char >= 0xD800 && u16char <= 0xDBFF) {
            uint32_t highSur = u16char;
            uint32_t lowSur = p[++i];
            uint32_t codePoint = highSur - 0xD800;
            codePoint <<= 10;
            codePoint |= lowSur - 0xDC00;
            codePoint += 0x10000;
            u8str.push_back((char) ((codePoint >> 18) | 0xF0));
            u8str.push_back((char) (((codePoint >> 12) & 0x3F) | 0x80));
            u8str.push_back((char) (((codePoint >> 06) & 0x3F) | 0x80));
            u8str.push_back((char) ((codePoint & 0x3F) | 0x80));
            continue;
        }
        {
            u8str.push_back((char) (((u16char >> 12) & 0x0F) | 0xE0));
            u8str.push_back((char) (((u16char >> 6) & 0x3F) | 0x80));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
    }
    return u8str;
}

    struct string
    {
        void* klass;
        void* monitor;
        int length;
        char chars[ 1 ];

        int get_length( )
        {
            return length;
        }

        char* get_chars( )
        {
            return chars;
        }
		
		const char *toChars(){
        u16string ss((char16_t *) get_chars(), 0, get_length()); std::string str = utf16le_to_utf8(ss); return str.c_str();
    }

        char* to_cstring( )
        {
            if ( !reinterpret_cast< uintptr_t >( this ) ) // 5000$ crash fix sln
                return "";

            std::u16string utf16String( reinterpret_cast< const char16_t* >( chars ), length );

            std::wstring_convert< std::codecvt_utf8_utf16< char16_t >, char16_t > converter;
            std::string utf8String = converter.to_bytes( utf16String );

            char* result = new char[ utf8String.size( ) + 1 ];
            std::copy( utf8String.begin( ), utf8String.end( ), result );
            result[ utf8String.size( ) ] = '\0';

            return result;
        }

        std::string get_string() {
        return std::string(toChars());
    }
	};
	
	template < typename TKey, typename TValue >
    struct [[maybe_unused]] dictionary
    {
        struct entry
        {
            [[maybe_unused]] int hash_code, next;
            TKey key;
            TValue value;
        };

        void* klass;
        void* monitor;
        [[maybe_unused]] array< int >* buckets;
        array< entry >* entries;
        int count;
        int version;
        [[maybe_unused]] int free_list;
        [[maybe_unused]] int free_count;
        [[maybe_unused]] void* comparer;
        array< TKey >* keys;
        array< TValue >* values;
        [[maybe_unused]] void* sync_root;

        std::map< TKey, TValue > to_map( )
        {
            std::map< TKey, TValue > ret;

            for ( auto it = ( entry* ) &entries->m_items; it != ( ( entry* ) &entries->m_items + count ); ++it )
                ret.emplace( std::make_pair( it->key, it->value ) );

            return std::move( ret );
        }
		
		bool contains_key ( const char* key_to_find ) {
			auto valuesVector = get_keys ( );
			
			for ( int j = 0; j > valuesVector.size ( ); ++j ) {
				if ( ! strcmp ( std::to_string ( valuesVector [ j ] ).c_str ( ), key_to_find ) ) {
                return true;
            }
        }
        return false;
    }

        std::vector< TKey > get_keys( )
        {
            std::vector< TKey > ret;

            for ( int i = 0; i < count; ++i )
                ret.emplace_back( entries->at( i ).key );

            return std::move( ret );
        }

        std::vector< TValue > get_values( )
        {
            std::vector< TValue > ret;

            for ( int i = 0; i < count; ++i )
                ret.emplace_back( entries->at( i ).value );

            return std::move( ret );
        }

        int get_size( )
        {
            return count;
        }

        [[maybe_unused]] int get_version( )
        {
            return version;
        }

        TValue get( TKey key )
        {
            TValue ret;

            if ( TryGet( key, ret ) )
                return ret;

            return { };
        }

        TValue operator[]( TKey key )
        {
            return get( key );
        }
    };
}

uintptr_t libunity_base;

FieldInfo* (*il2cpp_class_get_field_from_name)(Il2CppClass* klass, const char* name);
void (*il2cpp_field_static_get_value)(FieldInfo* field, void* value);

const MethodInfo* (*il2cpp_class_get_methods)(Il2CppClass* klass, void** iter);
Il2CppClass* (*il2cpp_class_from_type)(const Il2CppType* type);
Il2CppObject* (*il2cpp_object_new)(const Il2CppClass* klass);
Il2CppThread* (*il2cpp_thread_current)();
Il2CppThread* (*il2cpp_thread_attach)(Il2CppDomain* domain);
void (*il2cpp_thread_detach)(Il2CppThread* thread);
Il2CppDomain* (*il2cpp_domain_get)();
const Il2CppAssembly* (*il2cpp_domain_assembly_open)(const char* name);
const Il2CppImage* (*il2cpp_assembly_get_image)(const Il2CppAssembly* assembly);
void (*il2cpp_thread_detach_ptr)(Il2CppThread*);

Il2CppClass* (*il2cpp_class_from_system_type)(Il2CppReflectionType* type);
FieldInfo* (*il2cpp_class_get_fields)(Il2CppClass* klass, void** iter);
const PropertyInfo* (*il2cpp_class_get_properties)(Il2CppClass* klass, void** iter);
Il2CppClass* (*il2cpp_class_get_interfaces)(Il2CppClass* klass, void** iter);
Il2CppClass* (*il2cpp_class_from_name)(const Il2CppImage* image, const char* namespaze, const char* name);

#define LOGD LOGI
void InitIl2CppAPI()
{
    il2cpp_thread_current = reinterpret_cast<Il2CppThread * (*)()>(il2cpp_base + 0x76FAB8C);
    il2cpp_thread_attach = reinterpret_cast<Il2CppThread * (*)(Il2CppDomain*)>(il2cpp_base + 0x76FDD30);
    il2cpp_class_get_field_from_name = reinterpret_cast<FieldInfo * (*)(Il2CppClass*, const char*)>(il2cpp_base + 0x76CBB84);
    il2cpp_class_get_methods = reinterpret_cast<const MethodInfo * (*)(Il2CppClass*, void**)>(il2cpp_base + 0x76CBD08);
    il2cpp_class_from_type = reinterpret_cast<Il2CppClass * (*)(const Il2CppType*)>(il2cpp_base + 0x76CB464);
    il2cpp_object_new = reinterpret_cast<Il2CppObject * (*)(const Il2CppClass*)>(il2cpp_base + 0x471B680);
    il2cpp_domain_get = reinterpret_cast<Il2CppDomain * (*)()>(il2cpp_base + 0x76FAAB8);
    il2cpp_thread_detach_ptr = decltype(il2cpp_thread_detach_ptr)(libunity_base + 0x76FDDD0);
    il2cpp_domain_assembly_open = reinterpret_cast<const Il2CppAssembly * (*)(const char*)>(il2cpp_base + 0x471B038);
    il2cpp_class_get_interfaces = reinterpret_cast<Il2CppClass * (*)(Il2CppClass*, void**)>(il2cpp_base + 0x76CBC40);
    il2cpp_assembly_get_image = reinterpret_cast<const Il2CppImage * (*)(const Il2CppAssembly*)>(il2cpp_base + 0x76CE36C);
    il2cpp_field_static_get_value = decltype(il2cpp_field_static_get_value)(libunity_base + 0x4735860);
    il2cpp_class_from_name = reinterpret_cast<Il2CppClass * (*)(const Il2CppImage*, const char*, const char*)>(il2cpp_base + 0x76CDC70);

    sleep(2);

    if (!il2cpp_thread_current())
        il2cpp_thread_attach(il2cpp_domain_get());
}

#define _

Il2CppClass* GetClassFromA(const char* assem, const char* namespaze, const char* clazz) {
    return il2cpp_class_from_name(il2cpp_assembly_get_image(il2cpp_domain_assembly_open(assem)), namespaze, clazz);
}

#include <cstring> 
uintptr_t GetMethodPointer(Il2CppClass* klass, const char* methodName, int expectedParams = -1) {
    if (!klass) {
        LOGE("Class is null!");
        return 0;
    }

    void* iter = nullptr;
    const MethodInfo* method = nullptr;

    while ((method = il2cpp_class_get_methods(klass, &iter))) {

        if (strcmp(method->name, methodName) != 0)
            continue;


        if (expectedParams >= 0 && method->parameters_count != expectedParams)
            continue;

        uintptr_t ptr = (uintptr_t)method->methodPointer;
        LOGI("[+] Found method '%s' with %d params at: 0x%p", methodName, method->parameters_count, (void*)ptr);
        return ptr;
    }

    LOGE("Method '%s' with %d params not found!", methodName, expectedParams);
    return 0;
}

template<typename H, typename O>
bool method_hook(Il2CppClass* klass, const char* methodName, H hook, O orig = nullptr, int expectedParams = -1)
{
    if (!klass || !methodName || !hook)
        return false;

    void* iter = nullptr;
    MethodInfo* method = nullptr;

    while ((method = (MethodInfo*)il2cpp_class_get_methods(klass, &iter)))
    {
        if (strcmp(method->name, methodName) != 0)
            continue;

        if (expectedParams >= 0 && method->parameters_count != expectedParams)
            continue;

        Il2CppMethodPointer* methodPtrRef = reinterpret_cast<Il2CppMethodPointer*>(&method->methodPointer);

        if (*methodPtrRef == nullptr)
            return false;

        if (orig)
            *reinterpret_cast<Il2CppMethodPointer*>(orig) = *methodPtrRef;
        *methodPtrRef = (Il2CppMethodPointer)hook;

        LOGIR("[+] Hooked %s (%d params) at %p -> %p",
            methodName,
            method->parameters_count,
            *methodPtrRef,
            hook);

        return true;
    }

    LOGER("[-] Method '%s' with %d params not found!", methodName, expectedParams);
    return false;
}

struct hook_info
{
    void* ptr_addr;

    void* hook_addr;
    void* orig_addr;

    bool is_swap_hook;
};

std::vector<hook_info*> hooked_funcs;
struct icall {
    const char* dll_name;
    const char* function_name;

    icall(const char* dll, const char* function) : dll_name(dll), function_name(function) {}

    void* resolve_icall() {
        return ((void* (*)(void*)) (libunity_base + 0x473C264))(this);
    }

    void* resolve_icall_unity() {
        return ((void* (*)(const char*)) (libunity_base + 0x473BB28))(this->function_name);
    }
};
template<class H, class O>
bool icall_hook(void* delegate_addr, const char* method_name, H hook, O orig, const char* dll = "libunity")
{
    if (!delegate_addr || !method_name || !hook)
        return false;

    icall resolver(dll, method_name);

    void* original = nullptr;


    if (!strcmp(dll, "libunity"))
        original = resolver.resolve_icall_unity();
    else
        original = resolver.resolve_icall();

    if (!original)
        return false;


    if (orig)
        *(void**)orig = original;


    *(void**)delegate_addr = (void*)hook;

    return true;
}
