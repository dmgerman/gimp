begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmessagebox.h  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MESSAGE_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MESSAGE_BOX_H__
define|#
directive|define
name|__GIMP_MESSAGE_BOX_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_MESSAGE_BOX
define|#
directive|define
name|GIMP_TYPE_MESSAGE_BOX
value|(gimp_message_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_MESSAGE_BOX (obj)
define|#
directive|define
name|GIMP_MESSAGE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MESSAGE_BOX, GimpMessageBox))
end_define

begin_define
DECL|macro|GIMP_MESSAGE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_MESSAGE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MESSAGE_BOX, GimpMessageBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_MESSAGE_BOX (obj)
define|#
directive|define
name|GIMP_IS_MESSAGE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MESSAGE_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_MESSAGE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MESSAGE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MESSAGE_BOX))
end_define

begin_define
DECL|macro|GIMP_MESSAGE_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MESSAGE_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MESSAGE_BOX, GimpMessageBoxClass))
end_define

begin_typedef
DECL|typedef|GimpMessageBoxClass
typedef|typedef
name|struct
name|_GimpMessageBoxClass
name|GimpMessageBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMessageBox
struct|struct
name|_GimpMessageBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|repeat
name|gint
name|repeat
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
index|[
literal|3
index|]
decl_stmt|;
DECL|member|image
name|GtkWidget
modifier|*
name|image
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMessageBoxClass
struct|struct
name|_GimpMessageBoxClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_message_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_message_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_message_box_set_primary_text
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_message_box_set_text
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_message_box_set_markup
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|gint
name|gimp_message_box_repeat
parameter_list|(
name|GimpMessageBox
modifier|*
name|box
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
comment|/* __GIMP_MESSAGE_BOX_H__ */
end_comment

end_unit

