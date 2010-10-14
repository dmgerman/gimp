begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpunitmenu.h  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

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

begin_ifdef
ifdef|#
directive|ifdef
name|GTK_DISABLE_DEPRECATED
end_ifdef

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtkoptionmenu.h>
end_include

begin_define
DECL|macro|GTK_DISABLE_DEPRECATED
define|#
directive|define
name|GTK_DISABLE_DEPRECATED
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_UNIT_MENU
define|#
directive|define
name|GIMP_TYPE_UNIT_MENU
value|(gimp_unit_menu_get_type ())
end_define

begin_define
DECL|macro|GIMP_UNIT_MENU (obj)
define|#
directive|define
name|GIMP_UNIT_MENU
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UNIT_MENU, GimpUnitMenu))
end_define

begin_define
DECL|macro|GIMP_UNIT_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_UNIT_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNIT_MENU, GimpUnitMenuClass))
end_define

begin_define
DECL|macro|GIMP_IS_UNIT_MENU (obj)
define|#
directive|define
name|GIMP_IS_UNIT_MENU
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_UNIT_MENU))
end_define

begin_define
DECL|macro|GIMP_IS_UNIT_MENU_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNIT_MENU_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNIT_MENU))
end_define

begin_define
DECL|macro|GIMP_UNIT_MENU_GET_CLASS (obj)
define|#
directive|define
name|GIMP_UNIT_MENU_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_UNIT_MENU, GimpUnitMenuClass))
end_define

begin_typedef
DECL|typedef|GimpUnitMenuClass
typedef|typedef
name|struct
name|_GimpUnitMenuClass
name|GimpUnitMenuClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUnitMenu
struct|struct
name|_GimpUnitMenu
block|{
DECL|member|parent_instance
name|GtkOptionMenu
name|parent_instance
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
DECL|member|pixel_digits
name|gint
name|pixel_digits
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
DECL|member|tv
name|GtkWidget
modifier|*
name|tv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
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
name|menu
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
name|gimp_unit_menu_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_unit_menu_new
parameter_list|(
specifier|const
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
end_function_decl

begin_function_decl
name|void
name|gimp_unit_menu_set_unit
parameter_list|(
name|GimpUnitMenu
modifier|*
name|menu
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_unit_menu_get_unit
parameter_list|(
name|GimpUnitMenu
modifier|*
name|menu
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_menu_set_pixel_digits
parameter_list|(
name|GimpUnitMenu
modifier|*
name|menu
parameter_list|,
name|gint
name|digits
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_unit_menu_get_pixel_digits
parameter_list|(
name|GimpUnitMenu
modifier|*
name|menu
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
comment|/* __GIMP_UNIT_MENU_H__ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

end_unit

