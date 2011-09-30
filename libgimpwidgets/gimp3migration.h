begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp3migration.h  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_3_MIGRATION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_3_MIGRATION_H__
define|#
directive|define
name|__GIMP_3_MIGRATION_H__
end_define

begin_comment
comment|/* This file is evil. Its purpose is to keep GIMP's gtk3-port branch  * managable, and contains functions that are only in GTK+ 3.x but  * are *not* in GTK+ 2.x. Please just ignore the uglyness and move  * along. This file will be removed in GIMP 3.  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_box_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|,
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_3_MIGRATION_H__ */
end_comment

end_unit

