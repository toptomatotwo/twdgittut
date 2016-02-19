<?php
function unikue_check_und($param) {
    if (isset($param['und'])) {
        return $param['und'][0];
    } else {
        return $param[0];
    }
}

/**
 * @param $font
 * @return string
 * Parse font to css
 */
function unikue_typo_builder_to_css($typo) {
    $css = '';
    $script = '';
    if(!empty($typo)) {
        $typo_decode = json_decode($typo);
        foreach($typo_decode as $key => $value) {
            if(!empty($value[0]->value)) {
                $css .= $value[0]->value. ' { ' .' font-family: ' . $value[1]->value . ';' . 'font-weight: ' .$value[2]->value . ';' . 'font-style: ' . $value[3]->value . ';' .'font-size: ' . $value[4]->value . $value[5]->value . ';' . 'text-transform: ' . $value[6]->value . ';' . 'color: ' .$value[7]->value . ';' . '}' . "\n";
                if(isset($value[1]->value)) {
                    $script .= "
                    jQuery(function(){
                        jQuery(document).ready(function(){
                            WebFont.load({
                                google: {
                                  families: ['".$value[1]->value."']
                                }
                            });
                        })
                    })
                    ";
                }
            }
        }
    }
    return $css;
}

/**
 * Global $base_url
 */
// Function helper to convert background theme-settings to css
function _theme_background_settings_to_css ($name) {
    $output = 'background: ';
    $bg_attributes = array();
    if(!empty($name)) {
        if(theme_get_setting($name.'_type')) {
            $type = theme_get_setting($name.'_type') ? theme_get_setting($name.'_type') : 'color';
            if($type == 'color') {
                $color = theme_get_setting($name.'_colorpicker');
                $output .= $color;
                $bg_attributes[] = $color;
            } else {
                $enable_parallax = theme_get_setting($name.'_image_enable_parallax');
                $extra = '';
                if($enable_parallax == 0) {
                    $extra .= theme_get_setting($name.'_image_position').' '.theme_get_setting($name.'_image_repeat').' '.theme_get_setting($name.'_image_attachment');
                    $bg_attributes[] = theme_get_setting($name.'_image_position');
                    $bg_attributes[] = theme_get_setting($name.'_image_repeat');
                    $bg_attributes[] = theme_get_setting($name.'_image_attachment');
                } else {
                    $extra .= ' fixed ';
                    $bg_attributes[] = 'fixed';
                }
                if(module_exists('media')) {
                    $media_file = theme_get_setting($name.'_media_file');
                    if(!empty($media_file)) {
                        $file = json_decode($media_file);
                        if($file) {
                            $output .= 'url('.$file->url.')'.' '.$extra;
                            $bg_attributes[] = 'url('.$file->url.')';
                        }
                    }
                } else {
                    $form_file = theme_get_setting($name.'_form_file');
                    if(!empty($form_file)) {
                        $file_url = file_create_url(file_stream_wrapper_uri_normalize("public://".$form_file));
                        if($file_url) {
                            $output .= 'url('.$file_url.')'.' '.$extra;
                            $bg_attributes[] = 'url('.$file_url.')';
                        }
                    }
                }
            }
        }
    }
    $bg_style = implode(" ",$bg_attributes);
    return $bg_style;
}
// Function transfer parallax settings to javascript
function _theme_parallax_settings($name) {
    $output = '';
    $outerHeight = true;
    if(theme_get_setting($name.'_img_pr_outerheight') == 0) {
        $outerHeight = false;
    }
    $xpos = theme_get_setting($name.'_img_pr_xpos') ? theme_get_setting($name.'_img_pr_xpos') : '50%';
    $speedFactor = theme_get_setting($name.'_img_pr_speed') ? theme_get_setting($name.'_img_pr_speed') : 0.1;

    $output .= '"'.$xpos.'",'.$speedFactor.','.$outerHeight.'';

    return $output;
}

// Function render css options for overlay
function _theme_overlay_settings_to_css($name) {
    $output = '';
    if(!empty($name)) {
        $output .= 'background: rgba(';
        $color = hex2RGB(theme_get_setting($name.'_overlay_colorpicker'));
        if(!empty($color)) {
            $output .= $color['red'].','.$color['green'].','.$color['blue'].',';
        }
        $overlay = theme_get_setting($name.'_overlay_opacity') ? (theme_get_setting($name.'_overlay_opacity')/100) : 0.8;
        $output .= $overlay;
        $output .= ')';
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
function hex2RGB($hexStr, $returnAsString = false, $seperator = ',') {
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

/**
 * @param $directory
 * @return array
 * Get Directory List
 */
function getDirectoryList ($directory)
{

    // create an array to hold directory list
    $results = array();

    // create a handler for the directory
    $handler = opendir($directory);

    // open directory and walk through the filenames
    while ($file = readdir($handler)) {

        // if file isn't this directory or its parent, add it to the results
        if ($file != "." && $file != "..") {
            $results[] = $file;
        }

    }

    // tidy up: close the handler
    closedir($handler);

    // done!
    return $results;

}
/**
 * @param $haystack
 * @param $needle
 * @param int $offset
 * @return bool
 * Check string in string
 */
function strposa($haystack, $needle, $offset=0) {
    if(!is_array($needle)) $needle = array($needle);
    foreach($needle as $query) {
        if(strpos($haystack, $query, $offset) !== false) return true; // stop on first true result
    }
    return false;
}
function icon_default_dialog() {

    $options = array();
    $icon_default_value = array();
    if(module_exists('icon')) {
        foreach (icon_bundles() as $bundle_name => $bundle) {
            if (!$bundle['status']) {
                continue;
            }
            foreach ($bundle['icons'] as $icon_key => $icon_value) {
                $icon_name = is_string($icon_key) ? $icon_key : $icon_value;
                if (is_array($icon_value) && isset($icon_value['name'])) {
                    $icon_name = $icon_value['name'];
                }
                $icon_title = is_string($icon_value) ? $icon_value : $icon_name;
                if (is_array($icon_value) && isset($icon_value['title'])) {
                    $icon_title = $icon_value['title'];
                }
                if(isset($bundle['name'])) {
                    $options[$bundle['title']][$bundle['name'] . '|' . $icon_name] = $icon_title;
                }
            }
            $icon_default_value = $options;
        }
        $icon_mark_up = '';
        $icon_fake_markup = '<ul class="list-icon">';
        foreach($icon_default_value as $key => $value) {
            $icon_mark_up .= '<option selected="selected" value="">- No Icon -</option><optgroup label="'.$key.'">';
            foreach ($icon_default_value[$key] as $key2 => $value2) {
                $fake_icon_explode = explode("|",$key2);
                $icon_fake_markup .= '<li><a href="#'.$fake_icon_explode[1].'" class="fake-icon" alt="'.$fake_icon_explode[1].'" icon-name="'.$fake_icon_explode[1].'" data-bundle="'.$fake_icon_explode[0].'" data-icon="'.$key2.'"><i class="'.$fake_icon_explode[0].' '.$fake_icon_explode[1].'"></i></a></li>';
                $icon_mark_up .= '<option value="'.$key2.'">'.$value2.'</option>';
            }
            $icon_mark_up .= '</optgroup>';
        }
        $icon_fake_markup .= '</ul>';
        drupal_add_js(array('icMarkUp' => $icon_mark_up),'setting');
        drupal_add_js(array('icFake' => $icon_fake_markup),'setting');
    }

}
function theme_path() {
    $theme_path = drupal_get_path('theme','unikue');
    return $theme_path;
}
function get_option_icon(){
    $options = array();
    $icon_default_value = array();
    if(module_exists('icon')) {
        foreach (icon_bundles() as $bundle_name => $bundle) {
            if (!$bundle['status']) {
                continue;
            }
            $class = isset($bundle['settings']['class']) ? $bundle['settings']['class'] : 'fa';
            foreach ($bundle['icons'] as $icon_key => $icon_value) {
                $icon_name = is_string($icon_key) ? $icon_key : $icon_value;
                if (is_array($icon_value) && isset($icon_value['name'])) {
                    $icon_name = $icon_value['name'];
                }
                $icon_title = is_string($icon_value) ? $icon_value : $icon_name;
                if (is_array($icon_value) && isset($icon_value['title'])) {
                    $icon_title = $icon_value['title'];
                }
                $options[$bundle['title']][$class . '|' . $icon_name] = $icon_title;
            }
            $icon_default_value = $options;
        }
    }
    return $icon_default_value;
}