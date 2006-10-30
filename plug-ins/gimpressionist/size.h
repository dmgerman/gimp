begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__SIZE_H
end_ifndef

begin_define
DECL|macro|__SIZE_H
define|#
directive|define
name|__SIZE_H
end_define

begin_enum
DECL|enum|SIZE_TYPE_ENUM
enum|enum
name|SIZE_TYPE_ENUM
block|{
DECL|enumerator|SIZE_TYPE_VALUE
name|SIZE_TYPE_VALUE
init|=
literal|0
block|,
DECL|enumerator|SIZE_TYPE_RADIUS
name|SIZE_TYPE_RADIUS
init|=
literal|1
block|,
DECL|enumerator|SIZE_TYPE_RANDOM
name|SIZE_TYPE_RANDOM
init|=
literal|2
block|,
DECL|enumerator|SIZE_TYPE_RADIAL
name|SIZE_TYPE_RADIAL
init|=
literal|3
block|,
DECL|enumerator|SIZE_TYPE_FLOWING
name|SIZE_TYPE_FLOWING
init|=
literal|4
block|,
DECL|enumerator|SIZE_TYPE_HUE
name|SIZE_TYPE_HUE
init|=
literal|5
block|,
DECL|enumerator|SIZE_TYPE_ADAPTIVE
name|SIZE_TYPE_ADAPTIVE
init|=
literal|6
block|,
DECL|enumerator|SIZE_TYPE_MANUAL
name|SIZE_TYPE_MANUAL
init|=
literal|7
block|, }
enum|;
end_enum

begin_function_decl
name|void
name|size_restore
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_sizepage
parameter_list|(
name|GtkNotebook
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|size_type_input
parameter_list|(
name|int
name|in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|size_map_free_resources
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* #ifndef __SIZE_H */
end_comment

end_unit

