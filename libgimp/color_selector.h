begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Colour selector module (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU Lesser General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
comment|/********************************/
end_comment

begin_comment
comment|/* color selector registration */
end_comment

begin_comment
comment|/* A function of this type should be called by the color selector each  * time the user modifies the selected color. */
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
name|void
modifier|*
name|data
parameter_list|,
name|int
name|r
parameter_list|,
name|int
name|g
parameter_list|,
name|int
name|b
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* A function of this type is called to create a new instance of the  * color selector.  The new selector should set its current color to  * the RGB triple given (each component is in the range 0 - 255  * inclusive, with white at 255,255,255 and black at 0,0,0).  *  * The selector should call "cb" with argument "data" each time the  * user modifies the selected color.  *  * The selector must return a GtkWidget which implements the color  * selection UI.  The selector can optionally return "selector_data",  * an opaque pointer which will be passed in to subsequent invokations  * on the selector. */
end_comment

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
name|int
name|r
parameter_list|,
name|int
name|g
parameter_list|,
name|int
name|b
parameter_list|,
name|GimpColorSelector_Callback
name|cb
parameter_list|,
name|void
modifier|*
name|data
parameter_list|,
name|void
modifier|*
modifier|*
name|selector_data
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* A function of this type is called when the color selector is no  * longer required.  This function should not free widgets that are  * containted within the UI widget returned by new(), since they are  * destroyed on behalf of the selector by the caller of this  * function. */
end_comment

begin_typedef
DECL|typedef|GimpColorSelector_FreeFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorSelector_FreeFunc
function_decl|)
parameter_list|(
name|void
modifier|*
name|selector_data
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* A function of this type is called to change the selector's current  * color.  The required color is specified as in the new() function.  * If the "set_current" parameter is FALSE, then only the old color  * should be set - if "set_current" is TRUE, both the old color and  * the current color should be set to the RGB triple given.  This  * function merely gives a hint to the color selector; the selector  * can choose to ignore this information. */
end_comment

begin_typedef
DECL|typedef|GimpColorSelector_SetColorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorSelector_SetColorFunc
function_decl|)
parameter_list|(
name|void
modifier|*
name|selector_data
parameter_list|,
name|int
name|r
parameter_list|,
name|int
name|g
parameter_list|,
name|int
name|b
parameter_list|,
name|int
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
name|void
modifier|*
name|GimpColorSelectorID
typedef|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_NOTEBOOK_C__
end_ifndef

begin_comment
comment|/* Bypass when compiling the source for 				 * these functions. */
end_comment

begin_comment
comment|/* Register a color selector.  Returns an identifier for the color  * selector on success, or NULL if the name is already in use.  Both  * the name and method table are internalised, so may be freed after  * this call. */
end_comment

begin_function_decl
name|GimpColorSelectorID
name|gimp_color_selector_register
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
specifier|const
name|char
modifier|*
name|help_page
parameter_list|,
name|GimpColorSelectorMethods
modifier|*
name|methods
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Remove the selector "id" from active service.  New instances of the  * selector will not be created, but existing ones are allowed to  * continue.  If "callback" is non-NULL, it will be called once all  * instances have finished.  The callback could be used to unload  * dynamiclly loaded code, for example.  *  * Returns TRUE on success, FALSE if "id" was not found. */
end_comment

begin_function_decl
name|gboolean
name|gimp_color_selector_unregister
parameter_list|(
name|GimpColorSelectorID
name|id
parameter_list|,
name|void
function_decl|(
modifier|*
name|callback
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
parameter_list|,
name|void
modifier|*
name|data
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

