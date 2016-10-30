begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptemplateeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"template-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

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
DECL|member|template
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|callback
name|GimpTemplateOptionsCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|editor
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|template_options_dialog_free
parameter_list|(
name|TemplateOptionsDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|template_options_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateOptionsDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public function  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|template_options_dialog_new (GimpTemplate * template,GimpContext * context,GtkWidget * parent,const gchar * title,const gchar * role,const gchar * icon_name,const gchar * desc,const gchar * help_id,GimpTemplateOptionsCallback callback,gpointer user_data)
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
name|icon_name
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
parameter_list|,
name|GimpTemplateOptionsCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|TemplateOptionsDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|template
operator|==
name|NULL
operator|||
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|role
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|desc
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_slice_new0
argument_list|(
name|TemplateOptionsDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|template
operator|=
name|template
expr_stmt|;
name|private
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|private
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|private
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
if|if
condition|(
name|template
condition|)
block|{
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|template
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|template
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_image
argument_list|)
argument_list|)
expr_stmt|;
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|template
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|viewable
argument_list|,
name|context
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|icon_name
argument_list|,
name|desc
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|help_id
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|template_options_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|template_options_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|private
operator|->
name|editor
operator|=
name|gimp_template_editor_new
argument_list|(
name|template
argument_list|,
name|context
operator|->
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|private
operator|->
name|editor
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|template_options_dialog_free (TemplateOptionsDialog * private)
name|template_options_dialog_free
parameter_list|(
name|TemplateOptionsDialog
modifier|*
name|private
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|TemplateOptionsDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|template_options_dialog_response (GtkWidget * dialog,gint response_id,TemplateOptionsDialog * private)
name|template_options_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateOptionsDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpTemplateEditor
modifier|*
name|editor
init|=
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|private
operator|->
name|editor
argument_list|)
decl_stmt|;
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|private
operator|->
name|template
argument_list|,
name|gimp_template_editor_get_template
argument_list|(
name|editor
argument_list|)
argument_list|,
name|private
operator|->
name|context
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

