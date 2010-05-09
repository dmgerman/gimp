begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GimpXmpModelText.h - custom text widget linked to the xmp model  *  * Copyright (C) 2010, RÃ³man Joost<romanofski@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_XMP_MODEL_TEXT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_XMP_MODEL_TEXT_H__
define|#
directive|define
name|__GIMP_XMP_MODEL_TEXT_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_XMP_MODEL_TEXT
define|#
directive|define
name|GIMP_TYPE_XMP_MODEL_TEXT
value|(gimp_xmp_model_text_get_type ())
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_TEXT (obj)
define|#
directive|define
name|GIMP_XMP_MODEL_TEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_XMP_MODEL_TEXT, GimpXmpModelText))
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_TEXT_CLASS (klass)
define|#
directive|define
name|GIMP_XMP_MODEL_TEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_XMP_MODEL_TEXT, XMPModelClass))
end_define

begin_define
DECL|macro|GIMP_IS_XMP_MODEL_TEXT (obj)
define|#
directive|define
name|GIMP_IS_XMP_MODEL_TEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_XMP_MODEL_TEXT))
end_define

begin_define
DECL|macro|GIMP_IS_XMP_MODEL_TEXT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_XMP_MODEL_TEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_XMP_MODEL_TEXT))
end_define

begin_define
DECL|macro|GIMP_XMP_MODEL_TEXT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_XMP_MODEL_TEXT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_XMP_MODEL_TEXT, XMPModelClass))
end_define

begin_typedef
DECL|typedef|GimpXmpModelText
typedef|typedef
name|struct
name|_GimpXmpModelText
name|GimpXmpModelText
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpXmpModelTextClass
typedef|typedef
name|struct
name|_GimpXmpModelTextClass
name|GimpXmpModelTextClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpXmpModelTextClass
struct|struct
name|_GimpXmpModelTextClass
block|{
DECL|member|parent_class
name|GtkTextViewClass
name|parent_class
decl_stmt|;
DECL|member|gimp_xmp_model_set_text_text
name|void
function_decl|(
modifier|*
name|gimp_xmp_model_set_text_text
function_decl|)
parameter_list|(
name|GimpXmpModelText
modifier|*
name|text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
DECL|member|gimp_xmp_model_get_text_text
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|gimp_xmp_model_get_text_text
function_decl|)
parameter_list|(
name|GimpXmpModelText
modifier|*
name|text
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpXmpModelText
struct|struct
name|_GimpXmpModelText
block|{
DECL|member|parent_instance
name|GtkTextView
name|parent_instance
decl_stmt|;
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_xmp_model_text_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_xmp_model_text_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|schema_uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property
parameter_list|,
name|XMPModel
modifier|*
name|xmp_model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_xmp_model_set_text_text
parameter_list|(
name|GimpXmpModelText
modifier|*
name|text
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_xmp_model_get_text_text
parameter_list|(
name|GimpXmpModelText
modifier|*
name|text
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
comment|/* __GIMP_XMP_MODEL_TEXT_H__ */
end_comment

end_unit

