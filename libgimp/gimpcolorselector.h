begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Colour selector module (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU Lesser General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_SELECTOR_H__
end_ifndef

begin_define
DECL|macro|__COLOR_SELECTOR_H__
define|#
directive|define
name|__COLOR_SELECTOR_H__
end_define

begin_comment
comment|/* For information look at the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpColorSelector_Callback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorSelector_Callback
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpColorSelector_NewFunc
typedef|typedef
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|GimpColorSelector_NewFunc
function_decl|)
parameter_list|(
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|GimpColorSelector_Callback
name|cb
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gpointer
modifier|*
name|selector_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpColorSelector_FreeFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorSelector_FreeFunc
function_decl|)
parameter_list|(
name|gpointer
name|selector_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpColorSelector_SetColorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorSelector_SetColorFunc
function_decl|)
parameter_list|(
name|gpointer
name|selector_data
parameter_list|,
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|gboolean
name|set_current
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpColorSelectorMethods
typedef|typedef
name|struct
name|_GimpColorSelectorMethods
name|GimpColorSelectorMethods
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorSelectorMethods
struct|struct
name|_GimpColorSelectorMethods
block|{
DECL|member|new
name|GimpColorSelector_NewFunc
name|new
decl_stmt|;
DECL|member|free
name|GimpColorSelector_FreeFunc
name|free
decl_stmt|;
DECL|member|setcolor
name|GimpColorSelector_SetColorFunc
name|setcolor
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpColorSelectorID
typedef|typedef
name|gpointer
name|GimpColorSelectorID
typedef|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_NOTEBOOK_C__
end_ifndef

begin_comment
comment|/*  Bypass when compiling the source for these functions.  */
end_comment

begin_function_decl
name|GimpColorSelectorID
name|gimp_color_selector_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_page
parameter_list|,
name|GimpColorSelectorMethods
modifier|*
name|methods
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpColorSelectorFinishedCB
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorSelectorFinishedCB
function_decl|)
parameter_list|(
name|gpointer
name|finished_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|gboolean
name|gimp_color_selector_unregister
parameter_list|(
name|GimpColorSelectorID
name|id
parameter_list|,
name|GimpColorSelectorFinishedCB
name|finished_cb
parameter_list|,
name|gpointer
name|finished_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !__COLOR_NOTEBOOK_C__ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __COLOR_SELECTOR_H__ */
end_comment

end_unit

