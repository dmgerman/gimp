begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_MESSAGE_WINDOW_H_
end_ifndef

begin_define
DECL|macro|_MESSAGE_WINDOW_H_
define|#
directive|define
name|_MESSAGE_WINDOW_H_
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
DECL|macro|MESSAGE_WINDOW (obj)
define|#
directive|define
name|MESSAGE_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST(obj, message_window_get_type(), MessageWindow)
DECL|macro|MESSAGE_WINDOW_CLASS (klass)
define|#
directive|define
name|MESSAGE_WINDOW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST(klass, message_window_get_type(), MessageWindowClass)
DECL|macro|IS_MESSAGE_WINDOW (obj)
define|#
directive|define
name|IS_MESSAGE_WINDOW
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE(obj, message_window_get_type())
DECL|typedef|MessageWindow
typedef|typedef
name|struct
name|_MessageWindow
name|MessageWindow
typedef|;
DECL|typedef|MessageWindowClass
typedef|typedef
name|struct
name|_MessageWindowClass
name|MessageWindowClass
typedef|;
DECL|struct|_MessageWindow
struct|struct
name|_MessageWindow
block|{
DECL|member|window
name|GtkWindow
name|window
decl_stmt|;
DECL|member|text
name|GtkWidget
modifier|*
name|text
decl_stmt|;
DECL|member|dismiss_button
name|GtkWidget
modifier|*
name|dismiss_button
decl_stmt|;
DECL|member|contains_messages
name|guint
name|contains_messages
range|:
literal|1
decl_stmt|;
block|}
struct|;
DECL|struct|_MessageWindowClass
struct|struct
name|_MessageWindowClass
block|{
DECL|member|parent_class
name|GtkWindowClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|guint
name|message_window_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|message_window_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
function_decl|;
name|void
name|message_window_clear
parameter_list|(
name|MessageWindow
modifier|*
name|mw
parameter_list|)
function_decl|;
name|void
name|message_window_append
parameter_list|(
name|MessageWindow
modifier|*
name|mw
parameter_list|,
specifier|const
name|gchar
modifier|*
name|msg
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
comment|/* _MESSAGE_WINDOW_H_ */
end_comment

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit

