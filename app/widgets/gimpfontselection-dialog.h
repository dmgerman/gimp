begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpfontselection-dialog.h  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FONT_SELECTION_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FONT_SELECTION_DIALOG_H__
define|#
directive|define
name|__GIMP_FONT_SELECTION_DIALOG_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GIMP_TYPE_FONT_SELECTION_DIALOG
define|#
directive|define
name|GIMP_TYPE_FONT_SELECTION_DIALOG
value|(gimp_font_selection_dialog_get_type ())
DECL|macro|GIMP_FONT_SELECTION_DIALOG (obj)
define|#
directive|define
name|GIMP_FONT_SELECTION_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FONT_SELECTION_DIALOG, GimpFontSelectionDialog))
DECL|macro|GIMP_FONT_SELECTION_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_FONT_SELECTION_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FONT_SELECTION_DIALOG, GimpFontSelectionDialogClass))
DECL|macro|GIMP_IS_FONT_SELECTION_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_FONT_SELECTION_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_FONT_SELECTION_DIALOG))
DECL|macro|GIMP_IS_FONT_SELECTION_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FONT_SELECTION_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FONT_SELECTION_DIALOG))
DECL|typedef|GimpFontSelectionDialog
typedef|typedef
name|struct
name|_GimpFontSelectionDialog
name|GimpFontSelectionDialog
typedef|;
DECL|typedef|GimpFontSelectionDialogClass
typedef|typedef
name|struct
name|_GimpFontSelectionDialogClass
name|GimpFontSelectionDialogClass
typedef|;
DECL|struct|_GimpFontSelectionDialog
struct|struct
name|_GimpFontSelectionDialog
block|{
DECL|member|parent_instance
name|GtkDialog
name|parent_instance
decl_stmt|;
DECL|member|fontsel
name|GimpFontSelection
modifier|*
name|fontsel
decl_stmt|;
DECL|member|font_desc
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
DECL|member|font_clist
name|GtkWidget
modifier|*
name|font_clist
decl_stmt|;
DECL|member|font_style_clist
name|GtkWidget
modifier|*
name|font_style_clist
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpFontSelectionDialogClass
struct|struct
name|_GimpFontSelectionDialogClass
block|{
DECL|member|parent_class
name|GtkDialogClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|GType
name|gimp_font_selection_dialog_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_font_selection_dialog_new
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
parameter_list|)
function_decl|;
name|void
name|gimp_font_selection_dialog_set_font_desc
parameter_list|(
name|GimpFontSelectionDialog
modifier|*
name|dialog
parameter_list|,
name|PangoFontDescription
modifier|*
name|new_desc
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FONT_SELECTION_DIALOG_H__ */
end_comment

end_unit

