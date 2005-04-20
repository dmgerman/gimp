begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__SHADOW_H__
end_ifndef

begin_define
DECL|macro|__SHADOW_H__
define|#
directive|define
name|__SHADOW_H__
end_define

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_function_decl
name|GdkPixbuf
modifier|*
name|create_shadowed_pixbuf
parameter_list|(
name|GdkPixbuf
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __SHADOW_H__ */
end_comment

end_unit

