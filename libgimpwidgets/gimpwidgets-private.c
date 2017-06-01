begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgets-private.c  * Copyright (C) 2003 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<babl/babl.h>
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpicons.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-private.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|gimp_widgets_initialized
specifier|static
name|gboolean
name|gimp_widgets_initialized
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_gimp_standard_help_func
name|GimpHelpFunc
name|_gimp_standard_help_func
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_gimp_get_foreground_func
name|GimpGetColorFunc
name|_gimp_get_foreground_func
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_gimp_get_background_func
name|GimpGetColorFunc
name|_gimp_get_background_func
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|_gimp_ensure_modules_func
name|GimpEnsureModulesFunc
name|_gimp_ensure_modules_func
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_widgets_init_foreign_enums (void)
name|gimp_widgets_init_foreign_enums
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpEnumDesc
name|input_mode_descs
index|[]
init|=
block|{
block|{
name|GDK_MODE_DISABLED
block|,
name|NC_
argument_list|(
literal|"input-mode"
argument_list|,
literal|"Disabled"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GDK_MODE_SCREEN
block|,
name|NC_
argument_list|(
literal|"input-mode"
argument_list|,
literal|"Screen"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GDK_MODE_WINDOW
block|,
name|NC_
argument_list|(
literal|"input-mode"
argument_list|,
literal|"Window"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|GDK_TYPE_INPUT_MODE
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|GDK_TYPE_INPUT_MODE
argument_list|,
literal|"input-mode"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|GDK_TYPE_INPUT_MODE
argument_list|,
name|input_mode_descs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_widgets_init (GimpHelpFunc standard_help_func,GimpGetColorFunc get_foreground_func,GimpGetColorFunc get_background_func,GimpEnsureModulesFunc ensure_modules_func)
name|gimp_widgets_init
parameter_list|(
name|GimpHelpFunc
name|standard_help_func
parameter_list|,
name|GimpGetColorFunc
name|get_foreground_func
parameter_list|,
name|GimpGetColorFunc
name|get_background_func
parameter_list|,
name|GimpEnsureModulesFunc
name|ensure_modules_func
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|standard_help_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_widgets_initialized
condition|)
name|g_error
argument_list|(
literal|"gimp_widgets_init() must only be called once!"
argument_list|)
expr_stmt|;
name|_gimp_standard_help_func
operator|=
name|standard_help_func
expr_stmt|;
name|_gimp_get_foreground_func
operator|=
name|get_foreground_func
expr_stmt|;
name|_gimp_get_background_func
operator|=
name|get_background_func
expr_stmt|;
name|_gimp_ensure_modules_func
operator|=
name|ensure_modules_func
expr_stmt|;
name|babl_init
argument_list|()
expr_stmt|;
comment|/* color selectors use babl */
name|gimp_icons_init
argument_list|()
expr_stmt|;
name|gtk_window_set_default_icon_name
argument_list|(
name|GIMP_ICON_WILBER
argument_list|)
expr_stmt|;
name|gimp_widgets_init_foreign_enums
argument_list|()
expr_stmt|;
name|gimp_widgets_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_comment
comment|/* clean up babl (in particular, so that the fish cache is constructed) if the  * compiler supports destructors  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_FUNC_ATTRIBUTE_DESTRUCTOR
end_ifdef

begin_macro
name|__attribute__
argument_list|(
argument|(destructor)
argument_list|)
end_macro

begin_function
specifier|static
name|void
DECL|function|gimp_widgets_exit (void)
name|gimp_widgets_exit
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|gimp_widgets_initialized
condition|)
name|babl_exit
argument_list|()
expr_stmt|;
block|}
end_function

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|__GNUC__
argument_list|)
end_elif

begin_warning
warning|#
directive|warning
warning|babl_init() not paired with babl_exit()
end_warning

begin_endif
endif|#
directive|endif
end_endif

end_unit

