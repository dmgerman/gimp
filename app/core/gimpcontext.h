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
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

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
typedef|typedef
enum|enum
DECL|enum|__anon27ef59c00103
block|{
DECL|enumerator|GIMP_CONTEXT_ARG_OPACITY
name|GIMP_CONTEXT_ARG_OPACITY
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_PAINT_MODE
name|GIMP_CONTEXT_ARG_PAINT_MODE
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_IMAGE
name|GIMP_CONTEXT_ARG_IMAGE
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_DISPLAY
name|GIMP_CONTEXT_ARG_DISPLAY
init|=
literal|1
operator|<<
literal|3
block|,
comment|/* aliases    */
DECL|enumerator|GIMP_CONTEXT_ARG_PAINT
name|GIMP_CONTEXT_ARG_PAINT
init|=
name|GIMP_CONTEXT_ARG_OPACITY
operator||
name|GIMP_CONTEXT_ARG_PAINT_MODE
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_ALL
name|GIMP_CONTEXT_ARG_ALL
init|=
name|GIMP_CONTEXT_ARG_PAINT
operator||
name|GIMP_CONTEXT_ARG_IMAGE
operator||
name|GIMP_CONTEXT_ARG_DISPLAY
DECL|typedef|GimpContextArgs
block|}
name|GimpContextArgs
typedef|;
end_typedef

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
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|parent
name|GimpContext
modifier|*
name|parent
decl_stmt|;
comment|/*  FIXME: the solution of having a boolean for each attribute and the    *         name "defined" need some brainstorming    */
DECL|member|opacity_defined
name|gboolean
name|opacity_defined
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|paint_mode_defined
name|gboolean
name|paint_mode_defined
decl_stmt|;
DECL|member|paint_mode
name|gint
name|paint_mode
decl_stmt|;
DECL|member|image_defined
name|gboolean
name|image_defined
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|display_defined
name|gboolean
name|display_defined
decl_stmt|;
DECL|member|display
name|GDisplay
modifier|*
name|display
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
parameter_list|,
name|gdouble
name|opacity
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
parameter_list|,
name|gint
name|paint_mode
parameter_list|)
function_decl|;
DECL|member|image_changed
name|void
function_decl|(
modifier|*
name|image_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|image
parameter_list|)
function_decl|;
DECL|member|display_changed
name|void
function_decl|(
modifier|*
name|display_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|display
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
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpContext
modifier|*
name|template
parameter_list|,
name|GimpContext
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  TODO: - gimp_context_set_parent ()  *        - gimp_context_get_parent ()  *        - gimp_context_find ()  *  *        probably interacting with the context manager:  *        - gimp_context_push () which will call gimp_context_set_parent()  *        - gimp_context_push_new () to do a GL-style push  *        - gimp_context_pop ()  *  *        a proper mechanism to prevent silly operations like pushing  *        the user context to some client stack etc.  */
end_comment

begin_comment
comment|/*  to be used by the context management system only  *  *  FIXME: move them to a private header  */
end_comment

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

begin_function_decl
name|void
name|gimp_context_set_user
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_default
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  these are always available  */
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
name|GimpContext
modifier|*
name|gimp_context_get_user
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_context_get_default
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_context_get_standard
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  functions for manipulating a single context  *  *  FIXME: this interface may be ok but the implementation is  *         ugly code duplication. There needs to be a generic way.  */
end_comment

begin_function_decl
name|gchar
modifier|*
name|gimp_context_get_name
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_context_get_parent
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_parent
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContext
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

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
name|gboolean
name|gimp_context_opacity_defined
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_define_opacity
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|defined
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

begin_function_decl
name|gboolean
name|gimp_context_paint_mode_defined
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_define_paint_mode
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|defined
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_context_get_image
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_image
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_image_defined
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_define_image
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|defined
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GDisplay
modifier|*
name|gimp_context_get_display
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_display
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_display_defined
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_define_display
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|defined
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

