begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_GAS_H_
end_ifndef

begin_define
DECL|macro|_GAS_H_
define|#
directive|define
name|_GAS_H_
end_define

begin_include
include|#
directive|include
file|"expressions.h"
end_include

begin_decl_stmt
specifier|extern
name|int
name|expression_max_depth
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|DBL
name|gas_const_prob
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|DBL
function_decl|(
modifier|*
name|gas_leaf_probability
function_decl|)
parameter_list|(
name|int
name|depth
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* determines if end expression now or not */
end_comment

begin_function_decl
specifier|extern
name|DBL
function_decl|(
modifier|*
name|gas_operator_weight
function_decl|)
parameter_list|(
name|int
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* weight of operator */
end_comment

begin_function_decl
specifier|extern
name|DBL
function_decl|(
modifier|*
name|random_number
function_decl|)
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|gas_leaf_prob_const
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|gas_leaf_prob_desc
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|gas_operator_weight_const
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|NODE
modifier|*
name|gas_random
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|NODE
modifier|*
name|gas_mate
parameter_list|(
name|DBL
parameter_list|,
name|NODE
modifier|*
parameter_list|,
name|NODE
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*   functions& variables for MUTATING */
end_comment

begin_decl_stmt
specifier|extern
name|DBL
name|gas_mutate_prob
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|gas_mutate_func
typedef|typedef
name|NODE
modifier|*
function_decl|(
modifier|*
name|gas_mutate_func
function_decl|)
parameter_list|(
name|NODE
modifier|*
parameter_list|,
name|NODE
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2997b9a90108
typedef|typedef
struct|struct
block|{
DECL|member|func
name|gas_mutate_func
name|func
decl_stmt|;
DECL|member|desc
name|char
modifier|*
name|desc
decl_stmt|;
DECL|member|weight
name|DBL
name|weight
decl_stmt|;
DECL|member|noo
name|char
name|noo
decl_stmt|;
comment|/* how many arguments must have such node to aply this mutate function ? */
DECL|typedef|gas_mutate_methods_struct
block|}
name|gas_mutate_methods_struct
typedef|;
end_typedef

begin_comment
DECL|typedef|gas_mutate_methods_struct
comment|/* -1 .. arbitrary,  					   -2 - greater than zero (ie non constant),  					   -3 nofd != 0  					   -4 op->nofp == -1 					 */
end_comment

begin_function_decl
name|NODE
modifier|*
name|gas_mutate
parameter_list|(
name|NODE
modifier|*
parameter_list|,
name|NODE
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|int
name|Number_of_MutFunc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gas_mutate_methods_struct
name|MutFuncs
index|[]
decl_stmt|;
end_decl_stmt

begin_function_decl
name|DBL
name|gas_mfw_array
parameter_list|(
name|int
parameter_list|,
name|NODE
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|DBL
name|gas_mfw_const
parameter_list|(
name|int
parameter_list|,
name|NODE
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|DBL
function_decl|(
modifier|*
name|gas_get_mf_weight
function_decl|)
parameter_list|(
name|int
parameter_list|,
name|NODE
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

