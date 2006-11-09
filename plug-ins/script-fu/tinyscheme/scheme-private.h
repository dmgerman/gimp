begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* scheme-private.h */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_SCHEME_PRIVATE_H
end_ifndef

begin_define
DECL|macro|_SCHEME_PRIVATE_H
define|#
directive|define
name|_SCHEME_PRIVATE_H
end_define

begin_include
include|#
directive|include
file|"scheme.h"
end_include

begin_comment
comment|/*------------------ Ugly internals -----------------------------------*/
end_comment

begin_comment
comment|/*------------------ Of interest only to FFI users --------------------*/
end_comment

begin_comment
comment|/* macros for cell operations */
end_comment

begin_define
DECL|macro|arrayvalue (p)
define|#
directive|define
name|arrayvalue
parameter_list|(
name|p
parameter_list|)
value|((p)->_object._array._avalue)
end_define

begin_define
DECL|macro|arraylength (p)
define|#
directive|define
name|arraylength
parameter_list|(
name|p
parameter_list|)
value|((p)->_object._array._length)
end_define

begin_define
DECL|macro|arraytype (p)
define|#
directive|define
name|arraytype
parameter_list|(
name|p
parameter_list|)
value|((p)->_object._array._type)
end_define

begin_enum
DECL|enum|array_type
enum|enum
name|array_type
block|{
DECL|enumerator|array_int32
name|array_int32
init|=
literal|0
block|,
DECL|enumerator|array_int16
name|array_int16
init|=
literal|1
block|,
DECL|enumerator|array_int8
name|array_int8
init|=
literal|2
block|,
DECL|enumerator|array_float
name|array_float
init|=
literal|3
block|,
DECL|enumerator|array_string
name|array_string
init|=
literal|4
block|}
enum|;
end_enum

begin_enum
DECL|enum|scheme_port_kind
enum|enum
name|scheme_port_kind
block|{
DECL|enumerator|port_free
name|port_free
init|=
literal|0
block|,
DECL|enumerator|port_file
name|port_file
init|=
literal|1
block|,
DECL|enumerator|port_string
name|port_string
init|=
literal|2
block|,
DECL|enumerator|port_input
name|port_input
init|=
literal|16
block|,
DECL|enumerator|port_output
name|port_output
init|=
literal|32
block|}
enum|;
end_enum

begin_typedef
DECL|struct|port
typedef|typedef
struct|struct
name|port
block|{
DECL|member|kind
name|unsigned
name|char
name|kind
decl_stmt|;
DECL|union|__anon2779e656010a
union|union
block|{
DECL|struct|__anon2779e6560208
struct|struct
block|{
DECL|member|file
name|FILE
modifier|*
name|file
decl_stmt|;
DECL|member|closeit
name|int
name|closeit
decl_stmt|;
DECL|member|stdio
block|}
name|stdio
struct|;
DECL|struct|__anon2779e6560308
struct|struct
block|{
DECL|member|start
name|char
modifier|*
name|start
decl_stmt|;
DECL|member|past_the_end
name|char
modifier|*
name|past_the_end
decl_stmt|;
DECL|member|curr
name|char
modifier|*
name|curr
decl_stmt|;
DECL|member|string
block|}
name|string
struct|;
DECL|member|rep
block|}
name|rep
union|;
DECL|typedef|port
block|}
name|port
typedef|;
end_typedef

begin_comment
comment|/* cell structure */
end_comment

begin_struct
DECL|struct|cell
struct|struct
name|cell
block|{
DECL|member|_flag
name|unsigned
name|int
name|_flag
decl_stmt|;
DECL|union|__anon2779e656040a
union|union
block|{
DECL|struct|__anon2779e6560508
struct|struct
block|{
DECL|member|_avalue
name|void
modifier|*
name|_avalue
decl_stmt|;
DECL|member|_length
name|int
name|_length
decl_stmt|;
DECL|member|_type
name|int
name|_type
decl_stmt|;
DECL|member|_array
block|}
name|_array
struct|;
DECL|struct|__anon2779e6560608
struct|struct
block|{
DECL|member|_svalue
name|char
modifier|*
name|_svalue
decl_stmt|;
DECL|member|_length
name|int
name|_length
decl_stmt|;
DECL|member|_string
block|}
name|_string
struct|;
DECL|member|_number
name|num
name|_number
decl_stmt|;
DECL|member|_port
name|port
modifier|*
name|_port
decl_stmt|;
DECL|member|_ff
name|foreign_func
name|_ff
decl_stmt|;
DECL|struct|__anon2779e6560708
struct|struct
block|{
DECL|member|_car
name|struct
name|cell
modifier|*
name|_car
decl_stmt|;
DECL|member|_cdr
name|struct
name|cell
modifier|*
name|_cdr
decl_stmt|;
DECL|member|_cons
block|}
name|_cons
struct|;
DECL|member|_object
block|}
name|_object
union|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|scheme
struct|struct
name|scheme
block|{
comment|/* arrays for segments */
DECL|member|malloc
name|func_alloc
name|malloc
decl_stmt|;
DECL|member|free
name|func_dealloc
name|free
decl_stmt|;
comment|/* return code */
DECL|member|retcode
name|int
name|retcode
decl_stmt|;
DECL|member|tracing
name|int
name|tracing
decl_stmt|;
DECL|macro|CELL_SEGSIZE
define|#
directive|define
name|CELL_SEGSIZE
value|5000
comment|/* # of cells in one segment */
DECL|macro|CELL_NSEGMENT
define|#
directive|define
name|CELL_NSEGMENT
value|20
comment|/* # of segments for cells */
DECL|member|alloc_seg
name|char
modifier|*
name|alloc_seg
index|[
name|CELL_NSEGMENT
index|]
decl_stmt|;
DECL|member|cell_seg
name|pointer
name|cell_seg
index|[
name|CELL_NSEGMENT
index|]
decl_stmt|;
DECL|member|last_cell_seg
name|int
name|last_cell_seg
decl_stmt|;
comment|/* We use 4 registers. */
DECL|member|args
name|pointer
name|args
decl_stmt|;
comment|/* register for arguments of function */
DECL|member|envir
name|pointer
name|envir
decl_stmt|;
comment|/* stack register for current environment */
DECL|member|code
name|pointer
name|code
decl_stmt|;
comment|/* register for current code */
DECL|member|dump
name|pointer
name|dump
decl_stmt|;
comment|/* stack register for next evaluation */
DECL|member|interactive_repl
name|int
name|interactive_repl
decl_stmt|;
comment|/* are we in an interactive REPL? */
DECL|member|print_output
name|int
name|print_output
decl_stmt|;
comment|/* set to 1 to print results and error messages */
DECL|member|print_error
name|int
name|print_error
decl_stmt|;
comment|/* set to 1 while printing error messages */
DECL|member|_sink
name|struct
name|cell
name|_sink
decl_stmt|;
DECL|member|sink
name|pointer
name|sink
decl_stmt|;
comment|/* when mem. alloc. fails */
DECL|member|_NIL
name|struct
name|cell
name|_NIL
decl_stmt|;
DECL|member|NIL
name|pointer
name|NIL
decl_stmt|;
comment|/* special cell representing empty cell */
DECL|member|_HASHT
name|struct
name|cell
name|_HASHT
decl_stmt|;
DECL|member|T
name|pointer
name|T
decl_stmt|;
comment|/* special cell representing #t */
DECL|member|_HASHF
name|struct
name|cell
name|_HASHF
decl_stmt|;
DECL|member|F
name|pointer
name|F
decl_stmt|;
comment|/* special cell representing #f */
DECL|member|_EOF_OBJ
name|struct
name|cell
name|_EOF_OBJ
decl_stmt|;
DECL|member|EOF_OBJ
name|pointer
name|EOF_OBJ
decl_stmt|;
comment|/* special cell representing end-of-file object */
DECL|member|oblist
name|pointer
name|oblist
decl_stmt|;
comment|/* pointer to symbol table */
DECL|member|global_env
name|pointer
name|global_env
decl_stmt|;
comment|/* pointer to global environment */
comment|/* global pointers to special symbols */
DECL|member|LAMBDA
name|pointer
name|LAMBDA
decl_stmt|;
comment|/* pointer to syntax lambda */
DECL|member|QUOTE
name|pointer
name|QUOTE
decl_stmt|;
comment|/* pointer to syntax quote */
DECL|member|QQUOTE
name|pointer
name|QQUOTE
decl_stmt|;
comment|/* pointer to symbol quasiquote */
DECL|member|UNQUOTE
name|pointer
name|UNQUOTE
decl_stmt|;
comment|/* pointer to symbol unquote */
DECL|member|UNQUOTESP
name|pointer
name|UNQUOTESP
decl_stmt|;
comment|/* pointer to symbol unquote-splicing */
DECL|member|FEED_TO
name|pointer
name|FEED_TO
decl_stmt|;
comment|/* => */
DECL|member|COLON_HOOK
name|pointer
name|COLON_HOOK
decl_stmt|;
comment|/* *colon-hook* */
DECL|member|ERROR_HOOK
name|pointer
name|ERROR_HOOK
decl_stmt|;
comment|/* *error-hook* */
DECL|member|SHARP_HOOK
name|pointer
name|SHARP_HOOK
decl_stmt|;
comment|/* *sharp-hook* */
DECL|member|free_cell
name|pointer
name|free_cell
decl_stmt|;
comment|/* pointer to top of free cells */
DECL|member|fcells
name|long
name|fcells
decl_stmt|;
comment|/* # of free cells */
DECL|member|inport
name|pointer
name|inport
decl_stmt|;
DECL|member|outport
name|pointer
name|outport
decl_stmt|;
DECL|member|save_inport
name|pointer
name|save_inport
decl_stmt|;
DECL|member|loadport
name|pointer
name|loadport
decl_stmt|;
DECL|macro|MAXFIL
define|#
directive|define
name|MAXFIL
value|64
DECL|member|load_stack
name|port
name|load_stack
index|[
name|MAXFIL
index|]
decl_stmt|;
comment|/* Stack of open files for port -1 (LOADing) */
DECL|member|nesting_stack
name|int
name|nesting_stack
index|[
name|MAXFIL
index|]
decl_stmt|;
DECL|member|file_i
name|int
name|file_i
decl_stmt|;
DECL|member|nesting
name|int
name|nesting
decl_stmt|;
DECL|member|gc_verbose
name|char
name|gc_verbose
decl_stmt|;
comment|/* if gc_verbose is not zero, print gc status */
DECL|member|no_memory
name|char
name|no_memory
decl_stmt|;
comment|/* Whether mem. alloc. has failed */
DECL|macro|LINESIZE
define|#
directive|define
name|LINESIZE
value|1024
DECL|member|linebuff
name|char
name|linebuff
index|[
name|LINESIZE
index|]
decl_stmt|;
DECL|member|strbuff
name|char
name|strbuff
index|[
name|LINESIZE
index|]
decl_stmt|;
DECL|member|tmpfp
name|FILE
modifier|*
name|tmpfp
decl_stmt|;
DECL|member|tok
name|int
name|tok
decl_stmt|;
DECL|member|print_flag
name|int
name|print_flag
decl_stmt|;
DECL|member|value
name|pointer
name|value
decl_stmt|;
DECL|member|op
name|int
name|op
decl_stmt|;
DECL|member|ext_data
name|void
modifier|*
name|ext_data
decl_stmt|;
comment|/* For the benefit of foreign functions */
DECL|member|gensym_cnt
name|long
name|gensym_cnt
decl_stmt|;
DECL|member|vptr
name|struct
name|scheme_interface
modifier|*
name|vptr
decl_stmt|;
DECL|member|dump_base
name|void
modifier|*
name|dump_base
decl_stmt|;
comment|/* pointer to base of allocated dump stack */
DECL|member|dump_size
name|int
name|dump_size
decl_stmt|;
comment|/* number of frames allocated for dump stack */
DECL|member|backchar
name|gunichar
name|backchar
decl_stmt|;
DECL|member|bc_flag
name|int
name|bc_flag
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* operator code */
end_comment

begin_enum
DECL|enum|scheme_opcodes
enum|enum
name|scheme_opcodes
block|{
DECL|macro|_OP_DEF (A,B,C,D,E,OP)
define|#
directive|define
name|_OP_DEF
parameter_list|(
name|A
parameter_list|,
name|B
parameter_list|,
name|C
parameter_list|,
name|D
parameter_list|,
name|E
parameter_list|,
name|OP
parameter_list|)
value|OP,
include|#
directive|include
file|"opdefines.h"
DECL|enumerator|OP_MAXDEFINED
name|OP_MAXDEFINED
block|}
enum|;
end_enum

begin_define
DECL|macro|cons (sc,a,b)
define|#
directive|define
name|cons
parameter_list|(
name|sc
parameter_list|,
name|a
parameter_list|,
name|b
parameter_list|)
value|_cons(sc,a,b,0)
end_define

begin_define
DECL|macro|immutable_cons (sc,a,b)
define|#
directive|define
name|immutable_cons
parameter_list|(
name|sc
parameter_list|,
name|a
parameter_list|,
name|b
parameter_list|)
value|_cons(sc,a,b,1)
end_define

begin_function_decl
name|int
name|is_string
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|string_value
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_number
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|num
name|nvalue
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|long
name|ivalue
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|double
name|rvalue
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_integer
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_real
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_array
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_character
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|string_length
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gunichar
name|charvalue
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_vector
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_port
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_pair
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|pair_car
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|pair_cdr
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|set_car
parameter_list|(
name|pointer
name|p
parameter_list|,
name|pointer
name|q
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|set_cdr
parameter_list|(
name|pointer
name|p
parameter_list|,
name|pointer
name|q
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_symbol
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|symname
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|hasprop
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_syntax
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_proc
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_foreign
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|syntaxname
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_closure
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_macro
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|closure_code
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|pointer
name|closure_env
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_continuation
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_promise
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_environment
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|is_immutable
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|setimmutable
parameter_list|(
name|pointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

