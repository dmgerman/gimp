begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__EXPRTREE_H__
end_ifndef

begin_define
DECL|macro|__EXPRTREE_H__
define|#
directive|define
name|__EXPRTREE_H__
end_define

begin_include
include|#
directive|include
file|"vars.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|USE_TREE
end_ifdef

begin_typedef
DECL|typedef|function
typedef|typedef
name|double
function_decl|(
modifier|*
name|function
function_decl|)
parameter_list|(
name|double
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|function
typedef|typedef
name|void
function_decl|(
modifier|*
name|function
function_decl|)
parameter_list|(
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ident
typedef|typedef
name|char
name|ident
index|[
literal|64
index|]
typedef|;
end_typedef

begin_typedef
DECL|struct|_exprtree
typedef|typedef
struct|struct
name|_exprtree
block|{
DECL|member|type
name|int
name|type
decl_stmt|;
union|union
DECL|union|__anon294404bc010a
block|{
DECL|member|number
name|double
name|number
decl_stmt|;
DECL|member|var
name|variable
modifier|*
name|var
decl_stmt|;
struct|struct
DECL|struct|__anon294404bc0208
block|{
DECL|member|numArgs
name|int
name|numArgs
decl_stmt|;
DECL|member|routine
name|function
name|routine
decl_stmt|;
DECL|member|args
name|struct
name|_exprtree
modifier|*
name|args
decl_stmt|;
DECL|member|func
block|}
name|func
struct|;
struct|struct
DECL|struct|__anon294404bc0308
block|{
DECL|member|left
name|struct
name|_exprtree
modifier|*
name|left
decl_stmt|;
DECL|member|right
name|struct
name|_exprtree
modifier|*
name|right
decl_stmt|;
DECL|member|operator
block|}
name|operator
struct|;
struct|struct
DECL|struct|__anon294404bc0408
block|{
DECL|member|var
name|variable
modifier|*
name|var
decl_stmt|;
DECL|member|value
name|struct
name|_exprtree
modifier|*
name|value
decl_stmt|;
DECL|member|assignment
block|}
name|assignment
struct|;
struct|struct
DECL|struct|__anon294404bc0508
block|{
DECL|member|condition
name|struct
name|_exprtree
modifier|*
name|condition
decl_stmt|;
DECL|member|consequence
name|struct
name|_exprtree
modifier|*
name|consequence
decl_stmt|;
DECL|member|alternative
name|struct
name|_exprtree
modifier|*
name|alternative
decl_stmt|;
DECL|member|label1
name|int
name|label1
decl_stmt|;
DECL|member|label2
name|int
name|label2
decl_stmt|;
DECL|member|ifExpr
block|}
name|ifExpr
struct|;
struct|struct
DECL|struct|__anon294404bc0608
block|{
DECL|member|invariant
name|struct
name|_exprtree
modifier|*
name|invariant
decl_stmt|;
DECL|member|body
name|struct
name|_exprtree
modifier|*
name|body
decl_stmt|;
DECL|member|label1
name|int
name|label1
decl_stmt|;
DECL|member|label2
name|int
name|label2
decl_stmt|;
DECL|member|whileExpr
block|}
name|whileExpr
struct|;
DECL|member|val
block|}
name|val
union|;
DECL|member|next
name|struct
name|_exprtree
modifier|*
name|next
decl_stmt|;
DECL|typedef|exprtree
block|}
name|exprtree
typedef|;
end_typedef

begin_define
DECL|macro|EXPR_NUMBER
define|#
directive|define
name|EXPR_NUMBER
value|1
end_define

begin_define
DECL|macro|EXPR_ADD
define|#
directive|define
name|EXPR_ADD
value|2
end_define

begin_define
DECL|macro|EXPR_SUB
define|#
directive|define
name|EXPR_SUB
value|3
end_define

begin_define
DECL|macro|EXPR_MUL
define|#
directive|define
name|EXPR_MUL
value|4
end_define

begin_define
DECL|macro|EXPR_DIV
define|#
directive|define
name|EXPR_DIV
value|5
end_define

begin_define
DECL|macro|EXPR_MOD
define|#
directive|define
name|EXPR_MOD
value|6
end_define

begin_define
DECL|macro|EXPR_NEG
define|#
directive|define
name|EXPR_NEG
value|7
end_define

begin_define
DECL|macro|EXPR_FUNC
define|#
directive|define
name|EXPR_FUNC
value|8
end_define

begin_define
DECL|macro|EXPR_VAR_X
define|#
directive|define
name|EXPR_VAR_X
value|9
end_define

begin_define
DECL|macro|EXPR_VAR_Y
define|#
directive|define
name|EXPR_VAR_Y
value|10
end_define

begin_define
DECL|macro|EXPR_VAR_R
define|#
directive|define
name|EXPR_VAR_R
value|11
end_define

begin_define
DECL|macro|EXPR_VAR_A
define|#
directive|define
name|EXPR_VAR_A
value|12
end_define

begin_define
DECL|macro|EXPR_VAR_W
define|#
directive|define
name|EXPR_VAR_W
value|13
end_define

begin_define
DECL|macro|EXPR_VAR_H
define|#
directive|define
name|EXPR_VAR_H
value|14
end_define

begin_define
DECL|macro|EXPR_VAR_BIG_R
define|#
directive|define
name|EXPR_VAR_BIG_R
value|15
end_define

begin_define
DECL|macro|EXPR_VAR_BIG_X
define|#
directive|define
name|EXPR_VAR_BIG_X
value|16
end_define

begin_define
DECL|macro|EXPR_VAR_BIG_Y
define|#
directive|define
name|EXPR_VAR_BIG_Y
value|17
end_define

begin_define
DECL|macro|EXPR_SEQUENCE
define|#
directive|define
name|EXPR_SEQUENCE
value|18
end_define

begin_define
DECL|macro|EXPR_ASSIGNMENT
define|#
directive|define
name|EXPR_ASSIGNMENT
value|19
end_define

begin_define
DECL|macro|EXPR_VARIABLE
define|#
directive|define
name|EXPR_VARIABLE
value|20
end_define

begin_define
DECL|macro|EXPR_IF_THEN
define|#
directive|define
name|EXPR_IF_THEN
value|21
end_define

begin_define
DECL|macro|EXPR_IF_THEN_ELSE
define|#
directive|define
name|EXPR_IF_THEN_ELSE
value|22
end_define

begin_define
DECL|macro|EXPR_WHILE
define|#
directive|define
name|EXPR_WHILE
value|23
end_define

begin_define
DECL|macro|EXPR_DO_WHILE
define|#
directive|define
name|EXPR_DO_WHILE
value|24
end_define

begin_function_decl
name|exprtree
modifier|*
name|make_number
parameter_list|(
name|double
name|num
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_var
parameter_list|(
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_operator
parameter_list|(
name|int
name|type
parameter_list|,
name|exprtree
modifier|*
name|left
parameter_list|,
name|exprtree
modifier|*
name|right
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_function
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|exprtree
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_sequence
parameter_list|(
name|exprtree
modifier|*
name|left
parameter_list|,
name|exprtree
modifier|*
name|right
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_assignment
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|exprtree
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_if_then
parameter_list|(
name|exprtree
modifier|*
name|condition
parameter_list|,
name|exprtree
modifier|*
name|conclusion
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_if_then_else
parameter_list|(
name|exprtree
modifier|*
name|condition
parameter_list|,
name|exprtree
modifier|*
name|conclusion
parameter_list|,
name|exprtree
modifier|*
name|alternative
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_while
parameter_list|(
name|exprtree
modifier|*
name|invariant
parameter_list|,
name|exprtree
modifier|*
name|body
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|make_do_while
parameter_list|(
name|exprtree
modifier|*
name|body
parameter_list|,
name|exprtree
modifier|*
name|invariant
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|exprtree
modifier|*
name|arglist_append
parameter_list|(
name|exprtree
modifier|*
name|list1
parameter_list|,
name|exprtree
modifier|*
name|list2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|double
name|eval_exprtree
parameter_list|(
name|exprtree
modifier|*
name|tree
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

