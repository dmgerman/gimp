begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpviewable.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VIEWABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VIEWABLE_H__
define|#
directive|define
name|__GIMP_VIEWABLE_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_define
DECL|macro|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
define|#
directive|define
name|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
value|1024
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_MAX_POPUP_SIZE
define|#
directive|define
name|GIMP_VIEWABLE_MAX_POPUP_SIZE
value|256
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_MAX_BUTTON_SIZE
define|#
directive|define
name|GIMP_VIEWABLE_MAX_BUTTON_SIZE
value|64
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_MAX_MENU_SIZE
define|#
directive|define
name|GIMP_VIEWABLE_MAX_MENU_SIZE
value|48
end_define

begin_define
DECL|macro|GIMP_TYPE_VIEWABLE
define|#
directive|define
name|GIMP_TYPE_VIEWABLE
value|(gimp_viewable_get_type ())
end_define

begin_define
DECL|macro|GIMP_VIEWABLE (obj)
define|#
directive|define
name|GIMP_VIEWABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VIEWABLE, GimpViewable))
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_VIEWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VIEWABLE, GimpViewableClass))
end_define

begin_define
DECL|macro|GIMP_IS_VIEWABLE (obj)
define|#
directive|define
name|GIMP_IS_VIEWABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VIEWABLE))
end_define

begin_define
DECL|macro|GIMP_IS_VIEWABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VIEWABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VIEWABLE))
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VIEWABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VIEWABLE, GimpViewableClass))
end_define

begin_typedef
DECL|typedef|GimpViewableClass
typedef|typedef
name|struct
name|_GimpViewableClass
name|GimpViewableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpViewable
struct|struct
name|_GimpViewable
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
comment|/*<  private>*/
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpViewableClass
struct|struct
name|_GimpViewableClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|default_stock_id
specifier|const
name|gchar
modifier|*
name|default_stock_id
decl_stmt|;
DECL|member|name_changed_signal
specifier|const
name|gchar
modifier|*
name|name_changed_signal
decl_stmt|;
comment|/*  signals  */
DECL|member|invalidate_preview
name|void
function_decl|(
modifier|*
name|invalidate_preview
function_decl|)
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
DECL|member|size_changed
name|void
function_decl|(
modifier|*
name|size_changed
function_decl|)
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|get_preview_size
name|void
function_decl|(
modifier|*
name|get_preview_size
function_decl|)
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|is_popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
DECL|member|get_popup_size
name|gboolean
function_decl|(
modifier|*
name|get_popup_size
function_decl|)
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
DECL|member|get_preview
name|TempBuf
modifier|*
function_decl|(
modifier|*
name|get_preview
function_decl|)
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
DECL|member|get_new_preview
name|TempBuf
modifier|*
function_decl|(
modifier|*
name|get_new_preview
function_decl|)
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
DECL|member|get_description
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_description
function_decl|)
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_viewable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_viewable_invalidate_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_viewable_size_changed
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_viewable_calc_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|aspect_width
parameter_list|,
name|gint
name|aspect_height
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|,
name|gint
modifier|*
name|return_width
parameter_list|,
name|gint
modifier|*
name|return_height
parameter_list|,
name|gboolean
modifier|*
name|scaling_up
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_viewable_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_viewable_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_viewable_get_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_viewable_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_viewable_get_preview_pixbuf
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_viewable_get_new_preview_pixbuf
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_viewable_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_viewable_get_stock_id
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_viewable_set_stock_id
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_VIEWABLE_H__ */
end_comment

end_unit

