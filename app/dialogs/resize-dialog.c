begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsizebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"resize-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_typedef
DECL|typedef|ResizeDialog
typedef|typedef
name|struct
name|_ResizeDialog
name|ResizeDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_ResizeDialog
struct|struct
name|_ResizeDialog
block|{
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|box
name|GtkWidget
modifier|*
name|box
decl_stmt|;
DECL|member|callback
name|GimpResizeCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|resize_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|resize_dialog_reset
parameter_list|(
name|ResizeDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|resize_dialog_new (GimpViewable * viewable,const gchar * title,const gchar * role,GtkWidget * parent,GimpHelpFunc help_func,const gchar * help_id,GimpUnit unit,GimpResizeCallback callback,gpointer user_data)
name|resize_dialog_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
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
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|GimpResizeCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|ResizeDialog
modifier|*
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
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
if|if
condition|(
name|GIMP_IS_IMAGE
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|text
operator|=
name|_
argument_list|(
literal|"Canvas Size"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|text
operator|=
name|_
argument_list|(
literal|"Layer Size"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|viewable
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|GIMP_STOCK_RESIZE
argument_list|,
name|title
argument_list|,
name|parent
argument_list|,
name|help_func
argument_list|,
name|help_id
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GIMP_STOCK_RESIZE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
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
name|private
operator|=
name|g_new0
argument_list|(
name|ResizeDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|g_free
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|private
operator|->
name|viewable
operator|=
name|viewable
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
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|private
operator|->
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SIZE_BOX
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"unit"
argument_list|,
name|unit
argument_list|,
literal|"xresolution"
argument_list|,
name|xres
argument_list|,
literal|"yresolution"
argument_list|,
name|yres
argument_list|,
literal|"keep-aspect"
argument_list|,
name|TRUE
argument_list|,
literal|"edit-resolution"
argument_list|,
name|FALSE
argument_list|,
name|NULL
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
name|resize_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|private
operator|->
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|box
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Offset"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|resize_dialog_response (GtkWidget * dialog,gint response_id,ResizeDialog * private)
name|resize_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GTK_RESPONSE_CANCEL
case|:
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
case|case
name|RESPONSE_RESET
case|:
name|resize_dialog_reset
argument_list|(
name|private
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
name|g_object_get
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"width"
argument_list|,
operator|&
name|width
argument_list|,
literal|"height"
argument_list|,
operator|&
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|private
operator|->
name|viewable
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|resize_dialog_reset (ResizeDialog * private)
name|resize_dialog_reset
parameter_list|(
name|ResizeDialog
modifier|*
name|private
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
if|if
condition|(
name|GIMP_IS_IMAGE
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
condition|)
block|{
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|private
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_item_width
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_height
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|private
operator|->
name|box
argument_list|,
literal|"width"
argument_list|,
name|width
argument_list|,
literal|"height"
argument_list|,
name|height
argument_list|,
literal|"xresolution"
argument_list|,
name|xres
argument_list|,
literal|"yresolution"
argument_list|,
name|yres
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|typedef struct _ResizePrivate ResizePrivate;  struct _ResizePrivate {   ResizeDialog   dialog;    GtkCallback    ok_callback;   gpointer       ok_data;
comment|/*  size frame  */
end_comment

begin_comment
unit|GtkWidget     *orig_width_label;   GtkWidget     *orig_height_label;    GtkWidget     *size_se;    GtkObject     *ratio_x_adj;   GtkObject     *ratio_y_adj;   GtkWidget     *constrain;
comment|/*  offset frame  */
end_comment

begin_comment
unit|GtkWidget     *offset_se;   GtkWidget     *offset_area;
comment|/*  resolution frame  */
end_comment

begin_comment
unit|GtkWidget     *printsize_se;   GtkWidget     *resolution_se;   GtkWidget     *equal_res;
comment|/*  interpolation menu  */
end_comment

begin_comment
unit|GtkWidget     *interpolation_menu;    gint           old_width, old_height;   gdouble        old_res_x, old_res_y; };   static void  unit_update                 (GtkWidget    *widget, 					  gpointer      data); static gint  resize_bound_off_x          (ResizeDialog *dialog, 					  gint          off_x); static gint  resize_bound_off_y          (ResizeDialog *dialog, 					  gint          off_y); static void  orig_labels_update          (GtkWidget    *widget, 					  gpointer      data); static void  response_callback           (GtkWidget    *widget,                                           gint          response_id, 					  ResizeDialog *dialog); static void  size_callback               (GtkWidget    *widget, 					  ResizeDialog *dialog); static void  ratio_callback              (GtkWidget *   widget, 					  ResizeDialog *dialog); static void  size_update                 (ResizeDialog *dialog, 					  gdouble       width, 					  gdouble       height, 					  gdouble       ratio_x, 					  gdouble       ratio_y); static void  offset_area_offsets_changed (GtkWidget    *offset_area,                                           gint          offset_x,                                           gint          offset_y,                                           gpointer      data); static void  offset_update               (GtkWidget    *widget, 					  gpointer      data); static void  offset_center_clicked       (GtkWidget    *widget,                                           gpointer      data); static void  printsize_update            (GtkWidget    *widget, 					  gpointer      data); static void  resolution_callback         (GtkWidget    *widget, 					  gpointer      data); static void  resolution_update           (ResizeDialog *dialog, 					  gdouble       res_x, 					  gdouble       res_y);   ResizeDialog * resize_dialog_new (GimpViewable *viewable,                    GtkWidget    *parent,                    ResizeType    type, 		   gint          width, 		   gint          height, 		   gdouble       resolution_x, 		   gdouble       resolution_y, 		   GimpUnit      unit, 		   GCallback     ok_cb, 		   gpointer      user_data) {   ResizeDialog   *dialog;   ResizePrivate  *private;   GimpCoreConfig *config;   GtkWidget      *main_vbox;   GtkWidget      *vbox;   GtkWidget      *hbox;   GtkWidget      *table;   GtkWidget      *table2;   GtkWidget      *label;   GtkWidget      *frame = NULL;   GtkWidget      *spinbutton;   GtkObject      *adjustment;    g_return_val_if_fail (GIMP_IS_ITEM (viewable) ||                         GIMP_IS_IMAGE (viewable), NULL);   g_return_val_if_fail (ok_cb != NULL, NULL);    private = g_new0 (ResizePrivate, 1);    private->ok_callback = (GtkCallback) ok_cb;   private->ok_data     = user_data;   private->old_width   = width;   private->old_height  = height;   private->old_res_x   = resolution_x;   private->old_res_y   = resolution_y;    dialog = (ResizeDialog *) private;    if (GIMP_IS_IMAGE (viewable))     {       dialog->gimage = GIMP_IMAGE (viewable);       dialog->target = RESIZE_IMAGE;     }   else     {       dialog->gimage = gimp_item_get_image (GIMP_ITEM (viewable));       dialog->target = RESIZE_LAYER;     }    config = dialog->gimage->gimp->config;    dialog->type          = type;   dialog->width         = width;   dialog->height        = height;   dialog->resolution_x  = resolution_x;   dialog->resolution_y  = resolution_y;   dialog->unit          = unit;   dialog->ratio_x       = 1.0;   dialog->ratio_y       = 1.0;   dialog->offset_x      = 0;   dialog->offset_y      = 0;   dialog->interpolation = config->interpolation_type;
comment|/*  dialog box  */
end_comment

begin_comment
unit|{     const gchar *role         = NULL;     const gchar *window_title = NULL;     const gchar *stock_id     = NULL;     const gchar *window_desc  = NULL;     gchar *help_page          = NULL;      switch (type)       {       case RESIZE_DIALOG:         stock_id = GIMP_STOCK_RESIZE;  	switch (dialog->target) 	  { 	  case RESIZE_LAYER: 	    role         = "gimp-layer-resize"; 	    window_title = _("Resize Layer");             window_desc  = _("Resize Layer Options"); 	    help_page    = GIMP_HELP_LAYER_RESIZE; 	    frame        = gimp_frame_new (_("Size")); 	    break;  	  case RESIZE_IMAGE: 	    role         = "gimp-image-resize"; 	    window_title = _("Resize Image");             window_desc  = _("Resize Image Options"); 	    help_page    = GIMP_HELP_IMAGE_RESIZE; 	    frame        = gimp_frame_new (_("Pixel Dimensions")); 	    break; 	  } 	break;        case RESIZE_DIALOG:         stock_id = GIMP_STOCK_RESIZE;  	switch (dialog->target) 	  { 	  case RESIZE_LAYER: 	    role         = "gimp-layer-resize"; 	    window_title = _("Layer Boundary Size");             window_desc  = _("Set Layer Boundary Size"); 	    help_page    = GIMP_HELP_LAYER_RESIZE; 	    break;  	  case RESIZE_IMAGE: 	    role         = "gimp-image-resize"; 	    window_title = _("Canvas Size");             window_desc  = _("Set Image Canvas Size"); 	    help_page    = GIMP_HELP_IMAGE_RESIZE; 	    break; 	  } 	frame = gimp_frame_new (_("Size")); 	break;       }      dialog->shell =       gimp_viewable_dialog_new (viewable,                                 window_title, role,                                 stock_id, window_desc,                                 parent,                                 gimp_standard_help_func, help_page,                                  GIMP_STOCK_RESET, RESIZE_RESPONSE_RESET,                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,                                 GTK_STOCK_OK,     GTK_RESPONSE_OK,                                  NULL);      g_signal_connect (dialog->shell, "response",                       G_CALLBACK (response_callback),                       dialog);      g_object_weak_ref (G_OBJECT (dialog->shell), 		       (GWeakNotify) g_free, 		       private);      gtk_window_set_resizable (GTK_WINDOW (dialog->shell), FALSE);   }
comment|/*  the main vbox  */
end_comment

begin_comment
unit|main_vbox = gtk_vbox_new (FALSE, 12);   gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 12);   gtk_container_add (GTK_CONTAINER (GTK_DIALOG (dialog->shell)->vbox), 		     main_vbox);
comment|/*  the pixel dimensions frame  */
end_comment

begin_comment
unit|gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);   gtk_widget_show (frame);    vbox = gtk_vbox_new (FALSE, 2);   gtk_container_add (GTK_CONTAINER (frame), vbox);    table = gtk_table_new (6, 2, FALSE);   gtk_table_set_col_spacings (GTK_TABLE (table), 2);   gtk_table_set_col_spacing (GTK_TABLE (table), 0, 4);   gtk_table_set_row_spacings (GTK_TABLE (table), 2);   gtk_table_set_row_spacing (GTK_TABLE (table), 0, 4);   gtk_table_set_row_spacing (GTK_TABLE (table), 1, 4);   gtk_table_set_row_spacing (GTK_TABLE (table), 3, 4);   gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, FALSE, 0);   gtk_widget_show (table);
comment|/*  the original width& height labels  */
end_comment

begin_comment
unit|label = gtk_label_new (_("Current width:"));   gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (label);    label = gtk_label_new (_("Current height:"));   gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table), label, 0, 1, 1, 2, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (label);    private->orig_width_label = gtk_label_new ("");   gtk_misc_set_alignment (GTK_MISC (private->orig_width_label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table),  private->orig_width_label, 1, 2, 0, 1, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (private->orig_width_label);    private->orig_height_label = gtk_label_new ("");   gtk_misc_set_alignment (GTK_MISC (private->orig_height_label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table), private->orig_height_label, 1, 2, 1, 2, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (private->orig_height_label);
comment|/*  the new size labels  */
end_comment

begin_comment
unit|label = gtk_label_new (_("New width:"));   gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table), label, 0, 1, 2, 3, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (label);    label = gtk_label_new (_("New height:"));   gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table), label, 0, 1, 3, 4, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (label);
comment|/*  the new size sizeentry  */
end_comment

begin_comment
unit|spinbutton = gimp_spin_button_new (&adjustment,                                      1, 1, 1, 1, 10, 1,                                      1, 2);   gtk_entry_set_width_chars (GTK_ENTRY (spinbutton), SB_WIDTH);    private->size_se = gimp_size_entry_new (1, unit, "%a",                                           TRUE, TRUE, FALSE, SB_WIDTH,                                           GIMP_SIZE_ENTRY_UPDATE_SIZE);   gtk_table_set_col_spacing (GTK_TABLE (private->size_se), 1, 4);   gtk_table_set_row_spacing (GTK_TABLE (private->size_se), 0, 2);    gimp_size_entry_add_field (GIMP_SIZE_ENTRY (private->size_se), 			     GTK_SPIN_BUTTON (spinbutton), NULL);   gtk_table_attach_defaults (GTK_TABLE (private->size_se), spinbutton, 			     1, 2, 0, 1);   gtk_widget_show (spinbutton);    gtk_table_attach (GTK_TABLE (table), private->size_se, 1, 2, 2, 4, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (private->size_se);    gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->size_se), 0, 				  resolution_x, FALSE);   gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->size_se), 1, 				  resolution_y, FALSE);    gimp_size_entry_set_refval_boundaries (GIMP_SIZE_ENTRY (private->size_se), 0, 					 GIMP_MIN_IMAGE_SIZE, 					 GIMP_MAX_IMAGE_SIZE);   gimp_size_entry_set_refval_boundaries (GIMP_SIZE_ENTRY (private->size_se), 1, 					 GIMP_MIN_IMAGE_SIZE, 					 GIMP_MAX_IMAGE_SIZE);    gimp_size_entry_set_size (GIMP_SIZE_ENTRY (private->size_se), 0, 0, width);   gimp_size_entry_set_size (GIMP_SIZE_ENTRY (private->size_se), 1, 0, height);    gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->size_se), 0, width);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->size_se), 1, height);    g_signal_connect (private->size_se, "value_changed", 		    G_CALLBACK (size_callback), 		    dialog);   g_signal_connect (private->size_se, "unit_changed", 		    G_CALLBACK (orig_labels_update), 		    dialog);
comment|/*  initialize the original width& height labels  */
end_comment

begin_comment
unit|orig_labels_update (private->size_se, dialog);
comment|/*  the resize ratio labels  */
end_comment

begin_comment
unit|label = gtk_label_new (_("X ratio:"));   gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table), label, 0, 1, 4, 5, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (label);    label = gtk_label_new (_("Y ratio:"));   gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);   gtk_table_attach (GTK_TABLE (table), label, 0, 1, 5, 6, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (label);
comment|/*  a table for the spinbuttons and the chainbutton  */
end_comment

begin_comment
unit|hbox = gtk_hbox_new (FALSE, 0);   gtk_table_attach (GTK_TABLE (table), hbox, 1, 2, 4, 6, 		    GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (hbox);    table2 = gtk_table_new (2, 2, FALSE);   gtk_table_set_col_spacing (GTK_TABLE (table2), 0, 2);   gtk_table_set_row_spacing (GTK_TABLE (table2), 0, 2);   gtk_box_pack_start (GTK_BOX (hbox), table2, FALSE, FALSE, 0);   gtk_widget_show (table2);
comment|/*  the resize ratio spinbuttons  */
end_comment

begin_comment
unit|spinbutton =     gimp_spin_button_new (&private->ratio_x_adj,                           dialog->ratio_x,                           (double) GIMP_MIN_IMAGE_SIZE / (double) dialog->width,                           (double) GIMP_MAX_IMAGE_SIZE / (double) dialog->width,                           0.01, 0.1, 1,                           0.01, 4);   gtk_entry_set_width_chars (GTK_ENTRY (spinbutton), SB_WIDTH);   gtk_table_attach_defaults (GTK_TABLE (table2), spinbutton, 0, 1, 0, 1);   gtk_widget_show (spinbutton);    g_signal_connect (private->ratio_x_adj, "value_changed", 		    G_CALLBACK (ratio_callback), 		    dialog);    spinbutton =     gimp_spin_button_new (&private->ratio_y_adj,                           dialog->ratio_y,                           (double) GIMP_MIN_IMAGE_SIZE / (double) dialog->height,                           (double) GIMP_MAX_IMAGE_SIZE / (double) dialog->height,                           0.01, 0.1, 1,                           0.01, 4);   gtk_entry_set_width_chars (GTK_ENTRY (spinbutton), SB_WIDTH);   gtk_table_attach_defaults (GTK_TABLE (table2), spinbutton, 0, 1, 1, 2);   gtk_widget_show (spinbutton);    g_signal_connect (private->ratio_y_adj, "value_changed", 		    G_CALLBACK (ratio_callback), 		    dialog);
comment|/*  the constrain ratio chainbutton  */
end_comment

begin_comment
unit|private->constrain = gimp_chain_button_new (GIMP_CHAIN_RIGHT);   gimp_chain_button_set_active (GIMP_CHAIN_BUTTON (private->constrain), TRUE);   gtk_table_attach (GTK_TABLE (table2), private->constrain, 1, 2, 0, 2,                     GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);   gtk_widget_show (private->constrain);    gimp_help_set_help_data (GIMP_CHAIN_BUTTON (private->constrain)->button,                            _("Constrain aspect ratio"), NULL);    gtk_widget_show (vbox);
comment|/*  the offset frame  */
end_comment

begin_comment
unit|if (type == RESIZE_DIALOG)     {       GtkWidget *button;       GtkWidget *abox;        frame = gimp_frame_new (_("Offset"));       gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);       gtk_widget_show (frame);        vbox = gtk_vbox_new (FALSE, 6);       gtk_container_add (GTK_CONTAINER (frame), vbox);       gtk_widget_show (vbox);
comment|/*  the offset sizeentry  */
end_comment

begin_comment
unit|spinbutton = gimp_spin_button_new (&adjustment,                                          1, 1, 1, 1, 10, 1,                                          1, 2);       gtk_entry_set_width_chars (GTK_ENTRY (spinbutton), SB_WIDTH);        private->offset_se = gimp_size_entry_new (1, unit, "%a",                                                 TRUE, FALSE, FALSE, SB_WIDTH,                                                 GIMP_SIZE_ENTRY_UPDATE_SIZE);       gtk_table_set_col_spacing (GTK_TABLE (private->offset_se), 0, 4);       gtk_table_set_col_spacing (GTK_TABLE (private->offset_se), 1, 4);       gtk_table_set_col_spacing (GTK_TABLE (private->offset_se), 3, 8);       gtk_table_set_row_spacing (GTK_TABLE (private->offset_se), 0, 2);        gimp_size_entry_add_field (GIMP_SIZE_ENTRY (private->offset_se), 				 GTK_SPIN_BUTTON (spinbutton), NULL);       gtk_table_attach_defaults (GTK_TABLE (private->offset_se), spinbutton, 				 1, 2, 0, 1);       gtk_widget_show (spinbutton);        gimp_size_entry_attach_label (GIMP_SIZE_ENTRY (private->offset_se), 				    _("_X:"), 0, 0, 0.0);       gimp_size_entry_attach_label (GIMP_SIZE_ENTRY (private->offset_se), 				    _("_Y:"), 1, 0, 0.0);       gtk_box_pack_start (GTK_BOX (vbox), private->offset_se, FALSE, FALSE, 0);       gtk_widget_show (private->offset_se);        gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->offset_se), 0, 				      resolution_x, FALSE);       gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->offset_se), 1, 				      resolution_y, FALSE);        gimp_size_entry_set_refval_boundaries 	(GIMP_SIZE_ENTRY (private->offset_se), 0, 0, 0);       gimp_size_entry_set_refval_boundaries 	(GIMP_SIZE_ENTRY (private->offset_se), 1, 0, 0);        gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->offset_se), 0, 0);       gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->offset_se), 1, 0);        g_signal_connect (private->offset_se, "value_changed", 			G_CALLBACK (offset_update), 			dialog);        button = gtk_button_new_with_mnemonic (_("C_enter"));       gtk_misc_set_padding (GTK_MISC (GTK_BIN (button)->child), 4, 0);       gtk_table_attach_defaults (GTK_TABLE (private->offset_se), button,                                  4, 5, 1, 2);       gtk_widget_show (button);        g_signal_connect (button, "clicked", 			G_CALLBACK (offset_center_clicked), 			dialog);
comment|/*  frame to hold GimpOffsetArea  */
end_comment

begin_comment
unit|abox = gtk_alignment_new (0.5, 0.5, 0.0, 0.0);       gtk_box_pack_start (GTK_BOX (vbox), abox, FALSE, FALSE, 0);       gtk_widget_show (abox);        frame = gtk_frame_new (NULL);       gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);       gtk_container_add (GTK_CONTAINER (abox), frame);        private->offset_area = gimp_offset_area_new (private->old_width,                                                    private->old_height);       gtk_container_add (GTK_CONTAINER (frame), private->offset_area);       gtk_widget_show (private->offset_area);        {         GdkPixbuf *pixbuf;         gint       w, h;          gimp_viewable_get_preview_size (viewable, 200, FALSE, TRUE,&w,&h);          pixbuf = gimp_viewable_get_pixbuf (viewable, w, h);         gimp_offset_area_set_pixbuf (GIMP_OFFSET_AREA (private->offset_area),                                      pixbuf);       }        g_signal_connect (private->offset_area, "offsets_changed", 			G_CALLBACK (offset_area_offsets_changed), 			dialog);        gtk_widget_show (frame);     }
comment|/*  the resolution stuff  */
end_comment

begin_comment
unit|if ((type == RESIZE_DIALOG)&& (dialog->target == RESIZE_IMAGE))     {       frame = gimp_frame_new (_("Print Size& Display Unit"));       gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);       gtk_widget_show (frame);        vbox = gtk_vbox_new (FALSE, 6);       gtk_container_add (GTK_CONTAINER (frame), vbox);        table = gtk_table_new (4, 2, FALSE);       gtk_table_set_col_spacing (GTK_TABLE (table), 0, 4);       gtk_table_set_row_spacings (GTK_TABLE (table), 2);       gtk_table_set_row_spacing (GTK_TABLE (table), 1, 4);       gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, FALSE, 0);
comment|/*  the print size labels  */
end_comment

begin_comment
unit|label = gtk_label_new (_("New width:"));       gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);       gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1, 			GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);       gtk_widget_show (label);        label = gtk_label_new (_("New height:"));       gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);       gtk_table_attach (GTK_TABLE (table), label, 0, 1, 1, 2, 			GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);       gtk_widget_show (label);
comment|/*  the print size sizeentry  */
end_comment

begin_comment
unit|hbox = gtk_hbox_new (FALSE, 0);       gtk_table_attach (GTK_TABLE (table), hbox, 1, 2, 0, 1, 			GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);       gtk_widget_show (hbox);        spinbutton = gimp_spin_button_new (&adjustment,                                          1, 1, 1, 1, 10, 1,                                          1, 2);       gtk_entry_set_width_chars (GTK_ENTRY (spinbutton), SB_WIDTH);       gtk_box_pack_start (GTK_BOX (hbox), spinbutton, FALSE, FALSE, 0);       gtk_widget_show (spinbutton);        hbox = gtk_hbox_new (FALSE, 0);       gtk_table_attach (GTK_TABLE (table), hbox, 1, 2, 1, 2, 			GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);       gtk_widget_show (hbox);        private->printsize_se = gimp_size_entry_new (1, unit, "%a",                                                    FALSE, FALSE, FALSE, SB_WIDTH,                                                    GIMP_SIZE_ENTRY_UPDATE_SIZE);       gtk_table_set_col_spacing (GTK_TABLE (private->printsize_se), 1, 4);        gimp_size_entry_add_field (GIMP_SIZE_ENTRY (private->printsize_se), 				 GTK_SPIN_BUTTON (spinbutton), NULL);        gtk_box_pack_start (GTK_BOX (hbox),                           private->printsize_se, FALSE, FALSE, 0);       gtk_widget_show (private->printsize_se);        gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->printsize_se), 				      0, resolution_x, FALSE);       gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->printsize_se), 				      1, resolution_y, FALSE);        gimp_size_entry_set_refval_boundaries 	(GIMP_SIZE_ENTRY (private->printsize_se), 	 0, GIMP_MIN_IMAGE_SIZE, GIMP_MAX_IMAGE_SIZE);       gimp_size_entry_set_refval_boundaries 	(GIMP_SIZE_ENTRY (private->printsize_se), 	 1, GIMP_MIN_IMAGE_SIZE, GIMP_MAX_IMAGE_SIZE);        gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->printsize_se), 				  0, dialog->width);       gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->printsize_se), 				  1, dialog->height);        g_signal_connect (private->printsize_se, "value_changed", 			G_CALLBACK (printsize_update), 			dialog);       g_signal_connect (private->printsize_se, "unit_changed", 			G_CALLBACK (unit_update), 			dialog);
comment|/*  the resolution labels  */
end_comment

begin_comment
unit|label = gtk_label_new (_("X resolution:"));       gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);       gtk_table_attach (GTK_TABLE (table), label, 0, 1, 2, 3, 			GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);       gtk_widget_show (label);        label = gtk_label_new (_("Y resolution:"));       gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);       gtk_table_attach (GTK_TABLE (table), label, 0, 1, 3, 4, 			GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);       gtk_widget_show (label);
comment|/*  the resolution sizeentry  */
end_comment

begin_comment
unit|spinbutton = gimp_spin_button_new (&adjustment,                                          1, 1, 1, 1, 10, 1,                                          1, 2);       gtk_entry_set_width_chars (GTK_ENTRY (spinbutton), SB_WIDTH);        private->resolution_se = 	gimp_size_entry_new (1, config->default_image->resolution_unit, 			     _("pixels/%a"), 			     FALSE, FALSE, FALSE, SB_WIDTH, 			     GIMP_SIZE_ENTRY_UPDATE_RESOLUTION);       gtk_table_set_col_spacing (GTK_TABLE (private->resolution_se), 1, 2);       gtk_table_set_col_spacing (GTK_TABLE (private->resolution_se), 2, 2);       gtk_table_set_row_spacing (GTK_TABLE (private->resolution_se), 0, 2);        gimp_size_entry_add_field (GIMP_SIZE_ENTRY (private->resolution_se), 				 GTK_SPIN_BUTTON (spinbutton), NULL);       gtk_table_attach_defaults (GTK_TABLE (private->resolution_se), spinbutton, 				 1, 2, 0, 1);       gtk_widget_show (spinbutton);        gtk_table_attach (GTK_TABLE (table), private->resolution_se, 1, 2, 2, 4, 			GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);       gtk_widget_show (private->resolution_se);        gimp_size_entry_set_refval_boundaries 	(GIMP_SIZE_ENTRY (private->resolution_se), 	 0, GIMP_MIN_RESOLUTION, GIMP_MAX_RESOLUTION);       gimp_size_entry_set_refval_boundaries 	(GIMP_SIZE_ENTRY (private->resolution_se), 	 1, GIMP_MIN_RESOLUTION, GIMP_MAX_RESOLUTION);        gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->resolution_se), 				  0, dialog->resolution_x);       gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->resolution_se), 				  1, dialog->resolution_y);        g_signal_connect (private->resolution_se, "value_changed", 			G_CALLBACK (resolution_callback), 			dialog);
comment|/*  the resolution chainbutton  */
end_comment

begin_comment
unit|private->equal_res = gimp_chain_button_new (GIMP_CHAIN_RIGHT);       gimp_chain_button_set_active 	(GIMP_CHAIN_BUTTON (private->equal_res), 	 ABS (dialog->resolution_x - dialog->resolution_y)< 1e-5);       gtk_table_attach_defaults (GTK_TABLE (private->resolution_se), 				 private->equal_res, 2, 3, 0, 2);       gtk_widget_show (private->equal_res);        gtk_widget_show (table);       gtk_widget_show (vbox);     }
comment|/*  the interpolation menu  */
end_comment

begin_comment
unit|if (type == RESIZE_DIALOG)     {       GtkWidget *hbox;       GtkWidget *combo;        hbox = gtk_hbox_new (FALSE, 6);       gtk_box_pack_start (GTK_BOX (main_vbox), hbox, FALSE, FALSE, 0);       gtk_widget_show (hbox);        label = gtk_label_new (_("Interpolation:"));       gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);       gtk_widget_show (label);        combo = gimp_enum_combo_box_new (GIMP_TYPE_INTERPOLATION_TYPE);       gimp_int_combo_box_set_active (GIMP_INT_COMBO_BOX (combo),                                      dialog->interpolation);        g_signal_connect (combo, "changed",                         G_CALLBACK (gimp_int_combo_box_get_active),&dialog->interpolation);        gtk_box_pack_start (GTK_BOX (hbox), combo, FALSE, FALSE, 0);       gtk_widget_show (combo);        private->interpolation_menu = combo;        if (gimp_image_base_type (dialog->gimage) == GIMP_INDEXED)         {           label = gtk_label_new (_("Indexed color layers are always resized "                                    "without interpolation. The chosen "                                    "interpolation type will affect scaling "                                    "channels and masks only."));           gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.0);           gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);           gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);           gtk_box_pack_start (GTK_BOX (main_vbox), label, FALSE, FALSE, 0);           gtk_widget_show (label);         }     }    gtk_widget_show (main_vbox);
comment|/*  finally, activate the first entry  */
end_comment

begin_comment
unit|gimp_size_entry_grab_focus (GIMP_SIZE_ENTRY (private->size_se));    return dialog; }  static gint resize_bound_off_x (ResizeDialog *dialog, 		    gint          off_x) {   ResizePrivate *private = (ResizePrivate *) dialog;    if (private->old_width<= dialog->width)     off_x = CLAMP (off_x, 0, (dialog->width - private->old_width));   else     off_x = CLAMP (off_x, (dialog->width - private->old_width), 0);    return off_x; }  static gint resize_bound_off_y (ResizeDialog *dialog, 		    gint          off_y) {   ResizePrivate *private = (ResizePrivate *) dialog;    if (private->old_height<= dialog->height)     off_y = CLAMP (off_y, 0, (dialog->height - private->old_height));   else     off_y = CLAMP (off_y, (dialog->height - private->old_height), 0);    return off_y; }  static void orig_labels_update (GtkWidget *widget, 		    gpointer   data) {   ResizeDialog  *dialog  = data;   ResizePrivate *private = (ResizePrivate *) dialog;   GimpUnit       unit;   gchar          format_buf[16];   gchar          buf[32];    static GimpUnit label_unit = GIMP_UNIT_PIXEL;    unit = gimp_size_entry_get_unit (GIMP_SIZE_ENTRY (widget));    if (unit != GIMP_UNIT_PERCENT)     label_unit = unit;    if (label_unit)
comment|/* unit != GIMP_UNIT_PIXEL */
end_comment

begin_comment
unit|{       gdouble unit_factor = gimp_unit_get_factor (label_unit);        g_snprintf (format_buf, sizeof (format_buf), "%%.%df %s",                   gimp_unit_get_digits (label_unit) + 1,                   gimp_unit_get_symbol (label_unit));       g_snprintf (buf, sizeof (buf), format_buf,                   private->old_width * unit_factor / private->old_res_x);       gtk_label_set_text (GTK_LABEL (private->orig_width_label), buf);       g_snprintf (buf, sizeof (buf), format_buf,                   private->old_height * unit_factor / private->old_res_y);       gtk_label_set_text (GTK_LABEL (private->orig_height_label), buf);     }   else
comment|/* unit == GIMP_UNIT_PIXEL */
end_comment

begin_comment
unit|{       g_snprintf (buf, sizeof (buf), "%d", private->old_width);       gtk_label_set_text (GTK_LABEL (private->orig_width_label), buf);       g_snprintf (buf, sizeof (buf), "%d", private->old_height);       gtk_label_set_text (GTK_LABEL (private->orig_height_label), buf);     } }  static void unit_update (GtkWidget *widget, 	     gpointer   data) {   ResizeDialog *dialog = data;    dialog->unit = gimp_size_entry_get_unit (GIMP_SIZE_ENTRY (widget)); }  static void offset_update (GtkWidget *widget, 	       gpointer   data) {   ResizeDialog  *dialog  = data;   ResizePrivate *private = (ResizePrivate *) dialog;    dialog->offset_x = resize_bound_off_x (dialog,                                          RINT (gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->offset_se), 0)));    dialog->offset_y = resize_bound_off_y (dialog,                                          RINT (gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->offset_se), 1)));    gimp_offset_area_set_offsets (GIMP_OFFSET_AREA (private->offset_area),                                 dialog->offset_x, dialog->offset_y); }  static void offset_center_clicked (GtkWidget *widget,                        gpointer   data) {   ResizeDialog  *dialog  = data;   ResizePrivate *private = (ResizePrivate *) dialog;   gint           off_x, off_y;    off_x = resize_bound_off_x (dialog,                               (dialog->width - private->old_width)  / 2);    off_y = resize_bound_off_y (dialog,                               (dialog->height - private->old_height) / 2);    gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->offset_se), 0, off_x);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->offset_se), 1, off_y);    g_signal_emit_by_name (private->offset_se, "value_changed", 0); }  static void response_callback (GtkWidget    *widget,                    gint          response_id,                    ResizeDialog *dialog) {   ResizePrivate *private = (ResizePrivate *) dialog;    switch (response_id)     {     case RESIZE_RESPONSE_RESET:
comment|/* restore size and ratio settings */
end_comment

begin_comment
unit|size_update (dialog, private->old_width, private->old_height, 1.0, 1.0);        if ((dialog->type == RESIZE_DIALOG)&& (dialog->target == RESIZE_IMAGE))         {
comment|/* restore resolution settings */
end_comment

begin_comment
unit|resolution_update (dialog, private->old_res_x, private->old_res_y);         }        if (dialog->type == RESIZE_DIALOG)         {           dialog->interpolation =             dialog->gimage->gimp->config->interpolation_type;            gimp_int_combo_box_set_active (GIMP_INT_COMBO_BOX (private->interpolation_menu),                                          dialog->interpolation);         }       break;      case GTK_RESPONSE_OK:       private->ok_callback (widget, private->ok_data);       break;      default:       gtk_widget_destroy (widget);       break;     } }  static void size_callback (GtkWidget    *widget,                ResizeDialog *dialog) {   ResizePrivate *private = (ResizePrivate *) dialog;   gdouble        width;   gdouble        height;   gdouble        ratio_x;   gdouble        ratio_y;    width  = gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->size_se), 0);   height = gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->size_se), 1);    ratio_x = width  / (gdouble) private->old_width;   ratio_y = height / (gdouble) private->old_height;    if (gimp_chain_button_get_active (GIMP_CHAIN_BUTTON (private->constrain)))     {       if (ratio_x != dialog->ratio_x) 	{ 	  ratio_y = ratio_x; 	  height = (gdouble) private->old_height * ratio_y; 	  height = CLAMP (height, GIMP_MIN_IMAGE_SIZE, GIMP_MAX_IMAGE_SIZE); 	}       else 	{ 	  ratio_x = ratio_y; 	  width = (gdouble) private->old_width * ratio_x; 	  width = CLAMP (width, GIMP_MIN_IMAGE_SIZE, GIMP_MAX_IMAGE_SIZE); 	}     }    size_update (dialog, width, height, ratio_x, ratio_y); }  static void ratio_callback (GtkWidget    *widget,                 ResizeDialog *dialog) {   ResizePrivate *private = (ResizePrivate *) dialog;   gdouble        width;   gdouble        height;   gdouble        ratio_x;   gdouble        ratio_y;    ratio_x = GTK_ADJUSTMENT (private->ratio_x_adj)->value;   ratio_y = GTK_ADJUSTMENT (private->ratio_y_adj)->value;    if (gimp_chain_button_get_active (GIMP_CHAIN_BUTTON (private->constrain)))     {       if (ratio_x != dialog->ratio_x) 	{ 	  ratio_y = ratio_x; 	}       else 	{ 	  ratio_x = ratio_y; 	}     }    width  = CLAMP (private->old_width * ratio_x, 		  GIMP_MIN_IMAGE_SIZE, GIMP_MAX_IMAGE_SIZE);   height = CLAMP (private->old_height * ratio_y, 		  GIMP_MIN_IMAGE_SIZE, GIMP_MAX_IMAGE_SIZE);    size_update (dialog, width, height, ratio_x, ratio_y); }  static void size_update (ResizeDialog *dialog, 	     double        width, 	     double        height, 	     double        ratio_x, 	     double        ratio_y) {   ResizePrivate *private = (ResizePrivate *) dialog;    dialog->width  = (gint) (width  + 0.5);   dialog->height = (gint) (height + 0.5);    dialog->ratio_x = ratio_x;   dialog->ratio_y = ratio_y;    if (private->offset_area)     gimp_offset_area_set_size (GIMP_OFFSET_AREA (private->offset_area), 			       dialog->width, dialog->height);    g_signal_handlers_block_by_func (private->size_se,                                    size_callback, dialog);    gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->size_se), 			      0, width);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->size_se), 			      1, height);    g_signal_handlers_unblock_by_func (private->size_se,                                      size_callback, dialog);    g_signal_handlers_block_by_func (private->ratio_x_adj,                                    ratio_callback, dialog);   g_signal_handlers_block_by_func (private->ratio_y_adj,                                    ratio_callback, dialog);    gtk_adjustment_set_value (GTK_ADJUSTMENT (private->ratio_x_adj), ratio_x);   gtk_adjustment_set_value (GTK_ADJUSTMENT (private->ratio_y_adj), ratio_y);    g_signal_handlers_unblock_by_func (private->ratio_x_adj,                                      ratio_callback, dialog);   g_signal_handlers_unblock_by_func (private->ratio_y_adj,                                      ratio_callback, dialog);    if (dialog->type == RESIZE_DIALOG)     {       gimp_size_entry_set_refval_boundaries         (GIMP_SIZE_ENTRY (private->offset_se), 0,          MIN (0, dialog->width - private->old_width),          MAX (0, dialog->width - private->old_width));       gimp_size_entry_set_refval_boundaries         (GIMP_SIZE_ENTRY (private->offset_se), 1,          MIN (0, dialog->height - private->old_height),          MAX (0, dialog->height - private->old_height));     }    if ((dialog->type == RESIZE_DIALOG)&& (dialog->target == RESIZE_IMAGE))     {       g_signal_handlers_block_by_func (private->printsize_se,                                        printsize_update, dialog);        gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->printsize_se), 				  0, width);       gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->printsize_se), 				  1, height);        g_signal_handlers_unblock_by_func (private->printsize_se,                                          printsize_update, dialog);     } }  static void offset_area_offsets_changed (GtkWidget *offset_area,                              gint       offset_x,                              gint       offset_y,                              gpointer   data) {   ResizeDialog  *dialog  = data;   ResizePrivate *private = (ResizePrivate *) dialog;    dialog->offset_x = offset_x;   dialog->offset_y = offset_y;    gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->offset_se),                               0, dialog->offset_x);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->offset_se),                               1, dialog->offset_y); }   static void printsize_update (GtkWidget *widget, 		  gpointer   data) {   ResizeDialog  *dialog  = data;   ResizePrivate *private = (ResizePrivate *) dialog;   gdouble        width;   gdouble        height;   gdouble        print_width;   gdouble        print_height;   gdouble        res_x;   gdouble        res_y;    width  = gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->size_se), 0);   height = gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->size_se), 1);    print_width =     gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->printsize_se), 0);   print_height =     gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->printsize_se), 1);
comment|/*  this is tricky: we use the sizes in pixels (which is otherwise    *  meaningless for the "print size" widgets) to calculate the new    *  resolution.    */
end_comment

begin_comment
unit|res_x = CLAMP (dialog->resolution_x * width / print_width, 		 GIMP_MIN_RESOLUTION, GIMP_MAX_RESOLUTION);   res_y = CLAMP (dialog->resolution_y * height / print_height, 		 GIMP_MIN_RESOLUTION, GIMP_MAX_RESOLUTION);    if (gimp_chain_button_get_active (GIMP_CHAIN_BUTTON (private->equal_res)))     {       if (res_x != dialog->resolution_x) 	{ 	  res_y = res_x; 	}       else 	{ 	  res_x = res_y; 	}     }    dialog->resolution_x = res_x;   dialog->resolution_y = res_y;    g_signal_handlers_block_by_func (private->resolution_se,                                    resolution_callback,                                    dialog);    gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->resolution_se), 			      0, res_x);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->resolution_se), 			      1, res_y);    g_signal_handlers_unblock_by_func (private->resolution_se,                                      resolution_callback, dialog);    g_signal_handlers_block_by_func (private->size_se,                                    size_callback, dialog);    gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->size_se), 				  0, res_x, TRUE);   gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->size_se), 				  1, res_y, TRUE);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->size_se), 			      0, width);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->size_se), 			      1, height);    g_signal_handlers_unblock_by_func (private->size_se,                                      size_callback, dialog);    g_signal_handlers_block_by_func (private->printsize_se,                                    printsize_update, dialog);    gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->printsize_se), 				  0, res_x, TRUE);   gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->printsize_se), 				  1, res_y, TRUE);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->printsize_se), 			      0, width);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->printsize_se), 			      1, height);    g_signal_handlers_unblock_by_func (private->printsize_se,                                      printsize_update, dialog); }
comment|/* Callback for resolution change. */
end_comment

begin_comment
unit|static void resolution_callback (GtkWidget *widget, 		     gpointer   data) {   ResizeDialog  *dialog  = data;   ResizePrivate *private = (ResizePrivate *) dialog;   gdouble        res_x;   gdouble        res_y;    res_x =     gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->resolution_se), 0);   res_y =     gimp_size_entry_get_refval (GIMP_SIZE_ENTRY (private->resolution_se), 1);    if (gimp_chain_button_get_active (GIMP_CHAIN_BUTTON (private->equal_res)))     {       if (res_x != dialog->resolution_x) 	{ 	  res_y = res_x; 	}       else 	{ 	  res_x = res_y; 	}     }    resolution_update (dialog, res_x, res_y); }
comment|/* Update widgets with resolution settings found in given Resize struct. */
end_comment

begin_endif
unit|static void resolution_update (ResizeDialog *dialog, 		   gdouble       res_x, 		   gdouble       res_y) {   ResizePrivate *private = (ResizePrivate *) dialog;    dialog->resolution_x = res_x;   dialog->resolution_y = res_y;    g_signal_handlers_block_by_func (private->resolution_se,                                    resolution_callback, dialog);    gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->resolution_se), 			      0, res_x);   gimp_size_entry_set_refval (GIMP_SIZE_ENTRY (private->resolution_se), 			      1, res_y);    g_signal_handlers_unblock_by_func (private->resolution_se,                                      resolution_callback, dialog);    g_signal_handlers_block_by_func (private->size_se,                                    size_callback, dialog);    gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->size_se), 				  0, res_x, TRUE);   gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->size_se), 				  1, res_y, TRUE);    g_signal_handlers_unblock_by_func (private->size_se,                                      size_callback, dialog);    g_signal_handlers_block_by_func (private->printsize_se,                                    printsize_update, dialog);    gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->printsize_se), 				  0, res_x, TRUE);   gimp_size_entry_set_resolution (GIMP_SIZE_ENTRY (private->printsize_se), 				  1, res_y, TRUE);    g_signal_handlers_unblock_by_func (private->printsize_se,                                      printsize_update, dialog); }
endif|#
directive|endif
end_endif

end_unit

