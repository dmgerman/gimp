begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMPOLDPREVIEW  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpoldpreview.h  * This file contains the implementation of the gimpoldpreview widget  * which is used by a few plug-ins.  This shouldn't be used by any  * foreign plug-in, because it uses some deprecated stuff.  We only  * used it there since we do not a better preview widget for now.  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OLD_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OLD_PREVIEW_H__
define|#
directive|define
name|__GIMP_OLD_PREVIEW_H__
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
typedef|typedef
struct|struct
DECL|struct|__anon2af2498e0108
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
comment|/* bpp of the drawable */
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
DECL|member|is_gray
name|gboolean
name|is_gray
decl_stmt|;
DECL|typedef|GimpOldPreview
block|}
name|GimpOldPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOldPreviewFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpOldPreviewFunc
function_decl|)
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GimpOldPreview
modifier|*
name|gimp_old_preview_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpOldPreview
modifier|*
name|gimp_old_preview_new2
parameter_list|(
name|GimpImageType
name|drawable_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_old_preview_free
parameter_list|(
name|GimpOldPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_old_preview_update
parameter_list|(
name|GimpOldPreview
modifier|*
name|preview
parameter_list|,
name|GimpOldPreviewFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_old_preview_fill_with_thumb
parameter_list|(
name|GimpOldPreview
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
name|gimp_old_preview_fill
parameter_list|(
name|GimpOldPreview
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
name|gimp_old_preview_fill_scaled
parameter_list|(
name|GimpOldPreview
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
name|gimp_old_preview_do_row
parameter_list|(
name|GimpOldPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_old_preview_put_pixel
parameter_list|(
name|GimpOldPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_old_preview_get_pixel
parameter_list|(
name|GimpOldPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|pixel
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
comment|/* __GIMP_OLD_PREVIEW_H__ */
end_comment

end_unit

