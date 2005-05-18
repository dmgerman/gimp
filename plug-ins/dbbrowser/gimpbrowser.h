begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrowser.h  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BROWSER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BROWSER_H__
define|#
directive|define
name|__GIMP_BROWSER_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkhpaned.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_BROWSER
define|#
directive|define
name|GIMP_TYPE_BROWSER
value|(gimp_browser_get_type ())
end_define

begin_define
DECL|macro|GIMP_BROWSER (obj)
define|#
directive|define
name|GIMP_BROWSER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BROWSER, GimpBrowser))
end_define

begin_define
DECL|macro|GIMP_BROWSER_CLASS (klass)
define|#
directive|define
name|GIMP_BROWSER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BROWSER, GimpBrowserClass))
end_define

begin_define
DECL|macro|GIMP_IS_BROWSER (obj)
define|#
directive|define
name|GIMP_IS_BROWSER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BROWSER))
end_define

begin_define
DECL|macro|GIMP_IS_BROWSER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BROWSER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BROWSER))
end_define

begin_define
DECL|macro|GIMP_BROWSER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BROWSER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BROWSER, GimpBrowserClass))
end_define

begin_typedef
DECL|typedef|GimpBrowser
typedef|typedef
name|struct
name|_GimpBrowser
name|GimpBrowser
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrowserClass
typedef|typedef
name|struct
name|_GimpBrowserClass
name|GimpBrowserClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrowser
struct|struct
name|_GimpBrowser
block|{
DECL|member|parent_instance
name|GtkHPaned
name|parent_instance
decl_stmt|;
DECL|member|left_vbox
name|GtkWidget
modifier|*
name|left_vbox
decl_stmt|;
DECL|member|search_entry
name|GtkWidget
modifier|*
name|search_entry
decl_stmt|;
DECL|member|search_timeout_id
name|guint
name|search_timeout_id
decl_stmt|;
DECL|member|search_type_combo
name|GtkWidget
modifier|*
name|search_type_combo
decl_stmt|;
DECL|member|search_type
name|gint
name|search_type
decl_stmt|;
DECL|member|count_label
name|GtkWidget
modifier|*
name|count_label
decl_stmt|;
DECL|member|right_vbox
name|GtkWidget
modifier|*
name|right_vbox
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrowserClass
struct|struct
name|_GimpBrowserClass
block|{
DECL|member|parent_class
name|GtkHPanedClass
name|parent_class
decl_stmt|;
DECL|member|search
name|void
function_decl|(
modifier|*
name|search
function_decl|)
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
name|gint
name|search_type
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_browser_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_browser_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_browser_add_search_types
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|first_type_label
parameter_list|,
name|gint
name|first_type_id
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_browser_set_widget
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_browser_show_message
parameter_list|(
name|GimpBrowser
modifier|*
name|browser
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BROWSER_H__  */
end_comment

end_unit

