begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpLangRc: pre-parsing of gimprc returning the language.  * Copyright (C) 2017  Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LANG_RC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LANG_RC_H__
define|#
directive|define
name|__GIMP_LANG_RC_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_LANG_RC
define|#
directive|define
name|GIMP_TYPE_LANG_RC
value|(gimp_lang_rc_get_type ())
end_define

begin_define
DECL|macro|GIMP_LANG_RC (obj)
define|#
directive|define
name|GIMP_LANG_RC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LANG_RC, GimpLangRc))
end_define

begin_define
DECL|macro|GIMP_LANG_RC_CLASS (klass)
define|#
directive|define
name|GIMP_LANG_RC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LANG_RC, GimpLangRcClass))
end_define

begin_define
DECL|macro|GIMP_IS_LANG_RC (obj)
define|#
directive|define
name|GIMP_IS_LANG_RC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LANG_RC))
end_define

begin_define
DECL|macro|GIMP_IS_LANG_RC_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LANG_RC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LANG_RC))
end_define

begin_typedef
DECL|typedef|GimpLangRcClass
typedef|typedef
name|struct
name|_GimpLangRcClass
name|GimpLangRcClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLangRc
struct|struct
name|_GimpLangRc
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|user_gimprc
name|GFile
modifier|*
name|user_gimprc
decl_stmt|;
DECL|member|system_gimprc
name|GFile
modifier|*
name|system_gimprc
decl_stmt|;
DECL|member|verbose
name|gboolean
name|verbose
decl_stmt|;
DECL|member|language
name|gchar
modifier|*
name|language
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLangRcClass
struct|struct
name|_GimpLangRcClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_lang_rc_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpLangRc
modifier|*
name|gimp_lang_rc_new
parameter_list|(
name|GFile
modifier|*
name|system_gimprc
parameter_list|,
name|GFile
modifier|*
name|user_gimprc
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_lang_rc_get_language
parameter_list|(
name|GimpLangRc
modifier|*
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_LANG_RC_H__ */
end_comment

end_unit

