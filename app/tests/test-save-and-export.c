begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptooloptionseditor.h"
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
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-procedure.h"
end_include

begin_include
include|#
directive|include
file|"file/file-save.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_include
include|#
directive|include
file|"tests.h"
end_include

begin_include
include|#
directive|include
file|"gimp-app-test-utils.h"
end_include

begin_define
DECL|macro|ADD_TEST (function)
define|#
directive|define
name|ADD_TEST
parameter_list|(
name|function
parameter_list|)
define|\
value|g_test_add_data_func ("/gimp-save-and-export/" #function, gimp, function);
end_define

begin_typedef
DECL|typedef|GimpUiTestFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpUiTestFunc
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/**  * new_file_has_no_uris:  * @data:  *  * Tests that the URIs are correct for a newly created image.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|new_file_has_no_uris (gconstpointer data)
name|new_file_has_no_uris
parameter_list|(
name|gconstpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_test_utils_create_image_from_dalog
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * opened_xcf_file_uris:  * @data:  *  * Tests that GimpImage URIs are correct for an XCF file that has just  * been opened.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|opened_xcf_file_uris (gconstpointer data)
name|opened_xcf_file_uris
parameter_list|(
name|gconstpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
argument_list|,
literal|"app/tests/files/gimp-2-6-file.xcf"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
comment|/*progress*/
argument_list|,
name|uri
argument_list|,
name|filename
argument_list|,
name|FALSE
comment|/*as_new*/
argument_list|,
name|NULL
comment|/*file_proc*/
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
operator|&
name|status
argument_list|,
name|NULL
comment|/*mime_type*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
comment|/* Don't bother g_free()ing strings */
block|}
end_function

begin_comment
comment|/**  * imported_file_uris:  * @data:  *  * Tests that URIs are correct for an imported image.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|imported_file_uris (gconstpointer data)
name|imported_file_uris
parameter_list|(
name|gconstpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
argument_list|,
literal|"desktop/64x64/gimp.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
comment|/*progress*/
argument_list|,
name|uri
argument_list|,
name|filename
argument_list|,
name|FALSE
comment|/*as_new*/
argument_list|,
name|NULL
comment|/*file_proc*/
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
operator|&
name|status
argument_list|,
name|NULL
comment|/*mime_type*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * saved_imported_file_uris:  * @data:  *  * Tests that the URIs are correct for an image that has been imported  * and then saved.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|saved_imported_file_uris (gconstpointer data)
name|saved_imported_file_uris
parameter_list|(
name|gconstpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|import_uri
decl_stmt|;
name|gchar
modifier|*
name|import_filename
decl_stmt|;
name|gchar
modifier|*
name|save_uri
decl_stmt|;
name|gchar
modifier|*
name|save_filename
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|import_filename
operator|=
name|g_build_filename
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
argument_list|,
literal|"desktop/64x64/gimp.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|import_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|import_filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|save_filename
operator|=
name|g_build_filename
argument_list|(
name|g_get_tmp_dir
argument_list|()
argument_list|,
literal|"gimp-test.xcf"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|save_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|save_filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Import */
name|image
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
comment|/*progress*/
argument_list|,
name|import_uri
argument_list|,
name|import_filename
argument_list|,
name|FALSE
comment|/*as_new*/
argument_list|,
name|NULL
comment|/*file_proc*/
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
operator|&
name|status
argument_list|,
name|NULL
comment|/*mime_type*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
comment|/* Save */
name|proc
operator|=
name|file_procedure_find
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|plug_in_manager
operator|->
name|save_procs
argument_list|,
name|save_uri
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|file_save
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|NULL
comment|/*progress*/
argument_list|,
name|save_uri
argument_list|,
name|proc
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|TRUE
comment|/*change_saved_state*/
argument_list|,
name|FALSE
comment|/*export_backward*/
argument_list|,
name|FALSE
comment|/*export_forward*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
comment|/* Assert */
name|g_assert_cmpstr
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
name|save_uri
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_unlink
argument_list|(
name|save_filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * new_file_has_no_uris:  * @data:  *  * Tests that the URIs for an exported, newly created file are  * correct.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|exported_file_uris (gconstpointer data)
name|exported_file_uris
parameter_list|(
name|gconstpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|save_uri
decl_stmt|;
name|gchar
modifier|*
name|save_filename
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_test_utils_create_image_from_dalog
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|save_filename
operator|=
name|g_build_filename
argument_list|(
name|g_get_tmp_dir
argument_list|()
argument_list|,
literal|"gimp-test.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|save_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|save_filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|proc
operator|=
name|file_procedure_find
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|plug_in_manager
operator|->
name|export_procs
argument_list|,
name|save_uri
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|file_save
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|NULL
comment|/*progress*/
argument_list|,
name|save_uri
argument_list|,
name|proc
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|FALSE
comment|/*change_saved_state*/
argument_list|,
name|FALSE
comment|/*export_backward*/
argument_list|,
name|TRUE
comment|/*export_forward*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
name|save_uri
argument_list|)
expr_stmt|;
name|g_unlink
argument_list|(
name|save_filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * clear_import_uri_after_export:  * @data:  *  * Tests that after a XCF file that was imported has been exported,  * the import URI is cleared. An image can not be considered both  * imported and exported at the same time.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|clear_import_uri_after_export (gconstpointer data)
name|clear_import_uri_after_export
parameter_list|(
name|gconstpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|save_uri
decl_stmt|;
name|gchar
modifier|*
name|save_filename
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
argument_list|,
literal|"desktop/64x64/gimp.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
comment|/*progress*/
argument_list|,
name|uri
argument_list|,
name|filename
argument_list|,
name|FALSE
comment|/*as_new*/
argument_list|,
name|NULL
comment|/*file_proc*/
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
operator|&
name|status
argument_list|,
name|NULL
comment|/*mime_type*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|save_filename
operator|=
name|g_build_filename
argument_list|(
name|g_get_tmp_dir
argument_list|()
argument_list|,
literal|"gimp-test.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|save_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|save_filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|proc
operator|=
name|file_procedure_find
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|plug_in_manager
operator|->
name|export_procs
argument_list|,
name|save_uri
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|file_save
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|NULL
comment|/*progress*/
argument_list|,
name|save_uri
argument_list|,
name|proc
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|FALSE
comment|/*change_saved_state*/
argument_list|,
name|FALSE
comment|/*export_backward*/
argument_list|,
name|TRUE
comment|/*export_forward*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_image_get_imported_uri
argument_list|(
name|image
argument_list|)
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|gimp_image_get_exported_uri
argument_list|(
name|image
argument_list|)
argument_list|,
operator|==
argument_list|,
name|save_uri
argument_list|)
expr_stmt|;
name|g_unlink
argument_list|(
name|save_filename
argument_list|)
expr_stmt|;
block|}
end_function

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
name|Gimp
modifier|*
name|gimp
init|=
name|NULL
decl_stmt|;
name|gint
name|result
init|=
operator|-
literal|1
decl_stmt|;
name|gimp_test_bail_if_no_display
argument_list|()
expr_stmt|;
name|gtk_test_init
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
name|gimp_test_utils_set_gimp2_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|,
literal|"app/tests/gimpdir"
argument_list|)
expr_stmt|;
name|gimp_test_utils_setup_menus_dir
argument_list|()
expr_stmt|;
comment|/* Start up GIMP */
name|gimp
operator|=
name|gimp_init_for_gui_testing
argument_list|(
name|TRUE
comment|/*show_gui*/
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|ADD_TEST
argument_list|(
name|new_file_has_no_uris
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|opened_xcf_file_uris
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|imported_file_uris
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|saved_imported_file_uris
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|exported_file_uris
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|clear_import_uri_after_export
argument_list|)
expr_stmt|;
comment|/* Run the tests and return status */
name|result
operator|=
name|g_test_run
argument_list|()
expr_stmt|;
comment|/* Don't write files to the source dir */
name|gimp_test_utils_set_gimp2_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_BUILDDIR"
argument_list|,
literal|"app/tests/gimpdir-output"
argument_list|)
expr_stmt|;
comment|/* Exit properly so we don't break script-fu plug-in wire */
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

end_unit

