begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpstock.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_STOCK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_STOCK_H__
define|#
directive|define
name|__GIMP_STOCK_H__
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
comment|/* For information look into the C source or the html documentation */
DECL|macro|GIMP_STOCK_ANCHOR
define|#
directive|define
name|GIMP_STOCK_ANCHOR
value|"gimp-anchor"
DECL|macro|GIMP_STOCK_DELETE
define|#
directive|define
name|GIMP_STOCK_DELETE
value|"gimp-delete"
DECL|macro|GIMP_STOCK_DUPLICATE
define|#
directive|define
name|GIMP_STOCK_DUPLICATE
value|"gimp-duplicate"
DECL|macro|GIMP_STOCK_EDIT
define|#
directive|define
name|GIMP_STOCK_EDIT
value|"gimp-edit"
DECL|macro|GIMP_STOCK_LOWER
define|#
directive|define
name|GIMP_STOCK_LOWER
value|"gimp-lower"
DECL|macro|GIMP_STOCK_NEW
define|#
directive|define
name|GIMP_STOCK_NEW
value|"gimp-new"
DECL|macro|GIMP_STOCK_PASTE
define|#
directive|define
name|GIMP_STOCK_PASTE
value|"gimp-paste"
DECL|macro|GIMP_STOCK_PASTE_AS_NEW
define|#
directive|define
name|GIMP_STOCK_PASTE_AS_NEW
value|"gimp-paste-as-new"
DECL|macro|GIMP_STOCK_PASTE_INTO
define|#
directive|define
name|GIMP_STOCK_PASTE_INTO
value|"gimp-paste-into"
DECL|macro|GIMP_STOCK_RAISE
define|#
directive|define
name|GIMP_STOCK_RAISE
value|"gimp-raise"
DECL|macro|GIMP_STOCK_REFRESH
define|#
directive|define
name|GIMP_STOCK_REFRESH
value|"gimp-refresh"
DECL|macro|GIMP_STOCK_RESET
define|#
directive|define
name|GIMP_STOCK_RESET
value|"gimp-reset"
DECL|macro|GIMP_STOCK_TO_PATH
define|#
directive|define
name|GIMP_STOCK_TO_PATH
value|"gimp-to-path"
DECL|macro|GIMP_STOCK_TO_SELECTION
define|#
directive|define
name|GIMP_STOCK_TO_SELECTION
value|"gimp-to-selection"
DECL|macro|GIMP_STOCK_ZOOM_IN
define|#
directive|define
name|GIMP_STOCK_ZOOM_IN
value|"gimp-zoom-in"
DECL|macro|GIMP_STOCK_ZOOM_OUT
define|#
directive|define
name|GIMP_STOCK_ZOOM_OUT
value|"gimp-zoom-out"
name|void
name|gimp_stock_init
parameter_list|(
name|void
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
comment|/* __GIMP_STOCK_H__ */
end_comment

end_unit

