begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_PIPE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_PIPE_H__
define|#
directive|define
name|__GIMP_BRUSH_PIPE_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpixmap.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushlist.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushlistP.h"
end_include

begin_typedef
DECL|struct|_GimpBrushPipe
typedef|typedef
struct|struct
name|_GimpBrushPipe
block|{
DECL|member|pixmap_brush
name|GimpBrushPixmap
name|pixmap_brush
decl_stmt|;
DECL|member|brush_list
name|GimpBrushList
modifier|*
name|brush_list
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|filename
name|char
modifier|*
name|filename
decl_stmt|;
DECL|typedef|GimpBrushPipe
block|}
name|GimpBrushPipe
typedef|;
end_typedef

begin_typedef
DECL|struct|_GimpBrushPipeClass
typedef|typedef
struct|struct
name|_GimpBrushPipeClass
block|{
DECL|member|parent_class
name|GimpBrushPixmapClass
name|parent_class
decl_stmt|;
DECL|member|generate
name|void
function_decl|(
modifier|*
name|generate
function_decl|)
parameter_list|(
name|GimpBrushPipe
modifier|*
name|brush
parameter_list|)
function_decl|;
DECL|typedef|GimpBrushPipeClass
block|}
name|GimpBrushPipeClass
typedef|;
end_typedef

begin_comment
comment|/* object stuff */
end_comment

begin_define
DECL|macro|GIMP_TYPE_BRUSH_PIPE
define|#
directive|define
name|GIMP_TYPE_BRUSH_PIPE
value|(gimp_brush_pipe_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_PIPE (obj)
define|#
directive|define
name|GIMP_BRUSH_PIPE
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_PIPE, GimpBrushPipe))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_PIPE (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_PIPE
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CHECK_TYPE ((obj), GIMP_TYPE_BRUSH_PIPE))
end_define

begin_function_decl
name|GtkType
name|gimp_brush_pipe_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushPipe
modifier|*
name|gimp_brush_pipe_new
parameter_list|(
name|char
modifier|*
name|file_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBrushPipe
modifier|*
name|gimp_brush_pipe_load
parameter_list|(
name|char
modifier|*
name|file_name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPBRUSHPIPE_H__ */
end_comment

end_unit

