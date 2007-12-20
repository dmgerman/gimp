%plugins = (
    'AlienMap2' => { ui => 1 },
    'CEL' => { ui => 1 },
    'CML_explorer' => { ui => 1 },
    'aa' => { ui => 1, optional => 1 },
    'align_layers' => { ui => 1 },
    'animationplay' => { ui => 1 },
    'animoptimize' => {},
    'antialias' => {},
    'apply_lens' => { ui => 1 },
    'autocrop' => {},
    'autostretch_hsv' => {},
    'blinds' => { ui => 1 },
    'blur' => {},
    'borderaverage' => { ui => 1 },
    'bumpmap' => { ui => 1 },
    'c_astretch' => {},
    'cartoon' => { ui => 1 },
    'ccanalyze' => { ui => 1 },
    'channel_mixer' => { ui => 1 },
    'checkerboard' => { ui => 1 },
    'color_enhance' => { ui => 1 },
    'colorify' => { ui => 1 },
    'colormap-remap' => { ui => 1 },
    'colortoalpha' => { ui => 1 },
    'compose' => { ui => 1 },
    'compressor' => {},
    'convmatrix' => { ui => 1 },
    'csource' => { ui => 1 },
    'cubism' => { ui => 1 },
    'curve_bend' => { ui => 1 },
    'decompose' => { ui => 1 },
    'deinterlace' => { ui => 1 },
    'depthmerge' => { ui => 1 },
    'desktop-link' => {},
    'despeckle' => { ui => 1 },
    'destripe' => { ui => 1 },
    'dicom' => { ui => 1 },
    'diffraction' => { ui => 1 },
    'displace' => { ui => 1 },
    'dog' => { ui => 1 },
    'edge' => { ui => 1 },
    'emboss' => { ui => 1 },
    'engrave' => { ui => 1 },
    'exchange' => { ui => 1 },
    'film' => { ui => 1 },
    'flarefx' => { ui => 1 },
    'fp' => { ui => 1 },
    'fractaltrace' => { ui => 1 },
    'gauss' => { ui => 1 },
    'gbr' => { ui => 1 },
    'gee' => { ui => 1 },
    'gee_zoom' => { ui => 1 },
    'gif-load' => {},
    'gif-save' => { ui => 1 },
    'gih' => { ui => 1 },
    'glasstile' => { ui => 1 },
    'glob' => {},
    'gqbist' => { ui => 1 },
    'gradmap' => {},
    'grid' => { ui => 1 },
    'gtm' => { ui => 1 },
    'guillotine' => {},
    'header' => { ui => 1 },
    'hot' => { ui => 1 },
    'illusion' => { ui => 1 },
    'iwarp' => { ui => 1 },
    'jigsaw' => { ui => 1 },
    'laplace' => {},
    'lcms' => { ui => 1, optional => 1 },
    'lens' => { ui => 1 },
    'lic' => { ui => 1 },
    'mail' => { ui => 1, optional => 1 },
    'max_rgb' => { ui => 1 },
    'mblur' => { ui => 1 },
    'mng' => { ui => 1, optional => 1 },
    'mosaic' => { ui => 1 },
    'neon' => { ui => 1 },
    'newsprint' => { ui => 1 },
    'nlfilt' => { ui => 1 },
    'noisify' => { ui => 1 },
    'normalize' => {},
    'nova' => { ui => 1 },
    'oilify' => { ui => 1 },
    'papertile' => { ui => 1 },
    'pat' => { ui => 1 },
    'pcx' => { ui => 1 },
    'photocopy' => { ui => 1 },
    'pix' => { ui => 1 },
    'pixelize' => { ui => 1 },
    'plasma' => { ui => 1 },
    'plugin-browser' => { ui => 1 },
    'png' => { ui => 1, optional => 1, cflags => 1 },
    'pnm' => { ui => 1 },
    'polar' => { ui => 1 },
    'poppler' => { ui => 1, optional => 1, cflags => 1 },
    'postscript' => { ui => 1 },
    'procedure-browser' => { ui => 1 },
    'psd-save' => { ui => 1 },
    'psp' => { ui => 1, optional => 1, libopt => 'z' },
    'randomize' => { ui => 1 },
    'raw' => { ui => 1 },
    'redeye' => { ui => 1 },
    'retinex' => { ui => 1 },
    'ripple' => { ui => 1 },
    'rotate' => {},
    'sample_colorize' => { ui => 1 },
    'scatter_hsv' => { ui => 1 },
    'screenshot' => { ui => 1, optional => 1, cflags => XFIXES_CFLAGS },
    'sel_gauss' => { ui => 1, cflags => 'MMX_EXTRA_CFLAGS' },
    'semiflatten' => {},
    'sharpen' => { ui => 1 },
    'shift' => { ui => 1 },
    'sinus' => { ui => 1 },
    'smooth_palette' => { ui => 1 },
    'snoise' => { ui => 1 },
    'sobel' => { ui => 1 },
    'softglow' => { ui => 1 },
    'sparkle' => { ui => 1 },
    'spheredesigner' => { ui => 1 },
    'spread' => { ui => 1 },
    'struc' => { ui => 1 },
    'sunras' => { ui => 1 },
    'svg' => { ui => 1, optional => 1, cflags => 1 },
    'tga' => { ui => 1 },
    'threshold_alpha' => { ui => 1 },
    'tiff-load' => { ui => 1, optional => 1, libs => 'LIBTIFF' },
    'tiff-save' => { ui => 1, optional => 1, libs => 'LIBTIFF' },
    'tile' => { ui => 1 },
    'tileit' => { ui => 1 },
    'tiler' => {},
    'uniteditor' => { ui => 1 },
    'unsharp' => { ui => 1 },
    'video' => { ui => 1 },
    'vinvert' => {},
    'vpropagate' => { ui => 1 },
    'warp' => { ui => 1 },
    'waves' => { ui => 1 },
    'webbrowser' => {},
    'whirlpinch' => { ui => 1 },
    'wind' => { ui => 1 },
    'wmf' => { ui => 1, optional => 1, cflags => 1 },
    'xbm' => { ui => 1 },
    'xpm' => { ui => 1, optional => 1 },
    'xwd' => {  ui => 1 },
    'zealouscrop' => {}
);
