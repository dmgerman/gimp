begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__VARS_H__
end_ifndef

begin_define
DECL|macro|__VARS_H__
define|#
directive|define
name|__VARS_H__
end_define

begin_define
DECL|macro|VAR_MAX_LENGTH
define|#
directive|define
name|VAR_MAX_LENGTH
value|32
end_define

begin_typedef
DECL|struct|_variable
typedef|typedef
struct|struct
name|_variable
block|{
DECL|member|name
name|char
name|name
index|[
name|VAR_MAX_LENGTH
index|]
decl_stmt|;
DECL|member|value
name|double
name|value
decl_stmt|;
DECL|member|next
name|struct
name|_variable
modifier|*
name|next
decl_stmt|;
DECL|typedef|variable
block|}
name|variable
typedef|;
end_typedef

begin_function_decl
name|variable
modifier|*
name|register_variable
parameter_list|(
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|clear_all_variables
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

