begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_g_gimp_colormap_dialog_import
end_ifndef

begin_define
DECL|macro|_g_gimp_colormap_dialog_import
define|#
directive|define
name|_g_gimp_colormap_dialog_import
end_define

begin_include
include|#
directive|include
file|<colormap_dialog.h>
end_include

begin_define
DECL|macro|TYPE_COLORMAP_DIALOG
define|#
directive|define
name|TYPE_COLORMAP_DIALOG
value|GIMP_TYPE_COLORMAP_DIALOG
end_define

begin_define
DECL|macro|ColormapDialog
define|#
directive|define
name|ColormapDialog
value|GimpColormapDialog
end_define

begin_define
DECL|macro|IS_COLORMAP_DIALOG
define|#
directive|define
name|IS_COLORMAP_DIALOG
value|GIMP_IS_COLORMAP_DIALOG
end_define

begin_define
DECL|macro|COLORMAP_DIALOG
define|#
directive|define
name|COLORMAP_DIALOG
value|GIMP_COLORMAP_DIALOG
end_define

begin_define
DECL|macro|colormap_dialog_create
define|#
directive|define
name|colormap_dialog_create
value|gimp_colormap_dialog_create
end_define

begin_define
DECL|macro|colormap_dialog_image
define|#
directive|define
name|colormap_dialog_image
value|gimp_colormap_dialog_image
end_define

begin_define
DECL|macro|colormap_dialog_col_index
define|#
directive|define
name|colormap_dialog_col_index
value|gimp_colormap_dialog_col_index
end_define

begin_define
DECL|macro|colormap_dialog_connect_selected
define|#
directive|define
name|colormap_dialog_connect_selected
value|gimp_colormap_dialog_connect_selected
end_define

begin_define
DECL|macro|colormap_dialog_selected
define|#
directive|define
name|colormap_dialog_selected
value|gimp_colormap_dialog_selected
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _g_gimp_colormap_dialog_import */
end_comment

end_unit

