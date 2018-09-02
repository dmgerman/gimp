begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbacktrace-backend.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BACKTRACE_BACKEND_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BACKTRACE_BACKEND_H__
define|#
directive|define
name|__GIMP_BACKTRACE_BACKEND_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__gnu_linux__
end_ifdef

begin_define
DECL|macro|GIMP_BACKTRACE_BACKEND_LINUX
define|#
directive|define
name|GIMP_BACKTRACE_BACKEND_LINUX
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|GIMP_BACKTRACE_BACKEND_NONE
define|#
directive|define
name|GIMP_BACKTRACE_BACKEND_NONE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BACKTRACE_BACKEND_H__  */
end_comment

end_unit

