begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpunitmenu.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UNIT_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNIT_MENU_H__
define|#
directive|define
name|__GIMP_UNIT_MENU_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpunit.h"
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
DECL|macro|GIMP_TYPE_UNIT_MENU
define|#
directive|define
name|GIMP_TYPE_UNIT_MENU
value|(gimp_unit_menu_get_type ())
DECL|macro|GIMP_UNIT_MENU (obj)
define|#
directive|define
name|GIMP_UNIT_MENU
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_UNIT_MENU, GimpUnitMenu))
DECL|macro|GIMP_UNIT_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_UNIT_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNIT_MENU, GimpUnitMenuClass))
DECL|macro|GIMP_IS_UNIT_MENU (obj)
define|#
directive|define
name|GIMP_IS_UNIT_MENU
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_UNIT_MENU))
DECL|macro|GIMP_IS_UNIT_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNIT_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNIT_MENU))
DECL|typedef|GimpUnitMenu
typedef|typedef
name|struct
name|_GimpUnitMenu
name|GimpUnitMenu
typedef|;
DECL|typedef|GimpUnitMenuClass
typedef|typedef
name|struct
name|_GimpUnitMenuClass
name|GimpUnitMenuClass
typedef|;
DECL|struct|_GimpUnitMenu
struct|struct
name|_GimpUnitMenu
block|{
DECL|member|optionmenu
name|GtkOptionMenu
name|optionmenu
decl_stmt|;
comment|/* private stuff */
DECL|member|selection
name|GtkWidget
modifier|*
name|selection
decl_stmt|;
DECL|member|clist
name|GtkWidget
modifier|*
name|clist
decl_stmt|;
comment|/* public */
DECL|member|format
name|gchar
modifier|*
name|format
decl_stmt|;
DECL|member|unit
name|GUnit
name|unit
decl_stmt|;
DECL|member|start
name|GUnit
name|start
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpUnitMenuClass
struct|struct
name|_GimpUnitMenuClass
block|{
DECL|member|parent_class
name|GtkOptionMenuClass
name|parent_class
decl_stmt|;
DECL|member|gimp_unit_menu
name|void
function_decl|(
modifier|*
name|gimp_unit_menu
function_decl|)
parameter_list|(
name|GimpUnitMenu
modifier|*
name|gum
parameter_list|)
function_decl|;
block|}
struct|;
name|guint
name|gimp_unit_menu_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
comment|/* format      -- a printf-like format string for the menu items  * unit        -- the unit selected on widget creation  * with_pixels -- should the menu contain 'pixels' ?  * with_custom -- should the menu contain an item 'More...' to pop up  *                the custom unit browser (not yet implemented)  *  *            the format string supports the following percent expansions:  *  *            %f -- factor (how many units make up an inch)  *            %y -- symbol ("''" for inch)  *            %a -- abbreviation  *            %s -- singular  *            %p -- plural  *            %% -- literal percent  */
name|GtkWidget
modifier|*
name|gimp_unit_menu_new
parameter_list|(
name|gchar
modifier|*
name|format
parameter_list|,
name|GUnit
name|unit
parameter_list|,
name|gboolean
name|with_pixels
parameter_list|,
name|gboolean
name|with_custom
parameter_list|)
function_decl|;
name|void
name|gimp_unit_menu_set_unit
parameter_list|(
name|GimpUnitMenu
modifier|*
name|gum
parameter_list|,
name|GUnit
name|unit
parameter_list|)
function_decl|;
name|GUnit
name|gimp_unit_menu_get_unit
parameter_list|(
name|GimpUnitMenu
modifier|*
name|gum
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
comment|/* __GIMP_UNIT_MENU_H__ */
end_comment

end_unit

