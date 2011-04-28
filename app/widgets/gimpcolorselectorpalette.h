begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorselectorpalette.h  * Copyright (C) 2006 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_SELECTOR_PALETTE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_SELECTOR_PALETTE_H__
define|#
directive|define
name|__GIMP_COLOR_SELECTOR_PALETTE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_COLOR_SELECTOR_PALETTE
define|#
directive|define
name|GIMP_TYPE_COLOR_SELECTOR_PALETTE
value|(gimp_color_selector_palette_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTOR_PALETTE (obj)
define|#
directive|define
name|GIMP_COLOR_SELECTOR_PALETTE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_SELECTOR_PALETTE, GimpColorSelectorPalette))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SELECTOR_PALETTE (obj)
define|#
directive|define
name|GIMP_IS_COLOR_SELECTOR_PALETTE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_SELECTOR_PALETTE))
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTOR_PALETTE_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_SELECTOR_PALETTE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_SELECTOR_PALETTE, GimpColorSelectorPaletteClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SELECTOR_PALETTE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_SELECTOR_PALETTE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_SELECTOR_PALETTE))
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTOR_PALETTE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_SELECTOR_PALETTE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_SELECTOR_PALETTE, GimpColorSelectorPaletteClass))
end_define

begin_typedef
DECL|typedef|GimpColorSelectorPalette
typedef|typedef
name|struct
name|_GimpColorSelectorPalette
name|GimpColorSelectorPalette
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorSelectorPaletteClass
typedef|typedef
name|struct
name|_GimpColorSelectorPaletteClass
name|GimpColorSelectorPaletteClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorSelectorPalette
struct|struct
name|_GimpColorSelectorPalette
block|{
DECL|member|parent_instance
name|GimpColorSelector
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorSelectorPaletteClass
struct|struct
name|_GimpColorSelectorPaletteClass
block|{
DECL|member|parent_class
name|GimpColorSelectorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_selector_palette_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_SELECTOR_PALETTE_H__ */
end_comment

end_unit

