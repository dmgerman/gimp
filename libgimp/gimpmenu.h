begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MENU_H__
define|#
directive|define
name|__GIMP_MENU_H__
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
DECL|typedef|GimpConstraintFunc
typedef|typedef
name|gint
function_decl|(
modifier|*
name|GimpConstraintFunc
function_decl|)
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|typedef|GimpMenuCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpMenuCallback
function_decl|)
parameter_list|(
name|gint32
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
comment|/* Popup the brush dialog interactively */
DECL|typedef|GRunBrushCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GRunBrushCallback
function_decl|)
parameter_list|(
name|gchar
modifier|*
parameter_list|,
comment|/* Name */
name|gdouble
parameter_list|,
comment|/* opacity */
name|gint
parameter_list|,
comment|/* spacing */
name|gint
parameter_list|,
comment|/* paint_mode */
name|gint
parameter_list|,
comment|/* width */
name|gint
parameter_list|,
comment|/* height */
name|gchar
modifier|*
parameter_list|,
comment|/* mask data */
name|gint
comment|/* dialog closing */
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_image_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_image
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_layer_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_layer
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_channel_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_channel
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_drawable_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_drawable
parameter_list|)
function_decl|;
name|void
name|gimp_interactive_selection_brush
parameter_list|(
name|gchar
modifier|*
name|dialogname
parameter_list|,
name|gchar
modifier|*
name|brush_name
parameter_list|,
name|GRunBrushCallback
name|callback
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
comment|/* __GIMP_MENU_H__ */
end_comment

end_unit

