begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpunitmenu.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpunit.h"
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
comment|/* public (read only) */
DECL|member|format
name|gchar
modifier|*
name|format
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|show_pixels
name|gboolean
name|show_pixels
decl_stmt|;
DECL|member|show_percent
name|gboolean
name|show_percent
decl_stmt|;
comment|/* private */
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
DECL|member|unit_changed
name|void
function_decl|(
modifier|*
name|unit_changed
function_decl|)
parameter_list|(
name|GimpUnitMenu
modifier|*
name|gum
parameter_list|)
function_decl|;
block|}
struct|;
comment|/* For information look into the C source or the html documentation */
name|GtkType
name|gimp_unit_menu_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_unit_menu_new
parameter_list|(
name|gchar
modifier|*
name|format
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|show_pixels
parameter_list|,
name|gboolean
name|show_percent
parameter_list|,
name|gboolean
name|show_custom
parameter_list|)
function_decl|;
name|void
name|gimp_unit_menu_set_unit
parameter_list|(
name|GimpUnitMenu
modifier|*
name|gum
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|GimpUnit
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

