<?php

/**
 * @file
 * Theme settings .
 */

function unikue_config_settings(&$form, &$form_state) {
    global $base_url;
    $theme_path = drupal_get_path('theme','unikue');
    $form['unikue_settings']['config'] = array(
        '#type' 					=> 'fieldset',
        '#weight' 				=> 0,
        '#prefix'  				=> '<div id="sf-config">',
        '#suffix'        => '</div><!-- / #sf-config -->',
    );

    $form['unikue_settings']['config']['backup'] = array(
        '#type' => 'fieldset',
        '#prefix' => '     <div class="widget">
                        <div class="title">
                            <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                            <h6>Backup Your Theme settings</h6>
                        </div>
                        ',
        '#suffix'       => '</div>',
    );
    $form['unikue_settings']['config']['backup']['backup_html'] = array(
        '#markup'     => '<div class="title"><h6>You can use button below to backup your current theme settings. Remember save your current settings before backup</h6></div>',
    );
    /*$form['unikue_settings']['config']['backup']['backup_code'] = array(
        '#type'         => 'textarea',
        '#description'        => 'Save your code'
    );*/
    $form['unikue_settings']['config']['backup']['backup_theme_settings'] = array(
        '#type' => 'submit',
        '#value'    => t('Backup'),
        '#submit'   => array('unikue_backup_theme_settings'),
        '#prefix'   =>  '<div class="formRow"><label>Backup All Settings</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );

    $form['unikue_settings']['config']['restore'] = array(
        '#type' => 'fieldset',
        '#prefix' => '     <div class="widget">
                        <div class="title">
                            <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                            <h6>Restore Theme Settings</h6>
                        </div>
                        ',
        '#suffix'       => '</div>',
    );

    $form['unikue_settings']['config']['restore']['restore_type'] = array(
        '#type'                     => 'select',
        '#options'                  => array(
            'upload'                => t('Upload file'),
            'select'                => t('Select list files')
        ),
        '#attributes' => array(
            'class' => array('select'),
        ),
        '#prefix'   =>  '<div class="formRow"><label>Choose type of restore theme settings</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight small">',
        '#field_suffix' => '</div>',
    );
    $form['unikue_settings']['config']['restore']['restore_from_file_upload'] = array(
        '#type'             => 'container',
        '#states'           => array(
            'visible'       => array(
                ':input[name="restore_type"]' => array(
                    'value'     => 'upload'
                )
            )
        ),
    );
    if(module_exists('media')) {
        $form['unikue_settings']['config']['restore']['restore_file_media_wrapper'] = array(
            '#type' => 'container',
            '#attributes'   => array(
                'class'     => array('brt-media-wrapper')
            )
        );
        $restore_file = new stdClass();
        $restore_file->url = '';
        $restore_file->fid = '';
        $restore_file->name = '';

        $restore_file_hidden_value = theme_get_setting('restore_file_media_upload',CURRENT_THEME);

        if(!empty($restore_file_hidden_value)) {
            if(is_array($restore_file_hidden_value) == false) {
                $restore_file = json_decode($restore_file_hidden_value);
            }
        }


        $form['unikue_settings']['config']['restore']['restore_file_media_wrapper']['restore_file_upload_media'] = array(
            '#markup'       => '
                <div class="form-wrapper  mb-20">
                    <div class="formRow"><label>Upload Your Theme Settings Backup File</label>
                        <div class="formRight">
                            <div class="form-elements">
                                <div class="preview">
                                    <img class="img-preview" src="'.(!empty($restore_file->url) ? $restore_file->url : $base_url.'/'.THEME_PATH.'/theme-settings/img/no_image.png').'" alt="">
                                    <p class="img-name">'.$restore_file->name.'</p>
                                </div>
                                <button class="media-select-button button launcher element-hidden wButton blueB md-button">'.t('Select').'</button>
                            </div>
                        </div>
                    </div>
                </div>'
        );
        $form['unikue_settings']['config']['restore']['restore_file_media_wrapper']['restore_file_media_upload'] = array(
            '#type'         => 'hidden',
            '#default_value' => theme_get_setting('restore_file_media_upload','unikue'),
            '#attributes'       =>  array(
                'class'         => array('media-hidden-value')
            )
        );
    } else {
        $form['unikue_settings']['config']['restore']['restore_file_simple_upload'] = array(
            '#type'         => 'file',
            '#prefix'   =>  '<div class="formRow"><label>Upload your backup file to restore theme settings</label>',
            '#suffix'   => '</div>',
            '#field_prefix' => '<div class="formRight">',
            '#field_suffix' => '</div>',
        );
    }
    $bu_folder = 'public://'.CURRENT_THEME.'_backup';
    if(file_prepare_directory($bu_folder) === false) {
        drupal_mkdir($bu_folder);
    }
    $backup_dir = getDirectoryList("public://".CURRENT_THEME."_backup");
    $list_files = array();
    if(!$backup_dir)
        $backup_dir = array();
    foreach($backup_dir as $key => $value) {
        if(strpos((string)($value),''.str_replace('_','-',CURRENT_THEME).'-backup') !== FALSE)
            $list_files[$value] = $value;
    }
    $form['unikue_settings']['config']['restore']['restore_from_file'] = array(
        '#type'             => 'container',
        '#states'           => array(
            'visible'       => array(
                ':input[name="restore_type"]' => array(
                    'value'     => 'select'
                )
            )
        ),
    );
    $form['unikue_settings']['config']['restore']['restore_from_file']['restore_from_file_select'] = array(
        '#type'             => 'select',
        '#options'          => $list_files,
        '#attributes' => array(
            'class' => array('select'),
        ),
        '#prefix'   =>  '<div class="formRow"><label>Choose your file you want to backup (Select list files are stored in "public://unikue_backup" folder)</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );
    /*
    $form['unikue_settings']['config']['restore']['restore_code'] = array(
        '#type' => 'textarea',
        '#title'    => t('Transfer Theme Options Data'),
        '#default_value' => '',
        '#description' => t('You can transfer the saved options data between different installs by copying the text inside the text box. To import data from another install, replace the data in the text box with the one from another install and click "Restore Options".')
    );
    */
    $form['unikue_settings']['config']['restore']['restore_theme_settings'] = array(
        '#type' => 'submit',
        '#value'    => 'Restore',
        '#submit'   => array('unikue_restore_theme_settings'),
        '#prefix'   =>  '<div class="formRow"><label>Restore Settings</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );


}