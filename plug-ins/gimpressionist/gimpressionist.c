begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|HAVE_DIRENT_H
define|#
directive|define
name|HAVE_DIRENT_H
end_define

begin_define
DECL|macro|HAVE_UNISTD_H
define|#
directive|define
name|HAVE_UNISTD_H
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<stdio.h>
end_include

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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_ifndef
ifndef|#
directive|ifndef
name|S_ISDIR
end_ifndef

begin_define
DECL|macro|S_ISDIR (m)
define|#
directive|define
name|S_ISDIR
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFDIR)
end_define

begin_define
DECL|macro|S_ISREG (m)
define|#
directive|define
name|S_ISREG
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFREG)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|dlg
specifier|static
name|GtkWidget
modifier|*
name|dlg
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tooltips
name|GtkTooltips
modifier|*
name|tooltips
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|infile
name|ppm_t
name|infile
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|inalpha
name|ppm_t
name|inalpha
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gr
name|GRand
modifier|*
name|gr
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|parsepath (void)
name|GList
modifier|*
name|parsepath
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GList
modifier|*
name|lastpath
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|gimpdatasubdir
decl_stmt|,
modifier|*
name|defaultpath
decl_stmt|,
modifier|*
name|tmps
decl_stmt|;
if|if
condition|(
name|lastpath
condition|)
return|return
name|lastpath
return|;
name|gimpdatasubdir
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"gimpressionist"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|defaultpath
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"gimpressionist"
argument_list|,
name|gimpdatasubdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|standalone
condition|)
block|{
name|tmps
operator|=
name|g_strdup
argument_list|(
name|defaultpath
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tmps
operator|=
name|gimp_gimprc_query
argument_list|(
literal|"gimpressionist-path"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tmps
condition|)
block|{
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|gimpdatasubdir
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
comment|/* No gimpressionist-path parameter,                  and the default doesn't exist */
name|gchar
modifier|*
name|path
init|=
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
literal|"gimpressionist"
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
literal|"${gimp_data_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
literal|"gimpressionist"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
comment|/* don't translate the gimprc entry */
name|g_message
argument_list|(
name|_
argument_list|(
literal|"It is highly recommended to add\n"
literal|" (gimpressionist-path \"%s\")\n"
literal|"(or similar) to your gimprc file."
argument_list|)
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
name|tmps
operator|=
name|g_strdup
argument_list|(
name|defaultpath
argument_list|)
expr_stmt|;
block|}
block|}
name|lastpath
operator|=
name|gimp_path_parse
argument_list|(
name|tmps
argument_list|,
literal|16
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmps
argument_list|)
expr_stmt|;
return|return
name|lastpath
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|findfile (const gchar * fn)
name|findfile
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fn
parameter_list|)
block|{
specifier|static
name|GList
modifier|*
name|rcpath
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|thispath
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
if|if
condition|(
operator|!
name|rcpath
condition|)
name|rcpath
operator|=
name|parsepath
argument_list|()
expr_stmt|;
name|thispath
operator|=
name|rcpath
expr_stmt|;
while|while
condition|(
name|rcpath
operator|&&
name|thispath
condition|)
block|{
name|filename
operator|=
name|g_build_filename
argument_list|(
name|thispath
operator|->
name|data
argument_list|,
name|fn
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
return|return
name|filename
return|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|thispath
operator|=
name|thispath
operator|->
name|next
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|storevals (void)
name|void
name|storevals
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|.
name|brushgamma
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|brushgammaadjust
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|generaldarkedge
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|generaldarkedgeadjust
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|paperinvert
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperinvert
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|generalpaintedges
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generalpaintedges
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|generaltileable
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generaltileable
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|generaldropshadow
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generaldropshadow
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|generalshadowdarkness
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|generalshadowadjust
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|generalshadowdepth
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|generalshadowdepth
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|generalshadowblur
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|generalshadowblur
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|devthresh
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|devthreshadjust
argument_list|)
operator|->
name|value
expr_stmt|;
name|pcvals
operator|.
name|placecenter
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placecenter
argument_list|)
operator|->
name|active
expr_stmt|;
name|pcvals
operator|.
name|paperoverlay
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperoverlay
argument_list|)
operator|->
name|active
expr_stmt|;
block|}
end_function

begin_function
DECL|function|restorevals (void)
name|void
name|restorevals
parameter_list|(
name|void
parameter_list|)
block|{
name|reselect
argument_list|(
name|brushlist
argument_list|,
name|pcvals
operator|.
name|selectedbrush
argument_list|)
expr_stmt|;
name|reselect
argument_list|(
name|paperlist
argument_list|,
name|pcvals
operator|.
name|selectedpaper
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|orientnumadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|orientnum
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|orientfirstadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|orientfirst
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|orientlastadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|orientlast
argument_list|)
expr_stmt|;
name|orientchange
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|pcvals
operator|.
name|orienttype
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|sizenumadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|sizenum
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|sizefirstadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|sizefirst
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|sizelastadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|sizelast
argument_list|)
expr_stmt|;
name|sizechange
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|pcvals
operator|.
name|sizetype
argument_list|)
expr_stmt|;
name|placechange
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|pcvals
operator|.
name|placetype
argument_list|)
expr_stmt|;
name|generalbgchange
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|pcvals
operator|.
name|generalbgtype
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brushgammaadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|brushgamma
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brushreliefadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|brushrelief
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brushaspectadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|brushaspect
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brushdensityadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|brushdensity
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|generaldarkedgeadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|generaldarkedge
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|generalshadowadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|generalshadowdarkness
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|devthreshadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|devthresh
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paperreliefadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperrelief
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|paperscaleadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperscale
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperinvert
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperinvert
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generalpaintedges
argument_list|)
argument_list|,
name|pcvals
operator|.
name|generalpaintedges
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generaltileable
argument_list|)
argument_list|,
name|pcvals
operator|.
name|generaltileable
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|generaldropshadow
argument_list|)
argument_list|,
name|pcvals
operator|.
name|generaldropshadow
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|generalshadowdepth
argument_list|)
argument_list|,
name|pcvals
operator|.
name|generalshadowdepth
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|generalshadowblur
argument_list|)
argument_list|,
name|pcvals
operator|.
name|generalshadowblur
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|placecenter
argument_list|)
argument_list|,
name|pcvals
operator|.
name|placecenter
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|paperoverlay
argument_list|)
argument_list|,
name|pcvals
operator|.
name|paperoverlay
argument_list|)
expr_stmt|;
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|generalcolbutton
argument_list|)
argument_list|,
operator|&
name|pcvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|colornoiseadjust
argument_list|)
argument_list|,
name|pcvals
operator|.
name|colornoise
argument_list|)
expr_stmt|;
name|colorchange
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|pcvals
operator|.
name|colortype
argument_list|)
expr_stmt|;
name|update_orientmap_dialog
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_close_callback (GtkWidget * widget,gpointer data)
name|dialog_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
DECL|function|dialog_ok_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|dialog_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|storevals
argument_list|()
expr_stmt|;
name|pcvals
operator|.
name|run
operator|=
literal|1
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
if|if
condition|(
name|omwindow
condition|)
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|omwindow
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|dialog_cancel_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|dialog_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|pcvals
operator|.
name|run
operator|=
literal|0
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|unselectall (GtkWidget * list)
name|void
name|unselectall
parameter_list|(
name|GtkWidget
modifier|*
name|list
parameter_list|)
block|{
name|GList
modifier|*
name|h
decl_stmt|;
name|GtkWidget
modifier|*
name|tmpw
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|h
operator|=
name|GTK_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|selection
expr_stmt|;
if|if
condition|(
operator|!
name|h
condition|)
break|break;
name|tmpw
operator|=
name|h
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|tmpw
condition|)
break|break;
name|gtk_list_unselect_child
argument_list|(
name|GTK_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|tmpw
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|reselect (GtkWidget * list,char * fname)
name|void
name|reselect
parameter_list|(
name|GtkWidget
modifier|*
name|list
parameter_list|,
name|char
modifier|*
name|fname
parameter_list|)
block|{
name|GList
modifier|*
name|h
decl_stmt|;
name|GtkWidget
modifier|*
name|tmpw
decl_stmt|;
name|char
modifier|*
name|tmps
decl_stmt|,
modifier|*
name|tmpfile
decl_stmt|;
name|tmpfile
operator|=
name|strrchr
argument_list|(
name|fname
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|tmpfile
condition|)
name|fname
operator|=
operator|++
name|tmpfile
expr_stmt|;
name|unselectall
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|h
operator|=
name|GTK_LIST
argument_list|(
name|list
argument_list|)
operator|->
name|children
expr_stmt|;
while|while
condition|(
name|h
condition|)
block|{
name|tmpw
operator|=
name|h
operator|->
name|data
expr_stmt|;
name|gtk_label_get
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|tmpw
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
operator|&
name|tmps
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|tmps
argument_list|,
name|fname
argument_list|)
condition|)
block|{
name|gtk_list_select_child
argument_list|(
name|GTK_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|tmpw
argument_list|)
expr_stmt|;
break|break;
block|}
name|h
operator|=
name|g_list_next
argument_list|(
name|h
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|readdirintolist_real (char * subdir,GtkWidget * list,char * selected)
name|void
name|readdirintolist_real
parameter_list|(
name|char
modifier|*
name|subdir
parameter_list|,
name|GtkWidget
modifier|*
name|list
parameter_list|,
name|char
modifier|*
name|selected
parameter_list|)
block|{
name|gchar
modifier|*
name|fpath
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|de
decl_stmt|;
name|GtkWidget
modifier|*
name|selectedw
init|=
name|NULL
decl_stmt|,
modifier|*
name|tmpw
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
name|GList
modifier|*
name|flist
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|selected
condition|)
block|{
if|if
condition|(
operator|!
name|selected
index|[
literal|0
index|]
condition|)
name|selected
operator|=
name|NULL
expr_stmt|;
else|else
block|{
name|char
modifier|*
name|nsel
decl_stmt|;
name|nsel
operator|=
name|strrchr
argument_list|(
name|selected
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|nsel
condition|)
name|selected
operator|=
operator|++
name|nsel
expr_stmt|;
block|}
block|}
name|dir
operator|=
name|g_dir_open
argument_list|(
name|subdir
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
return|return;
for|for
control|(
init|;
condition|;
control|)
block|{
name|gboolean
name|file_exists
decl_stmt|;
name|de
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|de
condition|)
break|break;
name|fpath
operator|=
name|g_build_filename
argument_list|(
name|subdir
argument_list|,
name|de
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file_exists
operator|=
name|g_file_test
argument_list|(
name|fpath
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|fpath
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file_exists
condition|)
continue|continue;
name|flist
operator|=
name|g_list_insert_sorted
argument_list|(
name|flist
argument_list|,
name|g_strdup
argument_list|(
name|de
argument_list|)
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|g_ascii_strcasecmp
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
while|while
condition|(
name|flist
condition|)
block|{
name|tmpw
operator|=
name|gtk_list_item_new_with_label
argument_list|(
name|flist
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|selected
condition|)
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|flist
operator|->
name|data
argument_list|,
name|selected
argument_list|)
condition|)
name|selectedw
operator|=
name|tmpw
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|list
argument_list|)
argument_list|,
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|flist
operator|->
name|data
argument_list|)
expr_stmt|;
name|flist
operator|=
name|g_list_remove
argument_list|(
name|flist
argument_list|,
name|flist
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|selectedw
condition|)
name|gtk_list_select_child
argument_list|(
name|GTK_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
name|selectedw
argument_list|)
expr_stmt|;
else|else
name|gtk_list_select_item
argument_list|(
name|GTK_LIST
argument_list|(
name|list
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|readdirintolist (char * subdir,GtkWidget * list,char * selected)
name|void
name|readdirintolist
parameter_list|(
name|char
modifier|*
name|subdir
parameter_list|,
name|GtkWidget
modifier|*
name|list
parameter_list|,
name|char
modifier|*
name|selected
parameter_list|)
block|{
name|char
modifier|*
name|tmpdir
decl_stmt|;
name|GList
modifier|*
name|thispath
init|=
name|parsepath
argument_list|()
decl_stmt|;
while|while
condition|(
name|thispath
condition|)
block|{
name|tmpdir
operator|=
name|g_build_filename
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|thispath
operator|->
name|data
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|readdirintolist_real
argument_list|(
name|tmpdir
argument_list|,
name|list
argument_list|,
name|selected
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpdir
argument_list|)
expr_stmt|;
name|thispath
operator|=
name|thispath
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|showabout (void)
specifier|static
name|void
name|showabout
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkWidget
modifier|*
name|window
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|tmpw
decl_stmt|,
modifier|*
name|tmpvbox
decl_stmt|,
modifier|*
name|tmphbox
decl_stmt|;
name|GtkWidget
modifier|*
name|logobox
decl_stmt|,
modifier|*
name|tmpframe
decl_stmt|;
name|int
name|y
decl_stmt|;
if|if
condition|(
name|window
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|window
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"The GIMPressionist!"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|window
argument_list|)
expr_stmt|;
name|gtk_quit_add_destroy
argument_list|(
literal|1
argument_list|,
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide_on_delete
argument_list|)
argument_list|,
operator|&
name|window
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_button_new_from_stock
argument_list|(
name|GTK_STOCK_CLOSE
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|tmpw
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|window
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|tmpvbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|tmpvbox
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|window
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|tmpvbox
argument_list|)
expr_stmt|;
name|tmphbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tmpvbox
argument_list|)
argument_list|,
name|tmphbox
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
name|tmphbox
argument_list|)
expr_stmt|;
name|logobox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tmphbox
argument_list|)
argument_list|,
name|logobox
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
name|logobox
argument_list|)
expr_stmt|;
name|tmpframe
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|tmpframe
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|logobox
argument_list|)
argument_list|,
name|tmpframe
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
name|tmpframe
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|tmpw
argument_list|)
argument_list|,
literal|177
argument_list|,
literal|70
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
literal|70
condition|;
name|y
operator|++
control|)
block|{
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|tmpw
argument_list|)
argument_list|,
operator|&
name|logobuffer
index|[
name|y
operator|*
literal|177
operator|*
literal|3
index|]
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
literal|177
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|tmpw
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|tmpframe
argument_list|)
argument_list|,
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|tmphbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tmpvbox
argument_list|)
argument_list|,
name|tmphbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|tmpw
operator|=
name|gtk_label_new
argument_list|(
literal|"\xa9 1999 Vidar Madsen\n"
literal|"vidar@prosalg.no\n"
literal|"http://www.prosalg.no/~vidar/gimpressionist/\n"
name|PLUG_IN_VERSION
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|tmphbox
argument_list|)
argument_list|,
name|tmpw
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpw
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmphbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tmpvbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|create_dialog (void)
specifier|static
name|int
name|create_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
name|GtkWidget
modifier|*
name|box1
decl_stmt|,
modifier|*
name|box2
decl_stmt|,
modifier|*
name|preview_box
decl_stmt|;
name|gint
name|argc
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
if|if
condition|(
name|standalone
condition|)
block|{
name|argc
operator|=
literal|1
expr_stmt|;
name|argv
operator|=
name|g_new
argument_list|(
name|char
operator|*
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|argv
index|[
literal|0
index|]
operator|=
literal|"gimpressionist"
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
name|gtk_rc_parse
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_widget_set_default_colormap
argument_list|(
name|gdk_rgb_get_colormap
argument_list|()
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_ui_init
argument_list|(
literal|"gimpressionist"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|tooltips
operator|=
name|gtk_tooltips_new
argument_list|()
expr_stmt|;
name|gtk_tooltips_enable
argument_list|(
name|tooltips
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Gimpressionist"
argument_list|)
argument_list|,
literal|"gimpressionist"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/gimpressionist.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"A_bout..."
argument_list|)
argument_list|,
name|showabout
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|dialog_cancel_callback
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|dialog_ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|dialog_close_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_help_init
argument_list|()
expr_stmt|;
name|box1
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|box1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box1
argument_list|)
expr_stmt|;
name|box2
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box1
argument_list|)
argument_list|,
name|box2
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
name|box2
argument_list|)
expr_stmt|;
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box1
argument_list|)
argument_list|,
name|notebook
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
comment|/*  gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook)); */
name|gtk_widget_show
argument_list|(
name|notebook
argument_list|)
expr_stmt|;
name|create_presetpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_paperpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_brushpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_orientationpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_sizepage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_placementpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_colorpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|create_generalpage
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|preview_box
operator|=
name|create_preview
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box2
argument_list|)
argument_list|,
name|preview_box
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
name|preview_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
block|}
end_function

begin_function
DECL|function|create_gimpressionist (void)
name|int
name|create_gimpressionist
parameter_list|(
name|void
parameter_list|)
block|{
name|pcvals
operator|.
name|run
operator|=
literal|0
expr_stmt|;
name|gr
operator|=
name|g_rand_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|standalone
condition|)
block|{
name|pcvals
operator|=
name|defaultpcvals
expr_stmt|;
name|create_dialog
argument_list|()
expr_stmt|;
name|restorevals
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|create_dialog
argument_list|()
expr_stmt|;
block|}
name|gtk_main
argument_list|()
expr_stmt|;
name|gimp_help_free
argument_list|()
expr_stmt|;
name|g_rand_free
argument_list|(
name|gr
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|pcvals
operator|.
name|run
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|standalone
name|char
modifier|*
name|standalone
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpPlugInInfo
name|PLUG_IN_INFO
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_comment
comment|/* No standalone on win32. */
end_comment

begin_macro
name|MAIN
argument_list|()
end_macro

begin_else
else|#
directive|else
end_else

begin_function
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
if|if
condition|(
name|argc
operator|!=
literal|2
condition|)
block|{
comment|/* Is this needed anymore? */
ifdef|#
directive|ifdef
name|__EMX__
name|set_gimp_PLUG_IN_INFO
argument_list|(
operator|&
name|PLUG_IN_INFO
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|gimp_main
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|)
return|;
block|}
name|standalone
operator|=
name|argv
index|[
literal|1
index|]
expr_stmt|;
name|grabarea
argument_list|()
expr_stmt|;
comment|/* Testing! */
comment|/*   copyppm(&infile,&inalpha);   img_has_alpha = 1;   */
if|if
condition|(
name|create_gimpressionist
argument_list|()
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Painting"
argument_list|)
expr_stmt|;
name|fflush
argument_list|(
name|stderr
argument_list|)
expr_stmt|;
name|repaint
argument_list|(
operator|&
name|infile
argument_list|,
operator|&
name|inalpha
argument_list|)
expr_stmt|;
name|saveppm
argument_list|(
operator|&
name|infile
argument_list|,
name|argv
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

