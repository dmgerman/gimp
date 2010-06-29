begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MEMSIZE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MEMSIZE_H__
define|#
directive|define
name|__GIMP_MEMSIZE_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/**  * GIMP_TYPE_MEMSIZE:  *  * #GIMP_TYPE_MEMSIZE is a #GType derived from #G_TYPE_UINT64.  **/
DECL|macro|GIMP_TYPE_MEMSIZE
define|#
directive|define
name|GIMP_TYPE_MEMSIZE
value|(gimp_memsize_get_type ())
DECL|macro|GIMP_VALUE_HOLDS_MEMSIZE (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_MEMSIZE
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_MEMSIZE))
name|GType
name|gimp_memsize_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gchar
modifier|*
name|gimp_memsize_serialize
argument_list|(
name|guint64
name|memsize
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_memsize_deserialize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|guint64
modifier|*
name|memsize
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_decl_stmt
name|gchar
modifier|*
name|gimp_memsize_to_string
argument_list|(
name|guint64
name|memsize
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

begin_comment
comment|/*  * GIMP_TYPE_PARAM_MEMSIZE  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_MEMSIZE
define|#
directive|define
name|GIMP_TYPE_PARAM_MEMSIZE
value|(gimp_param_memsize_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_MEMSIZE (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_MEMSIZE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_MEMSIZE))
end_define

begin_decl_stmt
name|GType
name|gimp_param_memsize_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_memsize
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
name|guint64
name|minimum
parameter_list|,
name|guint64
name|maximum
parameter_list|,
name|guint64
name|default_value
parameter_list|,
name|GParamFlags
name|flags
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
comment|/* __GIMP_MEMSIZE_H__ */
end_comment

end_unit

