begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmath.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MATH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MATH_H__
define|#
directive|define
name|__GIMP_MATH_H__
end_define

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_IEEEFP_H
end_ifdef

begin_include
include|#
directive|include
file|<ieeefp.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<float.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<libgimpmath/gimpmathtypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpmatrix.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpmd5.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpvector.h>
end_include

begin_expr_stmt
name|G_BEGIN_DECLS
comment|/* Some portability enhancing stuff. For use both by the gimp app  * as well as plug-ins and modules.  *  * Include this instead of just<math.h>.  */
comment|/* Use RINT() instead of rint() */
ifdef|#
directive|ifdef
name|HAVE_RINT
DECL|macro|RINT (x)
define|#
directive|define
name|RINT
parameter_list|(
name|x
parameter_list|)
value|rint(x)
else|#
directive|else
define|#
directive|define
name|RINT
parameter_list|(
name|x
parameter_list|)
value|floor ((x) + 0.5)
endif|#
directive|endif
DECL|macro|ROUND (x)
define|#
directive|define
name|ROUND
parameter_list|(
name|x
parameter_list|)
value|((int) ((x) + 0.5))
comment|/* Square */
DECL|macro|SQR (x)
define|#
directive|define
name|SQR
parameter_list|(
name|x
parameter_list|)
value|((x) * (x))
comment|/* Limit a (0->511) int to 255 */
DECL|macro|MAX255 (a)
define|#
directive|define
name|MAX255
parameter_list|(
name|a
parameter_list|)
value|((a) | (((a)& 256) - (((a)& 256)>> 8)))
comment|/* Clamp a>>int32<<-range int between 0 and 255 inclusive */
DECL|macro|CLAMP0255 (a)
define|#
directive|define
name|CLAMP0255
parameter_list|(
name|a
parameter_list|)
value|CLAMP(a,0,255)
DECL|macro|gimp_deg_to_rad (angle)
define|#
directive|define
name|gimp_deg_to_rad
parameter_list|(
name|angle
parameter_list|)
value|((angle) * (2.0 * G_PI) / 360.0)
DECL|macro|gimp_rad_to_deg (angle)
define|#
directive|define
name|gimp_rad_to_deg
parameter_list|(
name|angle
parameter_list|)
value|((angle) * 360.0 / (2.0 * G_PI))
name|G_END_DECLS
end_expr_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MATH_H__ */
end_comment

end_unit

