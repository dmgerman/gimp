begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  *  Goat exercise plug-in by Ãyvind KolÃ¥s, pippin@gimp.org  */
end_comment

begin_comment
comment|/*  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_define
DECL|macro|GIMP_DISABLE_COMPAR_CRUFT
define|#
directive|define
name|GIMP_DISABLE_COMPAR_CRUFT
end_define

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
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-goat-exercise"
end_define

begin_typedef
DECL|typedef|Goat
typedef|typedef
name|struct
name|_Goat
name|Goat
typedef|;
end_typedef

begin_typedef
DECL|typedef|GoatClass
typedef|typedef
name|struct
name|_GoatClass
name|GoatClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Goat
struct|struct
name|_Goat
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GoatClass
struct|struct
name|_GoatClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Declare local functions.  */
end_comment

begin_define
DECL|macro|GOAT_TYPE
define|#
directive|define
name|GOAT_TYPE
value|(goat_get_type ())
end_define

begin_define
DECL|macro|GOAT
define|#
directive|define
name|GOAT
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GOAT_TYPE, Goat))
end_define

begin_decl_stmt
name|GType
name|goat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|gchar
modifier|*
modifier|*
name|goat_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|goat_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|goat_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (Goat,goat,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Goat
argument_list|,
argument|goat
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|GOAT_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|goat_class_init
parameter_list|(
name|GoatClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|query_procedures
operator|=
name|goat_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|goat_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|goat_init (Goat * goat)
name|goat_init
parameter_list|(
name|Goat
modifier|*
name|goat
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gchar
modifier|*
modifier|*
DECL|function|goat_query_procedures (GimpPlugIn * plug_in)
name|goat_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|procedures
init|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
literal|2
argument_list|)
decl_stmt|;
name|procedures
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
name|PLUG_IN_PROC
argument_list|)
expr_stmt|;
return|return
name|procedures
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|goat_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|goat_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|goat_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Goat-exercise"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Exercise a goat"
argument_list|)
argument_list|,
literal|"takes a goat for a walk"
argument_list|,
name|PLUG_IN_PROC
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Ãyvind KolÃ¥s<pippin@gimp.org>"
argument_list|,
literal|"Ãyvind KolÃ¥s<pippin@gimp.org>"
argument_list|,
literal|"21march 2012"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_image_types
argument_list|(
name|procedure
argument_list|,
literal|"RGB*, INDEXED*, GRAY*"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Filters"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_icon
argument_list|(
name|procedure
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|GIMP_ICON_GEGL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"run-mode"
argument_list|,
literal|"Run mode"
argument_list|,
literal|"The run mode"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"The input image"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable_id
argument_list|(
literal|"drawable"
argument_list|,
literal|"Drawable"
argument_list|,
literal|"The input drawable"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|goat_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|goat_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint32
name|drawable_id
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"goat run %d %d %d\n"
argument_list|,
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|,
name|gimp_value_get_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
argument_list|,
name|gimp_value_get_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|drawable_id
operator|=
name|gimp_value_get_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable_id
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|shadow_buffer
decl_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|shadow_buffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|gegl_render_op
argument_list|(
name|buffer
argument_list|,
name|shadow_buffer
argument_list|,
literal|"gegl:invert"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shadow_buffer
argument_list|)
expr_stmt|;
comment|/* flushes the shadow tiles */
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable_id
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
name|gegl_exit
argument_list|()
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|status
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

