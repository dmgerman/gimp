begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugindebug.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_DEBUG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_DEBUG_H__
define|#
directive|define
name|__GIMP_PLUG_IN_DEBUG_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c4eb4a30103
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
name|GimpPlugInDebug
modifier|*
name|gimp_plug_in_debug_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_debug_free
parameter_list|(
name|GimpPlugInDebug
modifier|*
name|debug
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_plug_in_debug_argv
parameter_list|(
name|GimpPlugInDebug
modifier|*
name|debug
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDebugWrapFlag
name|flag
parameter_list|,
specifier|const
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
comment|/* __GIMP_PLUG_IN_DEBUG_H__ */
end_comment

end_unit

