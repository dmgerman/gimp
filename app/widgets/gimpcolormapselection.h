begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLORMAP_SELECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLORMAP_SELECTION_H__
define|#
directive|define
name|__GIMP_COLORMAP_SELECTION_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_COLORMAP_SELECTION
define|#
directive|define
name|GIMP_TYPE_COLORMAP_SELECTION
value|(gimp_colormap_selection_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLORMAP_SELECTION (obj)
define|#
directive|define
name|GIMP_COLORMAP_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLORMAP_SELECTION, GimpColormapSelection))
end_define

begin_define
DECL|macro|GIMP_COLORMAP_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_COLORMAP_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLORMAP_SELECTION, GimpColormapSelectionClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLORMAP_SELECTION (obj)
define|#
directive|define
name|GIMP_IS_COLORMAP_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLORMAP_SELECTION))
end_define

begin_define
DECL|macro|GIMP_IS_COLORMAP_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLORMAP_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLORMAP_SELECTION))
end_define

begin_define
DECL|macro|GIMP_COLORMAP_SELECTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLORMAP_SELECTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLORMAP_SELECTION, GimpColormapSelectionClass))
end_define

begin_typedef
DECL|typedef|GimpColormapSelectionClass
typedef|typedef
name|struct
name|_GimpColormapSelectionClass
name|GimpColormapSelectionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColormapSelection
struct|struct
name|_GimpColormapSelection
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|active_image
name|GimpImage
modifier|*
name|active_image
decl_stmt|;
DECL|member|active_palette
name|GimpPalette
modifier|*
name|active_palette
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
DECL|member|col_index
name|gint
name|col_index
decl_stmt|;
DECL|member|layout
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
DECL|member|index_adjustment
name|GtkAdjustment
modifier|*
name|index_adjustment
decl_stmt|;
DECL|member|index_spinbutton
name|GtkWidget
modifier|*
name|index_spinbutton
decl_stmt|;
DECL|member|color_entry
name|GtkWidget
modifier|*
name|color_entry
decl_stmt|;
DECL|member|color_dialog
name|GtkWidget
modifier|*
name|color_dialog
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
DECL|struct|_GimpColormapSelectionClass
struct|struct
name|_GimpColormapSelectionClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|color_context
name|void
function_decl|(
modifier|*
name|color_context
function_decl|)
parameter_list|(
name|GimpColormapSelection
modifier|*
name|selection
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
DECL|member|color_clicked
name|void
function_decl|(
modifier|*
name|color_clicked
function_decl|)
parameter_list|(
name|GimpColormapSelection
modifier|*
name|selection
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
DECL|member|color_activated
name|void
function_decl|(
modifier|*
name|color_activated
function_decl|)
parameter_list|(
name|GimpColormapSelection
modifier|*
name|selection
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_colormap_selection_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_colormap_selection_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_colormap_selection_get_index
parameter_list|(
name|GimpColormapSelection
modifier|*
name|selection
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|search
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_colormap_selection_set_index
parameter_list|(
name|GimpColormapSelection
modifier|*
name|selection
parameter_list|,
name|gint
name|index
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_colormap_selection_max_index
parameter_list|(
name|GimpColormapSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLORMAP_SELECTION_H__ */
end_comment

end_unit

