begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpparasite.h  * Copyright (C) 1998 Jay Cox<jaycox@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_BASE_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_BASE_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpbase/gimpbase.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PARASITE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PARASITE_H__
define|#
directive|define
name|__GIMP_PARASITE_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
comment|/*  * GIMP_TYPE_PARASITE  */
DECL|macro|GIMP_TYPE_PARASITE
define|#
directive|define
name|GIMP_TYPE_PARASITE
value|(gimp_parasite_get_type ())
DECL|macro|GIMP_VALUE_HOLDS_PARASITE (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_PARASITE
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_PARASITE))
name|GType
name|gimp_parasite_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_PARASITE  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_PARASITE
define|#
directive|define
name|GIMP_TYPE_PARAM_PARASITE
value|(gimp_param_parasite_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_PARASITE (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_PARASITE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_PARASITE))
end_define

begin_decl_stmt
name|GType
name|gimp_param_parasite_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_parasite
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_PARASITE_PERSISTENT
define|#
directive|define
name|GIMP_PARASITE_PERSISTENT
value|1
end_define

begin_define
DECL|macro|GIMP_PARASITE_UNDOABLE
define|#
directive|define
name|GIMP_PARASITE_UNDOABLE
value|2
end_define

begin_define
DECL|macro|GIMP_PARASITE_ATTACH_PARENT
define|#
directive|define
name|GIMP_PARASITE_ATTACH_PARENT
value|(0x80<< 8)
end_define

begin_define
DECL|macro|GIMP_PARASITE_PARENT_PERSISTENT
define|#
directive|define
name|GIMP_PARASITE_PARENT_PERSISTENT
value|(GIMP_PARASITE_PERSISTENT<< 8)
end_define

begin_define
DECL|macro|GIMP_PARASITE_PARENT_UNDOABLE
define|#
directive|define
name|GIMP_PARASITE_PARENT_UNDOABLE
value|(GIMP_PARASITE_UNDOABLE<< 8)
end_define

begin_define
DECL|macro|GIMP_PARASITE_ATTACH_GRANDPARENT
define|#
directive|define
name|GIMP_PARASITE_ATTACH_GRANDPARENT
value|(0x80<< 16)
end_define

begin_define
DECL|macro|GIMP_PARASITE_GRANDPARENT_PERSISTENT
define|#
directive|define
name|GIMP_PARASITE_GRANDPARENT_PERSISTENT
value|(GIMP_PARASITE_PERSISTENT<< 16)
end_define

begin_define
DECL|macro|GIMP_PARASITE_GRANDPARENT_UNDOABLE
define|#
directive|define
name|GIMP_PARASITE_GRANDPARENT_UNDOABLE
value|(GIMP_PARASITE_UNDOABLE<< 16)
end_define

begin_struct
DECL|struct|_GimpParasite
struct|struct
name|_GimpParasite
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* The name of the parasite. USE A UNIQUE PREFIX! */
DECL|member|flags
name|guint32
name|flags
decl_stmt|;
comment|/* save Parasite in XCF file, etc.                */
DECL|member|size
name|guint32
name|size
decl_stmt|;
comment|/* amount of data                                 */
DECL|member|data
name|gpointer
name|data
decl_stmt|;
comment|/* a pointer to the data.  plugin is              *                      * responsible for tracking byte order            */
block|}
struct|;
end_struct

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_parasite_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|guint32
name|flags
parameter_list|,
name|guint32
name|size
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parasite_free
parameter_list|(
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParasite
modifier|*
name|gimp_parasite_copy
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_parasite_compare
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_parasite_is_type
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_parasite_is_persistent
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_parasite_is_undoable
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_parasite_has_flag
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gulong
name|flag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gulong
name|gimp_parasite_flags
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_parasite_name
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gconstpointer
name|gimp_parasite_data
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|glong
name|gimp_parasite_data_size
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
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
comment|/* __GIMP_PARASITE_H__ */
end_comment

end_unit

