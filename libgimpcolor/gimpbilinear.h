begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BILINEAR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BILINEAR_H__
define|#
directive|define
name|__GIMP_BILINEAR_H__
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
comment|/*  bilinear interpolation functions taken from LibGCK  */
name|gdouble
name|gimp_bilinear
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|values
parameter_list|)
function_decl|;
name|guchar
name|gimp_bilinear_8
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guchar
modifier|*
name|values
parameter_list|)
function_decl|;
name|guint16
name|gimp_bilinear_16
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint16
modifier|*
name|values
parameter_list|)
function_decl|;
name|guint32
name|gimp_bilinear_32
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint32
modifier|*
name|values
parameter_list|)
function_decl|;
name|GimpRGB
name|gimp_bilinear_rgb
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|values
parameter_list|)
function_decl|;
name|GimpRGB
name|gimp_bilinear_rgba
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|values
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
comment|/* __GIMP_BILINEAR_H__ */
end_comment

end_unit

