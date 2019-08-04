begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp-debug.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DEBUG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DEBUG_H__
define|#
directive|define
name|__GIMP_DEBUG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon292c18ed0103
block|{
DECL|enumerator|GIMP_DEBUG_PID
name|GIMP_DEBUG_PID
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_DEBUG_FATAL_WARNINGS
name|GIMP_DEBUG_FATAL_WARNINGS
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_DEBUG_QUERY
name|GIMP_DEBUG_QUERY
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_DEBUG_INIT
name|GIMP_DEBUG_INIT
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_DEBUG_RUN
name|GIMP_DEBUG_RUN
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_DEBUG_QUIT
name|GIMP_DEBUG_QUIT
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_DEBUG_DEFAULT
name|GIMP_DEBUG_DEFAULT
init|=
operator|(
name|GIMP_DEBUG_RUN
operator||
name|GIMP_DEBUG_FATAL_WARNINGS
operator|)
DECL|typedef|GimpDebugFlag
block|}
name|GimpDebugFlag
typedef|;
end_typedef

begin_function_decl
name|void
name|_gimp_debug_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|basename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint
name|_gimp_debug_flags
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_debug_stop
parameter_list|(
name|void
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
comment|/* __GIMP_DEBUG_H__ */
end_comment

end_unit

