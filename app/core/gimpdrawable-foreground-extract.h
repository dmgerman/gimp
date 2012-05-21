begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
literal|0
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_FOREGROUND_EXTRACT_H__
end_ifndef

begin_define
define|#
directive|define
name|__GIMP_DRAWABLE_FOREGROUND_EXTRACT_H__
end_define

begin_comment
comment|/*  general API (as seen from the PDB)  */
end_comment

begin_comment
unit|void       gimp_drawable_foreground_extract (GimpDrawable              *drawable,                                              GimpForegroundExtractMode  mode,                                              GimpDrawable              *mask,                                              GimpProgress              *progress);
comment|/*  SIOX specific API  */
end_comment

begin_endif
unit|SioxState * gimp_drawable_foreground_extract_siox_init   (GimpDrawable *drawable,                                                           gint          x,                                                           gint          y,                                                           gint          width,                                                           gint          height); void        gimp_drawable_foreground_extract_siox  (GimpDrawable       *mask,                                                     SioxState          *state,                                                     SioxRefinementType  refinemane,                                                     gint                smoothness,                                                     const gdouble       sensitivity[3],                                                     gboolean            multiblob,                                                     GimpProgress       *progress); void        gimp_drawable_foreground_extract_siox_done (SioxState      *state);
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAWABLE_FOREGROUND_EXTRACT_H__  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

