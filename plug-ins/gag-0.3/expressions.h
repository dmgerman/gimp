begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_EXPRESSIONS_H_
end_ifndef

begin_define
DECL|macro|_EXPRESSIONS_H_
define|#
directive|define
name|_EXPRESSIONS_H_
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG
end_ifdef

begin_define
DECL|macro|DPRINT (S)
define|#
directive|define
name|DPRINT
parameter_list|(
name|S
parameter_list|)
value|{ printf("Debug: %s\n",S); }
end_define

begin_define
DECL|macro|DMPRINT (S,I,J,K)
define|#
directive|define
name|DMPRINT
parameter_list|(
name|S
parameter_list|,
name|I
parameter_list|,
name|J
parameter_list|,
name|K
parameter_list|)
value|{ printf(S,I,J,K); }
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|DPRINT (S)
define|#
directive|define
name|DPRINT
parameter_list|(
name|S
parameter_list|)
end_define

begin_define
DECL|macro|DMPRINT (SI,J,K)
define|#
directive|define
name|DMPRINT
parameter_list|(
name|SI
parameter_list|,
name|J
parameter_list|,
name|K
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|INFINITY
define|#
directive|define
name|INFINITY
value|1e100
end_define

begin_define
DECL|macro|MAX_NUMBER_OF_PARAMETERS
define|#
directive|define
name|MAX_NUMBER_OF_PARAMETERS
value|10
end_define

begin_define
DECL|macro|MAX_TREE_DEPTH
define|#
directive|define
name|MAX_TREE_DEPTH
value|20
end_define

begin_define
DECL|macro|MAX_STACK_ENTRIES
define|#
directive|define
name|MAX_STACK_ENTRIES
value|1000
end_define

begin_comment
DECL|macro|MAX_STACK_ENTRIES
comment|/* max number of operators in one expression  							 I hope it is enough :-)			*/
end_comment

begin_typedef
DECL|typedef|DBL
typedef|typedef
name|double
name|DBL
typedef|;
end_typedef

begin_typedef
DECL|typedef|NODE
typedef|typedef
name|struct
name|expr_node_struct
name|NODE
typedef|;
end_typedef

begin_typedef
DECL|typedef|FUNC_INFO
typedef|typedef
name|struct
name|func_info_struct
name|FUNC_INFO
typedef|;
end_typedef

begin_typedef
DECL|typedef|func_type
typedef|typedef
name|void
function_decl|(
name|func_type
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|expr_func
typedef|typedef
name|func_type
argument_list|(
operator|*
name|expr_func
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
end_typedef

begin_struct
DECL|struct|func_info_struct
struct|struct
name|func_info_struct
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|nofp
name|char
name|nofp
decl_stmt|;
comment|/* number of parameters,  nofp< 0 -=> arbitrary number of parameters */
DECL|member|nofd
name|char
name|nofd
decl_stmt|;
comment|/* number of data entries (doubles) - for vectors and doubles	nofp==0 || nofd==0 */
DECL|member|ret_type
name|char
name|ret_type
decl_stmt|;
comment|/* type of return: 1,3,4, -1 (whatever) */
DECL|member|paramtypes
name|char
modifier|*
name|paramtypes
decl_stmt|;
DECL|member|funcs
name|expr_func
modifier|*
name|funcs
decl_stmt|;
DECL|member|last_func
name|expr_func
name|last_func
decl_stmt|;
comment|/* this function is inserted to the stack as last... */
block|}
struct|;
end_struct

begin_struct
DECL|struct|expr_node_struct
struct|struct
name|expr_node_struct
block|{
DECL|member|op
name|FUNC_INFO
modifier|*
name|op
decl_stmt|;
DECL|member|data
name|DBL
name|data
index|[
literal|4
index|]
decl_stmt|;
comment|/* float values - such as constants and vectors ((rgb) or (rgbt) vectors) */
DECL|member|offsprings
name|NODE
modifier|*
name|offsprings
index|[
name|MAX_NUMBER_OF_PARAMETERS
index|]
decl_stmt|;
comment|/* too lazy to mallocate.... */
DECL|member|noo
name|int
name|noo
decl_stmt|;
comment|/* number of offsprings in expression tree */
DECL|member|tof
name|char
name|tof
decl_stmt|;
comment|/* type of return,.. */
block|}
struct|;
end_struct

begin_struct
DECL|struct|expr_compiled_struct
struct|struct
name|expr_compiled_struct
block|{
DECL|member|funcs
name|func_type
modifier|*
name|funcs
decl_stmt|;
DECL|member|data
name|DBL
modifier|*
name|data
decl_stmt|;
DECL|member|nodes
name|NODE
modifier|*
name|nodes
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|FUNC_INFO
name|FuncInfo
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|Number_of_Functions
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|DBL
name|x_val
decl_stmt|,
name|y_val
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|eval_xy
parameter_list|(
name|DBL
modifier|*
parameter_list|,
name|DBL
parameter_list|,
name|DBL
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|prepare_node
parameter_list|(
name|NODE
modifier|*
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|NODE
modifier|*
name|node_copy
parameter_list|(
name|NODE
modifier|*
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|destroy_node
parameter_list|(
name|NODE
modifier|*
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|expr_fprint
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|int
parameter_list|,
name|NODE
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|expr_sprint
parameter_list|(
name|char
modifier|*
name|s
parameter_list|,
name|NODE
modifier|*
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*          Some useful functions */
end_comment

begin_function_decl
name|NODE
modifier|*
name|parse_prefix_expression
parameter_list|(
name|char
modifier|*
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|dblrand
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|init_random
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|expr_init
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|solid_noise
parameter_list|(
name|DBL
parameter_list|,
name|DBL
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|double_and
parameter_list|(
name|DBL
name|p1
parameter_list|,
name|DBL
name|p2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|double_xor
parameter_list|(
name|DBL
name|p1
parameter_list|,
name|DBL
name|p2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|double_or
parameter_list|(
name|DBL
name|p1
parameter_list|,
name|DBL
name|p2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* this pointers are necessary for computation */
end_comment

begin_decl_stmt
specifier|extern
name|NODE
modifier|*
modifier|*
name|n_top
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|DBL
modifier|*
name|r_top
decl_stmt|,
modifier|*
name|g_top
decl_stmt|,
modifier|*
name|b_top
decl_stmt|,
modifier|*
name|alfa_top
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|DBL
modifier|*
name|data_top
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* wrapping functions - serve to project interval<-infty,infty> into<0..255> */
end_comment

begin_comment
comment|/* simple: real to color... */
end_comment

begin_function_decl
specifier|extern
name|unsigned
name|char
function_decl|(
modifier|*
name|wrap_func
function_decl|)
parameter_list|(
name|DBL
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|unsigned
name|char
name|wrap_func_cut
parameter_list|(
name|DBL
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|unsigned
name|char
name|wrap_func_rep
parameter_list|(
name|DBL
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|unsigned
name|char
name|wrap_func_pingpong
parameter_list|(
name|DBL
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

