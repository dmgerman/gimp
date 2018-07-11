begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextBuffer-serialize  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * inspired by  * gtktextbufferserialize.h  * Copyright (C) 2004  Nokia Corporation.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_BUFFER_SERIALIZE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_BUFFER_SERIALIZE_H__
define|#
directive|define
name|__GIMP_TEXT_BUFFER_SERIALIZE_H__
end_define

begin_define
DECL|macro|WORD_JOINER
define|#
directive|define
name|WORD_JOINER
value|"\342\201\240"
end_define

begin_define
DECL|macro|WORD_JOINER_LENGTH
define|#
directive|define
name|WORD_JOINER_LENGTH
value|3
end_define

begin_function_decl
name|guint8
modifier|*
name|gimp_text_buffer_serialize
parameter_list|(
name|GtkTextBuffer
modifier|*
name|register_buffer
parameter_list|,
name|GtkTextBuffer
modifier|*
name|content_buffer
parameter_list|,
specifier|const
name|GtkTextIter
modifier|*
name|start
parameter_list|,
specifier|const
name|GtkTextIter
modifier|*
name|end
parameter_list|,
name|gsize
modifier|*
name|length
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_buffer_deserialize
parameter_list|(
name|GtkTextBuffer
modifier|*
name|register_buffer
parameter_list|,
name|GtkTextBuffer
modifier|*
name|content_buffer
parameter_list|,
name|GtkTextIter
modifier|*
name|iter
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gsize
name|length
parameter_list|,
name|gboolean
name|create_tags
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_buffer_pre_serialize
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GtkTextBuffer
modifier|*
name|content
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_buffer_post_deserialize
parameter_list|(
name|GimpTextBuffer
modifier|*
name|buffer
parameter_list|,
name|GtkTextBuffer
modifier|*
name|content
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_BUFFER_SERIALIZE_H__ */
end_comment

end_unit

