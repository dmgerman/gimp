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
value|{ if((l)->mask) gimp_layer_mask_set_apply((l)->mask,(a),TRUE); else success = FALSE; }
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
value|{ if((l)->mask) gimp_layer_mask_set_show((l)->mask,(s),TRUE); else success = FALSE; }
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

