begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__PLACEMENT_H
end_ifndef

begin_define
DECL|macro|__PLACEMENT_H
define|#
directive|define
name|__PLACEMENT_H
end_define

begin_enum
DECL|enum|PLACEMENT_TYPE_ENUM
enum|enum
name|PLACEMENT_TYPE_ENUM
block|{
DECL|enumerator|PLACEMENT_TYPE_RANDOM
name|PLACEMENT_TYPE_RANDOM
init|=
literal|0
block|,
DECL|enumerator|PLACEMENT_TYPE_EVEN_DIST
name|PLACEMENT_TYPE_EVEN_DIST
init|=
literal|1
block|, }
enum|;
end_enum

begin_function_decl
name|void
name|place_store
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|place_restore
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

