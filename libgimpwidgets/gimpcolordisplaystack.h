begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolordisplaystack.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_DISPLAY_STACK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_DISPLAY_STACK_H__
define|#
directive|define
name|__GIMP_COLOR_DISPLAY_STACK_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look at the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLOR_DISPLAY_STACK
define|#
directive|define
name|GIMP_TYPE_COLOR_DISPLAY_STACK
value|(gimp_color_display_stack_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_STACK (obj)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_DISPLAY_STACK, GimpColorDisplayStack))
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_DISPLAY_STACK, GimpColorDisplayStackClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DISPLAY_STACK (obj)
define|#
directive|define
name|GIMP_IS_COLOR_DISPLAY_STACK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_DISPLAY_STACK))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DISPLAY_STACK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_DISPLAY_STACK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_DISPLAY_STACK))
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_STACK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_STACK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_DISPLAY_STACK, GimpColorDisplayStackClass))
end_define

begin_typedef
DECL|typedef|GimpColorDisplayStackClass
typedef|typedef
name|struct
name|_GimpColorDisplayStackClass
name|GimpColorDisplayStackClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorDisplayStack
struct|struct
name|_GimpColorDisplayStack
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorDisplayStackClass
struct|struct
name|_GimpColorDisplayStackClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
DECL|member|added
name|void
function_decl|(
modifier|*
name|added
function_decl|)
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
DECL|member|removed
name|void
function_decl|(
modifier|*
name|removed
function_decl|)
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|reordered
name|void
function_decl|(
modifier|*
name|reordered
function_decl|)
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_display_stack_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpColorDisplayStack
modifier|*
name|gimp_color_display_stack_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorDisplayStack
modifier|*
name|gimp_color_display_stack_clone
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_stack_changed
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_color_display_stack_get_filters
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_stack_add
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_stack_remove
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_stack_reorder_up
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_stack_reorder_down
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_display_stack_convert_buffer
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|area
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
comment|/* __GIMP_COLOR_DISPLAY_STACK_H__ */
end_comment

end_unit

