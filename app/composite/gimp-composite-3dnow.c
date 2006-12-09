begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * Gimp image compositing  * Copyright (C) 2003  Helvetix Victorinox, a pseudonym,<helvetix@gimp.org>  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimp-composite-3dnow.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|COMPILE_3DNOW_IS_OKAY
end_ifdef

begin_endif
endif|#
directive|endif
end_endif

end_unit

