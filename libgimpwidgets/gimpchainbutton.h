begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This implements a widget derived from gtk_button that visualizes    it's state with two different pixmaps showing a closed and a     broken chain. It's intented to be used with the gimpsizeentry    widget. The usage is quite similar to the one the gtk_toggle_button    provides.   */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHAIN_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHAIN_BUTTON_H__
define|#
directive|define
name|__GIMP_CHAIN_BUTTON_H__
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
DECL|macro|GIMP_TYPE_CHAIN_BUTTON
define|#
directive|define
name|GIMP_TYPE_CHAIN_BUTTON
value|(gimp_chain_button_get_type ())
DECL|macro|GIMP_CHAIN_BUTTON (obj)
define|#
directive|define
name|GIMP_CHAIN_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_CHAIN_BUTTON, GimpChainButton))
DECL|macro|GIMP_CHAIN_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_CHAIN_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CHAIN_BUTTON, GimpChainButtonClass))
DECL|macro|GIMP_IS_CHAIN_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_CHAIN_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_CHAIN_BUTTON))
DECL|macro|GIMP_IS_CHAIN_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CHAIN_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CHAIN_BUTTON))
DECL|typedef|GimpChainButton
typedef|typedef
name|struct
name|_GimpChainButton
name|GimpChainButton
typedef|;
DECL|typedef|GimpChainButtonClass
typedef|typedef
name|struct
name|_GimpChainButtonClass
name|GimpChainButtonClass
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28a193c30103
block|{
DECL|enumerator|GIMP_CHAIN_TOP
name|GIMP_CHAIN_TOP
block|,
DECL|enumerator|GIMP_CHAIN_LEFT
name|GIMP_CHAIN_LEFT
block|,
DECL|enumerator|GIMP_CHAIN_BOTTOM
name|GIMP_CHAIN_BOTTOM
block|,
DECL|enumerator|GIMP_CHAIN_RIGHT
name|GIMP_CHAIN_RIGHT
DECL|typedef|GimpChainPosition
block|}
name|GimpChainPosition
typedef|;
DECL|struct|_GimpChainButton
struct|struct
name|_GimpChainButton
block|{
DECL|member|table
name|GtkTable
name|table
decl_stmt|;
DECL|member|position
name|GimpChainPosition
name|position
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|line1
name|GtkWidget
modifier|*
name|line1
decl_stmt|;
DECL|member|line2
name|GtkWidget
modifier|*
name|line2
decl_stmt|;
DECL|member|pixmap
name|GtkWidget
modifier|*
name|pixmap
decl_stmt|;
DECL|member|broken
name|GdkPixmap
modifier|*
name|broken
decl_stmt|;
DECL|member|broken_mask
name|GdkBitmap
modifier|*
name|broken_mask
decl_stmt|;
DECL|member|chain
name|GdkPixmap
modifier|*
name|chain
decl_stmt|;
DECL|member|chain_mask
name|GdkBitmap
modifier|*
name|chain_mask
decl_stmt|;
DECL|member|active
name|gboolean
name|active
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpChainButtonClass
struct|struct
name|_GimpChainButtonClass
block|{
DECL|member|parent_class
name|GtkButtonClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|GtkType
name|gimp_chain_button_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_chain_button_new
parameter_list|(
name|GimpChainPosition
name|position
parameter_list|)
function_decl|;
name|void
name|gimp_chain_button_set_active
parameter_list|(
name|GimpChainButton
modifier|*
name|gcb
parameter_list|,
name|gboolean
name|is_active
parameter_list|)
function_decl|;
name|gboolean
name|gimp_chain_button_get_active
parameter_list|(
name|GimpChainButton
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
comment|/* __CHAIN_BUTTON_H__ */
end_comment

end_unit

