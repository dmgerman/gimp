begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_STATUSBAR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_STATUSBAR_H__
define|#
directive|define
name|__GIMP_STATUSBAR_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkstatusbar.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/*  maximal length of the format string for the cursor-coordinates  */
end_comment

begin_define
DECL|macro|CURSOR_FORMAT_LENGTH
define|#
directive|define
name|CURSOR_FORMAT_LENGTH
value|32
end_define

begin_define
DECL|macro|GIMP_TYPE_STATUSBAR
define|#
directive|define
name|GIMP_TYPE_STATUSBAR
value|(gimp_statusbar_get_type ())
end_define

begin_define
DECL|macro|GIMP_STATUSBAR (obj)
define|#
directive|define
name|GIMP_STATUSBAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_STATUSBAR, GimpStatusbar))
end_define

begin_define
DECL|macro|GIMP_STATUSBAR_CLASS (klass)
define|#
directive|define
name|GIMP_STATUSBAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_STATUSBAR, GimpStatusbarClass))
end_define

begin_define
DECL|macro|GIMP_IS_STATUSBAR (obj)
define|#
directive|define
name|GIMP_IS_STATUSBAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_STATUSBAR))
end_define

begin_define
DECL|macro|GIMP_IS_STATUSBAR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_STATUSBAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_STATUSBAR))
end_define

begin_define
DECL|macro|GIMP_STATUSBAR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_STATUSBAR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_STATUSBAR, GimpStatusbarClass))
end_define

begin_typedef
DECL|typedef|GimpStatusbarClass
typedef|typedef
name|struct
name|_GimpStatusbarClass
name|GimpStatusbarClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpStatusbar
struct|struct
name|_GimpStatusbar
block|{
DECL|member|parent_instance
name|GtkStatusbar
name|parent_instance
decl_stmt|;
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
DECL|member|cursor_frame
name|GtkWidget
modifier|*
name|cursor_frame
decl_stmt|;
DECL|member|cursor_label
name|GtkWidget
modifier|*
name|cursor_label
decl_stmt|;
DECL|member|cursor_format_str
name|gchar
name|cursor_format_str
index|[
name|CURSOR_FORMAT_LENGTH
index|]
decl_stmt|;
DECL|member|combo
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
DECL|member|progressbar
name|GtkWidget
modifier|*
name|progressbar
decl_stmt|;
DECL|member|progressid
name|guint
name|progressid
decl_stmt|;
DECL|member|cancelbutton
name|GtkWidget
modifier|*
name|cancelbutton
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpStatusbarClass
struct|struct
name|_GimpStatusbarClass
block|{
DECL|member|parent_class
name|GtkStatusbarClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_statusbar_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_statusbar_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_statusbar_push
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_statusbar_push_coords
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
name|x
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separator
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_statusbar_pop
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_statusbar_update_cursor
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_statusbar_resize_cursor
parameter_list|(
name|GimpStatusbar
modifier|*
name|statusbar
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
comment|/* __GIMP_STATUSBAR_H__ */
end_comment

end_unit

