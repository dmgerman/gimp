begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DND_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DND_H__
define|#
directive|define
name|__GIMP_DND_H__
end_define

begin_define
DECL|macro|GIMP_TARGET_URI_LIST
define|#
directive|define
name|GIMP_TARGET_URI_LIST
define|\
value|{ "text/uri-list", 0, GIMP_DND_TYPE_URI_LIST }
end_define

begin_define
DECL|macro|GIMP_TARGET_TEXT_PLAIN
define|#
directive|define
name|GIMP_TARGET_TEXT_PLAIN
define|\
value|{ "text/plain", 0, GIMP_DND_TYPE_TEXT_PLAIN }
end_define

begin_define
DECL|macro|GIMP_TARGET_NETSCAPE_URL
define|#
directive|define
name|GIMP_TARGET_NETSCAPE_URL
define|\
value|{ "_NETSCAPE_URL", 0, GIMP_DND_TYPE_NETSCAPE_URL }
end_define

begin_define
DECL|macro|GIMP_TARGET_XDS
define|#
directive|define
name|GIMP_TARGET_XDS
define|\
value|{ "XdndDirectSave0", 0, GIMP_DND_TYPE_XDS }
end_define

begin_define
DECL|macro|GIMP_TARGET_COLOR
define|#
directive|define
name|GIMP_TARGET_COLOR
define|\
value|{ "application/x-color", 0, GIMP_DND_TYPE_COLOR }
end_define

begin_define
DECL|macro|GIMP_TARGET_SVG
define|#
directive|define
name|GIMP_TARGET_SVG
define|\
value|{ "image/svg", 0, GIMP_DND_TYPE_SVG }
end_define

begin_define
DECL|macro|GIMP_TARGET_SVG_XML
define|#
directive|define
name|GIMP_TARGET_SVG_XML
define|\
value|{ "image/svg+xml", 0, GIMP_DND_TYPE_SVG_XML }
end_define

begin_comment
comment|/* just here for documentation purposes, the actual list of targets  * is created dynamically from available GdkPixbuf loaders  */
end_comment

begin_define
DECL|macro|GIMP_TARGET_PIXBUF
define|#
directive|define
name|GIMP_TARGET_PIXBUF
define|\
value|{ NULL, 0, GIMP_DND_TYPE_PIXBUF }
end_define

begin_define
DECL|macro|GIMP_TARGET_IMAGE
define|#
directive|define
name|GIMP_TARGET_IMAGE
define|\
value|{ "application/x-gimp-image-id", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_IMAGE }
end_define

begin_define
DECL|macro|GIMP_TARGET_COMPONENT
define|#
directive|define
name|GIMP_TARGET_COMPONENT
define|\
value|{ "application/x-gimp-component", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_COMPONENT }
end_define

begin_define
DECL|macro|GIMP_TARGET_LAYER
define|#
directive|define
name|GIMP_TARGET_LAYER
define|\
value|{ "application/x-gimp-layer-id", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_LAYER }
end_define

begin_define
DECL|macro|GIMP_TARGET_CHANNEL
define|#
directive|define
name|GIMP_TARGET_CHANNEL
define|\
value|{ "application/x-gimp-channel-id", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_CHANNEL }
end_define

begin_define
DECL|macro|GIMP_TARGET_LAYER_MASK
define|#
directive|define
name|GIMP_TARGET_LAYER_MASK
define|\
value|{ "application/x-gimp-layer-mask-id", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_LAYER_MASK }
end_define

begin_define
DECL|macro|GIMP_TARGET_VECTORS
define|#
directive|define
name|GIMP_TARGET_VECTORS
define|\
value|{ "application/x-gimp-vectors-id", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_VECTORS }
end_define

begin_define
DECL|macro|GIMP_TARGET_BRUSH
define|#
directive|define
name|GIMP_TARGET_BRUSH
define|\
value|{ "application/x-gimp-brush-name", 0, GIMP_DND_TYPE_BRUSH }
end_define

begin_define
DECL|macro|GIMP_TARGET_PATTERN
define|#
directive|define
name|GIMP_TARGET_PATTERN
define|\
value|{ "application/x-gimp-pattern-name", 0, GIMP_DND_TYPE_PATTERN }
end_define

begin_define
DECL|macro|GIMP_TARGET_GRADIENT
define|#
directive|define
name|GIMP_TARGET_GRADIENT
define|\
value|{ "application/x-gimp-gradient-name", 0, GIMP_DND_TYPE_GRADIENT }
end_define

begin_define
DECL|macro|GIMP_TARGET_PALETTE
define|#
directive|define
name|GIMP_TARGET_PALETTE
define|\
value|{ "application/x-gimp-palette-name", 0, GIMP_DND_TYPE_PALETTE }
end_define

begin_define
DECL|macro|GIMP_TARGET_FONT
define|#
directive|define
name|GIMP_TARGET_FONT
define|\
value|{ "application/x-gimp-font-name", 0, GIMP_DND_TYPE_FONT }
end_define

begin_define
DECL|macro|GIMP_TARGET_BUFFER
define|#
directive|define
name|GIMP_TARGET_BUFFER
define|\
value|{ "application/x-gimp-buffer-name", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_BUFFER }
end_define

begin_define
DECL|macro|GIMP_TARGET_IMAGEFILE
define|#
directive|define
name|GIMP_TARGET_IMAGEFILE
define|\
value|{ "application/x-gimp-imagefile-name", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_IMAGEFILE }
end_define

begin_define
DECL|macro|GIMP_TARGET_TEMPLATE
define|#
directive|define
name|GIMP_TARGET_TEMPLATE
define|\
value|{ "application/x-gimp-template-name", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_TEMPLATE }
end_define

begin_define
DECL|macro|GIMP_TARGET_TOOL_INFO
define|#
directive|define
name|GIMP_TARGET_TOOL_INFO
define|\
value|{ "application/x-gimp-tool-info-name", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_TOOL_INFO }
end_define

begin_define
DECL|macro|GIMP_TARGET_DIALOG
define|#
directive|define
name|GIMP_TARGET_DIALOG
define|\
value|{ "application/x-gimp-dialog", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_DIALOG }
end_define

begin_comment
comment|/*  dnd initialization  */
end_comment

begin_function_decl
name|void
name|gimp_dnd_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  uri list dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDragUriListFunc
typedef|typedef
name|GList
modifier|*
function_decl|(
modifier|*
name|GimpDndDragUriListFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDropUriListFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropUriListFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GList
modifier|*
name|uri_list
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_uri_list_source_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDragUriListFunc
name|get_uri_list_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_uri_list_source_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_uri_list_dest_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDropUriListFunc
name|set_uri_list_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_uri_list_dest_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  color dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDragColorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDragColorFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDropColorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropColorFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_color_source_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDragColorFunc
name|get_color_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_color_source_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_color_dest_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDropColorFunc
name|set_color_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_color_dest_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  stream dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDragStreamFunc
typedef|typedef
name|guchar
modifier|*
function_decl|(
modifier|*
name|GimpDndDragStreamFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gsize
modifier|*
name|stream_len
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDropStreamFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropStreamFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|stream
parameter_list|,
name|gsize
name|stream_len
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_svg_source_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDragStreamFunc
name|get_svg_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_svg_source_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_svg_dest_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDropStreamFunc
name|set_svg_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_svg_dest_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  pixbuf dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDragPixbufFunc
typedef|typedef
name|GdkPixbuf
modifier|*
function_decl|(
modifier|*
name|GimpDndDragPixbufFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDropPixbufFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropPixbufFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_pixbuf_source_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDragPixbufFunc
name|get_pixbuf_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_pixbuf_source_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_pixbuf_dest_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDropPixbufFunc
name|set_pixbuf_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_pixbuf_dest_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  component dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDragComponentFunc
typedef|typedef
name|GimpImage
modifier|*
function_decl|(
modifier|*
name|GimpDndDragComponentFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
modifier|*
name|context
parameter_list|,
name|GimpChannelType
modifier|*
name|channel
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDropComponentFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropComponentFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_component_source_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDragComponentFunc
name|get_comp_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_component_source_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_component_dest_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDropComponentFunc
name|set_comp_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_component_dest_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  GimpViewable (by GType) dnd functions  */
end_comment

begin_typedef
DECL|typedef|GimpDndDragViewableFunc
typedef|typedef
name|GimpViewable
modifier|*
function_decl|(
modifier|*
name|GimpDndDragViewableFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpContext
modifier|*
modifier|*
name|context
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDndDropViewableFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDndDropViewableFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|gboolean
name|gimp_dnd_drag_source_set_by_type
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|start_button_mask
parameter_list|,
name|GType
name|type
parameter_list|,
name|GdkDragAction
name|actions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dnd_viewable_source_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GType
name|type
parameter_list|,
name|GimpDndDragViewableFunc
name|get_viewable_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dnd_viewable_source_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dnd_drag_dest_set_by_type
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkDestDefaults
name|flags
parameter_list|,
name|GType
name|type
parameter_list|,
name|GdkDragAction
name|actions
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dnd_viewable_dest_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GType
name|type
parameter_list|,
name|GimpDndDropViewableFunc
name|set_viewable_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dnd_viewable_dest_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpViewable
modifier|*
name|gimp_dnd_get_drag_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Direct Save Protocol (XDS)  */
end_comment

begin_function_decl
name|void
name|gimp_dnd_xds_source_add
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDndDragViewableFunc
name|get_image_func
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dnd_xds_source_remove
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DND_H__ */
end_comment

end_unit

