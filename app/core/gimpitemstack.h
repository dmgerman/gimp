begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpitemstack.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_STACK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_STACK_H__
define|#
directive|define
name|__GIMP_ITEM_STACK_H__
end_define

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_ITEM_STACK
define|#
directive|define
name|GIMP_TYPE_ITEM_STACK
value|(gimp_item_stack_get_type ())
end_define

begin_define
DECL|macro|GIMP_ITEM_STACK (obj)
define|#
directive|define
name|GIMP_ITEM_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ITEM_STACK, GimpItemStack))
end_define

begin_define
DECL|macro|GIMP_ITEM_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_ITEM_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ITEM_STACK, GimpItemStackClass))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_STACK (obj)
define|#
directive|define
name|GIMP_IS_ITEM_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ITEM_STACK))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ITEM_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ITEM_STACK))
end_define

begin_typedef
DECL|typedef|GimpItemStackClass
typedef|typedef
name|struct
name|_GimpItemStackClass
name|GimpItemStackClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemStack
struct|struct
name|_GimpItemStack
block|{
DECL|member|parent_instance
name|GimpList
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpItemStackClass
struct|struct
name|_GimpItemStackClass
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
name|gimp_item_stack_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_item_stack_new
parameter_list|(
name|GType
name|item_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_item_stack_get_item_list
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_stack_get_item_by_tattoo
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|,
name|GimpTattoo
name|tattoo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItem
modifier|*
name|gimp_item_stack_get_item_by_name
parameter_list|(
name|GimpItemStack
modifier|*
name|stack
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_stack_invalidate_previews
parameter_list|(
name|GimpItemStack
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
comment|/*  __GIMP_ITEM_STACK_H__  */
end_comment

end_unit

