begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|MAPOBJECTUIH
end_ifndef

begin_define
DECL|macro|MAPOBJECTUIH
define|#
directive|define
name|MAPOBJECTUIH
end_define

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gck/gck.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"arcball.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_main.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_image.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_apply.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_preview.h"
end_include

begin_include
include|#
directive|include
file|"mapobject_pixmaps.h"
end_include

begin_comment
comment|/* Externally visible variables */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_decl_stmt
specifier|extern
name|GckApplicationWindow
modifier|*
name|appwin
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
specifier|extern
name|void
name|create_main_dialog
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

