<?php
/**
 * Add body classes if certain regions have content.
 */

function unikue_preprocess_html(&$vars) {
    global $base_url;
    $css = "";
    $themepath = drupal_get_path('theme','unikue');
    drupal_add_js(array('themePath' => $themepath),'setting');
    drupal_add_css($themepath . '/css/loading.css');
    drupal_add_css($themepath . '/css/base.css');
    drupal_add_css($themepath . '/css/normalize.css');
    drupal_add_css($themepath . '/css/style.css');
    drupal_add_css($themepath . '/css/drupal-additional.css');

    drupal_add_js($themepath . '/js/jquery-migrate-1.2.1.js');
    drupal_add_js($themepath . '/js/form.js');
    //drupal_add_js($themepath . '/js/jquery.min.js');
    drupal_add_js($themepath . '/js/jquery.countTo.js');
    drupal_add_js($themepath . '/js/modernizr.js');
    drupal_add_js($themepath . '/js/main.js');;
    drupal_add_js($themepath . '/js/woozy.js');
    drupal_add_js($themepath . '/js/twd.js');


///////////////////////////////////////// Construct page title //////////////////////////////////////////////////////.
    if (drupal_get_title()) {
        $head_title = array(
            'title' => str_replace(array('&lt;i&gt;','&lt;/i&gt;'),'',drupal_get_title()),
            'name' => check_plain(variable_get('site_name', 'Drupal')),
        );
    }
    else {
        $head_title = array('name' => check_plain(variable_get('site_name', 'Drupal')));
        if (variable_get('site_slogan', '')) {
            $head_title['slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
        }
    }

    $vars['head_title_array'] = $head_title;
    $vars['head_title'] = implode(' | ', $head_title);
    // Match path if necessary.
    $page_match = TRUE;
    $path = drupal_strtolower(drupal_get_path_alias($_GET['q']));


//////////////////////////////////////////// FAVICON SETTING ////////////////////////////////////////////
    // Add favicon.
    if (theme_get_setting('toggle_fvicon')) {
        $favicon_path = $base_url.'/'.$themepath.'/favicon.ico';
        if(theme_get_setting('default_favicon') == 0) {
            if(module_exists('media')) {
                $favicon = theme_get_setting('fvicon_upload');
                if(!empty($favicon)) {
                    $file = json_decode($favicon);
                    $favicon_path = $file->url;
                }
            } else {
                if ($favicon_file = theme_get_setting('fvicon_file')) {
                    $favicon_path =  file_create_url(file_build_uri($favicon_file));
                }
            }
        }
        $type = theme_get_setting('favicon_mimetype');
        drupal_add_html_head_link(array('rel' => 'shortcut icon', 'href' => drupal_strip_dangerous_protocols($favicon_path), 'type' => $type));
    }
    // iOs webclip
    $vars['ios_57'] = '';
    if(module_exists('media')) {
        if(theme_get_setting('ios_57x57_media_file')) {
            $file_upload = theme_get_setting('ios_57x57_media_file');
            if(!empty($file_upload)) {
                $file = json_decode($file_upload);
                $vars['ios_57'] = $file->url;
            }
        }
    } else {
        if (theme_get_setting('ios_57x57_form_file')) {
            $vars['ios_57'] =  file_create_url(file_build_uri(theme_get_setting('ios_57x57_form_file')));
        }
    }

    $vars['ios_72'] = '';
    if(module_exists('media')) {
        if(theme_get_setting('ios_72x72_media_file')) {
            $file_upload = theme_get_setting('ios_72x72_media_file');
            if(!empty($file_upload)) {
                $file = json_decode($file_upload);
                $vars['ios_72'] = $file->url;
            }
        }
    } else {
        if (theme_get_setting('ios_72x72_form_file')) {
            $vars['ios_72'] =  file_create_url(file_build_uri(theme_get_setting('ios_72x72_form_file')));
        }
    }

    $vars['ios_114'] = '';
    if(module_exists('media')) {
        if(theme_get_setting('ios_114x114_media_file')) {
            $file_upload = theme_get_setting('ios_114x114_media_file');
            if(!empty($file_upload)) {
                $file = json_decode($file_upload);
                $vars['ios_114'] = $file->url;
            }
        }
    } else {
        if (theme_get_setting('ios_114x114_form_file')) {
            $vars['ios_114'] =  file_create_url(file_build_uri(theme_get_setting('ios_114x114_form_file')));
        }
    }

    $vars['ios_144'] = '';
    if(module_exists('media')) {
        if(theme_get_setting('ios_144x144_media_file')) {
            $file_upload = theme_get_setting('ios_144x144_media_file');
            if(!empty($file_upload)) {
                $file = json_decode($file_upload);
                $vars['ios_144'] = $file->url;
            }
        }
    } else {
        if (theme_get_setting('ios_144x144_form_file')) {
            $vars['ios_144'] =  file_create_url(file_build_uri(theme_get_setting('ios_144x144_form_file')));
        }
    }

    $vars['theme_setting_css'] = $css;


    //Google Fonts
    if(theme_get_setting('typo_hidden')) {
        $typo = theme_get_setting('typo_hidden');
        $css .= unikue_typo_builder_to_css($typo);
    }



    /* Get theme settings
    ---------------------------------------------------------------------------------------- */
    $vars['footer_text']   = theme_get_setting('footer_text');
    $vars['header_code']   = theme_get_setting('header_code');
    $vars['footer_code']   = theme_get_setting('footer_code');
    if (theme_get_setting('custom_css')) {
        $vars['custom_css']  = theme_get_setting('custom_css');
    }
    drupal_add_css(path_to_theme() . '/css/ie7.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
    $vars['theme_setting_css'] = $css;
}


/**
 * Override or insert vars into the page template for HTML ounique
 */
function unikue_process_html(&$vars) {
    // Hook into color.module.
    if (module_exists('color')) {
        _color_html_alter($vars);
    }

    $classes = explode(' ', $vars['classes']);
    if ($node = menu_get_object()) {
        $node_type_class = drupal_html_class('node-type-' . $node->type);
        if (in_array($node_type_class, $classes)) {
            theme_get_setting('extra_page_classes') == 0 ? '' : $classes = str_replace($node_type_class, '', $classes);
            $classes = str_replace('node-type-', 'page-type-', $classes);
        }
    }
    $vars['classes'] = trim(implode(' ', $classes));
}



function unikue_custom_skin ($custom_color) {

}
