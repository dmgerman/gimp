begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_function_decl
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpRunMode
name|runmode
parameter_list|,
name|gboolean
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_function_decl
name|gint32
name|load_thumbnail_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

end_unit

