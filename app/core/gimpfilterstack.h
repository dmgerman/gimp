begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpfilterstack.h  * Copyright (C) 2008-2013 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILTER_STACK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILTER_STACK_H__
define|#
directive|define
name|__GIMP_FILTER_STACK_H__
end_define

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FILTER_STACK
define|#
directive|define
name|GIMP_TYPE_FILTER_STACK
value|(gimp_filter_stack_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILTER_STACK (obj)
define|#
directive|define
name|GIMP_FILTER_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILTER_STACK, GimpFilterStack))
end_define

begin_define
DECL|macro|GIMP_FILTER_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_FILTER_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILTER_STACK, GimpFilterStackClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILTER_STACK (obj)
define|#
directive|define
name|GIMP_IS_FILTER_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILTER_STACK))
end_define

begin_define
DECL|macro|GIMP_IS_FILTER_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILTER_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILTER_STACK))
end_define

begin_typedef
DECL|typedef|GimpFilterStackClass
typedef|typedef
name|struct
name|_GimpFilterStackClass
name|GimpFilterStackClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFilterStack
struct|struct
name|_GimpFilterStack
block|{
DECL|member|parent_instance
name|GimpList
name|parent_instance
decl_stmt|;
DECL|member|graph
name|GeglNode
modifier|*
name|graph
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFilterStackClass
struct|struct
name|_GimpFilterStackClass
block|{
DECL|member|parent_class
name|GimpListClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_filter_stack_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglNode
modifier|*
name|gimp_filter_stack_get_graph
parameter_list|(
name|GimpFilterStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_FILTER_STACK_H__  */
end_comment

end_unit

