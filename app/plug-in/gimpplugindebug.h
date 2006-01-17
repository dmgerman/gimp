begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_DEBUG_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_DEBUG_H__
define|#
directive|define
name|__PLUG_IN_DEBUG_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27e6e04a0103
block|{
DECL|enumerator|GIMP_DEBUG_WRAP_QUERY
name|GIMP_DEBUG_WRAP_QUERY
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_DEBUG_WRAP_INIT
name|GIMP_DEBUG_WRAP_INIT
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_DEBUG_WRAP_RUN
name|GIMP_DEBUG_WRAP_RUN
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_DEBUG_WRAP_DEFAULT
name|GIMP_DEBUG_WRAP_DEFAULT
init|=
name|GIMP_DEBUG_WRAP_RUN
DECL|typedef|GimpDebugWrapFlag
block|}
name|GimpDebugWrapFlag
typedef|;
end_typedef

begin_function_decl
name|void
name|plug_in_debug_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_debug_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|plug_in_debug_argv
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDebugWrapFlag
name|flag
parameter_list|,
name|gchar
modifier|*
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_DEBUG_H__ */
end_comment

end_unit

