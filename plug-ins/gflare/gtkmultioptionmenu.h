begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the Free  * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_comment
comment|/*   Modified 97-06-26	Eiichi Takamori<taka@ma1.seikyou.ne.jp>   GtkMultiOptionMenu, taken from GtkOptionMenu, can work with   hierarchal menus.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GTK_MULTI_OPTION_MENU_H__
end_ifndef

begin_define
DECL|macro|__GTK_MULTI_OPTION_MENU_H__
define|#
directive|define
name|__GTK_MULTI_OPTION_MENU_H__
end_define

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtkbutton.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GTK_MULTI_OPTION_MENU (obj)
define|#
directive|define
name|GTK_MULTI_OPTION_MENU
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, gtk_multi_option_menu_get_type (), GtkMultiOptionMenu)
DECL|macro|GTK_MULTI_OPTION_MENU_CLASS (klass)
define|#
directive|define
name|GTK_MULTI_OPTION_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, gtk_multi_option_menu_get_type (), GtkMultiOptionMenuClass)
DECL|macro|GTK_IS_MULTI_OPTION_MENU (obj)
define|#
directive|define
name|GTK_IS_MULTI_OPTION_MENU
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, gtk_multi_option_menu_get_type ())
DECL|typedef|GtkMultiOptionMenu
typedef|typedef
name|struct
name|_GtkMultiOptionMenu
name|GtkMultiOptionMenu
typedef|;
DECL|typedef|GtkMultiOptionMenuClass
typedef|typedef
name|struct
name|_GtkMultiOptionMenuClass
name|GtkMultiOptionMenuClass
typedef|;
DECL|struct|_GtkMultiOptionMenu
struct|struct
name|_GtkMultiOptionMenu
block|{
DECL|member|button
name|GtkButton
name|button
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
DECL|member|menu_item
name|GtkWidget
modifier|*
name|menu_item
decl_stmt|;
DECL|member|width
name|guint16
name|width
decl_stmt|;
DECL|member|height
name|guint16
name|height
decl_stmt|;
block|}
struct|;
DECL|struct|_GtkMultiOptionMenuClass
struct|struct
name|_GtkMultiOptionMenuClass
block|{
DECL|member|parent_class
name|GtkButtonClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|guint
name|gtk_multi_option_menu_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gtk_multi_option_menu_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gtk_multi_option_menu_get_menu
parameter_list|(
name|GtkMultiOptionMenu
modifier|*
name|multi_option_menu
parameter_list|)
function_decl|;
name|void
name|gtk_multi_option_menu_set_menu
parameter_list|(
name|GtkMultiOptionMenu
modifier|*
name|multi_option_menu
parameter_list|,
name|GtkWidget
modifier|*
name|menu
parameter_list|)
function_decl|;
name|void
name|gtk_multi_option_menu_remove_menu
parameter_list|(
name|GtkMultiOptionMenu
modifier|*
name|multi_option_menu
parameter_list|)
function_decl|;
name|void
name|gtk_multi_option_menu_set_history
parameter_list|(
name|GtkMultiOptionMenu
modifier|*
name|multi_option_menu
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GTK_MULTI_OPTION_MENU_H__ */
end_comment

end_unit

