begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"text/gimpfont.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpbrushselect.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpfontselect.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpgradientselect.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppaletteselect.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppatternselect.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpprogressdialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"actions/plug-in-actions.h"
end_include

begin_include
include|#
directive|include
file|"menus/menus.h"
end_include

begin_include
include|#
directive|include
file|"gui-message.h"
end_include

begin_include
include|#
directive|include
file|"gui-vtable.h"
end_include

begin_include
include|#
directive|include
file|"themes.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gui_ungrab
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_threads_enter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_threads_leave
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_help
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gui_get_program_class
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gui_get_display_name
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|,
name|gint
modifier|*
name|monitor_number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gui_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpObject
modifier|*
name|gui_display_get_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gui_display_get_ID
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint32
name|gui_display_get_window
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpObject
modifier|*
name|gui_display_create
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_display_delete
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_displays_reconnect
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old_image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProgress
modifier|*
name|gui_new_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_free_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_pdb_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_pdb_dialog_set
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_pdb_dialog_close
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gui_vtable_init (Gimp * gimp)
name|gui_vtable_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|ungrab
operator|=
name|gui_ungrab
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|threads_enter
operator|=
name|gui_threads_enter
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|threads_leave
operator|=
name|gui_threads_leave
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|set_busy
operator|=
name|gui_set_busy
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|unset_busy
operator|=
name|gui_unset_busy
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|show_message
operator|=
name|gui_message
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|help
operator|=
name|gui_help
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|get_program_class
operator|=
name|gui_get_program_class
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|get_display_name
operator|=
name|gui_get_display_name
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|get_theme_dir
operator|=
name|gui_get_theme_dir
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_get_by_id
operator|=
name|gui_display_get_by_ID
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_get_id
operator|=
name|gui_display_get_ID
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_get_window
operator|=
name|gui_display_get_window
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_create
operator|=
name|gui_display_create
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|display_delete
operator|=
name|gui_display_delete
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|displays_reconnect
operator|=
name|gui_displays_reconnect
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|progress_new
operator|=
name|gui_new_progress
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|progress_free
operator|=
name|gui_free_progress
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_new
operator|=
name|gui_pdb_dialog_new
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_set
operator|=
name|gui_pdb_dialog_set
expr_stmt|;
name|gimp
operator|->
name|gui
operator|.
name|pdb_dialog_close
operator|=
name|gui_pdb_dialog_close
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gui_ungrab (Gimp * gimp)
name|gui_ungrab
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gdk_display_get_default
argument_list|()
decl_stmt|;
if|if
condition|(
name|display
condition|)
block|{
name|gdk_display_pointer_ungrab
argument_list|(
name|display
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
name|gdk_display_keyboard_ungrab
argument_list|(
name|display
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_threads_enter (Gimp * gimp)
name|gui_threads_enter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GDK_THREADS_ENTER
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_threads_leave (Gimp * gimp)
name|gui_threads_leave
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GDK_THREADS_LEAVE
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_set_busy (Gimp * gimp)
name|gui_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gimp_displays_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_dialog_factories_set_busy
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_unset_busy (Gimp * gimp)
name|gui_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gimp_displays_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_dialog_factories_unset_busy
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_help (Gimp * gimp,const gchar * help_domain,const gchar * help_id)
name|gui_help
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|gimp_help_show
argument_list|(
name|gimp
argument_list|,
name|help_domain
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gui_get_program_class (Gimp * gimp)
name|gui_get_program_class
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|gdk_get_program_class
argument_list|()
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gui_get_display_name (Gimp * gimp,gint display_ID,gint * monitor_number)
name|gui_get_display_name
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|,
name|gint
modifier|*
name|monitor_number
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|NULL
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|gint
name|monitor
decl_stmt|;
if|if
condition|(
name|display_ID
operator|>
literal|0
condition|)
name|display
operator|=
name|gimp_display_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|display_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
condition|)
block|{
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|monitor
operator|=
name|gdk_screen_get_monitor_at_window
argument_list|(
name|screen
argument_list|,
name|display
operator|->
name|shell
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdk_display_get_pointer
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|,
operator|&
name|screen
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|monitor
operator|=
name|gdk_screen_get_monitor_at_point
argument_list|(
name|screen
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
operator|*
name|monitor_number
operator|=
name|monitor
expr_stmt|;
if|if
condition|(
name|screen
condition|)
return|return
name|gdk_screen_make_display_name
argument_list|(
name|screen
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gui_get_theme_dir (Gimp * gimp)
name|gui_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|themes_get_theme_dir
argument_list|(
name|gimp
argument_list|,
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|theme
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpObject
modifier|*
DECL|function|gui_display_get_by_ID (Gimp * gimp,gint ID)
name|gui_display_get_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
block|{
return|return
operator|(
name|GimpObject
operator|*
operator|)
name|gimp_display_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|ID
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gui_display_get_ID (GimpObject * display)
name|gui_display_get_ID
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
return|return
name|gimp_display_get_ID
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|gui_display_get_window (GimpObject * display)
name|gui_display_get_window
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|disp
init|=
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
decl_stmt|;
if|if
condition|(
name|disp
operator|->
name|shell
condition|)
return|return
operator|(
name|guint32
operator|)
name|gimp_window_get_native
argument_list|(
name|GTK_WINDOW
argument_list|(
name|disp
operator|->
name|shell
argument_list|)
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|GimpObject
modifier|*
DECL|function|gui_display_create (GimpImage * image,GimpUnit unit,gdouble scale)
name|gui_display_create
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GList
modifier|*
name|image_managers
decl_stmt|;
name|image_managers
operator|=
name|gimp_ui_managers_from_name
argument_list|(
literal|"<Image>"
argument_list|)
expr_stmt|;
name|display
operator|=
name|gimp_display_new
argument_list|(
name|image
argument_list|,
name|unit
argument_list|,
name|scale
argument_list|,
name|global_menu_factory
argument_list|,
name|image_managers
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_context_set_display
argument_list|(
name|gimp_get_user_context
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_ui_manager_update
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
operator|->
name|menubar_manager
argument_list|,
name|display
argument_list|)
expr_stmt|;
return|return
name|GIMP_OBJECT
argument_list|(
name|display
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_display_delete (GimpObject * display)
name|gui_display_delete
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|gimp_display_delete
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_displays_reconnect (Gimp * gimp,GimpImage * old_image,GimpImage * new_image)
name|gui_displays_reconnect
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old_image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
block|{
name|gimp_displays_reconnect
argument_list|(
name|gimp
argument_list|,
name|old_image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpProgress
modifier|*
DECL|function|gui_new_progress (Gimp * gimp,GimpObject * display)
name|gui_new_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|display
operator|==
name|NULL
operator|||
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
condition|)
return|return
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
return|;
return|return
name|GIMP_PROGRESS
argument_list|(
name|gimp_progress_dialog_new
argument_list|()
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_free_progress (Gimp * gimp,GimpProgress * progress)
name|gui_free_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
condition|)
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_pdb_dialog_present (GtkWindow * window)
name|gui_pdb_dialog_present
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|)
block|{
name|gtk_window_present
argument_list|(
name|window
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_pdb_dialog_new (Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpContainer * container,const gchar * title,const gchar * callback_name,const gchar * object_name,va_list args)
name|gui_pdb_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GType
name|dialog_type
init|=
name|G_TYPE_NONE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|dialog_role
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|help_id
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_BRUSH
condition|)
block|{
name|dialog_type
operator|=
name|GIMP_TYPE_BRUSH_SELECT
expr_stmt|;
name|dialog_role
operator|=
literal|"gimp-brush-selection"
expr_stmt|;
name|help_id
operator|=
name|GIMP_HELP_BRUSH_DIALOG
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_FONT
condition|)
block|{
name|dialog_type
operator|=
name|GIMP_TYPE_FONT_SELECT
expr_stmt|;
name|dialog_role
operator|=
literal|"gimp-font-selection"
expr_stmt|;
name|help_id
operator|=
name|GIMP_HELP_FONT_DIALOG
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_GRADIENT
condition|)
block|{
name|dialog_type
operator|=
name|GIMP_TYPE_GRADIENT_SELECT
expr_stmt|;
name|dialog_role
operator|=
literal|"gimp-gradient-selection"
expr_stmt|;
name|help_id
operator|=
name|GIMP_HELP_GRADIENT_DIALOG
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_PALETTE
condition|)
block|{
name|dialog_type
operator|=
name|GIMP_TYPE_PALETTE_SELECT
expr_stmt|;
name|dialog_role
operator|=
literal|"gimp-palette-selection"
expr_stmt|;
name|help_id
operator|=
name|GIMP_HELP_PALETTE_DIALOG
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_PATTERN
condition|)
block|{
name|dialog_type
operator|=
name|GIMP_TYPE_PATTERN_SELECT
expr_stmt|;
name|dialog_role
operator|=
literal|"gimp-pattern-selection"
expr_stmt|;
name|help_id
operator|=
name|GIMP_HELP_PATTERN_DIALOG
expr_stmt|;
block|}
if|if
condition|(
name|dialog_type
operator|!=
name|G_TYPE_NONE
condition|)
block|{
name|GimpObject
modifier|*
name|object
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|object_name
operator|&&
name|strlen
argument_list|(
name|object_name
argument_list|)
condition|)
name|object
operator|=
name|gimp_container_get_child_by_name
argument_list|(
name|container
argument_list|,
name|object_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|object
condition|)
name|object
operator|=
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|GParameter
modifier|*
name|params
init|=
name|NULL
decl_stmt|;
name|gint
name|n_params
init|=
literal|0
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|params
operator|=
name|gimp_parameters_append
argument_list|(
name|dialog_type
argument_list|,
name|params
argument_list|,
operator|&
name|n_params
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"role"
argument_list|,
name|dialog_role
argument_list|,
literal|"help-func"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"help-id"
argument_list|,
name|help_id
argument_list|,
literal|"pdb"
argument_list|,
name|gimp
operator|->
name|pdb
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"select-type"
argument_list|,
name|container
operator|->
name|children_type
argument_list|,
literal|"initial-object"
argument_list|,
name|object
argument_list|,
literal|"callback-name"
argument_list|,
name|callback_name
argument_list|,
literal|"menu-factory"
argument_list|,
name|global_menu_factory
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|params
operator|=
name|gimp_parameters_append_valist
argument_list|(
name|dialog_type
argument_list|,
name|params
argument_list|,
operator|&
name|n_params
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_newv
argument_list|(
name|dialog_type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|gimp_parameters_free
argument_list|(
name|params
argument_list|,
name|n_params
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_PDB_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|view
expr_stmt|;
if|if
condition|(
name|view
condition|)
name|gimp_docked_set_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
block|{
name|guint32
name|window
init|=
name|gimp_progress_get_window
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
condition|)
name|gimp_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
comment|/*  workaround for bug #360106  */
block|{
name|GSource
modifier|*
name|source
init|=
name|g_timeout_source_new
argument_list|(
literal|100
argument_list|)
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|closure
operator|=
name|g_cclosure_new_object
argument_list|(
name|G_CALLBACK
argument_list|(
name|gui_pdb_dialog_present
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_source_set_closure
argument_list|(
name|source
argument_list|,
name|closure
argument_list|)
expr_stmt|;
name|g_source_attach
argument_list|(
name|source
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_source_unref
argument_list|(
name|source
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_pdb_dialog_set (Gimp * gimp,GimpContainer * container,const gchar * callback_name,const gchar * object_name,va_list args)
name|gui_pdb_dialog_set
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GimpPdbDialogClass
modifier|*
name|klass
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_BRUSH
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_BRUSH_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_FONT
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_FONT_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_GRADIENT
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_GRADIENT_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_PALETTE
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_PALETTE_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_PATTERN
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_PATTERN_SELECT
argument_list|)
expr_stmt|;
if|if
condition|(
name|klass
condition|)
block|{
name|GimpPdbDialog
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_pdb_dialog_get_by_callback
argument_list|(
name|klass
argument_list|,
name|callback_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|&&
name|dialog
operator|->
name|select_type
operator|==
name|container
operator|->
name|children_type
condition|)
block|{
name|GimpObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|gimp_container_get_child_by_name
argument_list|(
name|container
argument_list|,
name|object_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|prop_name
init|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
decl_stmt|;
name|gimp_context_set_by_type
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|dialog
operator|->
name|select_type
argument_list|,
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|prop_name
condition|)
name|g_object_set_valist
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|prop_name
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_pdb_dialog_close (Gimp * gimp,GimpContainer * container,const gchar * callback_name)
name|gui_pdb_dialog_close
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
block|{
name|GimpPdbDialogClass
modifier|*
name|klass
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_BRUSH
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_BRUSH_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_FONT
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_FONT_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_GRADIENT
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_GRADIENT_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_PALETTE
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_PALETTE_SELECT
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|container
operator|->
name|children_type
operator|==
name|GIMP_TYPE_PATTERN
condition|)
name|klass
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_PATTERN_SELECT
argument_list|)
expr_stmt|;
if|if
condition|(
name|klass
condition|)
block|{
name|GimpPdbDialog
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_pdb_dialog_get_by_callback
argument_list|(
name|klass
argument_list|,
name|callback_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|&&
name|dialog
operator|->
name|select_type
operator|==
name|container
operator|->
name|children_type
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

