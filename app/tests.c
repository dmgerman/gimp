begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui.h"
end_include

begin_include
include|#
directive|include
file|"actions/actions.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"menus/menus.h"
end_include

begin_include
include|#
directive|include
file|"base/base.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-contexts.h"
end_include

begin_include
include|#
directive|include
file|"tests.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
end_include

begin_comment
comment|/**  * gimp_init_for_testing:  *  * Initialize the GIMP object system for unit testing. This is a  * selected subset of the initialization happning in app_run().  **/
end_comment

begin_function
name|Gimp
modifier|*
DECL|function|gimp_init_for_testing (gboolean use_cpu_accel)
name|gimp_init_for_testing
parameter_list|(
name|gboolean
name|use_cpu_accel
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_new
argument_list|(
literal|"Unit Tested GIMP"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|units_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|base_init
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|use_cpu_accel
argument_list|)
expr_stmt|;
return|return
name|gimp
return|;
block|}
end_function

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_function
specifier|static
name|void
DECL|function|gimp_status_func_dummy (const gchar * text1,const gchar * text2,gdouble percentage)
name|gimp_status_func_dummy
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{ }
end_function

begin_comment
comment|/**  * gimp_init_for_gui_testing:  * @use_cpu_accel:  *  * Initializes a #Gimp instance for use in test cases that rely on GUI  * code to be initialized.  *  * Returns: The #Gimp instance.  **/
end_comment

begin_function
name|Gimp
modifier|*
DECL|function|gimp_init_for_gui_testing (gboolean use_cpu_accel,gboolean show_gui)
name|gimp_init_for_gui_testing
parameter_list|(
name|gboolean
name|use_cpu_accel
parameter_list|,
name|gboolean
name|show_gui
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
comment|/* from main() */
name|g_thread_init
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
comment|/* from app_run() */
name|gimp
operator|=
name|gimp_new
argument_list|(
literal|"Unit Tested GIMP"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
operator|!
name|show_gui
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_set_show_gui
argument_list|(
name|gimp
argument_list|,
name|show_gui
argument_list|)
expr_stmt|;
name|units_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|base_init
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|use_cpu_accel
argument_list|)
expr_stmt|;
name|gui_init
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_initialize
argument_list|(
name|gimp
argument_list|,
name|gimp_status_func_dummy
argument_list|)
expr_stmt|;
name|gimp_restore
argument_list|(
name|gimp
argument_list|,
name|gimp_status_func_dummy
argument_list|)
expr_stmt|;
return|return
name|gimp
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_CONSOLE_COMPILATION */
end_comment

end_unit

