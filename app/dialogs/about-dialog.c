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
file|"dialogs-types.h"
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
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"about.h"
end_include

begin_include
include|#
directive|include
file|"git-version.h"
end_include

begin_include
include|#
directive|include
file|"about-dialog.h"
end_include

begin_include
include|#
directive|include
file|"authors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* The first authors are the creators and maintainers, don't shuffle  * them  */
end_comment

begin_define
DECL|macro|START_INDEX
define|#
directive|define
name|START_INDEX
value|(G_N_ELEMENTS (creators)    - 1
comment|/*NULL*/
value|+ \                      G_N_ELEMENTS (maintainers) - 1
comment|/*NULL*/
value|)
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27ef78e70108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|anim_area
name|GtkWidget
modifier|*
name|anim_area
decl_stmt|;
DECL|member|layout
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
DECL|member|n_authors
name|gint
name|n_authors
decl_stmt|;
DECL|member|shuffle
name|gint
name|shuffle
index|[
name|G_N_ELEMENTS
argument_list|(
name|authors
argument_list|)
operator|-
literal|1
index|]
decl_stmt|;
comment|/* NULL terminated */
DECL|member|timer
name|guint
name|timer
decl_stmt|;
DECL|member|index
name|gint
name|index
decl_stmt|;
DECL|member|animstep
name|gint
name|animstep
decl_stmt|;
DECL|member|textrange
name|gint
name|textrange
index|[
literal|2
index|]
decl_stmt|;
DECL|member|state
name|gint
name|state
decl_stmt|;
DECL|member|visible
name|gboolean
name|visible
decl_stmt|;
DECL|typedef|GimpAboutDialog
block|}
name|GimpAboutDialog
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|about_dialog_map
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|about_dialog_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkPixbuf
modifier|*
name|about_dialog_load_logo
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|about_dialog_add_animation
parameter_list|(
name|GtkWidget
modifier|*
name|vbox
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|about_dialog_anim_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|about_dialog_reshuffle
parameter_list|(
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|about_dialog_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
end_ifdef

begin_function_decl
specifier|static
name|void
name|about_dialog_add_unstable_message
parameter_list|(
name|GtkWidget
modifier|*
name|vbox
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_UNSTABLE */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|about_dialog_create (GimpContext * context)
name|about_dialog_create
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
specifier|static
name|GimpAboutDialog
name|dialog
decl_stmt|;
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
if|if
condition|(
operator|!
name|dialog
operator|.
name|dialog
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|container
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|gchar
modifier|*
name|copyright
decl_stmt|;
name|dialog
operator|.
name|n_authors
operator|=
name|G_N_ELEMENTS
argument_list|(
name|authors
argument_list|)
operator|-
literal|1
expr_stmt|;
name|pixbuf
operator|=
name|about_dialog_load_logo
argument_list|()
expr_stmt|;
name|copyright
operator|=
name|g_strdup_printf
argument_list|(
name|GIMP_COPYRIGHT
argument_list|,
name|GIMP_GIT_LAST_COMMIT_YEAR
argument_list|)
expr_stmt|;
name|widget
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_ABOUT_DIALOG
argument_list|,
literal|"role"
argument_list|,
literal|"gimp-about"
argument_list|,
literal|"window-position"
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|,
literal|"title"
argument_list|,
name|_
argument_list|(
literal|"About GIMP"
argument_list|)
argument_list|,
literal|"program-name"
argument_list|,
name|GIMP_ACRONYM
argument_list|,
literal|"version"
argument_list|,
name|GIMP_VERSION
argument_list|,
literal|"copyright"
argument_list|,
name|copyright
argument_list|,
literal|"comments"
argument_list|,
name|GIMP_NAME
argument_list|,
literal|"license"
argument_list|,
name|GIMP_LICENSE
argument_list|,
literal|"wrap-license"
argument_list|,
name|TRUE
argument_list|,
literal|"logo"
argument_list|,
name|pixbuf
argument_list|,
literal|"website"
argument_list|,
literal|"https://www.gimp.org/"
argument_list|,
literal|"website-label"
argument_list|,
name|_
argument_list|(
literal|"Visit the GIMP website"
argument_list|)
argument_list|,
literal|"authors"
argument_list|,
name|authors
argument_list|,
literal|"artists"
argument_list|,
name|artists
argument_list|,
literal|"documenters"
argument_list|,
name|documenters
argument_list|,
comment|/* Translators: insert your names here,                                 separated by newline */
literal|"translator-credits"
argument_list|,
name|_
argument_list|(
literal|"translator-credits"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|copyright
argument_list|)
expr_stmt|;
name|dialog
operator|.
name|dialog
operator|=
name|widget
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|dialog
operator|.
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"map"
argument_list|,
name|G_CALLBACK
argument_list|(
name|about_dialog_map
argument_list|)
argument_list|,
operator|&
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|about_dialog_unmap
argument_list|)
argument_list|,
operator|&
name|dialog
argument_list|)
expr_stmt|;
comment|/*  kids, don't try this at home!  */
name|container
operator|=
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_BOX
argument_list|(
name|children
operator|->
name|data
argument_list|)
condition|)
block|{
name|about_dialog_add_animation
argument_list|(
name|children
operator|->
name|data
argument_list|,
operator|&
name|dialog
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|about_dialog_add_unstable_message
argument_list|(
name|children
operator|->
name|data
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* GIMP_UNSTABLE */
block|}
else|else
name|g_warning
argument_list|(
literal|"%s: ooops, no box in this container?"
argument_list|,
name|G_STRLOC
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
operator|.
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|dialog
operator|.
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|about_dialog_map (GtkWidget * widget,GimpAboutDialog * dialog)
name|about_dialog_map
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|dialog
operator|->
name|layout
operator|&&
name|dialog
operator|->
name|timer
operator|==
literal|0
condition|)
block|{
name|dialog
operator|->
name|state
operator|=
literal|0
expr_stmt|;
name|dialog
operator|->
name|index
operator|=
literal|0
expr_stmt|;
name|dialog
operator|->
name|animstep
operator|=
literal|0
expr_stmt|;
name|dialog
operator|->
name|visible
operator|=
name|FALSE
expr_stmt|;
name|about_dialog_reshuffle
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|timer
operator|=
name|g_timeout_add
argument_list|(
literal|800
argument_list|,
name|about_dialog_timer
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|about_dialog_unmap (GtkWidget * widget,GimpAboutDialog * dialog)
name|about_dialog_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|dialog
operator|->
name|timer
condition|)
block|{
name|g_source_remove
argument_list|(
name|dialog
operator|->
name|timer
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|timer
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|about_dialog_load_logo (void)
name|about_dialog_load_logo
parameter_list|(
name|void
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GInputStream
modifier|*
name|input
decl_stmt|;
name|file
operator|=
name|gimp_data_directory_file
argument_list|(
literal|"images"
argument_list|,
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
literal|"gimp-devel-logo.png"
argument_list|,
else|#
directive|else
literal|"gimp-logo.png"
argument_list|,
endif|#
directive|endif
name|NULL
argument_list|)
expr_stmt|;
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|input
condition|)
block|{
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_stream
argument_list|(
name|input
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
block|}
return|return
name|pixbuf
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|about_dialog_add_animation (GtkWidget * vbox,GimpAboutDialog * dialog)
name|about_dialog_add_animation
parameter_list|(
name|GtkWidget
modifier|*
name|vbox
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gint
name|height
decl_stmt|;
name|dialog
operator|->
name|anim_area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|anim_area
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|anim_area
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|anim_area
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|layout
operator|=
name|gtk_widget_create_pango_layout
argument_list|(
name|dialog
operator|->
name|anim_area
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|anim_area
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_object_unref
argument_list|,
name|dialog
operator|->
name|layout
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_size
argument_list|(
name|dialog
operator|->
name|layout
argument_list|,
name|NULL
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|dialog
operator|->
name|anim_area
argument_list|,
operator|-
literal|1
argument_list|,
literal|2
operator|*
name|height
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|anim_area
argument_list|,
literal|"draw"
argument_list|,
name|G_CALLBACK
argument_list|(
name|about_dialog_anim_draw
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|about_dialog_reshuffle (GimpAboutDialog * dialog)
name|about_dialog_reshuffle
parameter_list|(
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GRand
modifier|*
name|gr
init|=
name|g_rand_new
argument_list|()
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|dialog
operator|->
name|n_authors
condition|;
name|i
operator|++
control|)
name|dialog
operator|->
name|shuffle
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
for|for
control|(
name|i
operator|=
name|START_INDEX
init|;
name|i
operator|<
name|dialog
operator|->
name|n_authors
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|j
init|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
name|START_INDEX
argument_list|,
name|dialog
operator|->
name|n_authors
argument_list|)
decl_stmt|;
if|if
condition|(
name|i
operator|!=
name|j
condition|)
block|{
name|gint
name|t
decl_stmt|;
name|t
operator|=
name|dialog
operator|->
name|shuffle
index|[
name|j
index|]
expr_stmt|;
name|dialog
operator|->
name|shuffle
index|[
name|j
index|]
operator|=
name|dialog
operator|->
name|shuffle
index|[
name|i
index|]
expr_stmt|;
name|dialog
operator|->
name|shuffle
index|[
name|i
index|]
operator|=
name|t
expr_stmt|;
block|}
block|}
name|g_rand_free
argument_list|(
name|gr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|about_dialog_anim_draw (GtkWidget * widget,cairo_t * cr,GimpAboutDialog * dialog)
name|about_dialog_anim_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|visible
condition|)
return|return
name|FALSE
return|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|text
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_size
argument_list|(
name|dialog
operator|->
name|layout
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|x
operator|=
operator|(
name|allocation
operator|.
name|width
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|y
operator|=
operator|(
name|allocation
operator|.
name|height
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|textrange
index|[
literal|1
index|]
operator|>
literal|0
condition|)
block|{
name|cairo_region_t
modifier|*
name|covered_region
decl_stmt|;
name|covered_region
operator|=
name|gdk_pango_layout_get_clip_region
argument_list|(
name|dialog
operator|->
name|layout
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|dialog
operator|->
name|textrange
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gdk_cairo_region
argument_list|(
name|cr
argument_list|,
name|covered_region
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|covered_region
argument_list|)
expr_stmt|;
block|}
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|dialog
operator|->
name|layout
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|insert_spacers (const gchar * string)
name|insert_spacers
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
block|{
name|GString
modifier|*
name|str
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|normalized
decl_stmt|;
name|gchar
modifier|*
name|ptr
decl_stmt|;
name|gunichar
name|unichr
decl_stmt|;
name|normalized
operator|=
name|g_utf8_normalize
argument_list|(
name|string
argument_list|,
operator|-
literal|1
argument_list|,
name|G_NORMALIZE_DEFAULT_COMPOSE
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|normalized
expr_stmt|;
while|while
condition|(
operator|(
name|unichr
operator|=
name|g_utf8_get_char
argument_list|(
name|ptr
argument_list|)
operator|)
condition|)
block|{
name|g_string_append_unichar
argument_list|(
name|str
argument_list|,
name|unichr
argument_list|)
expr_stmt|;
name|g_string_append_unichar
argument_list|(
name|str
argument_list|,
literal|0x200b
argument_list|)
expr_stmt|;
comment|/* ZERO WIDTH SPACE */
name|ptr
operator|=
name|g_utf8_next_char
argument_list|(
name|ptr
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|normalized
argument_list|)
expr_stmt|;
return|return
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|mix_colors (const GdkColor * start,const GdkColor * end,GdkColor * target,gdouble pos)
name|mix_colors
parameter_list|(
specifier|const
name|GdkColor
modifier|*
name|start
parameter_list|,
specifier|const
name|GdkColor
modifier|*
name|end
parameter_list|,
name|GdkColor
modifier|*
name|target
parameter_list|,
name|gdouble
name|pos
parameter_list|)
block|{
name|target
operator|->
name|red
operator|=
name|start
operator|->
name|red
operator|*
operator|(
literal|1.0
operator|-
name|pos
operator|)
operator|+
name|end
operator|->
name|red
operator|*
name|pos
expr_stmt|;
name|target
operator|->
name|green
operator|=
name|start
operator|->
name|green
operator|*
operator|(
literal|1.0
operator|-
name|pos
operator|)
operator|+
name|end
operator|->
name|green
operator|*
name|pos
expr_stmt|;
name|target
operator|->
name|blue
operator|=
name|start
operator|->
name|blue
operator|*
operator|(
literal|1.0
operator|-
name|pos
operator|)
operator|+
name|end
operator|->
name|blue
operator|*
name|pos
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|decorate_text (GimpAboutDialog * dialog,gint anim_type,gdouble time)
name|decorate_text
parameter_list|(
name|GimpAboutDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|anim_type
parameter_list|,
name|gdouble
name|time
parameter_list|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|dialog
operator|->
name|anim_area
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ptr
decl_stmt|;
name|gint
name|letter_count
init|=
literal|0
decl_stmt|;
name|gint
name|text_length
init|=
literal|0
decl_stmt|;
name|gint
name|text_bytelen
init|=
literal|0
decl_stmt|;
name|gint
name|cluster_start
decl_stmt|,
name|cluster_end
decl_stmt|;
name|gunichar
name|unichr
decl_stmt|;
name|PangoAttrList
modifier|*
name|attrlist
init|=
name|NULL
decl_stmt|;
name|PangoAttribute
modifier|*
name|attr
decl_stmt|;
name|PangoRectangle
name|irect
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|PangoRectangle
name|lrect
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GdkColor
name|mix
decl_stmt|;
name|mix_colors
argument_list|(
name|style
operator|->
name|bg
operator|+
name|GTK_STATE_NORMAL
argument_list|,
name|style
operator|->
name|fg
operator|+
name|GTK_STATE_NORMAL
argument_list|,
operator|&
name|mix
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|text
operator|=
name|pango_layout_get_text
argument_list|(
name|dialog
operator|->
name|layout
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|text
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|text_length
operator|=
name|g_utf8_strlen
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|text_bytelen
operator|=
name|strlen
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|attrlist
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|dialog
operator|->
name|textrange
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|dialog
operator|->
name|textrange
index|[
literal|1
index|]
operator|=
name|text_bytelen
expr_stmt|;
switch|switch
condition|(
name|anim_type
condition|)
block|{
case|case
literal|0
case|:
comment|/* Fade in */
name|attr
operator|=
name|pango_attr_foreground_new
argument_list|(
name|mix
operator|.
name|red
argument_list|,
name|mix
operator|.
name|green
argument_list|,
name|mix
operator|.
name|blue
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
name|text_bytelen
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrlist
argument_list|,
name|attr
argument_list|)
expr_stmt|;
break|break;
case|case
literal|1
case|:
comment|/* Fade in, spread */
name|attr
operator|=
name|pango_attr_foreground_new
argument_list|(
name|mix
operator|.
name|red
argument_list|,
name|mix
operator|.
name|green
argument_list|,
name|mix
operator|.
name|blue
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
name|text_bytelen
expr_stmt|;
name|pango_attr_list_change
argument_list|(
name|attrlist
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|text
expr_stmt|;
name|cluster_start
operator|=
literal|0
expr_stmt|;
while|while
condition|(
operator|(
name|unichr
operator|=
name|g_utf8_get_char
argument_list|(
name|ptr
argument_list|)
operator|)
condition|)
block|{
name|ptr
operator|=
name|g_utf8_next_char
argument_list|(
name|ptr
argument_list|)
expr_stmt|;
name|cluster_end
operator|=
operator|(
name|ptr
operator|-
name|text
operator|)
expr_stmt|;
if|if
condition|(
name|unichr
operator|==
literal|0x200b
condition|)
block|{
name|lrect
operator|.
name|width
operator|=
operator|(
literal|1.0
operator|-
name|time
operator|)
operator|*
literal|15.0
operator|*
name|PANGO_SCALE
operator|+
literal|0.5
expr_stmt|;
name|attr
operator|=
name|pango_attr_shape_new
argument_list|(
operator|&
name|irect
argument_list|,
operator|&
name|lrect
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
name|cluster_start
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
name|cluster_end
expr_stmt|;
name|pango_attr_list_change
argument_list|(
name|attrlist
argument_list|,
name|attr
argument_list|)
expr_stmt|;
block|}
name|cluster_start
operator|=
name|cluster_end
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
comment|/* Fade in, sinewave */
name|attr
operator|=
name|pango_attr_foreground_new
argument_list|(
name|mix
operator|.
name|red
argument_list|,
name|mix
operator|.
name|green
argument_list|,
name|mix
operator|.
name|blue
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
literal|0
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
name|text_bytelen
expr_stmt|;
name|pango_attr_list_change
argument_list|(
name|attrlist
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|text
expr_stmt|;
name|cluster_start
operator|=
literal|0
expr_stmt|;
while|while
condition|(
operator|(
name|unichr
operator|=
name|g_utf8_get_char
argument_list|(
name|ptr
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|unichr
operator|==
literal|0x200b
condition|)
block|{
name|cluster_end
operator|=
name|ptr
operator|-
name|text
expr_stmt|;
name|attr
operator|=
name|pango_attr_rise_new
argument_list|(
operator|(
literal|1.0
operator|-
name|time
operator|)
operator|*
literal|18000
operator|*
name|sin
argument_list|(
literal|4.0
operator|*
name|time
operator|+
operator|(
name|float
operator|)
name|letter_count
operator|*
literal|0.7
argument_list|)
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
name|cluster_start
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
name|cluster_end
expr_stmt|;
name|pango_attr_list_change
argument_list|(
name|attrlist
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|letter_count
operator|++
expr_stmt|;
name|cluster_start
operator|=
name|cluster_end
expr_stmt|;
block|}
name|ptr
operator|=
name|g_utf8_next_char
argument_list|(
name|ptr
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
comment|/* letterwise Fade in */
name|ptr
operator|=
name|text
expr_stmt|;
name|letter_count
operator|=
literal|0
expr_stmt|;
name|cluster_start
operator|=
literal|0
expr_stmt|;
while|while
condition|(
operator|(
name|unichr
operator|=
name|g_utf8_get_char
argument_list|(
name|ptr
argument_list|)
operator|)
condition|)
block|{
name|gint
name|border
init|=
operator|(
name|text_length
operator|+
literal|15
operator|)
operator|*
name|time
operator|-
literal|15
decl_stmt|;
name|gdouble
name|pos
decl_stmt|;
if|if
condition|(
name|letter_count
operator|<
name|border
condition|)
name|pos
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|letter_count
operator|>
name|border
operator|+
literal|15
condition|)
name|pos
operator|=
literal|1
expr_stmt|;
else|else
name|pos
operator|=
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|letter_count
operator|-
name|border
argument_list|)
operator|)
operator|/
literal|15
expr_stmt|;
name|mix_colors
argument_list|(
name|style
operator|->
name|fg
operator|+
name|GTK_STATE_NORMAL
argument_list|,
name|style
operator|->
name|bg
operator|+
name|GTK_STATE_NORMAL
argument_list|,
operator|&
name|mix
argument_list|,
name|pos
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|g_utf8_next_char
argument_list|(
name|ptr
argument_list|)
expr_stmt|;
name|cluster_end
operator|=
name|ptr
operator|-
name|text
expr_stmt|;
name|attr
operator|=
name|pango_attr_foreground_new
argument_list|(
name|mix
operator|.
name|red
argument_list|,
name|mix
operator|.
name|green
argument_list|,
name|mix
operator|.
name|blue
argument_list|)
expr_stmt|;
name|attr
operator|->
name|start_index
operator|=
name|cluster_start
expr_stmt|;
name|attr
operator|->
name|end_index
operator|=
name|cluster_end
expr_stmt|;
name|pango_attr_list_change
argument_list|(
name|attrlist
argument_list|,
name|attr
argument_list|)
expr_stmt|;
if|if
condition|(
name|pos
operator|<
literal|1.0
condition|)
name|dialog
operator|->
name|textrange
index|[
literal|1
index|]
operator|=
name|cluster_end
expr_stmt|;
name|letter_count
operator|++
expr_stmt|;
name|cluster_start
operator|=
name|cluster_end
expr_stmt|;
block|}
break|break;
default|default:
name|g_printerr
argument_list|(
literal|"Unknown animation type %d\n"
argument_list|,
name|anim_type
argument_list|)
expr_stmt|;
block|}
name|pango_layout_set_attributes
argument_list|(
name|dialog
operator|->
name|layout
argument_list|,
name|attrlist
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrlist
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|about_dialog_timer (gpointer data)
name|about_dialog_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpAboutDialog
modifier|*
name|dialog
init|=
name|data
decl_stmt|;
name|gint
name|timeout
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|animstep
operator|==
literal|0
condition|)
block|{
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|dialog
operator|->
name|visible
operator|=
name|TRUE
expr_stmt|;
switch|switch
condition|(
name|dialog
operator|->
name|state
condition|)
block|{
case|case
literal|0
case|:
name|dialog
operator|->
name|timer
operator|=
name|g_timeout_add
argument_list|(
literal|30
argument_list|,
name|about_dialog_timer
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|state
operator|+=
literal|1
expr_stmt|;
return|return
name|FALSE
return|;
case|case
literal|1
case|:
name|text
operator|=
name|insert_spacers
argument_list|(
name|_
argument_list|(
literal|"GIMP is brought to you by"
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|state
operator|+=
literal|1
expr_stmt|;
break|break;
case|case
literal|2
case|:
if|if
condition|(
operator|!
operator|(
name|dialog
operator|->
name|index
operator|<
name|dialog
operator|->
name|n_authors
operator|)
condition|)
name|dialog
operator|->
name|index
operator|=
literal|0
expr_stmt|;
name|text
operator|=
name|insert_spacers
argument_list|(
name|authors
index|[
name|dialog
operator|->
name|shuffle
index|[
name|dialog
operator|->
name|index
index|]
index|]
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|index
operator|+=
literal|1
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_return_val_if_fail
argument_list|(
name|text
operator|!=
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pango_layout_set_text
argument_list|(
name|dialog
operator|->
name|layout
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_set_attributes
argument_list|(
name|dialog
operator|->
name|layout
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dialog
operator|->
name|animstep
operator|<
literal|16
condition|)
block|{
name|decorate_text
argument_list|(
name|dialog
argument_list|,
literal|2
argument_list|,
operator|(
operator|(
name|gfloat
operator|)
name|dialog
operator|->
name|animstep
operator|)
operator|/
literal|15.0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|dialog
operator|->
name|animstep
operator|==
literal|16
condition|)
block|{
name|timeout
operator|=
literal|800
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|dialog
operator|->
name|animstep
operator|==
literal|17
condition|)
block|{
name|timeout
operator|=
literal|30
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|dialog
operator|->
name|animstep
operator|<
literal|33
condition|)
block|{
name|decorate_text
argument_list|(
name|dialog
argument_list|,
literal|1
argument_list|,
literal|1.0
operator|-
operator|(
call|(
name|gfloat
call|)
argument_list|(
name|dialog
operator|->
name|animstep
operator|-
literal|17
argument_list|)
operator|)
operator|/
literal|15.0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|dialog
operator|->
name|animstep
operator|==
literal|33
condition|)
block|{
name|dialog
operator|->
name|visible
operator|=
name|FALSE
expr_stmt|;
name|timeout
operator|=
literal|300
expr_stmt|;
block|}
else|else
block|{
name|dialog
operator|->
name|visible
operator|=
name|FALSE
expr_stmt|;
name|dialog
operator|->
name|animstep
operator|=
operator|-
literal|1
expr_stmt|;
name|timeout
operator|=
literal|30
expr_stmt|;
block|}
name|dialog
operator|->
name|animstep
operator|++
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|dialog
operator|->
name|anim_area
argument_list|)
expr_stmt|;
if|if
condition|(
name|timeout
operator|>
literal|0
condition|)
block|{
name|dialog
operator|->
name|timer
operator|=
name|g_timeout_add
argument_list|(
name|timeout
argument_list|,
name|about_dialog_timer
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/* else keep the current timeout */
return|return
name|TRUE
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
end_ifdef

begin_function
specifier|static
name|void
DECL|function|about_dialog_add_unstable_message (GtkWidget * vbox)
name|about_dialog_add_unstable_message
parameter_list|(
name|GtkWidget
modifier|*
name|vbox
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"This is an unstable development release\n"
literal|"commit %s"
argument_list|)
argument_list|,
name|GIMP_GIT_VERSION_ABBREV
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_CENTER
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_UNSTABLE */
end_comment

end_unit

