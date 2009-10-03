begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDisplayOptions  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_OPTIONS_H__
define|#
directive|define
name|__GIMP_DISPLAY_OPTIONS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DISPLAY_OPTIONS
define|#
directive|define
name|GIMP_TYPE_DISPLAY_OPTIONS
value|(gimp_display_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_TYPE_DISPLAY_OPTIONS_FULLSCREEN
define|#
directive|define
name|GIMP_TYPE_DISPLAY_OPTIONS_FULLSCREEN
value|(gimp_display_options_fullscreen_get_type ())
end_define

begin_define
DECL|macro|GIMP_TYPE_DISPLAY_OPTIONS_NO_IMAGE
define|#
directive|define
name|GIMP_TYPE_DISPLAY_OPTIONS_NO_IMAGE
value|(gimp_display_options_no_image_get_type ())
end_define

begin_define
DECL|macro|GIMP_DISPLAY_OPTIONS (obj)
define|#
directive|define
name|GIMP_DISPLAY_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DISPLAY_OPTIONS, GimpDisplayOptions))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_DISPLAY_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DISPLAY_OPTIONS, GimpDisplayOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_DISPLAY_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DISPLAY_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DISPLAY_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DISPLAY_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DISPLAY_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DISPLAY_OPTIONS, GimpDisplayOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpDisplayOptionsClass
typedef|typedef
name|struct
name|_GimpDisplayOptionsClass
name|GimpDisplayOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDisplayOptions
struct|struct
name|_GimpDisplayOptions
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
comment|/*  GimpImageWindow options  */
DECL|member|show_menubar
name|gboolean
name|show_menubar
decl_stmt|;
DECL|member|show_statusbar
name|gboolean
name|show_statusbar
decl_stmt|;
comment|/*  GimpDisplayShell options  */
DECL|member|show_rulers
name|gboolean
name|show_rulers
decl_stmt|;
DECL|member|show_scrollbars
name|gboolean
name|show_scrollbars
decl_stmt|;
comment|/*  GimpCanvas options  */
DECL|member|show_selection
name|gboolean
name|show_selection
decl_stmt|;
DECL|member|show_layer_boundary
name|gboolean
name|show_layer_boundary
decl_stmt|;
DECL|member|show_guides
name|gboolean
name|show_guides
decl_stmt|;
DECL|member|show_grid
name|gboolean
name|show_grid
decl_stmt|;
DECL|member|show_sample_points
name|gboolean
name|show_sample_points
decl_stmt|;
DECL|member|padding_mode
name|GimpCanvasPaddingMode
name|padding_mode
decl_stmt|;
DECL|member|padding_color
name|GimpRGB
name|padding_color
decl_stmt|;
DECL|member|padding_mode_set
name|gboolean
name|padding_mode_set
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDisplayOptionsClass
struct|struct
name|_GimpDisplayOptionsClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_display_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GType
name|gimp_display_options_fullscreen_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GType
name|gimp_display_options_no_image_get_type
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
comment|/* __GIMP_DISPLAY_OPTIONS_H__ */
end_comment

end_unit

