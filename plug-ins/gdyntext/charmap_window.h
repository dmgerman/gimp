begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_CHARMAP_WINDOW_H_
end_ifndef

begin_define
DECL|macro|_CHARMAP_WINDOW_H_
define|#
directive|define
name|_CHARMAP_WINDOW_H_
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
DECL|macro|CHARMAP_WINDOW (obj)
define|#
directive|define
name|CHARMAP_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST(obj, charmap_window_get_type(), CharMapWindow)
DECL|macro|CHARMAP_WINDOW_CLASS (klass)
define|#
directive|define
name|CHARMAP_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST(klass, charmap_window_get_type(), CharMapWindowClass)
DECL|macro|IS_CHARMAP_WINDOW (obj)
define|#
directive|define
name|IS_CHARMAP_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE(obj, charmap_window_get_type())
DECL|typedef|CharMapWindow
typedef|typedef
name|struct
name|_CharMapWindow
name|CharMapWindow
typedef|;
DECL|typedef|CharMapWindowClass
typedef|typedef
name|struct
name|_CharMapWindowClass
name|CharMapWindowClass
typedef|;
DECL|struct|_CharMapWindow
struct|struct
name|_CharMapWindow
block|{
DECL|member|window
name|GtkWindow
name|window
decl_stmt|;
DECL|member|charmap
name|GtkWidget
modifier|*
name|charmap
decl_stmt|;
DECL|member|scrolledwindow
name|GtkWidget
modifier|*
name|scrolledwindow
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|insert_button
name|GtkWidget
modifier|*
name|insert_button
decl_stmt|;
DECL|member|close_button
name|GtkWidget
modifier|*
name|close_button
decl_stmt|;
block|}
struct|;
DECL|struct|_CharMapWindowClass
struct|struct
name|_CharMapWindowClass
block|{
DECL|member|parent_class
name|GtkWindowClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|guint
name|charmap_window_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|charmap_window_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
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
comment|/* _CHARMAP_WINDOW_H_ */
end_comment

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit

