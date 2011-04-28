begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UI_H__
define|#
directive|define
name|__GIMP_UI_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpwidgets.h>
end_include

begin_define
DECL|macro|__GIMP_UI_H_INSIDE__
define|#
directive|define
name|__GIMP_UI_H_INSIDE__
end_define

begin_include
include|#
directive|include
file|<libgimp/gimpuitypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpexport.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpaspectpreview.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpdrawablepreview.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpbrushmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpfontmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpgradientmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppalettemenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppatternmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpprocbrowserdialog.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpprocview.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpprogressbar.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpitemcombobox.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpimagecombobox.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpselectbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpbrushselectbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpfontselectbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpgradientselectbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppaletteselectbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppatternselectbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpzoompreview.h>
end_include

begin_undef
undef|#
directive|undef
name|__GIMP_UI_H_INSIDE__
end_undef

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|void
name|gimp_ui_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
name|gboolean
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkWindow
modifier|*
name|gimp_ui_get_display_window
parameter_list|(
name|guint32
name|gdisp_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkWindow
modifier|*
name|gimp_ui_get_progress_window
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_window_set_transient_for_display
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|guint32
name|gdisp_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_window_set_transient
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UI_H__ */
end_comment

end_unit

