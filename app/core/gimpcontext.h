begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTEXT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTEXT_H__
define|#
directive|define
name|__GIMP_CONTEXT_H__
end_define

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTEXT
define|#
directive|define
name|GIMP_TYPE_CONTEXT
value|(gimp_context_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTEXT (obj)
define|#
directive|define
name|GIMP_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_CAST ((obj), GIMP_TYPE_CONTEXT, GimpContext))
end_define

begin_define
DECL|macro|GIMP_CONTEXT_CLASS (klass)
define|#
directive|define
name|GIMP_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GIMP_CHECK_CLASS_CAST (klass, GIMP_TYPE_CONTEXT, GimpContextClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTEXT (obj)
define|#
directive|define
name|GIMP_IS_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_TYPE ((obj), GIMP_TYPE_CONTEXT))
end_define

begin_define
DECL|macro|GIMP_IS_CONTEXT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GIMP_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTEXT))
end_define

begin_typedef
DECL|typedef|GimpContext
typedef|typedef
name|struct
name|_GimpContext
name|GimpContext
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpContextClass
typedef|typedef
name|struct
name|_GimpContextClass
name|GimpContextClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContext
struct|struct
name|_GimpContext
block|{
DECL|member|object
name|GimpObject
name|object
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|paint_mode
name|gint
name|paint_mode
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContextClass
struct|struct
name|_GimpContextClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|opacity_changed
name|void
function_decl|(
modifier|*
name|opacity_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
DECL|member|paint_mode_changed
name|void
function_decl|(
modifier|*
name|paint_mode_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_context_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_context_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  to be used by the context management system only  */
end_comment

begin_function_decl
name|GimpContext
modifier|*
name|gimp_context_get_current
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_current
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  functions for manipulating a single context  */
end_comment

begin_function_decl
name|gdouble
name|gimp_context_get_opacity
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_opacity
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_context_get_paint_mode
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_paint_mode
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONTEXT_H__ */
end_comment

end_unit

