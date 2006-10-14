begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DIALOGS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__DIALOGS_TYPES_H__
define|#
directive|define
name|__DIALOGS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"display/display-types.h"
end_include

begin_typedef
DECL|typedef|GimpScaleCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpScaleCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|,
name|GimpUnit
name|resolution_unit
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DIALOGS_TYPES_H__ */
end_comment

end_unit

