begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpchannellistitem.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpchannellistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_item_class_init
parameter_list|(
name|GimpChannelListItemClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_channel_list_item_init
parameter_list|(
name|GimpChannelListItem
modifier|*
name|list_item
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* static void   gimp_channel_list_item_drop_color (GtkWidget     *widget, 						 const GimpRGB *color, 						 gpointer       data); */
end_comment

begin_function
name|GType
DECL|function|gimp_channel_list_item_get_type (void)
name|gimp_channel_list_item_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|list_item_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|list_item_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|list_item_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpChannelListItemClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_channel_list_item_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpChannelListItem
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_channel_list_item_init
block|,       }
decl_stmt|;
name|list_item_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DRAWABLE_LIST_ITEM
argument_list|,
literal|"GimpChannelListItem"
argument_list|,
operator|&
name|list_item_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|list_item_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_item_class_init (GimpChannelListItemClass * klass)
name|gimp_channel_list_item_class_init
parameter_list|(
name|GimpChannelListItemClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_list_item_init (GimpChannelListItem * list_item)
name|gimp_channel_list_item_init
parameter_list|(
name|GimpChannelListItem
modifier|*
name|list_item
parameter_list|)
block|{
comment|/*   static GtkTargetEntry color_target_table[] =   {     GIMP_TARGET_COLOR   };   static guint n_color_targets = (sizeof (color_target_table) / 				  sizeof (color_target_table[0]));    gtk_drag_dest_set (GTK_WIDGET (list_item),                      GTK_DEST_DEFAULT_HIGHLIGHT |                      GTK_DEST_DEFAULT_MOTION    |                      GTK_DEST_DEFAULT_DROP,                      color_target_table, n_color_targets,                      GDK_ACTION_COPY);    gimp_dnd_color_dest_set (GTK_WIDGET (list_item), 			   gimp_channel_list_item_drop_color, NULL);   */
block|}
end_function

begin_comment
comment|/* static void gimp_channel_list_item_drop_color (GtkWidget     *widget, 				   const GimpRGB *color, 				   gpointer       data) {   GimpChannel *channel;    channel =     GIMP_CHANNEL (GIMP_PREVIEW (GIMP_LIST_ITEM (widget)->preview)->viewable);    if (gimp_rgba_distance (color,&channel->color)> 0.0001)     {       channel->color = *color;        drawable_update (GIMP_DRAWABLE (channel), 		       0, 0, 		       GIMP_DRAWABLE (channel)->width, 		       GIMP_DRAWABLE (channel)->height);        gdisplays_flush ();     } } */
end_comment

end_unit

