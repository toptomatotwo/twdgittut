
<!DOCTYPE html>
<html  xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"
    <?php print $rdf_namespaces; ?>>
<head profile="<?php print $grddl_profile;?>">
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>
    <?php if(isset($ios_144) && $ios_144 != null) :?><link rel="apple-touch-icon-precomposed" sizes="144x144" href="<?php print $ios_144;?>"><?php endif;?>
    <?php if(isset($ios_114) && $ios_114 != null) :?><link rel="apple-touch-icon-precomposed" sizes="114x114" href="<?php print $ios_114;?>"><?php endif;?>
    <?php if(isset($ios_72) && $ios_72 != null) :?><link rel="apple-touch-icon-precomposed" sizes="72x72" href="<?php print $ios_72;?>"><?php endif;?>
    <?php if(isset($ios_57) && $ios_57 != null) :?><link rel="apple-touch-icon-precomposed" sizes="57x57" href="<?php print $ios_57;?>"><?php endif;?>
    <meta name="msapplication-tap-highlight" content="no" />
    <meta name="viewport" content="user-scalable=0, width=device-width, initial-scale=1, minimum-scale=1.0, maximum-scale=1.0, minimal-ui" />
    <link href="http://netdna.bootstrapcdn.com/font-awesome/4.0.2/css/font-awesome.css" rel="stylesheet">
    <?php
    print $styles;

    global $base_url;
    ?>
    <style type="text/css">
        <?php if (isset($theme_setting_css)): print $theme_setting_css; endif; ?>
        <?php if (isset($custom_css)): print $custom_css; endif; ?>
    </style>
    <script src="//ajax.googleapis.com/ajax/libs/webfont/1.4.7/webfont.js"></script>
    <!--[if lte IE 9]><script src="https://cdnjs.cloudflare.com/ajax/libs/placeholders/3.0.2/placeholders.min.js"></script><![endif]-->
    <?php if (isset($header_code)): print $header_code; endif;?>
<link href='http://fonts.googleapis.com/css?family=Pacifico' rel='stylesheet' type='text/css'>
<link href='http://fonts.googleapis.com/css?family=Cookie' rel='stylesheet' type='text/css'>
<link href='http://fonts.googleapis.com/css?family=Leckerli+One' rel='stylesheet' type='text/css'>
<!-- NEED H2 TAGS -->
<link href='https://fonts.googleapis.com/css?family=Damion' rel='stylesheet' type='text/css'>
<link href='https://fonts.googleapis.com/css?family=Lily+Script+One' rel='stylesheet' type='text/css'>

</head>

<body class="<?php print $classes; ?>" <?php print $attributes;?> >
    <div id="widthMonitor" style="position:absolute;top:0;left:0;height:50px;width:50px;background-color:#000;color:#fff;z-index:100000;"></div>
<?php print $page_top; ?>
<?php print $page; ?>
<?php print $page_bottom;
print $scripts;
if (isset($footer_code)): print $footer_code; endif;
?>
<script>jQuery('#widthMonitor').html(jQuery.windowWidth); alert('foote script loaded')</script>
</body>
</html>