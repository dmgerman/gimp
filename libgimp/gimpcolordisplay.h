begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU Lesser General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_DISPLAY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_DISPLAY_H__
define|#
directive|define
name|__GIMP_COLOR_DISPLAY_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<gmodule.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpparasite.h>
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
comment|/* For information look at the html documentation */
DECL|typedef|GimpColorDisplayInit
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorDisplayInit
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayNew
typedef|typedef
name|gpointer
function_decl|(
modifier|*
name|GimpColorDisplayNew
function_decl|)
parameter_list|(
name|gint
name|type
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayClone
typedef|typedef
name|gpointer
function_decl|(
modifier|*
name|GimpColorDisplayClone
function_decl|)
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayConvert
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorDisplayConvert
function_decl|)
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayDestroy
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorDisplayDestroy
function_decl|)
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayFinalize
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorDisplayFinalize
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayLoadState
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorDisplayLoadState
function_decl|)
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplaySaveState
typedef|typedef
name|GimpParasite
modifier|*
function_decl|(
modifier|*
name|GimpColorDisplaySaveState
function_decl|)
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayConfigure
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorDisplayConfigure
function_decl|)
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|,
name|GFunc
name|ok_func
parameter_list|,
name|gpointer
name|ok_data
parameter_list|,
name|GFunc
name|cancel_func
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayConfigureCancel
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpColorDisplayConfigureCancel
function_decl|)
parameter_list|(
name|gpointer
name|cd_ID
parameter_list|)
function_decl|;
DECL|typedef|GimpColorDisplayMethods
typedef|typedef
name|struct
name|_GimpColorDisplayMethods
name|GimpColorDisplayMethods
typedef|;
DECL|struct|_GimpColorDisplayMethods
struct|struct
name|_GimpColorDisplayMethods
block|{
DECL|member|init
name|GimpColorDisplayInit
name|init
decl_stmt|;
DECL|member|new
name|GimpColorDisplayNew
name|new
decl_stmt|;
DECL|member|clone
name|GimpColorDisplayClone
name|clone
decl_stmt|;
DECL|member|convert
name|GimpColorDisplayConvert
name|convert
decl_stmt|;
DECL|member|destroy
name|GimpColorDisplayDestroy
name|destroy
decl_stmt|;
DECL|member|finalize
name|GimpColorDisplayFinalize
name|finalize
decl_stmt|;
DECL|member|load
name|GimpColorDisplayLoadState
name|load
decl_stmt|;
DECL|member|save
name|GimpColorDisplaySaveState
name|save
decl_stmt|;
DECL|member|configure
name|GimpColorDisplayConfigure
name|configure
decl_stmt|;
DECL|member|cancel
name|GimpColorDisplayConfigureCancel
name|cancel
decl_stmt|;
block|}
struct|;
comment|/*  The following two functions are implemted and exported by gimp/app  *  but need to be marked for it here too ...  */
name|G_MODULE_EXPORT
name|gboolean
name|gimp_color_display_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpColorDisplayMethods
modifier|*
name|methods
parameter_list|)
function_decl|;
name|G_MODULE_EXPORT
name|gboolean
name|gimp_color_display_unregister
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
comment|/* __GIMP_COLOR_DISPLAY_H__ */
end_comment

end_unit

