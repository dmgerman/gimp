begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimp-paint.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpclone.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolve.h"
end_include

begin_include
include|#
directive|include
file|"gimpdodgeburn.h"
end_include

begin_include
include|#
directive|include
file|"gimperaser.h"
end_include

begin_include
include|#
directive|include
file|"gimpheal.h"
end_include

begin_include
include|#
directive|include
file|"gimpink.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrush.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimppencil.h"
end_include

begin_include
include|#
directive|include
file|"gimpperspectiveclone.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudge.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_paint_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|paint_type
parameter_list|,
name|GType
name|paint_options_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_paint_init (Gimp * gimp)
name|gimp_paint_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPaintRegisterFunc
name|register_funcs
index|[]
init|=
block|{
name|gimp_dodge_burn_register
block|,
name|gimp_smudge_register
block|,
name|gimp_convolve_register
block|,
name|gimp_perspective_clone_register
block|,
name|gimp_heal_register
block|,
name|gimp_clone_register
block|,
ifdef|#
directive|ifdef
name|HAVE_LIBMYPAINT
name|gimp_mybrush_register
block|,
endif|#
directive|endif
name|gimp_ink_register
block|,
name|gimp_airbrush_register
block|,
name|gimp_eraser_register
block|,
name|gimp_paintbrush_register
block|,
name|gimp_pencil_register
block|}
decl_stmt|;
name|gint
name|i
decl_stmt|;
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
name|paint_info_list
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_PAINT_INFO
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|)
argument_list|,
literal|"paint infos"
argument_list|)
expr_stmt|;
name|gimp_container_freeze
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|register_funcs
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|register_funcs
index|[
name|i
index|]
operator|(
name|gimp
operator|,
name|gimp_paint_register
operator|)
expr_stmt|;
block|}
name|gimp_container_thaw
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paint_exit (Gimp * gimp)
name|gimp_paint_exit
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
name|gimp_paint_info_set_standard
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|paint_info_list
condition|)
block|{
name|gimp_container_foreach
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_object_run_dispose
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|paint_info_list
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_paint_register (Gimp * gimp,GType paint_type,GType paint_options_type,const gchar * identifier,const gchar * blurb,const gchar * icon_name)
name|gimp_paint_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|paint_type
parameter_list|,
name|GType
name|paint_options_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|paint_type
argument_list|,
name|GIMP_TYPE_PAINT_CORE
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|paint_options_type
argument_list|,
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|identifier
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|blurb
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|paint_info
operator|=
name|gimp_paint_info_new
argument_list|(
name|gimp
argument_list|,
name|paint_type
argument_list|,
name|paint_options_type
argument_list|,
name|identifier
argument_list|,
name|blurb
argument_list|,
name|icon_name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|paint_info
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|paint_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|paint_type
operator|==
name|GIMP_TYPE_PAINTBRUSH
condition|)
name|gimp_paint_info_set_standard
argument_list|(
name|gimp
argument_list|,
name|paint_info
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

