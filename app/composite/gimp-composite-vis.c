begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * -*- mode: c tab-width: 2; c-basic-indent: 2; indent-tabs-mode: nil -*-  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * Gimp image compositing  * Copyright (C) 2003  Helvetix Victorinox, a pseudonym,<helvetix@gimp.org>  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"base/base-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite.h"
end_include

begin_include
include|#
directive|include
file|"gimp-composite-vis.h"
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|USE_VIS
argument_list|)
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|ARCH_SPARC
argument_list|)
end_if

begin_if
if|#
directive|if
name|__GNUC__
operator|>=
literal|3
end_if

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GNUC__> 3 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(ARCH_SPARC) */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(USE_VIS) */
end_comment

begin_function
name|int
DECL|function|gimp_composite_vis_init (void)
name|gimp_composite_vis_init
parameter_list|(
name|void
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|ARCH_SPARC
return|return
operator|(
literal|1
operator|)
return|;
else|#
directive|else
return|return
operator|(
literal|0
operator|)
return|;
endif|#
directive|endif
block|}
end_function

end_unit

