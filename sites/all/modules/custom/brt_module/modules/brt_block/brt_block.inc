<?php
/**
 *
 *array :
 *['type']['config'] =>
 *  'title' => t('title for type'),
 *  'description' => 'description for type',
 *['type']['form'] =>
 *  write form default
 *['type']['js'] =>
 *  'file1.js',
 *  'file2.js'
 *['type']['css'] =>
 *  'file1.css',
 *  'file2.css'
 *
 **/
function brt_block_data($default_value = '') {
    brt_block_icon_default_dialog();
    $brt_data = array();
    /////////////////////////////// Twitter ///////////////////////////////
    $unikue_twitter_form = array(
        'description' => array(
            '#type' => 'textfield',
            '#title' => 'Block description',
            '#description' =>'A brief description of your block. Used on the Blocks administration page.',
            '#required' => true,
            '#default_value' => isset($default_value['description']) ? $default_value['description'] : ''
        ),
    );
    $unikue_twitter_form['twitter_username'] = array(
        '#type' => 'textfield',
        '#title'    =>  t('Twitter username'),
        '#size'         => '15',
        '#required'      => true,
        '#default_value'    => isset($default_value['twitter_username']) ? $default_value['twitter_username'] : ''
    );
    $unikue_twitter_form['twitter_num'] = array(
        '#type'     => 'textfield',
        '#title'    => t('Tweets Posts'),
        '#size'     => '5',
        '#default_value'    => isset($default_value['twitter_num']) ? $default_value['twitter_num'] : ''
    );
    $unikue_twitter_form['twitter_consumer_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Consumer key'),
        '#description' => t('Enter your consumer key from your twitter app'),
        '#maxlength' => '50',
        '#default_value' => isset($default_value['twitter_consumer_key']) ? $default_value['twitter_consumer_key'] : ''
    );
    $unikue_twitter_form['twitter_consumer_secret'] = array(
        '#type' => 'textfield',
        '#title' => t('Consumer secret'),
        '#description' => t('Enter your consumer secret string from your twitter app'),
        '#maxlength' => '50',
        '#default_value' => isset($default_value['twitter_consumer_secret']) ? $default_value['twitter_consumer_secret'] : ''
    );
    $unikue_twitter_form['twitter_access_token'] = array(
        '#type' => 'textfield',
        '#title' => t('Access Token'),
        '#description' => t('Enter your access token string from your twitter app'),
        '#maxlength' => '50',
        '#default_value' => isset($default_value['twitter_access_token']) ? $default_value['twitter_access_token'] : ''
    );
    $unikue_twitter_form['twitter_access_token_secret'] = array(
        '#type' => 'textfield',
        '#title' => t('Access Token Secret'),
        '#description' => t('Enter your access token secret string from your twitter app'),
        '#maxlength' => '50',
        '#default_value' => isset($default_value['twitter_access_token_secret']) ? $default_value['twitter_access_token_secret'] : ''
    );
    $brt_data['unikue_twitter'] = array(
        'config'            => array(
            'title' => t('Unikue Twitter'),
            'description' => 'Create a simple blocks that display your Twitter feed',
            'url' => 'unikue-twitter'
        ),
        'form'              => $unikue_twitter_form,
    );
    /////////////////////////////// Flickr ///////////////////////////////
    $unikue_flickr_form = array(
        'description' => array(
            '#type' => 'textfield',
            '#title' => 'Block description',
            '#description' =>'A brief description of your block. Used on the Blocks administration page.',
            '#required' => true,
            '#default_value' => isset($default_value['description']) ? $default_value['description'] : ''
        ),
    );
    $unikue_flickr_form['flickr_id'] = array(
        '#type'             => 'textfield',
        '#title'            =>  t('Flickr Id'),
        '#size'             => '15',
        '#required'         => true,
        '#default_value' => isset($default_value['flickr_id']) ? $default_value['flickr_id'] : ''
    );
    $unikue_flickr_form['flickr_num'] = array(
        '#type'             => 'textfield',
        '#title'            => t('Flickr Images Number'),
        '#size'             => '5',
        '#default_value' => isset($default_value['flickr_num']) ? $default_value['flickr_num'] : ''
    );
    $brt_data['unikue_flickr'] = array(
        'config'            => array(
            'title' => t('Unikue Flickr'),
            'description' => 'Create a simple blocks that display your Flickr images',
            'url' => 'unikue-flickr'
        ),
        'form'              => $unikue_flickr_form,

    );
    /////////////////////////////// Instagram /////////////////////////////

    $unikue_instagram_form = array(
        'description' => array(
            '#type' => 'textfield',
            '#title' => 'Block description',
            '#description' =>'A brief description of your block. Used on the Blocks administration page.',
            '#required' => true,
            '#default_value' => isset($default_value['description']) ? $default_value['description'] : ''
        ),
    );
    $unikue_instagram_form['user_id'] = array(
        '#type' => 'textfield',
        '#title' => t('User Id'),
        '#description' => t('Your Unikue Instagram user id. Eg. 460786510'),
        '#default_value' => isset($default_value['user_id']) ? $default_value['user_id'] : ''
    );

    $unikue_instagram_form['access_token'] = array(
        '#type' => 'textfield',
        '#title' => t('Access Token'),
        '#description' => t('Your Instagram access token. Eg. 460786509.ab103e5.a54b6834494643588d4217ee986384a8'),
        '#default_value' => isset($default_value['access_token']) ? $default_value['access_token'] : ''
    );

    $unikue_instagram_form['count'] = array(
        '#type' => 'textfield',
        '#title' => t('Number of images to display.'),
        '#default_value' => isset($default_value['count']) ? $default_value['count'] : ''
    );

    $unikue_instagram_form['width'] = array(
        '#type' => 'textfield',
        '#title' => t('Image width in pixels.'),
        '#default_value' => isset($default_value['width']) ? $default_value['width'] : ''
    );

    $unikue_instagram_form['height'] = array(
        '#type' => 'textfield',
        '#title' => t('Image height in pixels.'),
        '#default_value' => isset($default_value['height']) ? $default_value['height'] : ''
    );

    $image_options = array(
        'thumbnail' => t('Thumbnail Preview'),
        'low_resolution' => t('Low Resolution'),
        'standard_resolution' => t('Standard Resolution'),
    );

    $unikue_instagram_form['img_resolution'] = array(
        '#type' => 'select',
        '#title' => t('Image resolution'),
        '#description' => t('Choose the quality of the images you would like to display.'),
        '#options' => $image_options,
        '#default_value' => isset($default_value['img_resolution']) ? $default_value['img_resolution'] : ''
    );
    $brt_data['unikue_instagram'] = array(
        'config'            => array(
            'title'         => t('Unikue Instagram'),
            'description'   => t('Create a simple blocks that display your Instagram images'),
            'url'           => 'unikue-instagram'),
        'form'              => $unikue_instagram_form,
        'css'               => array(
            BRT_BLOCK_PATH . '/css/unikue_instagram/instagram-block.css',
        )
    );

    ///////////////////////////////  Pinterest /////////////////////////////
    $pinterest_form = array(
        'description' => array(
            '#type' => 'textfield',
            '#title' => 'Block description',
            '#description' =>'A brief description of your block. Used on the Blocks administration page.',
            '#required' => true,
        ),
        '#default_value' => isset($default_value['description']) ? $default_value['description'] : ''
    );
    $pinterest_form['pinterest_profile_link'] = array(
        '#type'             => 'textfield',
        '#title'            => t('Pinterest Profile Link'),
        '#description'      => t('e/g: http://www.pinterest.com/pin/99360735500167749/'),
        '#default_value' => isset($default_value['pinterest_profile_link']) ? $default_value['pinterest_profile_link'] : ''
    );
    $brt_data['unikue_pinterest'] = array(
        'config'            => array(
            'title'         => t('Unikue Pinterest'),
            'description'   => t('Create a simple blocks that display your Pinterest images'),
            'url'           => 'unikue-pinterest'
        ),
        'form'              => $pinterest_form
    );

    ///////////////////////////////  Video Widget /////////////////////////////
    $video_form = array(
        'description' => array(
            '#type' => 'textfield',
            '#title' => 'Block description',
            '#description' =>'A brief description of your block. Used on the Blocks administration page.',
            '#required' => true,
            '#default_value' => isset($default_value['description']) ? $default_value['description'] : ''
        ),
    );
    if(module_exists('media')) {
        $video_form['video_media'] = array(
            '#type' => 'media',
            '#tree' => TRUE,
            '#title' => t('Select your video through media'),
            '#description'  => '',
            '#media_options' => array(
                'global' => array(
                    'types' => array(
                        'video' => 'video'
                    ),
                    'schemes' => array(
                        'public' => 'public',
                    ),
                    'file_directory' => 'media',
                    'file_extensions' => 'mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm',
                    'uri_scheme' => 'public',
                ),
            ),
            '#default_value' => array('fid' => (isset($default_value['video_media']['fid']) ? $default_value['video_media']['fid'] : ''))
        );
    }
    $brt_data['unikue_video'] = array(
        'config'            => array(
            'title'         => t('Unikue Video Widget'),
            'description'   => t('Unikue Drupal Theme unique block. You can insert youtube,vimeo,... videos from gallery, web to make a simple video widget')
        ),
        'form'              => $video_form,
    );


     ///////////////////////////////  Header Block /////////////////////////////
    $header_form = array(
        'description' => array(
            '#type' => 'textfield',
            '#title' => 'Block description',
            '#description' =>'A brief description of your block. Used on the Blocks administration page.',
            '#required' => true,
            '#default_value' => isset($default_value['description']) ? $default_value['description'] : '',
        ),
    );

    /*$header_form['header_height'] = array(
        '#type'         => 'textfield',
        '#title'        => 'Header Height',
        '#field_suffix' => ' (px)',
        '#element_validate' => array('element_validate_integer_positive'),
        '#default_value'    => isset($default_value['header_height']) ? $default_value['header_height'] : 600,
        '#states'       => array(
            'visible'   => array(
                ':input[name="header_type"]' => array('value' => 'home-fixheight')
            )
        )
    );*/
    // HEADER BACKGROUND
    $header_form['header_background'] = array(
        '#type'         => 'fieldset',
        '#title'        => t('Header Background'),
        '#collapsible'  => TRUE,
        '#collapsed'    => FALSE
    );

    _build_form_background_settings($header_form['header_background'],'header_bg','Header Background',$default_value);



    // HEADER CONTENT
    $header_form['header_content'] = array(
        '#type'         => 'fieldset',
        '#title'        => t('Header Content'),
        '#collapsible'  => TRUE,
        '#collapsed'    => FALSE
    );
    $header_form['header_content']['first_text'] = array(
        '#type'         => 'textfield',
        '#title'        => t('First Text'),
        '#default_value'    => isset($default_value['first_text']) ? $default_value['first_text'] : 'A template for design agencies - photographer&nbsp;- business and corporate'
    );
    $header_form['header_content']['enable_line'] = array(
        '#type'         => 'checkbox',
        '#title'        => t('Enable line'),
        '#default_value'    => isset($default_value['enable_line']) ? $default_value['enable_line'] : 1,
    );
    $content_json_default = isset($default_value['hd_bg_slide_content_us_data']) ? $default_value['hd_bg_slide_content_us_data'] : '';

    $header_form['header_content']['hd_bg_slide_content_us_wrapper'] = array(
        '#type'     => 'fieldset',
        '#title'    => 'Content Slide',
        '#prefix'       => '<div id="header-bg-slide-content" class="us-wrapper unlimited-settings">
                                <div class="us-add-button-wrap">
                                    <a href="#" class="us-add-button button edit">Add More</a>
                                </div>',
        '#suffix'       => '</div>'
    );
    $header_form['header_content']['hd_bg_slide_content_us_wrapper']['hd_slide_content_autoplay'] = array(
        '#type'         => 'checkbox',
        '#title'        => t('Autoplay'),
        '#default_value'    => isset($default_value['hd_slide_content_autoplay']) ? $default_value['hd_slide_content_autoplay'] : 1
    );
    $header_form['header_content']['hd_bg_slide_content_us_wrapper']['hd_slide_content_loop'] = array(
        '#type'         => 'checkbox',
        '#title'        => t('Loop'),
        '#default_value'    => isset($default_value['hd_slide_content_loop']) ? $default_value['hd_slide_content_loop'] : 1
    );
    $header_form['header_content']['hd_bg_slide_content_us_wrapper']['hd_slide_content_delay'] = array(
        '#type'         => 'textfield',
        '#title'        => t('Slide Delay'),
        '#element_validate' => array('element_validate_integer_positive'),
        '#default_value'    => isset($default_value['hd_slide_content_delay']) ? $default_value['hd_slide_content_delay'] : 6000
    );

    $header_form['header_content']['hd_bg_slide_content_us_wrapper']['hd_slide_content_animation_duration'] = array(
        '#type'         => 'textfield',
        '#title'        => t('Animation Duration'),
        '#element_validate' => array('element_validate_integer_positive'),
        '#default_value'    => isset($default_value['hd_slide_content_animation_duration']) ? $default_value['hd_slide_content_animation_duration'] : 800
    );

    $header_form['header_content']['hd_bg_slide_content_us_wrapper']['hd_bg_slide_content_us_form'] = array(
        '#markup'       => theme('us__header_slide_content', array()),
    );
    $header_form['header_content']['hd_bg_slide_content_us_wrapper']['hd_bg_slide_content_us_data'] = array(
        '#type'         => 'hidden',
        '#attributes'   => array(
            'class'     => array('us-hidden-value')
        ),
        '#default_value'    => $content_json_default
    );
    $header_form['header_content']['button_text'] = array(
        '#type'         => 'textfield',
        '#title'        => t('Button Text'),
        '#default_value'    => isset($default_value['button_text']) ? $default_value['button_text'] : 'Tell me more'
    );
    $header_form['header_content']['button_link'] = array(
        '#type'         => 'textfield',
        '#title'        => t('Button Link'),
        '#default_value'    => isset($default_value['button_link']) ? $default_value['button_link'] : '#about'
    );
    $brt_data['unikue_header'] = array(
        'config'            => array(
            'title'         => t('Unikue Header'),
            'description'   => t('Build your own Header with image, slider, video background and unique content')
        ),
        'form'              => $header_form,
    );


  
/////////////////////////////////////////////////////////////////////////
    ///////////////////////////////  Map Block /////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    $map_form = array(
        'description' => array(
            '#type' => 'textfield',
            '#title' => 'Block description',
            '#description' => 'A brief description of your block. Used on the Blocks administration page.',
            '#required' => TRUE,
            '#default_value' => isset($default_value['description']) ? $default_value['description'] : '',
        ),
    );

    $map_form['map_settings'] = array(
        '#type' => 'fieldset',
        '#title'    => 'Map Settings',
        '#collapsible'  => TRUE,
        '#collapsed'    => FALSE
    );
    $map_form['map_settings']['show_map_button_text'] = array(
        '#type' => 'textfield',
        '#title'    => t('Show Map Button Text'),
        '#description'  => '',
        '#default_value'    => isset($default_value['show_map_button_text']) ? $default_value['show_map_button_text'] : 'Locate Us On Map Now'
    );

    $map_form['map_settings']['map_latlng'] = array(
        '#type' => 'textfield',
        '#title'    => t('Map Latitude'),
        '#description'  => '',
        '#default_value'    => isset($default_value['map_latlng']) ? $default_value['map_latlng'] : '51.511214,-0.119824'
    );
    $map_form['map_settings']['map_zoom'] = array(
        '#type' => 'select',
        '#title'    => t('Map Zoom'),
        '#options'  => array(
            '11'    => '11',
            '12'    => '12',
            '13'    => '13',
            '14'    => '14',
            '15'    => '15',
            '16'    => '16',
            '17'    => '17',
            '18'    => '18',
            '19'    => '19',
            '20'    => '20',
            '21'    => '21',
            '22'    => '22',
            '23'    => '23',
            '24'    => '24',
            '25'    => '25',
            '26'    => '26',
            '27'    => '27',
            '28'    => '28',
            '29'    => '29',
            '30'    => '30',
        ),
        '#description'  => '',
        '#default_value'    => isset($default_value['map_zoom']) ? $default_value['map_zoom'] : 14
    );
    $map_form['map_settings']['map_type'] = array(
        '#type' => 'select',
        '#title'    => t('Map Types'),
        '#options'  => array(
            'roadmap'    => 'ROADMAP',
            'sateline'    => 'SATELLITE',
            'hybrid'    => 'HYBRID',
            'terrain'    => 'TERRAIN',
        ),
        '#description'  => '',
        '#default_value'    => isset($default_value['map_type']) ? $default_value['map_type'] : 'ROADMAP'
    );

    $brt_data['unikue_map'] = array(
        'config' => array(
            'title' => t('Unikue Map Block.'),
            'description' => t('Unikue Drupal Theme unique block. Show google map location'),
        ),
        'form' => $map_form,
    );
    return $brt_data;
}
function brt_block_icon_default_dialog() {

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