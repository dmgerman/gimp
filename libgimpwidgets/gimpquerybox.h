begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpquerybox.h  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>   *   * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_QUERY_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_QUERY_BOX_H__
define|#
directive|define
name|__GIMP_QUERY_BOX_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
comment|/*  query box callback prototypes  */
DECL|typedef|GimpQueryStringCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpQueryStringCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|gchar
modifier|*
name|string
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|typedef|GimpQueryIntCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpQueryIntCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|typedef|GimpQueryDoubleCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpQueryDoubleCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|typedef|GimpQuerySizeCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpQuerySizeCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
DECL|typedef|GimpQueryBooleanCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpQueryBooleanCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|query_box
parameter_list|,
name|gboolean
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
comment|/*  some simple query dialogs  */
name|GtkWidget
modifier|*
name|gimp_query_string_box
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
specifier|const
name|gchar
modifier|*
name|initial
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryStringCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_query_int_box
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gint
name|initial
parameter_list|,
name|gint
name|lower
parameter_list|,
name|gint
name|upper
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryIntCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_query_double_box
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gdouble
name|initial
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryDoubleCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_query_size_box
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gdouble
name|initial
parameter_list|,
name|gdouble
name|lower
parameter_list|,
name|gdouble
name|upper
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|resolution
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQuerySizeCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_query_boolean_box
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
name|gboolean
name|eek
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
specifier|const
name|gchar
modifier|*
name|true_button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|false_button
parameter_list|,
name|GtkObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signal
parameter_list|,
name|GimpQueryBooleanCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_QUERY_BOX_H__ */
end_comment

end_unit

