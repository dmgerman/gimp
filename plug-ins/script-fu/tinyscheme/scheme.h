begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* SCHEME.H */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_SCHEME_H
end_ifndef

begin_define
DECL|macro|_SCHEME_H
define|#
directive|define
name|_SCHEME_H
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/*  * Default values for #define'd symbols  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|STANDALONE
end_ifndef

begin_comment
comment|/* If used as standalone interpreter */
end_comment

begin_define
DECL|macro|STANDALONE
define|#
directive|define
name|STANDALONE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|_MSC_VER
end_ifndef

begin_define
DECL|macro|SCHEME_EXPORT
define|#
directive|define
name|SCHEME_EXPORT
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|USE_STRCASECMP
define|#
directive|define
name|USE_STRCASECMP
value|0
end_define

begin_define
DECL|macro|USE_STRLWR
define|#
directive|define
name|USE_STRLWR
value|0
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|_SCHEME_SOURCE
end_ifdef

begin_define
DECL|macro|SCHEME_EXPORT
define|#
directive|define
name|SCHEME_EXPORT
value|__declspec(dllexport)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|SCHEME_EXPORT
define|#
directive|define
name|SCHEME_EXPORT
value|__declspec(dllimport)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
name|USE_NO_FEATURES
end_if

begin_define
DECL|macro|USE_MATH
define|#
directive|define
name|USE_MATH
value|0
end_define

begin_define
DECL|macro|USE_CHAR_CLASSIFIERS
define|#
directive|define
name|USE_CHAR_CLASSIFIERS
value|0
end_define

begin_define
DECL|macro|USE_ASCII_NAMES
define|#
directive|define
name|USE_ASCII_NAMES
value|0
end_define

begin_define
DECL|macro|USE_STRING_PORTS
define|#
directive|define
name|USE_STRING_PORTS
value|0
end_define

begin_define
DECL|macro|USE_ERROR_HOOK
define|#
directive|define
name|USE_ERROR_HOOK
value|0
end_define

begin_define
DECL|macro|USE_TRACING
define|#
directive|define
name|USE_TRACING
value|0
end_define

begin_define
DECL|macro|USE_COLON_HOOK
define|#
directive|define
name|USE_COLON_HOOK
value|0
end_define

begin_define
DECL|macro|USE_DL
define|#
directive|define
name|USE_DL
value|0
end_define

begin_define
DECL|macro|USE_PLIST
define|#
directive|define
name|USE_PLIST
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * Leave it defined if you want continuations, and also for the Sharp Zaurus.  * Undefine it if you only care about faster speed and not strict Scheme compatibility.  */
end_comment

begin_define
DECL|macro|USE_SCHEME_STACK
define|#
directive|define
name|USE_SCHEME_STACK
end_define

begin_if
if|#
directive|if
name|USE_DL
end_if

begin_define
DECL|macro|USE_INTERFACE
define|#
directive|define
name|USE_INTERFACE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_MATH
end_ifndef

begin_comment
comment|/* If math support is needed */
end_comment

begin_define
DECL|macro|USE_MATH
define|#
directive|define
name|USE_MATH
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_CHAR_CLASSIFIERS
end_ifndef

begin_comment
comment|/* If char classifiers are needed */
end_comment

begin_define
DECL|macro|USE_CHAR_CLASSIFIERS
define|#
directive|define
name|USE_CHAR_CLASSIFIERS
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_ASCII_NAMES
end_ifndef

begin_comment
comment|/* If extended escaped characters are needed */
end_comment

begin_define
DECL|macro|USE_ASCII_NAMES
define|#
directive|define
name|USE_ASCII_NAMES
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_STRING_PORTS
end_ifndef

begin_comment
comment|/* Enable string ports */
end_comment

begin_define
DECL|macro|USE_STRING_PORTS
define|#
directive|define
name|USE_STRING_PORTS
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_TRACING
end_ifndef

begin_define
DECL|macro|USE_TRACING
define|#
directive|define
name|USE_TRACING
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_PLIST
end_ifndef

begin_define
DECL|macro|USE_PLIST
define|#
directive|define
name|USE_PLIST
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* To force system errors through user-defined error handling (see *error-hook*) */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|USE_ERROR_HOOK
end_ifndef

begin_define
DECL|macro|USE_ERROR_HOOK
define|#
directive|define
name|USE_ERROR_HOOK
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_COLON_HOOK
end_ifndef

begin_comment
comment|/* Enable qualified qualifier */
end_comment

begin_define
DECL|macro|USE_COLON_HOOK
define|#
directive|define
name|USE_COLON_HOOK
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_STRCASECMP
end_ifndef

begin_comment
comment|/* stricmp for Unix */
end_comment

begin_define
DECL|macro|USE_STRCASECMP
define|#
directive|define
name|USE_STRCASECMP
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_STRLWR
end_ifndef

begin_define
DECL|macro|USE_STRLWR
define|#
directive|define
name|USE_STRLWR
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|STDIO_ADDS_CR
end_ifndef

begin_comment
comment|/* Define if DOS/Windows */
end_comment

begin_define
DECL|macro|STDIO_ADDS_CR
define|#
directive|define
name|STDIO_ADDS_CR
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|INLINE
end_ifndef

begin_define
DECL|macro|INLINE
define|#
directive|define
name|INLINE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|USE_INTERFACE
end_ifndef

begin_define
DECL|macro|USE_INTERFACE
define|#
directive|define
name|USE_INTERFACE
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|scheme
typedef|typedef
name|struct
name|scheme
name|scheme
typedef|;
end_typedef

begin_typedef
DECL|typedef|pointer
typedef|typedef
name|struct
name|cell
modifier|*
name|pointer
typedef|;
end_typedef

begin_typedef
DECL|typedef|func_alloc
typedef|typedef
name|void
modifier|*
function_decl|(
modifier|*
name|func_alloc
function_decl|)
parameter_list|(
name|size_t
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|func_dealloc
typedef|typedef
name|void
function_decl|(
modifier|*
name|func_dealloc
function_decl|)
parameter_list|(
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* num, for generic arithmetic */
end_comment

begin_typedef
DECL|struct|num
typedef|typedef
struct|struct
name|num
block|{
DECL|member|is_fixnum
name|char
name|is_fixnum
decl_stmt|;
DECL|union|__anon2b9e1548010a
union|union
block|{
DECL|member|ivalue
name|long
name|ivalue
decl_stmt|;
DECL|member|rvalue
name|double
name|rvalue
decl_stmt|;
DECL|member|value
block|}
name|value
union|;
DECL|typedef|num
block|}
name|num
typedef|;
end_typedef

begin_function_decl
name|SCHEME_EXPORT
name|scheme
modifier|*
name|scheme_init_new
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|scheme
modifier|*
name|scheme_init_new_custom_alloc
parameter_list|(
name|func_alloc
name|malloc
parameter_list|,
name|func_dealloc
name|free
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|int
name|scheme_init
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|int
name|scheme_init_custom_alloc
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|func_alloc
parameter_list|,
name|func_dealloc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|void
name|scheme_deinit
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|scheme_set_input_port_file
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|FILE
modifier|*
name|fin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|scheme_set_input_port_string
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|char
modifier|*
name|start
parameter_list|,
name|char
modifier|*
name|past_the_end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|void
name|scheme_set_output_port_file
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|FILE
modifier|*
name|fin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|scheme_set_output_port_string
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|char
modifier|*
name|start
parameter_list|,
name|char
modifier|*
name|past_the_end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|void
name|scheme_load_file
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|FILE
modifier|*
name|fin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|void
name|scheme_load_string
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|cmd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|scheme_apply0
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|procname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|pointer
name|scheme_apply1
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|procname
parameter_list|,
name|pointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|scheme_set_external_data
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|void
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|SCHEME_EXPORT
name|void
name|scheme_define
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|env
parameter_list|,
name|pointer
name|symbol
parameter_list|,
name|pointer
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|foreign_func
typedef|typedef
name|pointer
function_decl|(
modifier|*
name|foreign_func
function_decl|)
parameter_list|(
name|scheme
modifier|*
parameter_list|,
name|pointer
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|pointer
name|_cons
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|,
name|pointer
name|b
parameter_list|,
name|int
name|immutable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|mk_integer
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|long
name|num
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|mk_real
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|double
name|num
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|mk_symbol
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|gensym
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|mk_string
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|mk_counted_string
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|str
parameter_list|,
name|int
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|mk_character
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|gunichar
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|mk_foreign_func
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|foreign_func
name|f
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|putstr
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
name|USE_INTERFACE
end_if

begin_struct
DECL|struct|scheme_interface
struct|struct
name|scheme_interface
block|{
DECL|member|scheme_define
name|void
function_decl|(
modifier|*
name|scheme_define
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|env
parameter_list|,
name|pointer
name|symbol
parameter_list|,
name|pointer
name|value
parameter_list|)
function_decl|;
DECL|member|cons
name|pointer
function_decl|(
modifier|*
name|cons
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|,
name|pointer
name|b
parameter_list|)
function_decl|;
DECL|member|immutable_cons
name|pointer
function_decl|(
modifier|*
name|immutable_cons
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|,
name|pointer
name|b
parameter_list|)
function_decl|;
DECL|member|reserve_cells
name|pointer
function_decl|(
modifier|*
name|reserve_cells
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|int
name|n
parameter_list|)
function_decl|;
DECL|member|mk_integer
name|pointer
function_decl|(
modifier|*
name|mk_integer
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|long
name|num
parameter_list|)
function_decl|;
DECL|member|mk_real
name|pointer
function_decl|(
modifier|*
name|mk_real
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|double
name|num
parameter_list|)
function_decl|;
DECL|member|mk_symbol
name|pointer
function_decl|(
modifier|*
name|mk_symbol
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
DECL|member|gensym
name|pointer
function_decl|(
modifier|*
name|gensym
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|)
function_decl|;
DECL|member|mk_string
name|pointer
function_decl|(
modifier|*
name|mk_string
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|str
parameter_list|)
function_decl|;
DECL|member|mk_counted_string
name|pointer
function_decl|(
modifier|*
name|mk_counted_string
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|str
parameter_list|,
name|int
name|len
parameter_list|)
function_decl|;
DECL|member|mk_character
name|pointer
function_decl|(
modifier|*
name|mk_character
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|gunichar
name|c
parameter_list|)
function_decl|;
DECL|member|mk_vector
name|pointer
function_decl|(
modifier|*
name|mk_vector
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|int
name|len
parameter_list|)
function_decl|;
DECL|member|mk_array
name|pointer
function_decl|(
modifier|*
name|mk_array
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|int
name|len
parameter_list|,
name|int
name|type
parameter_list|)
function_decl|;
DECL|member|mk_foreign_func
name|pointer
function_decl|(
modifier|*
name|mk_foreign_func
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|foreign_func
name|f
parameter_list|)
function_decl|;
DECL|member|mk_closure
name|pointer
function_decl|(
modifier|*
name|mk_closure
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|c
parameter_list|,
name|pointer
name|e
parameter_list|)
function_decl|;
DECL|member|putstr
name|void
function_decl|(
modifier|*
name|putstr
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|s
parameter_list|)
function_decl|;
DECL|member|putcharacter
name|void
function_decl|(
modifier|*
name|putcharacter
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|gunichar
name|c
parameter_list|)
function_decl|;
DECL|member|is_string
name|int
function_decl|(
modifier|*
name|is_string
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|string_length
name|int
function_decl|(
modifier|*
name|string_length
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|string_value
name|char
modifier|*
function_decl|(
modifier|*
name|string_value
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_number
name|int
function_decl|(
modifier|*
name|is_number
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|nvalue
name|num
function_decl|(
modifier|*
name|nvalue
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|ivalue
name|long
function_decl|(
modifier|*
name|ivalue
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|rvalue
name|double
function_decl|(
modifier|*
name|rvalue
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_integer
name|int
function_decl|(
modifier|*
name|is_integer
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_real
name|int
function_decl|(
modifier|*
name|is_real
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_character
name|int
function_decl|(
modifier|*
name|is_character
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|charvalue
name|gunichar
function_decl|(
modifier|*
name|charvalue
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_list
name|int
function_decl|(
modifier|*
name|is_list
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_vector
name|int
function_decl|(
modifier|*
name|is_vector
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|list_length
name|int
function_decl|(
modifier|*
name|list_length
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|)
function_decl|;
DECL|member|vector_length
name|long
function_decl|(
modifier|*
name|vector_length
function_decl|)
parameter_list|(
name|pointer
name|vec
parameter_list|)
function_decl|;
DECL|member|fill_vector
name|void
function_decl|(
modifier|*
name|fill_vector
function_decl|)
parameter_list|(
name|pointer
name|vec
parameter_list|,
name|pointer
name|elem
parameter_list|)
function_decl|;
DECL|member|vector_elem
name|pointer
function_decl|(
modifier|*
name|vector_elem
function_decl|)
parameter_list|(
name|pointer
name|vec
parameter_list|,
name|int
name|ielem
parameter_list|)
function_decl|;
DECL|member|set_vector_elem
name|pointer
function_decl|(
modifier|*
name|set_vector_elem
function_decl|)
parameter_list|(
name|pointer
name|vec
parameter_list|,
name|int
name|ielem
parameter_list|,
name|pointer
name|newel
parameter_list|)
function_decl|;
DECL|member|is_array
name|int
function_decl|(
modifier|*
name|is_array
function_decl|)
parameter_list|(
name|pointer
name|a
parameter_list|)
function_decl|;
DECL|member|array_elem
name|pointer
function_decl|(
modifier|*
name|array_elem
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|,
name|int
name|ielem
parameter_list|)
function_decl|;
DECL|member|set_array_elem
name|pointer
function_decl|(
modifier|*
name|set_array_elem
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|a
parameter_list|,
name|int
name|ielem
parameter_list|,
name|pointer
name|newel
parameter_list|)
function_decl|;
DECL|member|is_port
name|int
function_decl|(
modifier|*
name|is_port
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_pair
name|int
function_decl|(
modifier|*
name|is_pair
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|pair_car
name|pointer
function_decl|(
modifier|*
name|pair_car
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|pair_cdr
name|pointer
function_decl|(
modifier|*
name|pair_cdr
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|set_car
name|pointer
function_decl|(
modifier|*
name|set_car
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|,
name|pointer
name|q
parameter_list|)
function_decl|;
DECL|member|set_cdr
name|pointer
function_decl|(
modifier|*
name|set_cdr
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|,
name|pointer
name|q
parameter_list|)
function_decl|;
DECL|member|is_symbol
name|int
function_decl|(
modifier|*
name|is_symbol
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|symname
name|char
modifier|*
function_decl|(
modifier|*
name|symname
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_syntax
name|int
function_decl|(
modifier|*
name|is_syntax
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_proc
name|int
function_decl|(
modifier|*
name|is_proc
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_foreign
name|int
function_decl|(
modifier|*
name|is_foreign
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|syntaxname
name|char
modifier|*
function_decl|(
modifier|*
name|syntaxname
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_closure
name|int
function_decl|(
modifier|*
name|is_closure
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_macro
name|int
function_decl|(
modifier|*
name|is_macro
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|closure_code
name|pointer
function_decl|(
modifier|*
name|closure_code
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|closure_env
name|pointer
function_decl|(
modifier|*
name|closure_env
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_continuation
name|int
function_decl|(
modifier|*
name|is_continuation
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_promise
name|int
function_decl|(
modifier|*
name|is_promise
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_environment
name|int
function_decl|(
modifier|*
name|is_environment
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|is_immutable
name|int
function_decl|(
modifier|*
name|is_immutable
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|setimmutable
name|void
function_decl|(
modifier|*
name|setimmutable
function_decl|)
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
DECL|member|load_file
name|void
function_decl|(
modifier|*
name|load_file
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|FILE
modifier|*
name|fin
parameter_list|)
function_decl|;
DECL|member|load_string
name|void
function_decl|(
modifier|*
name|load_string
function_decl|)
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
specifier|const
name|char
modifier|*
name|input
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit

