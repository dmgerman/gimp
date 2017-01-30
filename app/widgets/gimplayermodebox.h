begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimplayermodebox.h  * Copyright (C) 2017  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_MODE_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_MODE_BOX_H__
define|#
directive|define
name|__GIMP_LAYER_MODE_BOX_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_LAYER_MODE_BOX
define|#
directive|define
name|GIMP_TYPE_LAYER_MODE_BOX
value|(gimp_layer_mode_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_LAYER_MODE_BOX (obj)
define|#
directive|define
name|GIMP_LAYER_MODE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LAYER_MODE_BOX, GimpLayerModeBox))
end_define

begin_define
DECL|macro|GIMP_LAYER_MODE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_LAYER_MODE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LAYER_MODE_BOX, GimpLayerModeBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_MODE_BOX (obj)
define|#
directive|define
name|GIMP_IS_LAYER_MODE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LAYER_MODE_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_LAYER_MODE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LAYER_MODE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LAYER_MODE_BOX))
end_define

begin_define
DECL|macro|GIMP_LAYER_MODE_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LAYER_MODE_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LAYER_MODE_BOX, GimpLayerModeBoxClass))
end_define

begin_typedef
DECL|typedef|GimpLayerModeBoxPrivate
typedef|typedef
name|struct
name|_GimpLayerModeBoxPrivate
name|GimpLayerModeBoxPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerModeBoxClass
typedef|typedef
name|struct
name|_GimpLayerModeBoxClass
name|GimpLayerModeBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLayerModeBox
struct|struct
name|_GimpLayerModeBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpLayerModeBoxPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerModeBoxClass
struct|struct
name|_GimpLayerModeBoxClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_layer_mode_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_layer_mode_box_new
parameter_list|(
name|gboolean
name|with_behind
parameter_list|,
name|gboolean
name|with_replace
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_mode_box_set_mode
parameter_list|(
name|GimpLayerModeBox
modifier|*
name|box
parameter_list|,
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMode
name|gimp_layer_mode_box_get_mode
parameter_list|(
name|GimpLayerModeBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_mode_box_set_label
parameter_list|(
name|GimpLayerModeBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_layer_mode_box_set_ellipsize
parameter_list|(
name|GimpLayerModeBox
modifier|*
name|box
parameter_list|,
name|PangoEllipsizeMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_MODE_BOX_H__ */
end_comment

end_unit

