begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__LIGHTING_UI_H__
end_ifndef

begin_define
DECL|macro|__LIGHTING_UI_H__
define|#
directive|define
name|__LIGHTING_UI_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<gck/gck.h>
end_include

begin_comment
comment|/* Externally visible variables */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_decl_stmt
specifier|extern
name|GckVisualInfo
modifier|*
name|visinfo
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GdkGC
modifier|*
name|gc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|previewarea
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Externally visible functions */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_function_decl
name|gboolean
name|main_dialog
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

