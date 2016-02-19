<?php
/*****************************************************************
 * MD Ambrosia Theme Block Module
 * author: MegaDrupal
 * email: info@megadrupal.com
 * @file
 ****************************************************************/
function md_ambrosia_block_preprocess_block(&$vars) {

    $block = $vars['block'];

    $variable_settings = variable_get($block->delta.'_block_settings');
    $settings = unserialize($variable_settings);

    if(!empty($settings['block_html_id'])) {
        $vars['block_html_id'] = $settings['block_html_id'];
    }

    if(!empty($settings['block_html_classes'])) {
        $vars['classes_array'][] = $settings['block_html_classes'];
    }
    //Block Bootstrap Layout
    $content_classes_array = array();
    $vars['content_classes'] = '';
    $vars['bootstrap_columns'] = '';
    if(isset($settings['enable_block_bt_layout']) && $settings['enable_block_bt_layout'] == 1) {
        if(isset($settings['block_bootstrap_container'])) {
            if($settings['block_bootstrap_container'] != 'none') {
                $content_classes_array[] = $settings['block_bootstrap_container'];
            }
        }
        if(isset($settings['block_bootstrap_columns'])) {
            switch ($settings['block_bootstrap_columns']) {
                case 'none':
                    $vars['bootstrap_columns'] = '';
                    break;
                case 'col_1' :
                    $vars['bootstrap_columns'] = 'col-md-1 col-xs-12 col-lg-1 col-sm-1';
                    break;
                case 'col_2' :
                    $vars['bootstrap_columns'] = 'col-md-2 col-xs-12 col-lg-2 col-sm-2';
                    break;
                case 'col_3' :
                    $vars['bootstrap_columns'] = 'col-md-3 col-xs-12 col-lg-3 col-sm-3';
                    break;
                case 'col_4' :
                    $vars['bootstrap_columns'] = 'col-md-4 col-xs-12 col-lg-4 col-sm-4';
                    break;
                case 'col_5' :
                    $vars['bootstrap_columns'] = 'col-md-5 col-xs-12 col-lg-5 col-sm-5';
                    break;
                case 'col_6' :
                    $vars['bootstrap_columns'] = 'col-md-6 col-xs-12 col-lg-6 col-sm-6';
                    break;
                case 'col_7' :
                    $vars['bootstrap_columns'] = 'col-md-7 col-xs-12 col-lg-7 col-sm-7';
                    break;
                case 'col_8' :
                    $vars['bootstrap_columns'] = 'col-md-8 col-xs-12 col-lg-8 col-sm-8';
                    break;
                case 'col_9' :
                    $vars['bootstrap_columns'] = 'col-md-9 col-xs-12 col-lg-9 col-sm-9';
                    break;
                case 'col_10' :
                    $vars['bootstrap_columns'] = 'col-md-10 col-xs-12 col-lg-10 col-sm-10';
                    break;
                case 'col_11' :
                    $vars['bootstrap_columns'] = 'col-md-11 col-xs-12 col-lg-11 col-sm-11';
                    break;
                case 'col_12' :
                    $vars['bootstrap_columns'] = 'col-md-12 col-xs-12 col-lg-12 col-sm-12';
                    break;

            }
        }
    }

    $title_text = '';
    $wrapper_title_classes = array();
    $title_classes = array();
    $css = '';
    $scripts = '';
    if($settings['block_title_style'] == 'no_style') {
        $wrapper_title_classes[] = 'normal-style';
        if($settings['block_title_no_style_text_skin'] == 'dark') {
            $title_classes[] = 'text-dark';
        }
        if($settings['block_title_no_style_text_skin'] == 'light') {
            $title_classes[] = 'text-light';
        }
    } else {
        if($settings['block_title_style'] == 'normal') {
            $wrapper_title_classes[] = 'awe-title-2';
        }
        if($settings['block_title_style'] == 'normal_border') {
            $wrapper_title_classes[] = 'awe-title-1';
        }
        if($settings['block_title_style'] == 'unique') {
            $wrapper_title_classes[] = 'awe-title-3';
        }

        if(!empty($settings['block_title_enable_ribbon']) && $settings['block_title_enable_ribbon'] == 1) {
            $wrapper_title_classes[] = 'ribbon';
            if($settings['block_title_text_skin'] == 'dark') {
                $wrapper_title_classes[] = 'ribbon-1';
            }
            if($settings['block_title_text_skin'] == 'dark_tc') {
                $wrapper_title_classes[] = 'ribbon-2';
            }
            if($settings['block_title_text_skin'] == 'color') {
                $wrapper_title_classes[] = 'ribbon-3';
            }
            if($settings['block_title_text_skin'] == 'light') {
                $wrapper_title_classes[] = 'ribbon-4';
            }
            $title_classes[] = 'sm';
        } else {
            $wrapper_title_classes[] = 'awe-title';
            $title_classes[] = 'lg';
            if($settings['block_title_text_skin'] == 'dark') {
                $wrapper_title_classes[] = 'awe-title-dark';
            }
            if($settings['block_title_text_skin'] == 'dark_tc') {
                $wrapper_title_classes[] = 'awe-title-dark-tc';
            }
            if($settings['block_title_text_skin'] == 'color') {
                $wrapper_title_classes[] = 'awe-title-color';
            }
            if($settings['block_title_text_skin'] == 'light') {
                $wrapper_title_classes[] = 'awe-title-light';
            }
        }
    }


    if(!empty($settings['block_title_text_transform'])) {
        $title_classes[] = $settings['block_title_text_transform'];
    }
    if(isset($settings['block_enable_bg']) && $settings['block_enable_bg'] == 1) {
        $css .= '#'.$vars['block_html_id'].' .block-bg {'._background_settings_to_css('block_bg',$settings).'} '."\n";
        $css .= '#'.$vars['block_html_id'].' .block-bg {background-size:cover} '."\n";
        if($settings['block_bg_enable_overlay'] == 1) {
            $color = $settings['block_bg_overlay_colorpicker'];
            $css .= '#'.$vars['block_html_id'].' .block-bg-overlay {'._overlay_settings_to_css('block_bg',$settings).'} '."\n";
        }
        if(isset($settings['block_bg_enable_parallax_effect']) && $settings['block_bg_enable_parallax_effect'] == 1) {
            drupal_add_js(MD_AMBROSIA_BLOCK_PATH.'/assets/js/jquery.parallax-1.1.3.js');
            $scripts .= '
            (function($){
                $(window).load(function(){
                    jQuery("#'.$vars['block_html_id'].' .block-bg").parallax('._parallax_settings('block_bg',$settings).');
                })
            })(jQuery);    
            '."\n";
        }
    }
    if(isset($settings['block_title_enable_bg']) && $settings['block_title_enable_bg'] == 1) {
        $css .= '#'.$vars['block_html_id'].' .block-title-bg {'._background_settings_to_css('block_tt_bg',$settings).'} '."\n";
        $css .= '#'.$vars['block_html_id'].' .block-title-bg {background-size:cover} '."\n";
        if($settings['block_tt_bg_enable_overlay'] == 1) {
            $color = $settings['block_tt_bg_overlay_colorpicker'];
            $css .= '#'.$vars['block_html_id'].' .block-title-overlay {'._overlay_settings_to_css('block_tt_bg',$settings).'} '."\n";
        }
        if(isset($settings['block_tt_bg_enable_parallax_effect']) && $settings['block_tt_bg_enable_parallax_effect'] == 1) {
            drupal_add_js(MD_AMBROSIA_BLOCK_PATH.'/assets/js/jquery.parallax-1.1.3.js');
            $scripts .= '
            (function($){
                $(window).load(function(){
                    jQuery("#'.$vars['block_html_id'].' .block-title-bg").parallax('._parallax_settings('block_tt_bg',$settings).');
                })
            })(jQuery);
            '."\n";
        }
    }

    if(isset($settings['enable_animation']) && $settings['enable_animation'] == 1) {
        $vars['classes_array'][] = 'wow';
        if(isset($settings['animation_type'])) {
            drupal_add_css(MD_AMBROSIA_BLOCK_PATH.'/assets/css/animate.css');
            drupal_add_js(MD_AMBROSIA_BLOCK_PATH.'/assets/js/jquery.wow.min.js');
            $vars['classes_array'][] = $settings['animation_type'];

            $vars['attributes_array']['data-wow-delay'] = isset($settings['animation_delay']) ? $settings['animation_delay'] : 600;
            $vars['attributes_array']['data-wow-duration'] = isset($settings['animation_duration']) ? $settings['animation_duration'] : 600;

            drupal_add_js('jQuery(document).ready(function(){new WOW().init();})','inline');
        }
    }

    drupal_add_css(MD_AMBROSIA_BLOCK_PATH.'/assets/css/md_ambrosia_block.css');
    drupal_add_css($css,'inline');
    drupal_add_js($scripts,'inline');
    $vars['wrapper_title_classes'] = implode(' ', $wrapper_title_classes);
    $vars['title_classes'] = implode(' ', $title_classes);
    $vars['title_attributes_array']['class'][] = implode(' ', $title_classes);
    $vars['content_classes'] = implode(' ', $content_classes_array);
    $vars['theme_hook_suggestions'][] = 'block__md_ambrosia_block';
}
// Function helper to convert background theme-settings to css
function _background_settings_to_css ($name,$settings) {
    $output = '';
    if(!empty($name)) {
        $output .= 'background: ';
        $type = $settings[$name.'_type'] ? $settings[$name.'_type'] : 'color';
        if($type == 'color') {
            $color = $settings[$name.'_colorpicker'];
            $output .= $color;
        } else {
            $enable_parallax = $settings[$name.'_enable_parallax_effect'];
            $extra = '';
            if($enable_parallax == 0) {
                $extra .= $settings[$name.'_image_position'].' '.$settings[$name.'_image_repeat'].' '.$settings[$name.'_image_attachment'];
            } else {
                $extra .= ' fixed ';

            }
            if(module_exists('media')) {
                $media_file = $settings[$name.'_media_file'];
                if(!empty($media_file)) {
                    $file = json_decode($media_file);
                    if($file) {
                        $output .= 'url('.$file->url.')'.' '.$extra;
                    }
                }
            } else {
                $form_file = $settings[$name.'_form_file'];
                if(!empty($form_file)) {
                    $file_url = file_create_url(file_stream_wrapper_uri_normalize("public://".$form_file));
                    if($file_url) {
                        $output .= 'url('.$file_url.')'.' '.$extra;
                    }
                }
            }
        }
    }
    return $output;
}
// Function transfer parallax settings to javascript
function _parallax_settings($name,$settings) {
    $output = '';
    $outerHeight = true;

    if($settings[$name.'_img_pr_outerheight'] == 0) {
        $outerHeight = false;
    }
    $xpos = $settings[$name.'_img_pr_xpos'] ? $settings[$name.'_img_pr_xpos'] : '50';
    $speedFactor = $settings[$name.'_img_pr_speed'] ? $settings[$name.'_img_pr_speed'] : 0.1;

    $output .= '"'.$xpos.'%",'.$speedFactor.','.$outerHeight;

    return $output;
}

// Function render css options for overlay
function _overlay_settings_to_css($name,$settings) {
    $output = '';
    if(!empty($name)) {
        if($settings[$name.'_enable_overlay'] == 1) {
            $output .= 'background: rgba(';
            $color = cvHex2RGB($settings[$name.'_overlay_colorpicker']);
            if(!empty($color)) {
                $output .= $color['red'].','.$color['green'].','.$color['blue'].',';
            }
            $overlay = $settings[$name.'_overlay_opacity'] ? $settings[$name.'_overlay_opacity'] : 80;
            $output .= $overlay;
            $output .= ')';
        }

    }
    return $output;
}
/**
 * Convert a hexa decimal color code to its RGB equivalent
 *
 * @param string $hexStr (hexadecimal color value)
 * @param boolean $returnAsString (if set true, returns the value separated by the separator character. Otherwise returns associative array)
 * @param string $seperator (to separate RGB values. Applicable only if second parameter is true.)
 * @return array or string (depending on second parameter. Returns False if invalid hex color value)
 */
function cvHex2RGB($hexStr, $returnAsString = false, $seperator = ',') {
    $hexStr = preg_replace("/[^0-9A-Fa-f]/", '', $hexStr); // Gets a proper hex string
    $rgbArray = array();
    if (strlen($hexStr) == 6) { //If a proper hex code, convert using bitwise operation. No overhead... faster
        $colorVal = hexdec($hexStr);
        $rgbArray['red'] = 0xFF & ($colorVal >> 0x10);
        $rgbArray['green'] = 0xFF & ($colorVal >> 0x8);
        $rgbArray['blue'] = 0xFF & $colorVal;
    } elseif (strlen($hexStr) == 3) { //if shorthand notation, need some string manipulations
        $rgbArray['red'] = hexdec(str_repeat(substr($hexStr, 0, 1), 2));
        $rgbArray['green'] = hexdec(str_repeat(substr($hexStr, 1, 1), 2));
        $rgbArray['blue'] = hexdec(str_repeat(substr($hexStr, 2, 1), 2));
    } else {
        return false; //Invalid hex color code
    }
    return $returnAsString ? implode($seperator, $rgbArray) : $rgbArray; // returns the rgb string or the associative array
}