begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorhexentry.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_COLOR_HEX_ENTRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_HEX_ENTRY_H__
define|#
directive|define
name|__GIMP_COLOR_HEX_ENTRY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_COLOR_HEX_ENTRY
define|#
directive|define
name|GIMP_TYPE_COLOR_HEX_ENTRY
value|(gimp_color_hex_entry_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_HEX_ENTRY (obj)
define|#
directive|define
name|GIMP_COLOR_HEX_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_HEX_ENTRY, GimpColorHexEntry))
end_define

begin_define
DECL|macro|GIMP_COLOR_HEX_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_HEX_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_HEX_ENTRY, GimpColorHexEntryClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_HEX_ENTRY (obj)
define|#
directive|define
name|GIMP_IS_COLOR_HEX_ENTRY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_HEX_ENTRY))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_HEX_ENTRY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_HEX_ENTRY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_HEX_ENTRY))
end_define

begin_define
DECL|macro|GIMP_COLOR_HEX_ENTRY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_HEX_ENTRY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_HEX_AREA, GimpColorHexEntryClass))
end_define

begin_typedef
DECL|typedef|GimpColorHexEntryClass
typedef|typedef
name|struct
name|_GimpColorHexEntryClass
name|GimpColorHexEntryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorHexEntry
struct|struct
name|_GimpColorHexEntry
block|{
DECL|member|parent_instance
name|GtkEntry
name|parent_instance
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorHexEntryClass
struct|struct
name|_GimpColorHexEntryClass
block|{
DECL|member|parent_class
name|GtkEntryClass
name|parent_class
decl_stmt|;
DECL|member|color_changed
name|void
function_decl|(
modifier|*
name|color_changed
function_decl|)
parameter_list|(
name|GimpColorHexEntry
modifier|*
name|entry
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
name|gimp_color_hex_entry_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_hex_entry_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_hex_entry_set_color
parameter_list|(
name|GimpColorHexEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_hex_entry_get_color
parameter_list|(
name|GimpColorHexEntry
modifier|*
name|entry
parameter_list|,
name|GimpRGB
modifier|*
name|color
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
comment|/* __GIMP_COLOR_HEX_ENTRY_H__ */
end_comment

end_unit

