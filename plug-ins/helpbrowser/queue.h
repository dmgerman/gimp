begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help Browser  * Copyright (C) 1999 Sven Neumann<sven@gimp.org>  *                    Michael Natterer<mitschel@cs.tu-berlin.de>  *  * Some code& ideas stolen from the GNOME help browser.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GIMP_HELP_QUEUE_H_
end_ifndef

begin_define
DECL|macro|_GIMP_HELP_QUEUE_H_
define|#
directive|define
name|_GIMP_HELP_QUEUE_H_
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_typedef
DECL|typedef|Queue
typedef|typedef
name|struct
name|_Queue
name|Queue
typedef|;
end_typedef

begin_function_decl
name|Queue
modifier|*
name|queue_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|queue_free
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|queue_prev
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gint
modifier|*
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|queue_next
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gint
modifier|*
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|queue_move_prev
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|queue_move_next
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|queue_add
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gchar
modifier|*
name|ref
parameter_list|,
name|gint
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|queue_mark_current
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gint
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|queue_isnext
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|queue_isprev
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _GIMP_HELP_QUEUE_H_ */
end_comment

end_unit

