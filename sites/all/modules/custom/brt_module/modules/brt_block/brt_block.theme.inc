<?php
function brt_block_preprocess_unikue_header(&$vars) {
    global $base_url;
    global $user;
    $brt_data = isset($vars['brt_block']) ? $vars['brt_block'] : null;
    if($brt_data != null) {
        $css = '';
        $scripts = '';
        $header_content = '';
        $duration = isset($brt_data['hd_slide_content_animation_duration']) ? $brt_data['hd_slide_content_animation_duration'] : 800;
        $delay = isset($brt_data['hd_slide_content_delay']) ? $brt_data['hd_slide_content_delay'] : 6000;
        $autoplay = isset($brt_data['hd_slide_content_autoplay']) ? $brt_data['hd_slide_content_autoplay'] : 1;
        $loop = isset($brt_data['hd_slide_content_loop']) ? $brt_data['hd_slide_content_loop'] : 1;
        if($brt_data['hd_bg_slide_content_us_data'] != null) {
            $json_decode = drupal_json_decode($brt_data['hd_bg_slide_content_us_data']);
            $count = count($json_decode);
            $header_content .= '
            <div class="w-slider slider_home" data-animation="outin" data-duration="'.$duration.'" data-infinite="'.$loop.'" data-delay="'.$delay.'" data-autoplay="'.$autoplay.'">
                 <div class="w-slider-mask">';
                    $i = 1;
                    foreach($json_decode as $key => $value) {
                        $header_content .= '
                        <div class="w-slide slide-'.$i.'-home">
                        <div class="tittle_text" data-ix="fade-down-12">'.$value[0]['value'].'</div>
                        </div>';
                        $i++;
                    }
            $header_content .= '
                 </div>
                 <div class="w-slider-arrow-left hide-arrow">
                     <div class="w-icon-slider-left"></div>
                 </div>
                 <div class="w-slider-arrow-right hide-arrow">
                     <div class="w-icon-slider-right"></div>
                 </div>
                 <div class="w-slider-nav w-round slide-nav"></div>
             </div>';
        }
        if(theme_get_setting('enable_ds_title_bg') == 1) {
            if(theme_get_setting('ds_title_bg_type') == 'image') {
                $css .= ' {background-size:cover !important;} ';
            }
            $css .= '{background: '._brt_background_settings_to_css('ds_title_bg').';} '."\n";

            if(theme_get_setting('ds_title_bg_enable_overlay') == 1) {
                $color = theme_get_setting('ds_title_bg_overlay_colorpicker');

                $css .= '.background-overlay {'._brt_overlay_settings_to_css('ds_title_bg').'} '."\n";
            }
            if(theme_get_setting('ds_title_bg_enable_parallax_effect') == 1) {
                $scripts .= 'jQuery(" .background").parallax('._brt_parallax_settings('ds_title_bg').')'."\n";
            }
        }
        $vars['header_content'] = $header_content;
        drupal_add_css($css,'inline');
        drupal_add_js($scripts,array('type' => 'inline', 'scope' => 'footer'));
    }
}
function brt_block_preprocess_unikue_twitter(&$vars) {
    $brt_data = isset($vars['brt_block']) ? $vars['brt_block'] : null;
    if($brt_data != null) {
        $theme_path = drupal_get_path('theme','unique');
        $twitter_account = $brt_data['twitter_username'];
        $twitter_max = $brt_data['twitter_num'];
        $twitter_tck = $brt_data['twitter_consumer_key'];
        $twitter_tcs = $brt_data['twitter_consumer_secret'];
        $twitter_tat = $brt_data['twitter_access_token'];
        $twitter_tats = $brt_data['twitter_access_token_secret'];
        if(isset($twitter_account) && isset($twitter_max)){
            drupal_add_js(array('twitter_account'=>$twitter_account),'setting');
            drupal_add_js(array('twitter_num'=>$twitter_max),'setting');
            drupal_add_js(array('tck'=>$twitter_tck),'setting');
            drupal_add_js(array('tcs'=>$twitter_tcs),'setting');
            drupal_add_js(array('tat'=>$twitter_tat),'setting');
            drupal_add_js(array('tats'=>$twitter_tats),'setting');
            drupal_add_js(drupal_get_path('module', 'brt_block') . '/types/twitter/js/jquery.tweet.js');
            drupal_add_js(drupal_get_path('module', 'brt_block') . '/types/twitter/js/script.js');
        }
    }
}
function brt_block_preprocess_unikue_flickr(&$vars){
    $brt_data = isset($vars['brt_block']) ? $vars['brt_block'] : null;
    if($brt_data != null) {
        drupal_add_js(array('flickr' => array('flickrID' => $brt_data['flickr_id'],'flickrNum' => $brt_data['flickr_num'])),'setting');
        drupal_add_js(drupal_get_path('module', 'brt_block') . '/types/flickr/js/jquery.flickrfeed.min.js');
        drupal_add_js(drupal_get_path('module', 'brt_block') . '/types/flickr/js/flickr.custom.js');
    }
}
function brt_block_preprocess_unikue_video(&$vars) {
    $brt_data = isset($vars['brt_block']) ? $vars['brt_block'] : null;
    $render = '';
    if($brt_data != null) {
        if($brt_data['video_media']) {
            if($brt_data['video_media']['fid'] != 0) {
                $file = file_load($brt_data['video_media']['fid']);
                if (strpos($file->filemime, 'video/') !== 0) {
                    return;
                }
                $key = 'media_' . substr($file->filemime, 6) . '_video';
                $formatter_info = file_info_formatter_types($key);
                $content = array();
                $content['#theme'] = $key;
                $content['#uri'] = $file->uri;
                if (isset($formatter_info['default settings'])) {
                    $content['#options'] = $formatter_info['default settings'];
                }
                $render = drupal_render($content);
            }
        }
    }
    $vars['content'] = $render;
}
function brt_block_preprocess_unikue_map(&$vars) {
    $brt_data = isset($vars['brt_block']) ? $vars['brt_block'] : null;
    $render = '';
    if($brt_data != null) {

    }
}
function brt_block_preprocess_unikue_instagram(&$vars) {
    $brt_data = isset($vars['brt_block']) ? $vars['brt_block'] : null;
    $render = '';
    if($brt_data != null) {
        // Get configuration values.
        $values = variable_get('instagram_block_data', array());
        $img_resolution = isset($values['img_resolution']) ? $values['img_resolution'] : 'thumbnail';
        $content = array();
        // Check that block configuration is available.
        if (!isset($values['user_id']) || !isset($values['access_token'])) {
            // Remind user to fill in configuration.
            $content = brt_block_instagram_get_configuration_reminder();
        }
        else {
            $url = "https://api.instagram.com/v1/users/" . $values['user_id'] . "/media/recent/?access_token=" . $values['access_token'] . "&count=" . $values['count'];
            $response = drupal_http_request($url, array());
            $result = json_decode($response->data);
            $data = $result->data;
            foreach ($data as $key => $post) {
                $content['children'][$post->id] = array(
                    '#markup' => '',
                    '#theme' => 'unikue_instagram_image',
                    '#post' => $post,
                    '#href' => $post->link,
                    '#src' => $post->images->{$img_resolution}->url,
                    '#width' => $values['width'],
                    '#height' => $values['height'],
                );
            }
        }
    }
    $render = render($content);
    $vars['content'] = $render;
}

/**
 * Builds render array to remind user to configure block settings.
 */
function brt_block_instagram_get_configuration_reminder() {
    return array(
        '#markup' => t('Please don\'t forget to configure this block.')
    );
}
// Function helper to convert background theme-settings to css
function _brt_background_settings_to_css ($name) {
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
function _brt_parallax_settings($name) {
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
function _brt_overlay_settings_to_css($name) {
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

function _is_youtube($url)
{
    return (preg_match('/youtu\.be/i', $url) || preg_match('/youtube\.com\/watch/i', $url));
}

function _is_vimeo($url)
{
    return (preg_match('/vimeo\.com/i', $url));
}

function _brt_get_youtube_video_id($url)
{
  if(_is_youtube($url))
  {
      $pattern = '/^.*((youtu.be\/)|(v\/)|(\/u\/\w\/)|(embed\/)|(watch\?))\??v?=?([^#\&\?]*).*/';
      preg_match($pattern, $url, $matches);
      if (count($matches) && strlen($matches[7]) == 11)
      {
          return $matches[7];
      }
  }

  return '';
}

function _brt_get_vimeo_video_id($url)
{
    if(_is_vimeo($url))
    {
        $pattern = '/\/\/(www\.)?vimeo.com\/(\d+)($|\/)/';
        preg_match($pattern, $url, $matches);
        if (count($matches))
        {
            return $matches[2];
        }
    }

    return '';
}