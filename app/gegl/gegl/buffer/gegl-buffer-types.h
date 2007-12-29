begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* This file is part of GEGL.  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, see<http://www.gnu.org/licenses/>.  *  * Copyright 2006,2007 Ãyvind KolÃ¥s<pippin@gimp.org>  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GEGL_BUFFER_TYPES_H
end_ifndef

begin_define
DECL|macro|_GEGL_BUFFER_TYPES_H
define|#
directive|define
name|_GEGL_BUFFER_TYPES_H
end_define

begin_typedef
DECL|typedef|GeglSampler
typedef|typedef
name|struct
name|_GeglSampler
name|GeglSampler
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglTile
typedef|typedef
name|struct
name|_GeglTile
name|GeglTile
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglTileClass
typedef|typedef
name|struct
name|_GeglTileClass
name|GeglTileClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglProvider
typedef|typedef
name|struct
name|_GeglProvider
name|GeglProvider
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglProviderClass
typedef|typedef
name|struct
name|_GeglProviderClass
name|GeglProviderClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglTileBackend
typedef|typedef
name|struct
name|_GeglTileBackend
name|GeglTileBackend
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglTileBackendClass
typedef|typedef
name|struct
name|_GeglTileBackendClass
name|GeglTileBackendClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglHandler
typedef|typedef
name|struct
name|_GeglHandler
name|GeglHandler
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglHandlerClass
typedef|typedef
name|struct
name|_GeglHandlerClass
name|GeglHandlerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglHandlers
typedef|typedef
name|struct
name|_GeglHandlers
name|GeglHandlers
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglHandlersClass
typedef|typedef
name|struct
name|_GeglHandlersClass
name|GeglHandlersClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglStorage
typedef|typedef
name|struct
name|_GeglStorage
name|GeglStorage
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglStorageClass
typedef|typedef
name|struct
name|_GeglStorageClass
name|GeglStorageClass
typedef|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|_GEGL_BUFFER_H
end_ifndef

begin_typedef
DECL|typedef|GeglBuffer
typedef|typedef
name|struct
name|_GeglBuffer
name|GeglBuffer
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|GeglBufferClass
typedef|typedef
name|struct
name|_GeglBufferClass
name|GeglBufferClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglCache
typedef|typedef
name|struct
name|_GeglCache
name|GeglCache
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglCacheClass
typedef|typedef
name|struct
name|_GeglCacheClass
name|GeglCacheClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglBufferAllocator
typedef|typedef
name|struct
name|_GeglBufferAllocator
name|GeglBufferAllocator
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglBufferAllocatorClass
typedef|typedef
name|struct
name|_GeglBufferAllocatorClass
name|GeglBufferAllocatorClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglRegion
typedef|typedef
name|struct
name|_GeglRegion
name|GeglRegion
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

end_unit

