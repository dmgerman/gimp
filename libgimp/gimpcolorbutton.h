begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * Gimp Color Button  * Copyright (C) 1999 Sven Neumann  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
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
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_COLOR_BUTTON, GimpColorButton))
DECL|macro|GIMP_COLOR_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_BUTTON, GimpColorButtonClass))
DECL|macro|GIMP_IS_COLOR_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_COLOR_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_COLOR_BUTTON))
DECL|macro|GIMP_IS_COLOR_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_BUTTON))
DECL|typedef|GimpColorButton
typedef|typedef
name|struct
name|_GimpColorButton
name|GimpColorButton
typedef|;
DECL|typedef|GimpColorButtonClass
typedef|typedef
name|struct
name|_GimpColorButtonClass
name|GimpColorButtonClass
typedef|;
DECL|struct|_GimpColorButtonClass
struct|struct
name|_GimpColorButtonClass
block|{
DECL|member|parent_class
name|GtkButtonClass
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
name|GtkType
name|gimp_color_button_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_color_button_new
parameter_list|(
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
name|guchar
modifier|*
name|color
parameter_list|,
name|gint
name|bpp
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_color_button_double_new
parameter_list|(
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
name|gdouble
modifier|*
name|color
parameter_list|,
name|gint
name|bpp
parameter_list|)
function_decl|;
name|void
name|gimp_color_button_update
parameter_list|(
name|GimpColorButton
modifier|*
name|gcb
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
comment|/* __COLOR_BUTTON_H__ */
end_comment

end_unit

