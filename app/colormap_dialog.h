begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_g_gimp_colormap_dialog_funcs
end_ifndef

begin_define
DECL|macro|_g_gimp_colormap_dialog_funcs
define|#
directive|define
name|_g_gimp_colormap_dialog_funcs
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdialog.h>
end_include

begin_include
include|#
directive|include
file|<colormap_dialog.t.h>
end_include

begin_include
include|#
directive|include
file|<gimpset.h>
end_include

begin_include
include|#
directive|include
file|<gimpimage.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_function_decl
name|GimpColormapDialog
modifier|*
name|gimp_colormap_dialog_create
parameter_list|(
name|GimpSet
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_colormap_dialog_image
parameter_list|(
specifier|const
name|GimpColormapDialog
modifier|*
name|colormap_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_colormap_dialog_col_index
parameter_list|(
specifier|const
name|GimpColormapDialog
modifier|*
name|colormap_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpColormapDialogHandler_selected
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColormapDialogHandler_selected
function_decl|)
parameter_list|(
name|GimpColormapDialog
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_colormap_dialog_connect_selected
parameter_list|(
name|GimpColormapDialogHandler_selected
name|handler
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GimpColormapDialog
modifier|*
name|colormap_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _g_gimp_colormap_dialog_funcs */
end_comment

end_unit

