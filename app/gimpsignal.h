begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SIGNAL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SIGNAL_H__
define|#
directive|define
name|__GIMP_SIGNAL_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtksignal.h>
end_include

begin_comment
comment|/* This is the gtk "signal id" */
end_comment

begin_typedef
DECL|typedef|GimpSignalID
typedef|typedef
name|guint
name|GimpSignalID
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSignalType
typedef|typedef
specifier|const
name|struct
name|_GimpSignalType
name|GimpSignalType
typedef|;
end_typedef

begin_comment
comment|/* The arguments are encoded in the names.. */
end_comment

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_void
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerVoid
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerVoid
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_pointer
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerPointer
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerPointer
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|p
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_int
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerInt
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerInt
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gint
name|i
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_double
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerDouble
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerDouble
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gdouble
name|d
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_int_int_int
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerIntIntInt
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerIntIntInt
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gint
name|i1
parameter_list|,
name|gint
name|i2
parameter_list|,
name|gint
name|i3
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_int_int_int_int
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerIntIntIntInt
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerIntIntIntInt
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gint
name|i1
parameter_list|,
name|gint
name|i2
parameter_list|,
name|gint
name|i3
parameter_list|,
name|gint
name|i4
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GimpSignalID
name|gimp_signal_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GtkSignalRunType
name|signal_flags
parameter_list|,
name|GtkType
name|object_type
parameter_list|,
name|guint
name|function_offset
parameter_list|,
name|GimpSignalType
modifier|*
name|sig_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SIGNAL_H__ */
end_comment

end_unit

