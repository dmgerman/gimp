begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LCMS_LCMS_H
end_ifdef

begin_include
include|#
directive|include
file|<lcms/lcms.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<lcms.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|CDISPLAY_TYPE_PROOF_INTENT
define|#
directive|define
name|CDISPLAY_TYPE_PROOF_INTENT
value|(cdisplay_proof_intent_type)
end_define

begin_function_decl
specifier|static
name|GType
name|cdisplay_proof_intent_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|enum_values
specifier|static
specifier|const
name|GEnumValue
name|enum_values
index|[]
init|=
block|{
block|{
name|INTENT_PERCEPTUAL
block|,
literal|"INTENT_PERCEPTUAL"
block|,
literal|"perceptual    "
block|}
block|,
block|{
name|INTENT_RELATIVE_COLORIMETRIC
block|,
literal|"INTENT_RELATIVE_COLORIMETRIC"
block|,
literal|"relative-colorimetric"
block|}
block|,
block|{
name|INTENT_SATURATION
block|,
literal|"INTENT_SATURATION"
block|,
literal|"saturation"
block|}
block|,
block|{
name|INTENT_ABSOLUTE_COLORIMETRIC
block|,
literal|"INTENT_ABSOLUTE_COLORIMETRIC"
literal|"absolute-colorimetric"
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
end_decl_stmt

begin_decl_stmt
DECL|variable|enum_descs
specifier|static
specifier|const
name|GimpEnumDesc
name|enum_descs
index|[]
init|=
block|{
block|{
name|INTENT_PERCEPTUAL
block|,
name|N_
argument_list|(
literal|"Perceptual"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|INTENT_RELATIVE_COLORIMETRIC
block|,
name|N_
argument_list|(
literal|"Relative Colorimetric"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|INTENT_SATURATION
block|,
name|N_
argument_list|(
literal|"Saturation"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|INTENT_ABSOLUTE_COLORIMETRIC
block|,
name|N_
argument_list|(
literal|"Absolute Colorimetric"
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
end_decl_stmt

begin_define
DECL|macro|CDISPLAY_TYPE_PROOF
define|#
directive|define
name|CDISPLAY_TYPE_PROOF
value|(cdisplay_proof_type)
end_define

begin_define
DECL|macro|CDISPLAY_PROOF (obj)
define|#
directive|define
name|CDISPLAY_PROOF
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), CDISPLAY_TYPE_PROOF, CdisplayProof))
end_define

begin_define
DECL|macro|CDISPLAY_PROOF_CLASS (klass)
define|#
directive|define
name|CDISPLAY_PROOF_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), CDISPLAY_TYPE_PROOF, CdisplayProofClass))
end_define

begin_define
DECL|macro|CDISPLAY_IS_PROOF (obj)
define|#
directive|define
name|CDISPLAY_IS_PROOF
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CDISPLAY_TYPE_PROOF))
end_define

begin_define
DECL|macro|CDISPLAY_IS_PROOF_CLASS (klass)
define|#
directive|define
name|CDISPLAY_IS_PROOF_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), CDISPLAY_TYPE_PROOF))
end_define

begin_typedef
DECL|typedef|CdisplayProof
typedef|typedef
name|struct
name|_CdisplayProof
name|CdisplayProof
typedef|;
end_typedef

begin_typedef
DECL|typedef|CdisplayProofClass
typedef|typedef
name|struct
name|_CdisplayProofClass
name|CdisplayProofClass
typedef|;
end_typedef

begin_struct
DECL|struct|_CdisplayProof
struct|struct
name|_CdisplayProof
block|{
DECL|member|parent_instance
name|GimpColorDisplay
name|parent_instance
decl_stmt|;
DECL|member|intent
name|gint
name|intent
decl_stmt|;
DECL|member|bpc
name|gboolean
name|bpc
decl_stmt|;
DECL|member|profile
name|gchar
modifier|*
name|profile
decl_stmt|;
DECL|member|transform
name|cmsHTRANSFORM
name|transform
decl_stmt|;
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|combo
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
DECL|member|toggle
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_CdisplayProofClass
struct|struct
name|_CdisplayProofClass
block|{
DECL|member|parent_instance
name|GimpColorDisplayClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_enum
enum|enum
DECL|enum|__anon27fea97e0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_INTENT
name|PROP_INTENT
block|,
DECL|enumerator|PROP_BPC
name|PROP_BPC
block|,
DECL|enumerator|PROP_PROFILE
name|PROP_PROFILE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GType
name|cdisplay_proof_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_class_init
parameter_list|(
name|CdisplayProofClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_init
parameter_list|(
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpColorDisplay
modifier|*
name|cdisplay_proof_clone
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_convert
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_load_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpParasite
modifier|*
name|cdisplay_proof_save_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|cdisplay_proof_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_configure_reset
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|cdisplay_proof_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|proof_intent_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|proof_bpc_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|proof_file_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|cdisplay_proof_info
specifier|static
specifier|const
name|GimpModuleInfo
name|cdisplay_proof_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"Color proof filter using ICC color profile"
argument_list|)
block|,
literal|"Banlu Kemiyatorn<id@project-ile.net>"
block|,
literal|"v0.1"
block|,
literal|"(c) 2002-2003, released under the GPL"
block|,
literal|"November 14, 2003"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cdisplay_proof_type
specifier|static
name|GType
name|cdisplay_proof_type
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cdisplay_proof_intent_type
specifier|static
name|GType
name|cdisplay_proof_intent_type
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorDisplayClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
DECL|function|gimp_module_query (GTypeModule * module)
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|cdisplay_proof_info
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|gboolean
DECL|function|gimp_module_register (GTypeModule * module)
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|cdisplay_proof_get_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
name|cdisplay_proof_intent_get_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|cdisplay_proof_get_type (GTypeModule * module)
name|cdisplay_proof_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
if|if
condition|(
operator|!
name|cdisplay_proof_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|display_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|CdisplayProofClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|cdisplay_proof_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|CdisplayProof
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|cdisplay_proof_init
block|,       }
decl_stmt|;
name|cdisplay_proof_type
operator|=
name|g_type_module_register_type
argument_list|(
name|module
argument_list|,
name|GIMP_TYPE_COLOR_DISPLAY
argument_list|,
literal|"CdisplayProof"
argument_list|,
operator|&
name|display_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|cdisplay_proof_type
return|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|cdisplay_proof_intent_get_type (GTypeModule * module)
name|cdisplay_proof_intent_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
if|if
condition|(
operator|!
name|cdisplay_proof_intent_type
condition|)
block|{
name|cdisplay_proof_intent_type
operator|=
name|gimp_module_register_enum
argument_list|(
name|module
argument_list|,
literal|"CDisplayProofIntent"
argument_list|,
name|enum_values
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|cdisplay_proof_intent_type
argument_list|,
name|enum_descs
argument_list|)
expr_stmt|;
block|}
return|return
name|cdisplay_proof_intent_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_class_init (CdisplayProofClass * klass)
name|cdisplay_proof_class_init
parameter_list|(
name|CdisplayProofClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpColorDisplayClass
modifier|*
name|display_class
init|=
name|GIMP_COLOR_DISPLAY_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|cdisplay_proof_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|cdisplay_proof_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|cdisplay_proof_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|cdisplay_proof_set_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_INTENT
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"intent"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|CDISPLAY_TYPE_PROOF_INTENT
argument_list|,
name|INTENT_PERCEPTUAL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
operator||
name|GIMP_MODULE_PARAM_SERIALIZE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BPC
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"black-point-compensation"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
operator||
name|GIMP_MODULE_PARAM_SERIALIZE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PROFILE
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"profile"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
operator||
name|GIMP_MODULE_PARAM_SERIALIZE
argument_list|)
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Color Proof"
argument_list|)
expr_stmt|;
name|display_class
operator|->
name|help_id
operator|=
literal|"gimp-colordisplay-proof"
expr_stmt|;
name|display_class
operator|->
name|clone
operator|=
name|cdisplay_proof_clone
expr_stmt|;
name|display_class
operator|->
name|convert
operator|=
name|cdisplay_proof_convert
expr_stmt|;
name|display_class
operator|->
name|load_state
operator|=
name|cdisplay_proof_load_state
expr_stmt|;
name|display_class
operator|->
name|save_state
operator|=
name|cdisplay_proof_save_state
expr_stmt|;
name|display_class
operator|->
name|configure
operator|=
name|cdisplay_proof_configure
expr_stmt|;
name|display_class
operator|->
name|configure_reset
operator|=
name|cdisplay_proof_configure_reset
expr_stmt|;
name|display_class
operator|->
name|changed
operator|=
name|cdisplay_proof_changed
expr_stmt|;
name|cmsErrorAction
argument_list|(
name|LCMS_ERROR_IGNORE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_init (CdisplayProof * proof)
name|cdisplay_proof_init
parameter_list|(
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
block|{
name|proof
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
name|proof
operator|->
name|profile
operator|=
name|NULL
expr_stmt|;
name|proof
operator|->
name|table
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_dispose (GObject * object)
name|cdisplay_proof_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|proof
operator|->
name|table
condition|)
name|gtk_widget_destroy
argument_list|(
name|proof
operator|->
name|table
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_finalize (GObject * object)
name|cdisplay_proof_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|proof
operator|->
name|profile
condition|)
block|{
name|g_free
argument_list|(
name|proof
operator|->
name|profile
argument_list|)
expr_stmt|;
name|proof
operator|->
name|profile
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|proof
operator|->
name|transform
condition|)
block|{
name|cmsDeleteTransform
argument_list|(
name|proof
operator|->
name|transform
argument_list|)
expr_stmt|;
name|proof
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|cdisplay_proof_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_INTENT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|proof
operator|->
name|intent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BPC
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|proof
operator|->
name|bpc
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PROFILE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|proof
operator|->
name|profile
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|cdisplay_proof_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_INTENT
case|:
name|proof
operator|->
name|intent
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BPC
case|:
name|proof
operator|->
name|bpc
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PROFILE
case|:
name|g_free
argument_list|(
name|proof
operator|->
name|profile
argument_list|)
expr_stmt|;
name|proof
operator|->
name|profile
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_color_display_changed
argument_list|(
name|GIMP_COLOR_DISPLAY
argument_list|(
name|proof
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpColorDisplay
modifier|*
DECL|function|cdisplay_proof_clone (GimpColorDisplay * display)
name|cdisplay_proof_clone
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|CdisplayProof
modifier|*
name|copy
decl_stmt|;
name|copy
operator|=
name|CDISPLAY_PROOF
argument_list|(
name|gimp_color_display_new
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|proof
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|copy
operator|->
name|intent
operator|=
name|proof
operator|->
name|intent
expr_stmt|;
name|copy
operator|->
name|bpc
operator|=
name|proof
operator|->
name|bpc
expr_stmt|;
name|copy
operator|->
name|profile
operator|=
name|g_strdup
argument_list|(
name|proof
operator|->
name|profile
argument_list|)
expr_stmt|;
return|return
name|GIMP_COLOR_DISPLAY
argument_list|(
name|copy
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_convert (GimpColorDisplay * display,guchar * buf,gint width,gint height,gint bpp,gint bpl)
name|cdisplay_proof_convert
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
name|bpl
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gint
name|y
decl_stmt|;
if|if
condition|(
name|bpp
operator|!=
literal|3
condition|)
return|return;
if|if
condition|(
operator|!
name|proof
operator|->
name|transform
condition|)
return|return;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
operator|,
name|buf
operator|+=
name|bpl
control|)
name|cmsDoTransform
argument_list|(
name|proof
operator|->
name|transform
argument_list|,
name|buf
argument_list|,
name|buf
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_load_state (GimpColorDisplay * display,GimpParasite * state)
name|cdisplay_proof_load_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|GimpParasite
modifier|*
name|state
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|display
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|str
operator|=
name|gimp_parasite_data
argument_list|(
name|state
argument_list|)
expr_stmt|;
if|if
condition|(
name|str
index|[
name|gimp_parasite_data_size
argument_list|(
name|state
argument_list|)
operator|-
literal|1
index|]
operator|==
literal|'\0'
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|tokens
init|=
name|g_strsplit
argument_list|(
name|str
argument_list|,
literal|","
argument_list|,
literal|3
argument_list|)
decl_stmt|;
if|if
condition|(
name|tokens
index|[
literal|0
index|]
operator|&&
name|tokens
index|[
literal|1
index|]
operator|&&
name|tokens
index|[
literal|2
index|]
condition|)
block|{
name|g_object_set
argument_list|(
name|proof
argument_list|,
literal|"intent"
argument_list|,
name|atoi
argument_list|(
name|tokens
index|[
literal|0
index|]
argument_list|)
argument_list|,
literal|"black-point-compensation"
argument_list|,
name|atoi
argument_list|(
name|tokens
index|[
literal|1
index|]
argument_list|)
argument_list|,
literal|"profile"
argument_list|,
name|tokens
index|[
literal|2
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|tokens
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpParasite
modifier|*
DECL|function|cdisplay_proof_save_state (GimpColorDisplay * display)
name|cdisplay_proof_save_state
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpParasite
modifier|*
name|state
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d,%d,%s"
argument_list|,
name|proof
operator|->
name|intent
argument_list|,
name|proof
operator|->
name|bpc
argument_list|,
name|proof
operator|->
name|profile
condition|?
name|proof
operator|->
name|profile
else|:
literal|""
argument_list|)
expr_stmt|;
name|state
operator|=
name|gimp_parasite_new
argument_list|(
literal|"Display/Proof"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|state
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|cdisplay_proof_configure (GimpColorDisplay * display)
name|cdisplay_proof_configure
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
if|if
condition|(
name|proof
operator|->
name|table
condition|)
name|gtk_widget_destroy
argument_list|(
name|proof
operator|->
name|table
argument_list|)
expr_stmt|;
name|proof
operator|->
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|proof
operator|->
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|proof
operator|->
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|proof
operator|->
name|table
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|proof
operator|->
name|table
argument_list|)
expr_stmt|;
name|proof
operator|->
name|combo
operator|=
name|gimp_enum_combo_box_new
argument_list|(
name|CDISPLAY_TYPE_PROOF_INTENT
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|proof
operator|->
name|combo
argument_list|)
argument_list|,
name|proof
operator|->
name|intent
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|proof
operator|->
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|proof_intent_callback
argument_list|)
argument_list|,
name|proof
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|proof
operator|->
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Intent:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|proof
operator|->
name|combo
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_file_entry_new
argument_list|(
name|_
argument_list|(
literal|"Choose an ICC Color Profile"
argument_list|)
argument_list|,
name|proof
operator|->
name|profile
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|proof
operator|->
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Profile:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|entry
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
argument_list|,
literal|"filename-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|proof_file_callback
argument_list|)
argument_list|,
name|proof
argument_list|)
expr_stmt|;
name|proof
operator|->
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Black Point Compensation"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|proof
operator|->
name|toggle
argument_list|)
argument_list|,
name|proof
operator|->
name|bpc
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|proof
operator|->
name|table
argument_list|)
argument_list|,
name|proof
operator|->
name|toggle
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|proof
operator|->
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|proof
operator|->
name|toggle
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|proof_bpc_callback
argument_list|)
argument_list|,
name|proof
argument_list|)
expr_stmt|;
return|return
name|proof
operator|->
name|table
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_configure_reset (GimpColorDisplay * display)
name|cdisplay_proof_configure_reset
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|proof
argument_list|,
literal|"intent"
argument_list|,
name|INTENT_PERCEPTUAL
argument_list|,
literal|"black-point-compensation"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|proof
operator|->
name|table
condition|)
block|{
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|proof
operator|->
name|combo
argument_list|)
argument_list|,
name|proof
operator|->
name|intent
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|proof
operator|->
name|toggle
argument_list|)
argument_list|,
name|proof
operator|->
name|bpc
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_changed (GimpColorDisplay * display)
name|cdisplay_proof_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|)
block|{
name|CdisplayProof
modifier|*
name|proof
init|=
name|CDISPLAY_PROOF
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|cmsHPROFILE
name|rgbProfile
decl_stmt|;
name|cmsHPROFILE
name|proofProfile
decl_stmt|;
if|if
condition|(
name|proof
operator|->
name|transform
condition|)
block|{
name|cmsDeleteTransform
argument_list|(
name|proof
operator|->
name|transform
argument_list|)
expr_stmt|;
name|proof
operator|->
name|transform
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|proof
operator|->
name|profile
condition|)
return|return;
comment|/*  This should be read from the global parasite pool.    *  For now, just use the built-in sRGB profile.    */
name|rgbProfile
operator|=
name|cmsCreate_sRGBProfile
argument_list|()
expr_stmt|;
name|proofProfile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|proof
operator|->
name|profile
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|proofProfile
condition|)
block|{
name|proof
operator|->
name|transform
operator|=
name|cmsCreateProofingTransform
argument_list|(
name|rgbProfile
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|rgbProfile
argument_list|,
name|TYPE_RGB_8
argument_list|,
name|proofProfile
argument_list|,
name|proof
operator|->
name|intent
argument_list|,
name|proof
operator|->
name|intent
argument_list|,
name|cmsFLAGS_SOFTPROOFING
operator||
operator|(
name|proof
operator|->
name|bpc
condition|?
name|cmsFLAGS_WHITEBLACKCOMPENSATION
else|:
literal|0
operator|)
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|proofProfile
argument_list|)
expr_stmt|;
block|}
name|cmsCloseProfile
argument_list|(
name|rgbProfile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|proof_intent_callback (GtkWidget * widget,CdisplayProof * proof)
name|proof_intent_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
block|{
name|gint
name|value
decl_stmt|;
name|gimp_int_combo_box_get_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|proof
argument_list|,
literal|"intent"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|proof_bpc_callback (GtkWidget * widget,CdisplayProof * proof)
name|proof_bpc_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
block|{
name|gboolean
name|value
decl_stmt|;
name|gimp_toggle_button_update
argument_list|(
name|widget
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|proof
argument_list|,
literal|"black-point-compensation"
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|proof_file_callback (GtkWidget * widget,CdisplayProof * proof)
name|proof_file_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|gimp_file_entry_get_filename
argument_list|(
name|GIMP_FILE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|proof
argument_list|,
literal|"profile"
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

