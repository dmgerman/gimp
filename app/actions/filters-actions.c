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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"filters-actions.h"
end_include

begin_include
include|#
directive|include
file|"filters-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|filters_actions
specifier|static
specifier|const
name|GimpStringActionEntry
name|filters_actions
index|[]
init|=
block|{
block|{
literal|"filters-c2g"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Color to Gray..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Color to grayscale conversion"
argument_list|)
block|,
literal|"gegl:c2g"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_C2G */
block|}
block|,
block|{
literal|"filters-cartoon"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Ca_rtoon..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Simulate a cartoon by enhancing edges"
argument_list|)
block|,
literal|"gegl:cartoon"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_CARTOON */
block|}
block|,
block|{
literal|"filters-checkerboard"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Checkerboard..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Create a checkerboard pattern"
argument_list|)
block|,
literal|"gegl:checkerboard"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_CHECKERBOARD */
block|}
block|,
block|{
literal|"filters-color-reduction"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Color _Reduction..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Reduce the number of colors in the image, with optional dithering"
argument_list|)
block|,
literal|"gegl:color-reduction"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_COLOR_TEMPERATURE */
block|}
block|,
block|{
literal|"filters-color-temperature"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Color T_emperature..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Change the color temperature of the image"
argument_list|)
block|,
literal|"gegl:color-temperature"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_COLOR_TEMPERATURE */
block|}
block|,
block|{
literal|"filters-color-to-alpha"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Color to _Alpha..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Convert a specified color to transparency"
argument_list|)
block|,
literal|"gegl:color-to-alpha"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_COLOR_TO_ALPHA */
block|}
block|,
block|{
literal|"filters-cubism"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Cubism..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Convert the image into randomly rotated square blobs, somehow resembling a cubist painting style"
argument_list|)
block|,
literal|"gegl:cubism"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_CUBISM */
block|}
block|,
block|{
literal|"filters-difference-of-gaussians"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Difference of Gaussians..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Edge detection with control of edge thickness"
argument_list|)
block|,
literal|"gegl:difference-of-gaussians"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_DIFFERENCE_OF_GAUSSIANS */
block|}
block|,
block|{
literal|"filters-dot"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Dots..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Simplify image into an array of solid-colored dots"
argument_list|)
block|,
literal|"gegl:dot"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_DOT */
block|}
block|,
block|{
literal|"filters-emboss"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Emboss..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Simulate an image created by embossing"
argument_list|)
block|,
literal|"gegl:emboss"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_EMBOSS */
block|}
block|,
block|{
literal|"filters-exposure"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_E_xposure..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Changes Exposure and Contrast, mainly for use with high dynamic range images"
argument_list|)
block|,
literal|"gegl:exposure"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_EXPOSURE */
block|}
block|,
block|{
literal|"filters-gaussian-blur"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Gaussian Blur..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Apply a gaussian blur"
argument_list|)
block|,
literal|"gegl:gaussian-blur"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_GAUSSIAN_BLUR */
block|}
block|,
block|{
literal|"filters-laplace"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Laplace"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"High-resolution edge detection"
argument_list|)
block|,
literal|"gegl:edge-laplace"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_LAPLACE */
block|}
block|,
block|{
literal|"filters-lens-distortion"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Lens Distortion..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Corrects lens distortion"
argument_list|)
block|,
literal|"gegl:lens-distortion"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_LENS_DISTORTION */
block|}
block|,
block|{
literal|"filters-mono-mixer"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Mono Mixer..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Monochrome channel mixer"
argument_list|)
block|,
literal|"gegl:mono-mixer"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_MONO_MIXER */
block|}
block|,
block|{
literal|"filters-noise-cie-lch"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"CIE lch Noise..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Randomize lightness, chroma and hue independently"
argument_list|)
block|,
literal|"gegl:noise-CIE_lch"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_NOISE_CIE_LCH */
block|}
block|,
block|{
literal|"filters-noise-hsv"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"HSV Noise..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Scattering pixel values in HSV space"
argument_list|)
block|,
literal|"gegl:noise-hsv"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_NOISE_HSV */
block|}
block|,
block|{
literal|"filters-noise-hurl"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Hurl..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Completely randomize a fraction of pixels"
argument_list|)
block|,
literal|"gegl:noise-hurl"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_NOISE_HURL */
block|}
block|,
block|{
literal|"filters-noise-pick"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Pick..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Randomly interchange some pixels with neighbors"
argument_list|)
block|,
literal|"gegl:noise-pick"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_NOISE_PICK */
block|}
block|,
block|{
literal|"filters-noise-rgb"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_RGB Noise..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Distort colors by random amounts"
argument_list|)
block|,
literal|"gegl:noise-rgb"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_NOISE_RGB */
block|}
block|,
block|{
literal|"filters-noise-slur"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Slur..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Randomly slide some pixels downward (similar to melting)"
argument_list|)
block|,
literal|"gegl:noise-slur"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_NOISE_SLUR */
block|}
block|,
block|{
literal|"filters-photocopy"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Photocopy..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Simulate color distortion produced by a copy machine"
argument_list|)
block|,
literal|"gegl:photocopy"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_PHOTOCOPY */
block|}
block|,
block|{
literal|"filters-pixelize"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Pixelize..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Simplify image into an array of solid-colored squares"
argument_list|)
block|,
literal|"gegl:pixelize"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_PIXELIZE */
block|}
block|,
block|{
literal|"filters-polar-coordinates"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"P_olar Coordinates..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Convert image to or from polar coordinates"
argument_list|)
block|,
literal|"gegl:polar-coordinates"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_POLAR_COORDINATES */
block|}
block|,
block|{
literal|"filters-red-eye-removal"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Red Eye Removal..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Remove the red eye effect caused by camera flashes"
argument_list|)
block|,
literal|"gegl:red-eye-removal"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_RED_EYE_REMOVAL */
block|}
block|,
block|{
literal|"filters-ripple"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Ripple..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Displace pixels in a ripple pattern"
argument_list|)
block|,
literal|"gegl:ripple"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_RIPPLE */
block|}
block|,
block|{
literal|"filters-semi-flatten"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Semi-Flatten..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Replace partial transparency with a color"
argument_list|)
block|,
literal|"gimp:semi-flatten"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_POLAR_COORDINATES */
block|}
block|,
block|{
literal|"filters-sobel"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Sobel..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Specialized direction-dependent edge-detection"
argument_list|)
block|,
literal|"gegl:edge-sobel"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_SOBEL */
block|}
block|,
block|{
literal|"filters-softglow"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Softglow..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Simulate glow by making highlights intense and fuzzy"
argument_list|)
block|,
literal|"gegl:softglow"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_SOFTGLOW */
block|}
block|,
block|{
literal|"filters-threshold-alpha"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Threshold Alpha..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Make transparency all-or-nothing"
argument_list|)
block|,
literal|"gimp:threshold-alpha"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_POLAR_COORDINATES */
block|}
block|,
block|{
literal|"filters-unsharp-mask"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Unsharp Mask..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"The most widely used method for sharpening an image"
argument_list|)
block|,
literal|"gegl:unsharp-mask"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_UNSHARP_MASK */
block|}
block|,
block|{
literal|"filters-vignette"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"_Vignette..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Applies a vignette to an image"
argument_list|)
block|,
literal|"gegl:vignette"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_VIGNETTE */
block|}
block|,
block|{
literal|"filters-whirl-pinch"
block|,
name|GIMP_STOCK_GEGL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"W_hirl and Pinch..."
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"filters-action"
argument_list|,
literal|"Distort an image by whirling and pinching"
argument_list|)
block|,
literal|"gegl:whirl-pinch"
block|,
name|NULL
comment|/* FIXME GIMP_HELP_FILTER_WHIRL_PINCH */
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|filters_actions_setup (GimpActionGroup * group)
name|filters_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
literal|"filters-action"
argument_list|,
name|filters_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|filters_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|filters_filter_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|filters_actions_update (GimpActionGroup * group,gpointer data)
name|filters_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|gboolean
name|writable
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|gray
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|alpha
init|=
name|FALSE
decl_stmt|;
name|image
operator|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gray
operator|=
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|writable
operator|=
operator|!
name|gimp_item_is_content_locked
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|writable
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"filters-c2g"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-cartoon"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-checkerboard"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-color-reduction"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-color-temperature"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-color-to-alpha"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
operator|&&
name|alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-cubism"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-difference-of-gaussians"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-dot"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-emboss"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-exposure"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-gaussian-blur"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-laplace"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-mono-mixer"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-noise-cie-lch"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-noise-hsv"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-noise-hurl"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-noise-pick"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-noise-rgb"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-noise-slur"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-lens-distortion"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-photocopy"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-pixelize"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-polar-coordinates"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-red-eye-removal"
argument_list|,
name|writable
operator|&&
operator|!
name|gray
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-ripple"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-sobel"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-softglow"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-semi-flatten"
argument_list|,
name|writable
operator|&&
name|alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-threshold-alpha"
argument_list|,
name|writable
operator|&&
name|alpha
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-unsharp-mask"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-vignette"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"filters-whirl-pinch"
argument_list|,
name|writable
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

