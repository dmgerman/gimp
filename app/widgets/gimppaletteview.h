begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppaletteview.h  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PALETTE_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PALETTE_VIEW_H__
define|#
directive|define
name|__GIMP_PALETTE_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PALETTE_VIEW
define|#
directive|define
name|GIMP_TYPE_PALETTE_VIEW
value|(gimp_palette_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_PALETTE_VIEW (obj)
define|#
directive|define
name|GIMP_PALETTE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PALETTE_VIEW, GimpPaletteView))
end_define

begin_define
DECL|macro|GIMP_PALETTE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_PALETTE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PALETTE_VIEW, GimpPaletteViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_PALETTE_VIEW (obj)
define|#
directive|define
name|GIMP_IS_PALETTE_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_PALETTE_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_PALETTE_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PALETTE_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PALETTE_VIEW))
end_define

begin_define
DECL|macro|GIMP_PALETTE_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PALETTE_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PALETTE_VIEW, GimpPaletteViewClass))
end_define

begin_typedef
DECL|typedef|GimpPaletteViewClass
typedef|typedef
name|struct
name|_GimpPaletteViewClass
name|GimpPaletteViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaletteView
struct|struct
name|_GimpPaletteView
block|{
DECL|member|parent_instance
name|GimpView
name|parent_instance
decl_stmt|;
DECL|member|selected
name|GimpPaletteEntry
modifier|*
name|selected
decl_stmt|;
DECL|member|dnd_entry
name|GimpPaletteEntry
modifier|*
name|dnd_entry
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaletteViewClass
struct|struct
name|_GimpPaletteViewClass
block|{
DECL|member|parent_class
name|GimpViewClass
name|parent_class
decl_stmt|;
DECL|member|entry_clicked
name|void
function_decl|(
modifier|*
name|entry_clicked
function_decl|)
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
DECL|member|entry_selected
name|void
function_decl|(
modifier|*
name|entry_selected
function_decl|)
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
DECL|member|entry_activated
name|void
function_decl|(
modifier|*
name|entry_activated
function_decl|)
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
DECL|member|entry_context
name|void
function_decl|(
modifier|*
name|entry_context
function_decl|)
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
DECL|member|color_dropped
name|void
function_decl|(
modifier|*
name|color_dropped
function_decl|)
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_palette_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_palette_view_select_entry
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PALETTE_VIEW_H__ */
end_comment

end_unit

