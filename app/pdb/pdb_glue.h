begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PDB_GLUE_H__
end_ifndef

begin_define
DECL|macro|__PDB_GLUE_H__
define|#
directive|define
name|__PDB_GLUE_H__
end_define

begin_define
DECL|macro|gimp_drawable_layer
define|#
directive|define
name|gimp_drawable_layer
value|GIMP_IS_LAYER
end_define

begin_define
DECL|macro|gimp_drawable_layer_mask
define|#
directive|define
name|gimp_drawable_layer_mask
value|GIMP_IS_LAYER_MASK
end_define

begin_define
DECL|macro|gimp_drawable_channel
define|#
directive|define
name|gimp_drawable_channel
value|GIMP_IS_CHANNEL
end_define

begin_define
DECL|macro|gimp_layer_set_name (l,n)
define|#
directive|define
name|gimp_layer_set_name
parameter_list|(
name|l
parameter_list|,
name|n
parameter_list|)
value|gimp_object_set_name(GIMP_OBJECT(l),(n))
end_define

begin_define
DECL|macro|gimp_layer_get_name (l)
define|#
directive|define
name|gimp_layer_get_name
parameter_list|(
name|l
parameter_list|)
value|gimp_object_get_name(GIMP_OBJECT(l))
end_define

begin_define
DECL|macro|gimp_layer_get_visible (l)
define|#
directive|define
name|gimp_layer_get_visible
parameter_list|(
name|l
parameter_list|)
value|gimp_drawable_get_visible(GIMP_DRAWABLE(l))
end_define

begin_define
DECL|macro|gimp_layer_set_visible (l,v)
define|#
directive|define
name|gimp_layer_set_visible
parameter_list|(
name|l
parameter_list|,
name|v
parameter_list|)
value|gimp_drawable_set_visible(GIMP_DRAWABLE(l),(v))
end_define

begin_define
DECL|macro|gimp_layer_set_tattoo (l,t)
define|#
directive|define
name|gimp_layer_set_tattoo
parameter_list|(
name|l
parameter_list|,
name|t
parameter_list|)
value|gimp_drawable_set_tattoo(GIMP_DRAWABLE(l),(t))
end_define

begin_define
DECL|macro|gimp_layer_get_tattoo (l)
define|#
directive|define
name|gimp_layer_get_tattoo
parameter_list|(
name|l
parameter_list|)
value|gimp_drawable_get_tattoo(GIMP_DRAWABLE(l))
end_define

begin_define
DECL|macro|gimp_channel_set_name (c,n)
define|#
directive|define
name|gimp_channel_set_name
parameter_list|(
name|c
parameter_list|,
name|n
parameter_list|)
value|gimp_object_set_name(GIMP_OBJECT(c),(n))
end_define

begin_define
DECL|macro|gimp_channel_get_name (c)
define|#
directive|define
name|gimp_channel_get_name
parameter_list|(
name|c
parameter_list|)
value|gimp_object_get_name(GIMP_OBJECT(c))
end_define

begin_define
DECL|macro|gimp_channel_get_visible (c)
define|#
directive|define
name|gimp_channel_get_visible
parameter_list|(
name|c
parameter_list|)
value|gimp_drawable_get_visible(GIMP_DRAWABLE(c))
end_define

begin_define
DECL|macro|gimp_channel_set_visible (c,v)
define|#
directive|define
name|gimp_channel_set_visible
parameter_list|(
name|c
parameter_list|,
name|v
parameter_list|)
value|gimp_drawable_set_visible(GIMP_DRAWABLE(c),(v))
end_define

begin_define
DECL|macro|gimp_channel_set_tattoo (c,t)
define|#
directive|define
name|gimp_channel_set_tattoo
parameter_list|(
name|c
parameter_list|,
name|t
parameter_list|)
value|gimp_drawable_set_tattoo(GIMP_DRAWABLE(c),(t))
end_define

begin_define
DECL|macro|gimp_channel_get_tattoo (c)
define|#
directive|define
name|gimp_channel_get_tattoo
parameter_list|(
name|c
parameter_list|)
value|gimp_drawable_get_tattoo(GIMP_DRAWABLE(c))
end_define

begin_define
DECL|macro|gimp_layer_get_apply_mask (l)
define|#
directive|define
name|gimp_layer_get_apply_mask
parameter_list|(
name|l
parameter_list|)
value|(l)->mask ? gimp_layer_mask_get_apply((l)->mask) : FALSE;
end_define

begin_define
DECL|macro|gimp_layer_get_show_mask (l)
define|#
directive|define
name|gimp_layer_get_show_mask
parameter_list|(
name|l
parameter_list|)
value|(l)->mask ? gimp_layer_mask_get_show((l)->mask) : FALSE;
end_define

begin_define
DECL|macro|gimp_layer_get_edit_mask (l)
define|#
directive|define
name|gimp_layer_get_edit_mask
parameter_list|(
name|l
parameter_list|)
value|(l)->mask ? gimp_layer_mask_get_edit((l)->mask) : FALSE;
end_define

begin_define
DECL|macro|gimp_layer_set_apply_mask (l,a)
define|#
directive|define
name|gimp_layer_set_apply_mask
parameter_list|(
name|l
parameter_list|,
name|a
parameter_list|)
value|{ if((l)->mask) gimp_layer_mask_set_apply((l)->mask,(a)); else success = FALSE; }
end_define

begin_define
DECL|macro|gimp_layer_set_show_mask (l,s)
define|#
directive|define
name|gimp_layer_set_show_mask
parameter_list|(
name|l
parameter_list|,
name|s
parameter_list|)
value|{ if((l)->mask) gimp_layer_mask_set_show((l)->mask,(s)); else success = FALSE; }
end_define

begin_define
DECL|macro|gimp_layer_set_edit_mask (l,e)
define|#
directive|define
name|gimp_layer_set_edit_mask
parameter_list|(
name|l
parameter_list|,
name|e
parameter_list|)
value|{ if((l)->mask) gimp_layer_mask_set_edit((l)->mask,(e)); else success = FALSE; }
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PDB_GLUE_H__ */
end_comment

end_unit

