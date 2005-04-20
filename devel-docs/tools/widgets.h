begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__WIDGETS_H__
end_ifndef

begin_define
DECL|macro|__WIDGETS_H__
define|#
directive|define
name|__WIDGETS_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28dee5590103
block|{
DECL|enumerator|SMALL
name|SMALL
block|,
DECL|enumerator|MEDIUM
name|MEDIUM
block|,
DECL|enumerator|LARGE
name|LARGE
block|,
DECL|enumerator|ASIS
name|ASIS
DECL|typedef|WidgetSize
block|}
name|WidgetSize
typedef|;
end_typedef

begin_typedef
DECL|struct|WidgetInfo
typedef|typedef
struct|struct
name|WidgetInfo
block|{
DECL|member|window
name|GtkWidget
modifier|*
name|window
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|no_focus
name|gboolean
name|no_focus
decl_stmt|;
DECL|member|include_decorations
name|gboolean
name|include_decorations
decl_stmt|;
DECL|member|size
name|WidgetSize
name|size
decl_stmt|;
DECL|typedef|WidgetInfo
block|}
name|WidgetInfo
typedef|;
end_typedef

begin_function_decl
name|GList
modifier|*
name|get_all_widgets
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __WIDGETS_H__ */
end_comment

end_unit

