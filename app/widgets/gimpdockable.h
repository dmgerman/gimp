begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockable.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DOCKABLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DOCKABLE_H__
define|#
directive|define
name|__GIMP_DOCKABLE_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkbin.h>
end_include

begin_typedef
DECL|typedef|GimpDockableGetPreviewFunc
typedef|typedef
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|GimpDockableGetPreviewFunc
function_decl|)
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|,
name|gpointer
name|get_preview_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDockableSetContextFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDockableSetContextFunc
function_decl|)
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DOCKABLE
define|#
directive|define
name|GIMP_TYPE_DOCKABLE
value|(gimp_dockable_get_type ())
end_define

begin_define
DECL|macro|GIMP_DOCKABLE (obj)
define|#
directive|define
name|GIMP_DOCKABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DOCKABLE, GimpDockable))
end_define

begin_define
DECL|macro|GIMP_DOCKABLE_CLASS (klass)
define|#
directive|define
name|GIMP_DOCKABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DOCKABLE, GimpDockableClass))
end_define

begin_define
DECL|macro|GIMP_IS_DOCKABLE (obj)
define|#
directive|define
name|GIMP_IS_DOCKABLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DOCKABLE))
end_define

begin_define
DECL|macro|GIMP_IS_DOCKABLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DOCKABLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DOCKABLE))
end_define

begin_define
DECL|macro|GIMP_DOCKABLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DOCKABLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DOCKABLE, GimpDockableClass))
end_define

begin_typedef
DECL|typedef|GimpDockableClass
typedef|typedef
name|struct
name|_GimpDockableClass
name|GimpDockableClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDockable
struct|struct
name|_GimpDockable
block|{
DECL|member|parent_instance
name|GtkBin
name|parent_instance
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|member|stock_id
name|gchar
modifier|*
name|stock_id
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|tab_style
name|GimpTabStyle
name|tab_style
decl_stmt|;
DECL|member|dockbook
name|GimpDockbook
modifier|*
name|dockbook
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|get_preview_func
name|GimpDockableGetPreviewFunc
name|get_preview_func
decl_stmt|;
DECL|member|get_preview_data
name|gpointer
name|get_preview_data
decl_stmt|;
DECL|member|set_context_func
name|GimpDockableSetContextFunc
name|set_context_func
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDockableClass
struct|struct
name|_GimpDockableClass
block|{
DECL|member|parent_class
name|GtkBinClass
name|parent_class
decl_stmt|;
DECL|member|get_tab_widget
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|get_tab_widget
function_decl|)
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
DECL|member|set_context
name|void
function_decl|(
modifier|*
name|set_context
function_decl|)
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dockable_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dockable_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpDockableGetPreviewFunc
name|get_preview_func
parameter_list|,
name|gpointer
name|get_preview_data
parameter_list|,
name|GimpDockableSetContextFunc
name|set_context_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dockable_get_tab_widget
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpTabStyle
name|tab_style
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dockable_set_context
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DOCKABLE_H__ */
end_comment

end_unit

