begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLORMAP_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__COLORMAP_DIALOG_H__
define|#
directive|define
name|__COLORMAP_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdialog.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_COLORMAP_DIALOG
define|#
directive|define
name|GIMP_TYPE_COLORMAP_DIALOG
value|(gimp_colormap_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLORMAP_DIALOG (obj)
define|#
directive|define
name|GIMP_COLORMAP_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST((obj), GIMP_TYPE_COLORMAP_DIALOG, GimpColormapDialog))
end_define

begin_define
DECL|macro|GIMP_COLORMAP_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_COLORMAP_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST((klass), GIMP_TYPE_COLORMAP_DIALOG, GimpColormapDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLORMAP_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_COLORMAP_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE((obj), GIMP_TYPE_COLORMAP_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_COLORMAP_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLORMAP_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE((klass), GIMP_TYPE_COLORMAP_DIALOG))
end_define

begin_typedef
DECL|typedef|GimpColormapDialog
typedef|typedef
name|struct
name|_GimpColormapDialog
name|GimpColormapDialog
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColormapDialogClass
typedef|typedef
name|struct
name|_GimpColormapDialogClass
name|GimpColormapDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColormapDialog
struct|struct
name|_GimpColormapDialog
block|{
DECL|member|parent
name|GtkVBox
name|parent
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|col_index
name|gint
name|col_index
decl_stmt|;
DECL|member|dnd_col_index
name|gint
name|dnd_col_index
decl_stmt|;
DECL|member|palette
name|GtkWidget
modifier|*
name|palette
decl_stmt|;
DECL|member|image_menu
name|GtkWidget
modifier|*
name|image_menu
decl_stmt|;
DECL|member|popup_menu
name|GtkWidget
modifier|*
name|popup_menu
decl_stmt|;
DECL|member|option_menu
name|GtkOptionMenu
modifier|*
name|option_menu
decl_stmt|;
DECL|member|xn
name|gint
name|xn
decl_stmt|;
DECL|member|yn
name|gint
name|yn
decl_stmt|;
DECL|member|cellsize
name|gint
name|cellsize
decl_stmt|;
DECL|member|index_adjustment
name|GtkAdjustment
modifier|*
name|index_adjustment
decl_stmt|;
DECL|member|index_spinbutton
name|GtkWidget
modifier|*
name|index_spinbutton
decl_stmt|;
DECL|member|color_entry
name|GtkWidget
modifier|*
name|color_entry
decl_stmt|;
DECL|member|add_item
name|GtkWidget
modifier|*
name|add_item
decl_stmt|;
DECL|member|color_notebook
name|ColorNotebook
modifier|*
name|color_notebook
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColormapDialogClass
struct|struct
name|_GimpColormapDialogClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
DECL|member|selected
name|void
function_decl|(
modifier|*
name|selected
function_decl|)
parameter_list|(
name|GimpColormapDialog
modifier|*
name|gcd
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_colormap_dialog_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_colormap_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_colormap_dialog_selected
parameter_list|(
name|GimpColormapDialog
modifier|*
name|gcd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_colormap_dialog_set_image
parameter_list|(
name|GimpColormapDialog
modifier|*
name|gcd
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_colormap_dialog_get_image
parameter_list|(
name|GimpColormapDialog
modifier|*
name|gcd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_colormap_dialog_col_index
parameter_list|(
name|GimpColormapDialog
modifier|*
name|gcd
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __COLORMAP_DIALOG_H__ */
end_comment

end_unit

