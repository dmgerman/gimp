begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_define
DECL|macro|GIMP_TYPE_MEMSIZE
define|#
directive|define
name|GIMP_TYPE_MEMSIZE
value|(gimp_memsize_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_MEMSIZE (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_MEMSIZE
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_MEMSIZE))
end_define

begin_decl_stmt
name|GType
name|gimp_memsize_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gchar
modifier|*
name|gimp_memsize_serialize
parameter_list|(
name|guint64
name|memsize
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
name|gchar
modifier|*
name|gimp_memsize_to_string
parameter_list|(
name|guint64
name|memsize
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MEMSIZE_H__ */
end_comment

end_unit

