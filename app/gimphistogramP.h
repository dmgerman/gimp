begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphistogram module Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HISTOGRAM_P_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HISTOGRAM_P_H__
define|#
directive|define
name|__GIMP_HISTOGRAM_P_H__
end_define

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_MP
end_ifdef

begin_include
include|#
directive|include
file|<pthread.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_struct
DECL|struct|_GimpHistogram
struct|struct
name|_GimpHistogram
block|{
DECL|member|bins
name|int
name|bins
decl_stmt|;
DECL|member|values
name|double
modifier|*
modifier|*
name|values
decl_stmt|;
DECL|member|nchannels
name|int
name|nchannels
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
DECL|member|mutex
name|pthread_mutex_t
name|mutex
decl_stmt|;
DECL|member|nthreads
name|int
name|nthreads
decl_stmt|;
DECL|member|tmp_values
name|double
modifier|*
modifier|*
modifier|*
name|tmp_values
decl_stmt|;
DECL|member|tmp_slots
name|char
modifier|*
name|tmp_slots
decl_stmt|;
endif|#
directive|endif
comment|/* ENABLE_MP */
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HISTOGRAM_P_H__ */
end_comment

end_unit

