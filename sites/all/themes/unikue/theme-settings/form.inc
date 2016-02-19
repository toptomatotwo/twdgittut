<?php

global $base_url;
/**
 * Contain functions generate some specify form for theme-settings
 */
/**
 * Build form upload file via media or form
 * $machine_name: unique name you choose for this form
 */
function _build_form_upload_file(&$form, $machine_name, $title) {
    global $base_url;
    if(module_exists('media')) {
        $form[$machine_name.'_media_wrapper'] = array(
            '#type' => 'container',
            '#attributes'   => array(
                'class'     => array('brt-media-wrapper')
            ),
            '#prefix'       => '<div class="form-group">',
            '#suffix'       => '</div>'
        );

        $media_file = new stdClass();
        $media_file->url = '';
        $media_file->fid = '';
        $media_file->name = '';

        $media_file_hidden_value = theme_get_setting($machine_name.'_media_file');

        if(!empty($media_file_hidden_value)) {
            $media_file = json_decode($media_file_hidden_value);
        }

        $form[$machine_name.'_media_wrapper'][$machine_name.'_upload_media'] = array(
            '#markup'       => '
                    <div class="form-wrapper mb-20">
                        <div class="formRow"><label>Upload '.$title.'</label>
                            <div class="formRight">
                                <div class="form-elements">
                                    <div class="preview">
                                        <img class="img-preview" src="'.(!empty($media_file->url) ? $media_file->url : $base_url.'/'.THEME_PATH.'/theme-settings/img/no_image.png').'" alt="">
                                        <p class="img-name">'.$media_file->name.'</p>
                                    </div>
                                    <a class="media-select-button button launcher element-hidden wButton blueB brt-button" href="#">'.t('Select').'</a>
                                    <a class="media-remove-button button remove element-hidden wButton redB brt-button" href="#">'.t('Remove').'</a>
                                </div>
                            </div>
                        </div>
                    </div>'
        );
        $form[$machine_name.'_media_wrapper'][$machine_name.'_media_file'] = array(
            '#type'         => 'hidden',
            '#default_value' => theme_get_setting($machine_name.'_media_file'),
            '#attributes'       =>  array(
                'class'         => array('media-hidden-value')
            )
        );
    } else {
        $form_file_hidden_value = theme_get_setting($machine_name.'_form_file');

        if(!empty($form_file_hidden_value)) {
            $form_file_url = file_create_url("public://{$form_file_hidden_value}");
        } else {
            $form_file_url = $base_url.'/'.THEME_PATH.'/theme-settings/img/no_image.png';
        }
        $form[$machine_name.'_file_wrapper'] = array(
            '#type' => 'container',
            '#attributes'   => array(
                'class'     => array('brt-file-wrapper')
            ),
            '#prefix'       => '<div class="form-group">',
            '#suffix'       => '</div>'
        );
        $form[$machine_name.'_file_wrapper'][$machine_name.'_upload_preview'] = array(
            '#markup'       => '
                    <div class="form-wrapper mb-20">
                        <div class="formRow"><label>Upload '.$title.'</label>
                            <div class="formRight">
                                <div class="form-elements">
                                    <div class="preview">
                                        <img class="img-preview" src="'.(!empty($form_file_url) ? $form_file_url : $base_url.'/'.THEME_PATH.'/theme-settings/img/no_image.png').'" alt="">
                                        <p class="img-name">'.$form_file_hidden_value.'</p>
                                    </div>
                                    <button class="brt-file-select-button button launcher wButton blueB brt-button">'.t('Select').'</button>
                                    <button class="brt-file-remove-button button remove wButton redB brt-button">'.t('Remove').'</button>
                                </div>
                            </div>
                        </div>
                    </div>'
        );
        $form[$machine_name.'_file_wrapper'][$machine_name.'_upload_file'] = array(
            '#type'         => 'file',
            '#prefix'       => '<div class="brt-form-file-upload">',
            '#suffix'       => '</div>'
        );
        $form[$machine_name.'_file_wrapper'][$machine_name.'_form_file'] = array(
            '#type'         => 'hidden',
            '#default_value' => theme_get_setting($machine_name.'_form_file'),
            '#attributes'       =>  array(
                'class'         => array('file-hidden-value')
            )
        );
    }
}
/**
 * $machine_name: your unique name to create form
 * Contain background image, color, parallax setings, extra css settings, overlay (color, opacity).
 */
function _build_form_background_settings(&$form, $machine_name, $title) {
    global $base_url;
    $form[$machine_name.'_source'] = array(
        '#type'             => 'fieldset',
        '#prefix'           => '<div class="widget sub-widget">
                                <div class="title">
                                    <img src="'.$base_url.'/'.THEME_PATH.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                                    <h6>'.$title.' Background Source</h6>
                                </div>
                            ',
        '#suffix'           => '</div>',
    );
    $form[$machine_name.'_source'][$machine_name.'_type'] = array(
        '#type'         => 'select',
        '#default_value' => theme_get_setting($machine_name.'_type'),
        '#options'      => array(
            'image'             => t('Image'),
            'color'             => t('Color'),
        ),
        '#attributes'   => array(
            'class'     => array('select')
        ),
        '#prefix'   =>  '<div class="formRow"><label>Select Background Type</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',

    );
    // BACKGROUND COLORPICKER
    $form[$machine_name.'_source'][$machine_name.'_color'] = array(
        '#type' => 'container',
        '#states'       => array(
            'visible'   => array(
                ':input[name="'.$machine_name.'_type"]'   => array('value'  => 'color')
            )
        )
    );
    $form[$machine_name.'_source'][$machine_name.'_color'][$machine_name.'_colorpicker'] = array(
        '#type'                 => 'textfield',
        '#prefix'               =>  '<div class="formRow"><label>Background Color</label>',
        '#suffix'               => '</div>',
        '#field_prefix'         => '<div class="formRight">',
        '#field_suffix'         => '</div>',
        '#default_value'        => theme_get_setting($machine_name.'_colorpicker'),
        '#attributes'           => array(
            'class'             =>  array('form-colorpicker')
        ),
    );

    // BACKGROUND SELECT IMAGE
    $form[$machine_name.'_source'][$machine_name.'_image'] = array(
        '#type' => 'container',
        '#states'       => array(
            'visible'   => array(
                ':input[name="'.$machine_name.'_type"]' => array('value' => 'image')
            )
        )
    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_image_enable_parallax'] = array(
        '#type'             => 'checkbox',
        '#attributes'   => array(
            'class' => array('input-checkbox')
        ),
        '#default_value' => theme_get_setting($machine_name.'_image_enable_parallax'),
        '#prefix'   =>  '<div class="formRow"><label>Enable Parallax Effect</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_image_parallax'] = array(
        '#type'             => 'container',
        '#states'           => array(
            'visible'       => array(
                ':input[name="'.$machine_name.'_image_enable_parallax"]'  => array('checked' => TRUE)
            )
        ),
        '#prefix'       => '',
        '#suffix'       => '',
    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_image_parallax'][$machine_name.'_img_pr_xpos'] = array(
        '#type' 					=> 'textfield',
        '#default_value' 	        =>  theme_get_setting($machine_name.'_img_pr_xpos'),
        '#attributes'               => array(
            'class'                 => array('input-border small')
        ),
        '#prefix'   =>  '<div class="widget sub-widget">
                                <div class="title">
                                    <img src="'.$base_url.'/'.THEME_PATH.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                                    <h6>Parallax Settings</h6>
                                </div>
                                <div class="formRow"><label>X-Position</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_image_parallax'][$machine_name.'_img_pr_speed'] = array(
        '#type'          => 'select',
        '#default_value' => theme_get_setting($machine_name.'_img_pr_speed'),
        '#options'      => array(
            '0.1'             => '0.1',
            '0.2'             => '0.2',
            '0.3'             => '0.3',
            '0.4'             => '0.4',
            '0.5'             => '0.5',
            '0.6'             => '0.6',
            '0.7'             => '0.7',
            '0.8'             => '0.8',
            '0.9'             => '0.9',
        ),
        '#attributes'   => array(
            'class'     => array('select')
        ),
        '#prefix'   =>  '<div class="formRow"><label>SpeedFactor</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',

    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_image_parallax'][$machine_name.'_img_pr_outerheight'] = array(
        '#type'          => 'select',
        '#default_value' => theme_get_setting($machine_name.'_img_pr_outerheight'),
        '#options'      => array(
            1             => 'true',
            0             => 'false',
        ),
        '#attributes'   => array(
            'class'     => array('select')
        ),
        '#prefix'   =>  '<div class="formRow"><label>OuterHeight</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div></div>',
    );

    _build_form_upload_file($form[$machine_name.'_source'][$machine_name.'_image'],$machine_name, $title);

    $form[$machine_name.'_extra_settings'] = array(
        '#type'         => 'container',
        '#states'           => array(
            'invisible'       => array(
                ':input[name="'.$machine_name.'_image_enable_parallax"]'   => array("checked"  => TRUE)
            )
        )
    );
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'] = array(
        '#type'         => 'fieldset',
        '#prefix'       => '<div class="widget sub-widget">
                                <div class="title">
                                    <img src="'.$base_url.'/'.THEME_PATH.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                                    <h6>'.$title.' Background Extra Settings</h6>
                                </div>',
        '#suffix'       => '</div>',

    );

    // background repeat
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'][$machine_name.'_image_repeat'] = array(
        '#type' => 'select',
        '#options' => array(
            'no-repeat' => t('No repeat'),
            'repeat' => t('Repeat'),
            'repeat-x' => t('Repeat X'),
            'repeat-y' => t('Repeat Y'),
        ),
        '#default_value' => theme_get_setting($machine_name.'_image_repeat'),
        '#attributes'   => array(
            'class'     => array('select')
        ),
        '#prefix'   =>  '<div class="formRow"><label>Repeat</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',

    );

    // background position
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'][$machine_name.'_image_position'] = array(
        '#type' => 'select',
        '#options' => array(
            'center center' => t('Center Center'),
            'left top' => t('Left Top'),
            'left center' => t('Left Center'),
            'left bottom' => t('Left Bottom'),
            'center top' => t('Center Top'),
            'center bottom' => t('Center Bottom'),
            'right top' => t('Right Top'),
            'right center' => t('Right Center'),
            'right bottom' => t('Right Bottom'),
        ),
        '#default_value' => theme_get_setting($machine_name.'_image_position'),
        '#attributes'   => array(
            'class'     => array('select')
        ),
        '#prefix'   =>  '<div class="formRow"><label>Position</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );

    // background attachment
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'][$machine_name.'_image_attachment'] = array(
        '#type' => 'select',
        '#options' => array(
            'fixed' => t('Fixed'),
            'scroll' => t('Scroll'),
        ),
        '#default_value' => theme_get_setting($machine_name.'_image_attachment'),
        '#attributes'   => array(
            'class'     => array('select')
        ),
        '#prefix'   =>  '<div class="formRow"><label>Attachment</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',

    );
    // OVERLAY SETTINGS
    $form[$machine_name.'_overlay'] = array(
        '#type'         => 'fieldset',
        '#prefix'       => '<div class="widget sub-widget">
                        <div class="title">
                            <img src="'.$base_url.'/'.THEME_PATH.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                            <h6>'.$title.' Background Overlay Settings</h6>
                        </div>
                        ',
        '#suffix'       => '</div>',
    );
    $form[$machine_name.'_overlay'][$machine_name.'_enable_overlay'] = array(
        '#type'             => 'checkbox',
        '#attributes'   => array(
            'class' => array('input-checkbox')
        ),
        '#default_value' => theme_get_setting($machine_name.'_enable_overlay'),
        '#prefix'   =>  '<div class="formRow"><label>Enable Overlay</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );
    $form[$machine_name.'_overlay'][$machine_name.'_overlay_settings'] = array(
        '#type'                 => 'container',
        '#states'               => array(
            'visible'           => array(
                ':input[name="'.$machine_name.'_enable_overlay"]'   => array('checked'  => TRUE)
            )
        )
    );
    $form[$machine_name.'_overlay'][$machine_name.'_overlay_settings'][$machine_name.'_overlay_colorpicker'] = array(
        '#type'                 => 'textfield',
        '#default_value'        => theme_get_setting($machine_name.'_overlay_colorpicker'),
        '#attributes'           => array(
            'class'             =>  array('form-colorpicker')
        ),
        '#prefix'   =>  '<div class="formRow"><label>Overlay Color</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',

    );
    $form[$machine_name.'_overlay'][$machine_name.'_overlay_settings'][$machine_name.'_overlay_opacity'] = array(
        '#type'                     => 'textfield',
        '#attributes'               => array(
            'class'                 => array('input-border small slider-range'),
            'data-max'              => 100,
            'data-min'              => 0,
            'data-divine'           => 100,
            'data-value'            => theme_get_setting($machine_name.'_overlay_opacity')
        ),
        '#default_value'    => theme_get_setting($machine_name.'_overlay_opacity'),
        '#prefix'   =>  '<div class="formRow"><label>Overlay Opacity</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight form-slider-range">',
        '#field_suffix' => '</div>',
    );

}
/**
 * Path/pages Options for some settings
 */
function _build_form_page_options (&$form,$machine_name,$title) {
    global $base_url;

    $form[$machine_name.'_page_options'] = array(
        '#type'             => 'fieldset',
        '#prefix' => '     <div class="widget">
                        <div class="title">
                            <img src="'.$base_url.'/'.THEME_PATH.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                        </div>
                        ',
        '#suffix'       => '</div>',
    );
    $form[$machine_name.'_page_options']['enable_'.$machine_name.'_page_options'] = array(
        '#type'             => 'checkbox',
        '#prefix'   =>  '<div class="formRow"><label>Enable '.$title.' Options</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
        '#default_value'    => theme_get_setting('enable_'.$machine_name.'_page_options'),
        '#tree' => FALSE,
        '#description' => t('If you using "Delta & Context" modules to apply theme settings for specific paths or other condition, please uncheck this option')
    );
    $form[$machine_name.'_page_options'][$machine_name.'_options'] = array(
        '#type'         => 'container',
        '#states'       => array(
            'visible'   => array(
                ':input[name=enable_'.$machine_name.'_page_options]' => array('checked' => TRUE)
            )
        )
    );
    $form[$machine_name.'_page_options'][$machine_name.'_options'][$machine_name.'_path_options'] = array(
        '#type'             => 'radios',
        '#options'          => array(
            'all_except'    => t('All pages except those listed'),
            'only_listed'   => t('Only the listed pages')
        ),
        '#default_value'    => theme_get_setting($machine_name.'_path_options') ? theme_get_setting($machine_name.'_path_options') : 'all_except',
        '#prefix'   =>  '<div class="formRow"><label'.$title.' Options</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );
    $form[$machine_name.'_page_options'][$machine_name.'_options'][$machine_name.'_path_list'] = array(
        '#type'             => 'textarea',
        '#default_value'    => theme_get_setting($machine_name.'_path_list'),
        '#prefix'   =>  '<div class="formRow">',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
        '#attributes'           => array(
            'class'             => array('input-border')
        ),
        '#description'       => t('Specify pages by using their paths. Enter one path per line. The "*" character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. <front> is the front page.')
    );

}