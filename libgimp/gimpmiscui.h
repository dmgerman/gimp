begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmiscui.h  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk   *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MISCUI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MISCUI_H__
define|#
directive|define
name|__GIMP_MISCUI_H__
end_define

begin_include
include|#
directive|include
file|<libgimp/gimptypes.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/* Preview stuff. WARNING: don't use this in new code!!!!!!!  * It's just here to extract some general preview stuff from plug-ins so  * that it will be easier to change them when we have a real effect preview  * widget.  * Don't say I didn't warn you (Maurits).  */
end_comment

begin_typedef
DECL|struct|__anon29c50e590108
typedef|typedef
struct|struct
block|{
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|cache
name|guchar
modifier|*
name|cache
decl_stmt|;
DECL|member|even
name|guchar
modifier|*
name|even
decl_stmt|;
DECL|member|odd
name|guchar
modifier|*
name|odd
decl_stmt|;
DECL|member|buffer
name|guchar
modifier|*
name|buffer
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|rowstride
name|gint
name|rowstride
decl_stmt|;
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
DECL|member|cmap
name|guchar
modifier|*
name|cmap
decl_stmt|;
DECL|member|ncolors
name|gint
name|ncolors
decl_stmt|;
DECL|member|scale_x
name|gdouble
name|scale_x
decl_stmt|;
DECL|member|scale_y
name|gdouble
name|scale_y
decl_stmt|;
DECL|typedef|GimpFixMePreview
block|}
name|GimpFixMePreview
typedef|;
end_typedef

begin_function_decl
name|GimpFixMePreview
modifier|*
name|gimp_fixme_preview_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|has_frame
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_fixme_preview_free
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_fixme_preview_fill_with_thumb
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_fixme_preview_fill
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_fixme_preview_do_row
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|width
parameter_list|,
name|guchar
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_plug_in_parse_path
parameter_list|(
name|gchar
modifier|*
name|path_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dir_name
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MISCUI_H__ */
end_comment

end_unit

