%plugins = (
    'align-layers' => { ui => 1 },
    'animation-optimize' => {},
    'animation-play' => { ui => 1, gegl => 1 },
    'blinds' => { ui => 1 },
    'blur' => {},
    'border-average' => { ui => 1, gegl => 1 },
    'cartoon' => { ui => 1 },
    'checkerboard' => { ui => 1 },
    'cml-explorer' => { ui => 1 },
    'color-cube-analyze' => { ui => 1 },
    'color-enhance' => { ui => 1 },
    'colorify' => { ui => 1 },
    'colormap-remap' => { ui => 1, gegl => 1 },
    'compose' => { ui => 1, gegl => 1 },
    'contrast-normalize' => {},
    'contrast-retinex' => { ui => 1 },
    'crop-zealous' => { gegl => 1 },
    'curve-bend' => { ui => 1 },
    'decompose' => { ui => 1, gegl => 1 },
    'depth-merge' => { ui => 1 },
    'despeckle' => { ui => 1 },
    'destripe' => { ui => 1 },
    'edge-dog' => { ui => 1 },
    'edge-neon' => { ui => 1 },
    'emboss' => { ui => 1 },
    'file-aa' => { ui => 1, gegl => 1, optional => 1, libs => 'AA_LIBS' },
    'file-cel' => { ui => 1, gegl => 1 },
    'file-csource' => { ui => 1, gegl => 1 },
    'file-compressor' => { gio => 1, libdep => 'Z:BZIP2:LZMA', cflags => 'LZMA_CFLAGS' },
    'file-desktop-link' => {},
    'file-dicom' => { ui => 1, gegl => 1, cflags => '-fno-strict-aliasing' },
    'file-gbr' => { ui => 1, gegl => 1 },
    'file-gegl' => { ui => 1, gegl => 1 },
    'file-gif-load' => { gegl => 1 },
    'file-gif-save' => { ui => 1, gegl => 1 },
    'file-gih' => { ui => 1, gegl => 1 },
    'file-glob' => {},
    'file-header' => { ui => 1, gegl => 1 },
    'file-html-table' => { ui => 1, gegl => 1 },
    'file-jp2-load' => { ui => 1, optional => 1, gegl => 1, libs => 'JP2_LIBS' },
    'file-mng' => { ui => 1, gegl => 1, optional => 1, libs => 'MNG_LIBS', cflags => 'MNG_CFLAGS' },
    'file-pat' => { ui => 1, gegl => 1 },
    'file-pcx' => { ui => 1, gegl => 1 },
    'file-pix' => { ui => 1, gegl => 1 },
    'file-png' => { ui => 1, gegl => 1, libs => 'PNG_LIBS', cflags => 'PNG_CFLAGS' },
    'file-pnm' => { ui => 1, gegl => 1 },
    'file-pdf-load' => { ui => 1, optional => 1, libs => 'POPPLER_LIBS', cflags => 'POPPLER_CFLAGS' },
    'file-pdf-save' => { ui => 1, gegl => 1, optional => 1, libs => 'CAIRO_PDF_LIBS', cflags => 'CAIRO_PDF_CFLAGS' },
    'file-ps' => { ui => 1, gegl => 1, optional => 1, libs => 'GS_LIBS' },
    'file-psp' => { ui => 1, gegl => 1, libs => 'Z_LIBS' },
    'file-raw-data' => { ui => 1, gegl => 1 },
    'file-sunras' => { ui => 1, gegl => 1 },
    'file-svg' => { ui => 1, libs => 'SVG_LIBS', cflags => 'SVG_CFLAGS' },
    'file-tga' => { ui => 1, gegl => 1 },
    'file-wmf' => { ui => 1, gegl => 1, optional => 1, libs => 'WMF_LIBS', cflags => 'WMF_CFLAGS' },
    'file-xbm' => { ui => 1, gegl => 1 },
    'file-xmc' => { ui => 1, gegl => 1, optional => 1, libs => 'XMC_LIBS' },
    'file-xpm' => { ui => 1, gegl => 1, optional => 1, libs => 'XPM_LIBS' },
    'file-xwd' => {  ui => 1, gegl => 1 },
    'film' => { ui => 1 },
    'filter-pack' => { ui => 1 },
    'fractal-trace' => { ui => 1 },
    'goat-exercise' => { gegl => 1 },
    'gradient-map' => { gegl => 1 },
    'grid' => { ui => 1 },
    'guillotine' => {},
    'hot' => { ui => 1 },
    'jigsaw' => { ui => 1 },
    'mail' => { ui => 1, optional => 1 },
    'max-rgb' => { ui => 1 },
    'metadata' => { ui => 1, libs => 'GEXIV2_LIBS', cflags => 'GEXIV2_CFLAGS' },
    'newsprint' => { ui => 1 },
    'nl-filter' => { ui => 1 },
    'oilify' => { ui => 1 },
    'photocopy' => { ui => 1 },
    'plugin-browser' => { ui => 1 },
    'procedure-browser' => { ui => 1 },
    'qbist' => { ui => 1 },
    'ripple' => { ui => 1 },
    'sample-colorize' => { ui => 1 },
    'sharpen' => { ui => 1 },
    'smooth-palette' => { ui => 1, gegl => 1 },
    'softglow' => { ui => 1 },
    'sparkle' => { ui => 1 },
    'sphere-designer' => { ui => 1 },
    'tile' => { ui => 1, gegl => 1 },
    'tile-small' => { ui => 1 },
    'unit-editor' => { ui => 1 },
    'unsharp-mask' => { ui => 1 },
    'van-gogh-lic' => { ui => 1 },
    'warp' => { ui => 1 },
    'wavelet-decompose' => { ui => 1, gegl => 1 },
    'web-browser' => { ui => 1, ldflags => '$(framework_cocoa)', cppflags => '$(AM_CPPFLAGS) $(xobjective_c)' },
    'web-page' => { ui => 1, optional => 1, libs => 'WEBKIT_LIBS', cflags => 'WEBKIT_CFLAGS' }
);
