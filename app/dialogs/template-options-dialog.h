begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TEMPLATE_OPTIONS_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__TEMPLATE_OPTIONS_DIALOG_H__
define|#
directive|define
name|__TEMPLATE_OPTIONS_DIALOG_H__
end_define

begin_typedef
DECL|typedef|TemplateOptionsDialog
typedef|typedef
name|struct
name|_TemplateOptionsDialog
name|TemplateOptionsDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_TemplateOptionsDialog
struct|struct
name|_TemplateOptionsDialog
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|editor
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|template
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|TemplateOptionsDialog
modifier|*
name|template_options_dialog_new
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TEMPLATE_OPTIONS_DIALOG_H__ */
end_comment

end_unit

