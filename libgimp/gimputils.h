begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimputils.h  *  * Copyright (C) 2000 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPUTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMPUTILS_H__
define|#
directive|define
name|__GIMPUTILS_H__
end_define

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
comment|/* For information look into the C source or the html documentation */
comment|/*    *  Right now all you find here is the g_strescape function out of   *  glib-1.3. We need its functionality, but don't want to rely on  *  that version being installed   */
if|#
directive|if
operator|(
name|defined
argument_list|(
name|GLIB_CHECK_VERSION
argument_list|)
operator|&&
name|GLIB_CHECK_VERSION
argument_list|(
literal|1
operator|,
literal|3
operator|,
literal|1
argument_list|)
operator|)
DECL|macro|gimp_strescape (string,exceptions)
define|#
directive|define
name|gimp_strescape
parameter_list|(
name|string
parameter_list|,
name|exceptions
parameter_list|)
value|g_strescape (string, exceptions)
else|#
directive|else
name|gchar
modifier|*
name|gimp_strescape
parameter_list|(
specifier|const
name|gchar
modifier|*
name|source
parameter_list|,
specifier|const
name|gchar
modifier|*
name|exceptions
parameter_list|)
function_decl|;
endif|#
directive|endif
comment|/* GLIB<= 1.3 */
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
comment|/* __GIMPUTILS_H__ */
end_comment

end_unit

