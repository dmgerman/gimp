begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UI_H__
define|#
directive|define
name|__GIMP_UI_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpchainbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpcolorbutton.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpdialog.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpexport.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpfileselection.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimphelpui.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppatheditor.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppixmap.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpquerybox.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpsizeentry.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpunitmenu.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpwidgets.h>
end_include

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
comment|/* For information look into the C source or the html documentation */
name|void
name|gimp_ui_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
name|gboolean
name|preview
parameter_list|)
function_decl|;
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
comment|/* __GIMP_UI_H__ */
end_comment

end_unit

