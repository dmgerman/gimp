begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpmath.h  *  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPMATH_H__
end_ifndef

begin_define
DECL|macro|__GIMPMATH_H__
define|#
directive|define
name|__GIMPMATH_H__
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
include|#
directive|include
file|<math.h>
comment|/* Some portability enhancing stuff. For use both by the gimp app  * as well as plug-ins and modules.  *  * Include this instead of just<math.h>.  */
ifndef|#
directive|ifndef
name|G_PI
comment|/* G_PI will be in GLib eventually */
DECL|macro|G_PI
define|#
directive|define
name|G_PI
value|3.14159265358979323846
endif|#
directive|endif
ifndef|#
directive|ifndef
name|G_PI_2
comment|/* As will G_PI_2 */
DECL|macro|G_PI_2
define|#
directive|define
name|G_PI_2
value|1.57079632679489661923
endif|#
directive|endif
ifndef|#
directive|ifndef
name|G_PI_4
comment|/* As will G_PI_4 */
DECL|macro|G_PI_4
define|#
directive|define
name|G_PI_4
value|0.78539816339744830962
endif|#
directive|endif
ifndef|#
directive|ifndef
name|G_SQRT2
comment|/* As will G_SQRT2 */
DECL|macro|G_SQRT2
define|#
directive|define
name|G_SQRT2
value|1.4142135623730951
endif|#
directive|endif
ifndef|#
directive|ifndef
name|RAND_MAX
DECL|macro|G_MAXRAND
define|#
directive|define
name|G_MAXRAND
value|G_MAXINT
else|#
directive|else
define|#
directive|define
name|G_MAXRAND
value|RAND_MAX
endif|#
directive|endif
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
comment|/* limit a (0->511) int to 255 */
DECL|macro|MAX255 (a)
define|#
directive|define
name|MAX255
parameter_list|(
name|a
parameter_list|)
value|((a) | (((a)& 256) - (((a)& 256)>> 8)))
comment|/* clamp a>>int32<<-range int between 0 and 255 inclusive */
comment|/* broken! -> #define CLAMP0255(a)  ((a& 0xFFFFFF00)? (~(a>>31)) : a) */
DECL|macro|CLAMP0255 (a)
define|#
directive|define
name|CLAMP0255
parameter_list|(
name|a
parameter_list|)
value|CLAMP(a,0,255)
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
comment|/*  __GIMPMATH_H__  */
end_comment

end_unit

