begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpcolorbutton.h  * Copyright (C) 1999-2001 Sven Neumann  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This provides a button with a color preview. The preview  * can handle transparency by showing the checkerboard.  * On click, a color selector is opened, which is already  * fully functional wired to the preview button.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_BUTTON_H__
define|#
directive|define
name|__GIMP_COLOR_BUTTON_H__
end_define

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpbutton.h>
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
DECL|macro|GIMP_TYPE_COLOR_BUTTON
define|#
directive|define
name|GIMP_TYPE_COLOR_BUTTON
value|(gimp_color_button_get_type ())
DECL|macro|GIMP_COLOR_BUTTON (obj)
define|#
directive|define
name|GIMP_COLOR_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_BUTTON, GimpColorButton))
DECL|macro|GIMP_COLOR_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_BUTTON, GimpColorButtonClass))
DECL|macro|GIMP_IS_COLOR_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_COLOR_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_BUTTON))
DECL|macro|GIMP_IS_COLOR_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_BUTTON))
DECL|macro|GIMP_COLOR_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_BUTTON, GimpColorButtonClass))
DECL|typedef|GimpColorButtonClass
typedef|typedef
name|struct
name|_GimpColorButtonClass
name|GimpColorButtonClass
typedef|;
DECL|struct|_GimpColorButton
struct|struct
name|_GimpColorButton
block|{
DECL|member|parent_instance
name|GimpButton
name|parent_instance
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|color_area
name|GtkWidget
modifier|*
name|color_area
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|item_factory
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpColorButtonClass
struct|struct
name|_GimpColorButtonClass
block|{
DECL|member|parent_class
name|GimpButtonClass
name|parent_class
decl_stmt|;
DECL|member|color_changed
name|void
function_decl|(
modifier|*
name|color_changed
function_decl|)
parameter_list|(
name|GimpColorButton
modifier|*
name|gcb
parameter_list|)
function_decl|;
block|}
struct|;
name|GType
name|gimp_color_button_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_color_button_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
function_decl|;
name|void
name|gimp_color_button_set_color
parameter_list|(
name|GimpColorButton
modifier|*
name|gcb
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
name|void
name|gimp_color_button_get_color
parameter_list|(
name|GimpColorButton
modifier|*
name|gcb
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
name|gboolean
name|gimp_color_button_has_alpha
parameter_list|(
name|GimpColorButton
modifier|*
name|gcb
parameter_list|)
function_decl|;
name|void
name|gimp_color_button_set_type
parameter_list|(
name|GimpColorButton
modifier|*
name|gcb
parameter_list|,
name|GimpColorAreaType
name|alpha
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
comment|/* __GIMP_COLOR_BUTTON_H__ */
end_comment

end_unit

