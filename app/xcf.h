begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__XCF_H__
end_ifndef

begin_define
DECL|macro|__XCF_H__
define|#
directive|define
name|__XCF_H__
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_typedef
DECL|typedef|XcfInfo
typedef|typedef
name|struct
name|_XcfInfo
name|XcfInfo
typedef|;
end_typedef

begin_struct
DECL|struct|_XcfInfo
struct|struct
name|_XcfInfo
block|{
DECL|member|fp
name|FILE
modifier|*
name|fp
decl_stmt|;
DECL|member|cp
name|guint
name|cp
decl_stmt|;
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
DECL|member|active_layer
name|int
name|active_layer
decl_stmt|;
DECL|member|active_channel
name|int
name|active_channel
decl_stmt|;
DECL|member|floating_sel_drawable
name|int
name|floating_sel_drawable
decl_stmt|;
DECL|member|floating_sel_offset
name|guint
name|floating_sel_offset
decl_stmt|;
DECL|member|swap_num
name|int
name|swap_num
decl_stmt|;
DECL|member|ref_count
name|int
modifier|*
name|ref_count
decl_stmt|;
DECL|member|compression
name|int
name|compression
decl_stmt|;
DECL|member|file_version
name|int
name|file_version
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|xcf_init
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
comment|/* __XCF_H__ */
end_comment

end_unit

