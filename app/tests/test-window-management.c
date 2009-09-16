begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

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
file|"dialogs/dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
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
file|"tests.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29550ee10108
block|{
DECL|member|dummy
name|int
name|dummy
decl_stmt|;
DECL|typedef|GimpTestFixture
block|}
name|GimpTestFixture
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_test_window_roles
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp
specifier|static
name|Gimp
modifier|*
name|gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|main (int argc,char ** argv)
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|int
name|test_result
decl_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|g_test_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* We share the same application instance across all tests */
name|gimp
operator|=
name|gimp_init_for_gui_testing
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Setup the tests */
name|g_test_add
argument_list|(
literal|"/gimp-window-management/window-roles"
argument_list|,
name|GimpTestFixture
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_test_window_roles
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Run the tests and return status */
name|test_result
operator|=
name|g_test_run
argument_list|()
expr_stmt|;
comment|/* Exit somewhat properly to avoid annoying warnings */
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|test_result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_window_roles:  * @fixture:  * @data:  *  * Makes sure that different windows have the right roles specified.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_window_roles (GimpTestFixture * fixture,gconstpointer data)
name|gimp_test_window_roles
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dock
init|=
name|gimp_dialog_factory_dock_new
argument_list|(
name|global_dock_factory
argument_list|,
name|gdk_screen_get_default
argument_list|()
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|toolbox
init|=
name|gimp_dialog_factory_dock_new
argument_list|(
name|global_toolbox_factory
argument_list|,
name|gdk_screen_get_default
argument_list|()
argument_list|)
decl_stmt|;
name|g_assert_cmpstr
argument_list|(
name|gtk_window_get_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|toolbox
argument_list|)
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|"gimp-toolbox"
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|gtk_window_get_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock
argument_list|)
argument_list|)
argument_list|,
operator|==
argument_list|,
literal|"gimp-dock"
argument_list|)
expr_stmt|;
comment|/* When we get here we have a ref count of one, but the signals we    * emit cause the reference count to become less than zero for some    * reason. So we're lazy and simply ignore to unref these   g_object_unref (toolbox);   g_object_unref (dock);    */
block|}
end_function

end_unit

