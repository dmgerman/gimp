begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_g_gimp_colormap_dialog_type
end_ifndef

begin_define
DECL|macro|_g_gimp_colormap_dialog_type
define|#
directive|define
name|_g_gimp_colormap_dialog_type
end_define

begin_include
include|#
directive|include
file|<gtk/gtktypeutils.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_COLORMAP_DIALOG
define|#
directive|define
name|GIMP_TYPE_COLORMAP_DIALOG
define|\
value|(_gimp_colormap_dialog_type ? (void)0 : _gimp_colormap_dialog_init_type (), _gimp_colormap_dialog_type)
end_define

begin_decl_stmt
specifier|extern
name|GtkType
name|_gimp_colormap_dialog_type
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|_gimp_colormap_dialog_init_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpColormapDialog
typedef|typedef
name|struct
name|_GimpColormapDialog
name|GimpColormapDialog
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_IS_COLORMAP_DIALOG (o)
define|#
directive|define
name|GIMP_IS_COLORMAP_DIALOG
parameter_list|(
name|o
parameter_list|)
value|GTK_CHECK_TYPE(o, GIMP_TYPE_COLORMAP_DIALOG)
end_define

begin_define
DECL|macro|GIMP_COLORMAP_DIALOG (o)
define|#
directive|define
name|GIMP_COLORMAP_DIALOG
parameter_list|(
name|o
parameter_list|)
value|GTK_CHECK_CAST(o, GIMP_TYPE_COLORMAP_DIALOG, GimpColormapDialog)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _g_gimp_colormap_dialog_type */
end_comment

end_unit

