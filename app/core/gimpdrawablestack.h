begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpdrawablestack.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_STACK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_STACK_H__
define|#
directive|define
name|__GIMP_DRAWABLE_STACK_H__
end_define

begin_include
include|#
directive|include
file|"gimpitemstack.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE_STACK
define|#
directive|define
name|GIMP_TYPE_DRAWABLE_STACK
value|(gimp_drawable_stack_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_STACK (obj)
define|#
directive|define
name|GIMP_DRAWABLE_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DRAWABLE_STACK, GimpDrawableStack))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_DRAWABLE_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAWABLE_STACK, GimpDrawableStackClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_STACK (obj)
define|#
directive|define
name|GIMP_IS_DRAWABLE_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DRAWABLE_STACK))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAWABLE_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAWABLE_STACK))
end_define

begin_typedef
DECL|typedef|GimpDrawableStackClass
typedef|typedef
name|struct
name|_GimpDrawableStackClass
name|GimpDrawableStackClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawableStack
struct|struct
name|_GimpDrawableStack
block|{
DECL|member|parent_instance
name|GimpItemStack
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawableStackClass
struct|struct
name|_GimpDrawableStackClass
block|{
DECL|member|parent_class
name|GimpItemStackClass
name|parent_class
decl_stmt|;
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_drawable_stack_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_drawable_stack_new
parameter_list|(
name|GType
name|drawable_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|void
name|gimp_drawable_stack_update
parameter_list|(
name|GimpDrawableStack
modifier|*
name|stack
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAWABLE_STACK_H__  */
end_comment

end_unit

