begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmisc.h  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk   *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MISC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MISC_H__
define|#
directive|define
name|__GIMP_MISC_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|enum
DECL|enum|__anon2901475e0103
type|{
DECL|enumerator|PIXEL_WRAP
name|PIXEL_WRAP
decl_stmt|,
DECL|enumerator|PIXEL_SMEAR
name|PIXEL_SMEAR
decl_stmt|,
DECL|enumerator|PIXEL_BLACK
name|PIXEL_BLACK
decl_stmt|,
end_decl_stmt

begin_typedef
unit|};
DECL|typedef|GimpPixelFetcher
typedef|typedef
name|struct
name|_GimpPixelFetcher
name|GimpPixelFetcher
typedef|;
end_typedef

begin_function_decl
name|GimpPixelFetcher
modifier|*
name|gimp_pixel_fetcher_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pixel_fetcher_set_bg_color
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pixel_fetcher_set_shadow
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|gboolean
name|shadow
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pixel_fetcher_get_pixel
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
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

begin_function_decl
name|void
name|gimp_pixel_fetcher_get_pixel2
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|wrapmode
parameter_list|,
name|guchar
modifier|*
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pixel_fetcher_put_pixel
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
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
name|gimp_pixel_fetcher_destroy
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_get_bg_guchar
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|transparent
parameter_list|,
name|guchar
modifier|*
name|bg
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|GimpRgnFunc1
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRgnFunc1
function_decl|)
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpRgnFunc2
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRgnFunc2
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
name|void
name|gimp_rgn_iterate1
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpRgnFunc1
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rgn_iterate2
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpRgnFunc2
name|func
parameter_list|,
name|gpointer
name|data
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
comment|/* __GIMP_MISC_H__ */
end_comment

end_unit

