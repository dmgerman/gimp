begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextBuffer  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_BUFFER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_BUFFER_H__
define|#
directive|define
name|__GIMP_TEXT_BUFFER_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TEXT_BUFFER
define|#
directive|define
name|GIMP_TYPE_TEXT_BUFFER
value|(gimp_text_buffer_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_BUFFER (obj)
define|#
directive|define
name|GIMP_TEXT_BUFFER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_BUFFER, GimpTextBuffer))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_BUFFER (obj)
define|#
directive|define
name|GIMP_IS_TEXT_BUFFER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_BUFFER))
end_define

begin_define
DECL|macro|GIMP_TEXT_BUFFER_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_BUFFER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT_BUFFER, GimpTextBufferClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_BUFFER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_BUFFER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT_BUFFER))
end_define

begin_typedef
DECL|typedef|GimpTextBufferClass
typedef|typedef
name|struct
name|_GimpTextBufferClass
name|GimpTextBufferClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextBuffer
struct|struct
name|_GimpTextBuffer
block|{
DECL|member|parent_instance
name|GtkTextBuffer
name|parent_instance
decl_stmt|;
DECL|member|bold_tag
name|GtkTextTag
modifier|*
name|bold_tag
decl_stmt|;
DECL|member|italic_tag
name|GtkTextTag
modifier|*
name|italic_tag
decl_stmt|;
DECL|member|underline_tag
name|GtkTextTag
modifier|*
name|underline_tag
decl_stmt|;
DECL|member|strikethrough_tag
name|GtkTextTag
modifier|*
name|strikethrough_tag
decl_stmt|;
DECL|member|insert_tags
name|GList
modifier|*
name|insert_tags
decl_stmt|;
DECL|member|insert_tags_set
name|gboolean
name|insert_tags_set
decl_stmt|;
DECL|member|markup_atom
name|GdkAtom
name|markup_atom
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextBufferClass
struct|struct
name|_GimpTextBufferClass
block|{
DECL|member|parent_class
name|GtkTextBufferClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_text_buffer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpTextBuffer
modifier|*
name|gimp_text_buffer_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_buffer_set_text
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_text_buffer_get_text
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_buffer_set_markup
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|markup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_text_buffer_get_markup
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_text_buffer_tag_to_name
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GtkTextTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkTextTag
modifier|*
name|gimp_text_buffer_name_to_tag
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_buffer_set_insert_tags
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GList
modifier|*
name|style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_buffer_clear_insert_tags
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_buffer_insert
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_text_buffer_get_iter_index
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GtkTextIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_buffer_load
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_buffer_save
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|selection_only
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_BUFFER_H__ */
end_comment

end_unit

