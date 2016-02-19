<?php
/**
 * Contain functions generate some specify form for md_block module
 */
/**
 * Build form upload file via media or form
 * $machine_name: unique name you choose for this form
 */
function _brt_module_build_form_upload_file(&$form, $machine_name, $title, $default_value) {
    global $base_url;
    if(module_exists('media')) {
        $form[$machine_name.'_media_wrapper'] = array(
            '#type' => 'container',
            '#attributes'   => array(
                'class'     => array('md-media-wrapper')
            ),
            '#prefix'       => '<div class="form-group">',
            '#suffix'       => '</div>'
        );

        $media_file = new stdClass();
        $media_file->url = '';
        $media_file->fid = '';
        $media_file->name = '';

        $media_file_hidden_value = isset($default_value[$machine_name.'_media_file']) ? $default_value[$machine_name.'_media_file'] : '';

        if(!empty($media_file_hidden_value)) {
            $media_file = json_decode($media_file_hidden_value);
        }

        $form[$machine_name.'_media_wrapper'][$machine_name.'_upload_media'] = array(
            '#markup'       => '
                        <label class="media-title">Upload '.$title.'</label>
                        <div class="form-wrapper mb-20">
                            <div class="formRow">
                                <div class="formRight">
                                    <div class="form-elements">
                                        <div class="preview">
                                            <img class="img-preview" src="'.(!empty($media_file->url) ? $media_file->url : $base_url.'/'.BRT_MODULE_PATH.'/imgs/no_image.png').'" alt="">
                                            <p class="img-name">'.$media_file->name.'</p>
                                        </div>
                                        <a class="media-select-button button launcher wButton blueB md-button" href="#">'.t('Select').'</a>
                                        <a class="media-remove-button button remove wButton redB md-button" href="#">'.t('Remove').'</a>
                                    </div>
                                </div>
                            </div>
                        </div>'
        );
        $form[$machine_name.'_media_wrapper'][$machine_name.'_media_file'] = array(
            '#type'         => 'hidden',
            '#default_value' => isset($default_value[$machine_name.'_media_file']) ? $default_value[$machine_name.'_media_file'] : '',
            '#attributes'       =>  array(
                'class'         => array('media-hidden-value')
            )
        );
    } else {
        $form_file_hidden_value = isset($default_value[$machine_name.'_form_file']) ? $default_value[$machine_name.'_form_file'] : '';

        if(!empty($form_file_hidden_value)) {
            $form_file_url = file_create_url("public://{$form_file_hidden_value}");
        } else {
            $form_file_url = $base_url.'/'.MD_AMBROSIA_BLOCK_PATH.'/assets/images/no_image.png';
        }
        $form[$machine_name.'_file_wrapper'] = array(
            '#type' => 'container',
            '#attributes'   => array(
                'class'     => array('md-file-wrapper')
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
                                            <img class="img-preview" src="'.(!empty($form_file_url) ? $form_file_url : $base_url.'/'.MD_AMBROSIA_BLOCK_PATH.'/imgs/no_image.png').'" alt="">
                                            <p class="img-name">'.$form_file_hidden_value.'</p>
                                        </div>
                                        <button class="md-file-select-button button launcher wButton blueB md-button">'.t('Select').'</button>
                                        <button class="md-file-remove-button button remove wButton redB md-button">'.t('Remove').'</button>
                                    </div>
                                </div>
                            </div>
                        </div>'
        );
        $form[$machine_name.'_file_wrapper'][$machine_name.'_upload_file'] = array(
            '#type'         => 'file',
            '#prefix'       => '<div class="md-form-file-upload">',
            '#suffix'       => '</div>'
        );
        $form[$machine_name.'_file_wrapper'][$machine_name.'_form_file'] = array(
            '#type'         => 'hidden',
            '#default_value' => isset($default_value[$machine_name.'_form_file']) ? $default_value[$machine_name.'_form_file'] : '',
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
function _brt_module_build_form_background_settings(&$form, $machine_name, $title, $default_value) {
    global $base_url;
    $form[$machine_name.'_source'] = array(
        '#type'             => 'fieldset',
        '#title'            => $title. 'Background Source',
        '#collapsible'      => TRUE,
        '#collapsed'        => FALSE,
    );
    $form[$machine_name.'_source'][$machine_name.'_type'] = array(
        '#type'         => 'select',
        '#title'        => 'Select Background Type',
        '#default_value' => isset($default_value[$machine_name.'_type']) ? $default_value[$machine_name.'_type'] : '',
        '#options'      => array(
            'image'             => t('Image'),
            'color'             => t('Color'),
        ),
        '#attributes'   => array(
            'class'     => array('select')
        ),
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
        '#title'                => 'Background Color',
        '#default_value'        => isset($default_value[$machine_name.'_colorpicker']) ? $default_value[$machine_name.'_colorpicker'] : '',
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
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_enable_parallax_effect'] = array(
        '#type'             => 'checkbox',
        '#title'        => 'Enable Parallax Effect',
        '#attributes'   => array(
            'class' => array('input-checkbox')
        ),
        '#default_value' => isset($default_value[$machine_name.'_enable_parallax_effect']) ? $default_value[$machine_name.'_enable_parallax_effect'] : '',
    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_parallax_effect'] = array(
        '#type'             => 'container',
        '#states'           => array(
            'visible'       => array(
                ':input[name="'.$machine_name.'_enable_parallax_effect"]'  => array('checked' => TRUE)
            )
        ),
        '#prefix'       => '',
        '#suffix'       => '',
    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_parallax_effect'][$machine_name.'_img_pr_xpos'] = array(
        '#type' 					=> 'textfield',
        '#title'                    => 'X-Position',
        '#default_value' 	        =>  isset($default_value[$machine_name.'_img_pr_xpos']) ? $default_value[$machine_name.'_img_pr_xpos'] : '50',
        '#attributes'               => array(
            'class'                 => array('input-border small')
        ),
        '#field_suffix'             => '%',
        '#description'              => 'Eg: 50'
    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_parallax_effect'][$machine_name.'_img_pr_speed'] = array(
        '#type'          => 'select',
        '#title'        => 'SpeedFactor',
        '#default_value' => isset($default_value[$machine_name.'_img_pr_speed']) ? $default_value[$machine_name.'_img_pr_speed'] : '',
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


    );
    $form[$machine_name.'_source'][$machine_name.'_image'][$machine_name.'_parallax_effect'][$machine_name.'_img_pr_outerheight'] = array(
        '#type'          => 'select',
        '#default_value' => isset($default_value[$machine_name.'_img_pr_outerheight']) ? $default_value[$machine_name.'_img_pr_outerheight'] :'',
        '#options'      => array(
            1             => 'true',
            0             => 'false',
        ),
        '#attributes'   => array(
            'class'     => array('select')
        ),
        '#title'        => 'OuterHeight',
    );

    _brt_module_build_form_upload_file($form[$machine_name.'_source'][$machine_name.'_image'],$machine_name, $title, $default_value);

    $form[$machine_name.'_extra_settings'] = array(
        '#type'         => 'container',
        '#states'           => array(
            'visible'   => array(
                ':input[name="'.$machine_name.'_type"]' => array('value'    => 'image')
            )
        )
    );
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'] = array(
        '#type'         => 'fieldset',
        '#title'        => $title.' Background Extra Settings',
        '#collapsible'  => TRUE,
        '#collapsed'    => FALSE
    );

    // background repeat
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'][$machine_name.'_image_repeat'] = array(
        '#type' => 'select',
        '#title'    => 'Repeat',
        '#options' => array(
            'no-repeat' => t('No repeat'),
            'repeat' => t('Repeat'),
            'repeat-x' => t('Repeat X'),
            'repeat-y' => t('Repeat Y'),
        ),
        '#default_value' => isset($default_value[$machine_name.'_image_repeat']) ? $default_value[$machine_name.'_image_repeat'] : '',
        '#attributes'   => array(
            'class'     => array('select')
        ),
    );

    // background position
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'][$machine_name.'_image_position'] = array(
        '#type' => 'select',
        '#title'    => 'Position',
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
        '#default_value' => isset($default_value[$machine_name.'_image_position']) ? $default_value[$machine_name.'_image_position'] : '',
        '#attributes'   => array(
            'class'     => array('select')
        ),
    );

    // background attachment
    $form[$machine_name.'_extra_settings'][$machine_name.'_extra_settings_wrapper'][$machine_name.'_image_attachment'] = array(
        '#type' => 'select',
        '#title'    => 'Attachment',
        '#options' => array(
            'fixed' => t('Fixed'),
            'scroll' => t('Scroll'),
        ),
        '#default_value' => isset($default_value[$machine_name.'_image_attachment']) ? $default_value[$machine_name.'_image_attachment'] : '',
        '#attributes'   => array(
            'class'     => array('select')
        ),
    );
    // OVERLAY SETTINGS
    $form[$machine_name.'_overlay'] = array(
        '#type'         => 'fieldset',
        '#title'        => $title.' Background Overlay Settings',
        '#collapsible'  => TRUE,
        '#collapsed'    => FALSE
    );
    $form[$machine_name.'_overlay'][$machine_name.'_enable_overlay'] = array(
        '#type'             => 'checkbox',
        '#title'        => 'Enable Overlay',
        '#attributes'   => array(
            'class' => array('input-checkbox')
        ),
        '#default_value' => isset($default_value[$machine_name.'_enable_overlay']) ?$default_value[$machine_name.'_enable_overlay'] : 1,
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
        '#title'                => 'Overlay Color',
        '#default_value'        => isset($default_value[$machine_name.'_overlay_colorpicker']) ?$default_value[$machine_name.'_overlay_colorpicker'] : '',
        '#attributes'           => array(
            'class'             =>  array('form-colorpicker')
        ),
    );
    $form[$machine_name.'_overlay'][$machine_name.'_overlay_settings'][$machine_name.'_overlay_opacity'] = array(
        '#type'                     => 'textfield',
        '#title'                    => 'Overlay Opacity',
        '#attributes'               => array(
            'class'                 => array('input-border small slider-range'),
            'data-max'              => 100,
            'data-min'              => 0,
            'data-divine'           => 100,
            'data-value'            => isset($default_value[$machine_name.'_overlay_opacity']) ?$default_value[$machine_name.'_overlay_opacity'] : '',
        ),
        '#default_value'    => isset($default_value[$machine_name.'_overlay_opacity']) ?$default_value[$machine_name.'_overlay_opacity'] : '',
    );

}