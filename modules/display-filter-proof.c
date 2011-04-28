begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* lcms.h uses the "inline" keyword */
end_comment

begin_include
include|#
directive|include
file|<lcms.h>
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|CDISPLAY_TYPE_PROOF
define|#
directive|define
name|CDISPLAY_TYPE_PROOF
value|(cdisplay_proof_get_type ())
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
DECL|enum|__anon2aa273350103
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
name|GType
name|cdisplay_proof_get_type
parameter_list|(
name|void
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
name|void
name|cdisplay_proof_convert_surface
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|cairo_surface_t
modifier|*
name|surface
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
name|cdisplay_proof_changed
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
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

begin_macro
DECL|function|G_DEFINE_DYNAMIC_TYPE (CdisplayProof,cdisplay_proof,GIMP_TYPE_COLOR_DISPLAY)
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|CdisplayProof
argument_list|,
argument|cdisplay_proof
argument_list|,
argument|GIMP_TYPE_COLOR_DISPLAY
argument_list|)
end_macro

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
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
name|cdisplay_proof_register_type
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
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_INTENT
argument_list|,
literal|"intent"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_COLOR_RENDERING_INTENT
argument_list|,
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_BPC
argument_list|,
literal|"black-point-compensation"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_PROFILE
argument_list|,
literal|"profile"
argument_list|,
name|NULL
argument_list|,
name|GIMP_CONFIG_PATH_FILE
argument_list|,
name|NULL
argument_list|,
literal|0
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
name|stock_id
operator|=
name|GIMP_STOCK_DISPLAY_FILTER_PROOF
expr_stmt|;
name|display_class
operator|->
name|convert_surface
operator|=
name|cdisplay_proof_convert_surface
expr_stmt|;
name|display_class
operator|->
name|configure
operator|=
name|cdisplay_proof_configure
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
DECL|function|cdisplay_proof_class_finalize (CdisplayProofClass * klass)
name|cdisplay_proof_class_finalize
parameter_list|(
name|CdisplayProofClass
modifier|*
name|klass
parameter_list|)
block|{ }
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
name|cdisplay_proof_parent_class
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
name|void
DECL|function|cdisplay_proof_convert_surface (GimpColorDisplay * display,cairo_surface_t * surface)
name|cdisplay_proof_convert_surface
parameter_list|(
name|GimpColorDisplay
modifier|*
name|display
parameter_list|,
name|cairo_surface_t
modifier|*
name|surface
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
name|width
init|=
name|cairo_image_surface_get_width
argument_list|(
name|surface
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|cairo_image_surface_get_height
argument_list|(
name|surface
argument_list|)
decl_stmt|;
name|gint
name|stride
init|=
name|cairo_image_surface_get_stride
argument_list|(
name|surface
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|buf
init|=
name|cairo_image_surface_get_data
argument_list|(
name|surface
argument_list|)
decl_stmt|;
name|cairo_format_t
name|fmt
init|=
name|cairo_image_surface_get_format
argument_list|(
name|surface
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|rowbuf
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
if|if
condition|(
name|fmt
operator|!=
name|CAIRO_FORMAT_ARGB32
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
name|rowbuf
operator|=
name|g_malloc
argument_list|(
name|stride
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
name|height
condition|;
name|y
operator|++
operator|,
name|buf
operator|+=
name|stride
control|)
block|{
comment|/* Switch buf from ARGB premul to ARGB non-premul, since lcms ignores the        * alpha channel.  The macro takes care of byte order.        */
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
name|GIMP_CAIRO_ARGB32_GET_PIXEL
argument_list|(
name|buf
operator|+
literal|4
operator|*
name|x
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|0
index|]
operator|=
name|a
expr_stmt|;
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|1
index|]
operator|=
name|r
expr_stmt|;
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|2
index|]
operator|=
name|g
expr_stmt|;
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|3
index|]
operator|=
name|b
expr_stmt|;
block|}
name|cmsDoTransform
argument_list|(
name|proof
operator|->
name|transform
argument_list|,
name|rowbuf
argument_list|,
name|rowbuf
argument_list|,
name|width
argument_list|)
expr_stmt|;
comment|/* And back to ARGB premul */
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
name|a
operator|=
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|0
index|]
expr_stmt|;
name|r
operator|=
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|1
index|]
expr_stmt|;
name|g
operator|=
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|2
index|]
expr_stmt|;
name|b
operator|=
name|rowbuf
index|[
literal|4
operator|*
name|x
operator|+
literal|3
index|]
expr_stmt|;
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|buf
operator|+
literal|4
operator|*
name|x
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|rowbuf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_combo_box_set_active (GimpColorProfileComboBox * combo,const gchar * filename)
name|cdisplay_proof_combo_box_set_active
parameter_list|(
name|GimpColorProfileComboBox
modifier|*
name|combo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|cmsHPROFILE
name|profile
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|label
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|filename
condition|)
name|profile
operator|=
name|cmsOpenProfileFromFile
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
block|{
name|label
operator|=
name|gimp_any_to_utf8
argument_list|(
name|cmsTakeProductDesc
argument_list|(
name|profile
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|label
condition|)
name|label
operator|=
name|gimp_any_to_utf8
argument_list|(
name|cmsTakeProductName
argument_list|(
name|profile
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cmsCloseProfile
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
name|gimp_color_profile_combo_box_set_active
argument_list|(
name|combo
argument_list|,
name|filename
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|cdisplay_proof_file_chooser_dialog_response (GtkFileChooser * dialog,gint response,GimpColorProfileComboBox * combo)
name|cdisplay_proof_file_chooser_dialog_response
parameter_list|(
name|GtkFileChooser
modifier|*
name|dialog
parameter_list|,
name|gint
name|response
parameter_list|,
name|GimpColorProfileComboBox
modifier|*
name|combo
parameter_list|)
block|{
if|if
condition|(
name|response
operator|==
name|GTK_RESPONSE_ACCEPT
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|gtk_file_chooser_get_filename
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|cdisplay_proof_combo_box_set_active
argument_list|(
name|combo
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|cdisplay_proof_file_chooser_dialog_new (void)
name|cdisplay_proof_file_chooser_dialog_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkFileFilter
modifier|*
name|filter
decl_stmt|;
name|dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Choose an ICC Color Profile"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_OPEN
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|GTK_RESPONSE_ACCEPT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_ACCEPT
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_ACCEPT
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
block|{
specifier|const
name|gchar
name|folder
index|[]
init|=
literal|"/usr/share/color/icc"
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|folder
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
name|gtk_file_chooser_add_shortcut_folder
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|folder
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|_
argument_list|(
literal|"All files (*.*)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|_
argument_list|(
literal|"ICC color profile (*.icc, *.icm)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*.[Ii][Cc][Cc]"
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*.[Ii][Cc][Mm]"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
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
DECL|function|cdisplay_proof_profile_changed (GtkWidget * combo,CdisplayProof * proof)
name|cdisplay_proof_profile_changed
parameter_list|(
name|GtkWidget
modifier|*
name|combo
parameter_list|,
name|CdisplayProof
modifier|*
name|proof
parameter_list|)
block|{
name|gchar
modifier|*
name|profile
decl_stmt|;
name|profile
operator|=
name|gimp_color_profile_combo_box_get_active
argument_list|(
name|GIMP_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|proof
argument_list|,
literal|"profile"
argument_list|,
name|profile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|profile
argument_list|)
expr_stmt|;
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
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gchar
modifier|*
name|history
decl_stmt|;
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
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|cdisplay_proof_file_chooser_dialog_new
argument_list|()
expr_stmt|;
name|history
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"profilerc"
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_color_profile_combo_box_new
argument_list|(
name|dialog
argument_list|,
name|history
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|history
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
name|cdisplay_proof_file_chooser_dialog_response
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|cdisplay_proof_profile_changed
argument_list|)
argument_list|,
name|proof
argument_list|)
expr_stmt|;
if|if
condition|(
name|proof
operator|->
name|profile
condition|)
name|cdisplay_proof_combo_box_set_active
argument_list|(
name|GIMP_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|proof
operator|->
name|profile
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
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
name|combo
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|proof
argument_list|)
argument_list|,
literal|"intent"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
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
name|combo
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|proof
argument_list|)
argument_list|,
literal|"black-point-compensation"
argument_list|,
name|_
argument_list|(
literal|"_Black Point Compensation"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
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
name|toggle
argument_list|)
expr_stmt|;
return|return
name|table
return|;
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
name|DWORD
name|flags
init|=
name|cmsFLAGS_SOFTPROOFING
decl_stmt|;
if|if
condition|(
name|proof
operator|->
name|bpc
condition|)
name|flags
operator||=
name|cmsFLAGS_BLACKPOINTCOMPENSATION
expr_stmt|;
name|proof
operator|->
name|transform
operator|=
name|cmsCreateProofingTransform
argument_list|(
name|rgbProfile
argument_list|,
name|TYPE_ARGB_8
argument_list|,
name|rgbProfile
argument_list|,
name|TYPE_ARGB_8
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
name|flags
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

end_unit

