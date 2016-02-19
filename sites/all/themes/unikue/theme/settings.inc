<?php
define('CURRENT_THEME',variable_get('theme_default'));
define('THEME_PATH',drupal_get_path('theme','unikue'));
/**
 * @file
 * settings.inc
 */

/**
 * Contains the form for the theme settings.
 *
 * @param array $form
 *   The form array, passed by reference.
 * @param array $form_state
 *   The form state array, passed by reference.
 */
function _unikue_settings_form(&$form, $form_state) {
    global $base_url;

    drupal_add_library('system', 'ui.widget');
    drupal_add_library('system', 'ui.mouse');
    drupal_add_library('system', 'ui.slider');
    drupal_add_library('system', 'ui.sortable');
    drupal_add_library('system', 'ui.tabs');
    drupal_add_library('system', 'ui.dialog');
    drupal_add_library('system', 'ui.slider');

    // Add media browser js
    if(module_exists('media')) {
        static $included;

        if ($included) {
            return;
        }
        $included = TRUE;
        module_load_include('inc', 'media', 'includes/media.browser');
        $javascript = media_browser_js();
        foreach ($javascript as $key => $definitions) {
            foreach ($definitions as $definition) {
                $function = 'drupal_add_' . $key;
                call_user_func_array($function, $definition);
            }
        }
        // Add wysiwyg-specific settings.
        $settings = array('wysiwyg_allowed_attributes' => variable_get('media__wysiwyg_allowed_attributes', array('height', 'width', 'hspace', 'vspace', 'border', 'align', 'style', 'class', 'id', 'usemap', 'data-picture-group', 'data-picture-align')));
        drupal_add_js(array('media' => $settings), 'setting');
    }

    drupal_add_css(THEME_PATH . '/theme-settings/css/reset.css', array('group' => CSS_THEME));
    drupal_add_css(THEME_PATH . '/theme-settings/css/bootstrap.css', array('group' => CSS_THEME));
    drupal_add_css(THEME_PATH . '/theme-settings/css/font-awesome.min.css', array('group' => CSS_THEME));
    drupal_add_css(THEME_PATH . '/theme-settings/css/spectrum.css', array('group' => CSS_THEME));
    drupal_add_css(THEME_PATH . '/theme-settings/css/main.css', array('group' => CSS_THEME));
    drupal_add_css(THEME_PATH . '/theme-settings/css/ui-custom.css', array('group' => CSS_THEME));
    drupal_add_css(THEME_PATH . '/theme-settings/css/drupal-custom.css', array('group' => CSS_THEME));

    drupal_add_js(array('baseUrl' => $base_url),'setting');
    drupal_add_js(THEME_PATH . '/theme-settings/js/jquery.cookie.js');
    drupal_add_js(THEME_PATH . '/theme-settings/js/jquery-migrate-1.2.1.js');
    drupal_add_js(THEME_PATH . '/theme-settings/js/spectrum.js');
    drupal_add_js(THEME_PATH . '/theme-settings/js/jquery.collapsible.min.js');
    drupal_add_js(THEME_PATH . '/theme-settings/js/uniform.js');
    drupal_add_js(THEME_PATH . '/theme-settings/js/unlimited-settings.js');

    drupal_add_js(THEME_PATH . '/theme-settings/js/script.js');

    unikue_include('unikue', 'theme-settings/form.inc');
    unikue_include('unikue', 'theme-settings/general.inc');
    unikue_include('unikue', 'theme-settings/typography.inc');
    unikue_include('unikue', 'theme-settings/menu.inc');
    unikue_include('unikue', 'theme-settings/footer.inc');
    unikue_include('unikue', 'theme-settings/custom-code.inc');
    unikue_include('unikue', 'theme-settings/config.inc');

    drupal_add_js(array('themePath' => $base_url.'/'.THEME_PATH),'setting');
    if(isset($form_id)){
        return;
    }
    unset($form['theme_settings']);
    //hide($form['actions']);
    hide($form['logo']);
    hide($form['favicon']);
    // Make default dialog markup for icon
    icon_default_dialog();
    $form['html_header'] = array(
        '#markup' => '<div id="main-settings">',

    );
    $form['unikue_settings']['html_open'] = array(
        '#markup' => '<!-- Left side content -->
<div id="leftSide">

    <!-- Left navigation -->
    <ul id="menu" class="nav list-unstyled">
        <li class="general"><a href="#sf-general" title=""  class="exp main-tab"><span>General Settings</span><strong>+</strong></a>
            <ul class="sub nav nested-tab list-unstyled">
                <li><a href="#general-settings" class="sub-tab" ">Sites Default Settings</a></li>
                <li><a href="#logo-favicon-webclip" class="sub-tab">Logo, Favicon &amp; Webclip IOS</a></li>
            </ul>
        </li>
        <li class="menu"><a href="#sf-menu" title="" class="main-tab"><span>Menu Settings</span></a></li>
        <li class="footer"><a href="#sf-footer" title="" class="main-tab"><span>Footer Settings</span></a></li>
        <li class="typo"><a href="#sf-typo" title="" class="main-tab"><span>Typography Settings</span></a></li>
        <li class="code"><a href="#sf-code" title="" class="exp main-tab"><span>Code Settings</span></a></li>
        <li class="config"><a href="#sf-config" title="" class="exp main-tab"><span>Backup & Restore Settings</span><strong>+</strong></a>
            <ul class="sub nav nested-tab list-unstyled">
                <li><a class="sub-tab" href="#config-backup" >Backup Theme Settings</a></li>
                <li><a class="sub-tab" href="#config-restore" >Restore Theme Settings</a></li>
            </ul>
        </li>
    </ul>
</div>

<!-- Right side -->
    <div id="rightSide">
        <div class="wrapper">',
        '#weight' => -99,
    );
    unikue_general_settings($form, $form_state);
    unikue_typo_settings($form, $form_state);
    unikue_code_settings($form, $form_state);
    unikue_footer_settings($form, $form_state);
    unikue_menu_settings($form, $form_state);
    unikue_config_settings($form, $form_state);
    $form['unikue_settings']['html_close'] = array(
        '#markup' => '</div>
                    </div>'
    ,
        '#weight'       => 97,
    );
    $form['html_footer'] = array(
        '#markup'   => '</div>',
    );


    $form['actions']['reset']      = array(
        '#type'         => 'submit',
        '#value'        => t('Reset Settings'),
        '#submit'       => array('unikue_reset_settings_submit'),
        '#weight'       => 98,
        '#attributes'   => array(
            'class' => array('wButton redB'),
            'onClick'   => 'return confirm("Are you sure want to reset all settings to default ?")'
        )
    );
    $form['actions']['submit']['#weight'] = 97;
    $form['actions']['submit']['#attributes'] = array(
        'class' => array('wButton blueB'),
    );
    $form['actions']['#prefix'] = '<div id="submit-footer" class="footer">';
    $form['actions']['#suffix'] = '</div>';

    $form['#validate'][] = 'unikue_validate_theme_settings';
    $form['#submit'][] = 'unikue_save_settings_submit';
}

/**
 * Custom validation for unique theme setting
 */
function unikue_validate_theme_settings($form, &$form_state) {

}


/**
 * Final submit handler.
 *
 * Reports what values were finally set.
 */

function unikue_save_settings_submit($form, &$form_state) {
    // Exclude unnecessary elements before saving.
    form_state_values_clean($form_state);
    //Save image file upload via drupal form
    foreach($form_state['values'] as $key => $value) {
        if(strpos($key,'_form_file') !== false) {
            if(isset($form_state['values'][''.str_replace('_form_file','_upload_file',$key).''])) {
                $form_state['values'][$key] = saveImage($form_state['values'][$key],str_replace('_form_file','_upload_file',$key));
            }
        }
    }
    $values = $form_state['values'];
    // Extract the name of the theme from the submitted form values, then remove
    // it from the array so that it is not saved as part of the variable.
    $theme_key = $values['var'];
    unset($values['var']);

    $form_input = $form_state['input'];


    $form_state['#rebuild'] = true;
    cache_clear_all();
}
function saveImage($path, $upload) {
    $validators = array('file_validate_extensions' => array('ico png gif jpg jpeg apng svg'));
    $save_path = $path;
    if($file = file_save_upload($upload,$validators)) {
        if (isset($file)) {
            // File upload was attempted.
            if ($file) {
                $parts = pathinfo($file->filename);
                $destination = 'public://' . $parts['basename'];
                $file->status = FILE_STATUS_PERMANENT;
                if (file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
                    $save_path = $parts['basename'];
                }
            }
            else {
                // File upload failed.
                form_set_error(key($path), t('File could not be uploaded.'));
            }
        } else {
            $save_path = $path;
        }
    } else {
        $save_path = $path;
    }
    return $save_path;
}
/**
 * @param $form
 * @param $form_state
 * Reset all theme settings
 */
function unikue_reset_settings_submit($form, &$form_state){
    $theme_settings = variable_get('theme_'.CURRENT_THEME.'_settings');
    $default_settings = _unikue_theme_default_settings($theme_settings);
    variable_set('theme_'.CURRENT_THEME.'_settings',null);
    variable_set('theme_'.CURRENT_THEME.'_settings',$default_settings);
    drupal_set_message('All settings reset to default');
    cache_clear_all();
}
/**
 * Backup Theme Settings
 */
function unikue_backup_theme_settings() {
    global $theme_key;
    $theme_settings = variable_get('theme_'.CURRENT_THEME.'_settings');
    $current_time = time();
    $cv_datetime = date("Y-m-d",$current_time);
    $backup_file = serialize(base64_encode(drupal_json_encode($theme_settings)));
    $bu_folder = 'public://'.CURRENT_THEME.'_backup';
    if(file_prepare_directory($bu_folder) === false) {
        drupal_mkdir($bu_folder);
    }
    if (file_unmanaged_save_data($backup_file, $bu_folder . '/'.str_replace('_','-',CURRENT_THEME).'-backup-'.$cv_datetime.'-'.$current_time.'.txt', FILE_EXISTS_REPLACE) === FALSE) {
        drupal_set_message(t("Could not create backup file."));
        return;
    } else {
        drupal_set_message(t("Backup Theme Settings Successful!"));
        drupal_set_message(t("Your backup settings is stored in ".file_create_url(''.$bu_folder.'/'.str_replace('_','-',CURRENT_THEME).'-backup-'.$cv_datetime.'-'.$current_time.'.txt').""));
    }
}
/**
 * Restore Theme settings
 */
function unikue_restore_theme_settings($form, &$form_state) {
    $values = $form_state['values'];
    if($values['restore_type'] !=  null) {

        if($values['restore_type'] == 'upload') {
            if($form_state['values']['restore_file_media_upload']['fid'] != 0) {
                $file = file_load($form_state['values']['restore_file_media_upload']['fid']);
                if($file == false) {
                    drupal_set_message(t("Your file upload isn't found, please upload again"),'warning');
                    return;
                }
                if(strpos((string)($file->filename), '*/'.str_replace('_','-',CURRENT_THEME).'-backup/*') !== FALSE) {
                    $file_content = file_get_contents($file->uri);
                    $restore_settings = drupal_json_decode(base64_decode(unserialize($file_content)));
                    if(is_array($restore_settings)) {
                        variable_set('theme_'.CURRENT_THEME.'_settings',array());
                        variable_set('theme_'.CURRENT_THEME.'_settings',$restore_settings);
                        file_delete($file,$force = true);
                        cache_clear_all();
                        drupal_set_message(t('All your theme settings have been restored'));
                    } else {
                        drupal_set_message(t("Your file upload isn't correct, please upload again"),'warning');
                        return;
                    }
                } else {
                    drupal_set_message(t("Your file upload isn't this theme backup types, please upload again"),'warning');
                    return;
                }

            } else {
                drupal_set_message(t('Please choose your file upload'),'error');
                return;
            }
        } else {
            if($values['restore_from_file'] == null) {
                drupal_set_message('Choose your backup file in list or move back up to backup folder','warning');
                return;
            } else {
                if(strpos((string)($values['restore_from_file']), '*/'.str_replace('_','-',CURRENT_THEME).'-backup/*') !== FALSE) {
                    $file_content = file_get_contents("public://".CURRENT_THEME."_backup/{$values['restore_from_file']}");
                    $restore_settings = drupal_json_decode(base64_decode(unserialize($file_content)));
                    if(is_array($restore_settings)) {
                        variable_set('theme_'.CURRENT_THEME.'_settings',array());
                        variable_set('theme_'.CURRENT_THEME.'_settings',$restore_settings);
                        cache_clear_all();
                        drupal_set_message(t('All your theme settings have been restored'));
                    } else {
                        drupal_set_message(t("Your choosen backup file isn't correct, please choose again"),'warning');
                        return;
                    }
                } else {
                    drupal_set_message(t("Your choosen backup file isn't this theme backup types, please choose again"),'warning');
                    return;
                }
            }



        }
    }



    if ($restore_file = file_save_upload('restore_file_simple_upload')) {
        $file_content = file_get_contents($restore_file->uri);
        $restore_settings = drupal_json_decode(base64_decode(unserialize($file_content)));
        variable_set('theme_'.CURRENT_THEME.'_settings',$restore_settings);
        cache_clear_all();
        drupal_set_message(t('All your theme settings have been restored'));
    }
    if(isset($form_state['values']['restore_file_media_upload'])) {

    }

}

/**
 * Default theme settings
 */
function _unikue_theme_default_settings ($theme_settings) {
    $default_settings = array();
    foreach ($theme_settings as $key => $setting) {
        $default_settings[$key] = null;
    }
    $default_settings['toggle_logo'] = 1;
    $default_settings['toggle_name'] = 1;
    $default_settings['toggle_slogan'] = 1;
    $default_settings['toggle_node_user_picture'] = 1;
    $default_settings['toggle_comment_user_picture'] = 1;
    $default_settings['toggle_comment_user_verification'] = 1;
    $default_settings['toggle_fvicon'] = 1;
    $default_settings['toggle_main_menu'] = 1;
    $default_settings['toggle_secondary_menu'] = 1;
    $default_settings['default_logo'] = 1;
    $default_settings['default_favicon'] = 1;
    $default_settings['css3_textarea'] = 0;
    $default_settings['webclip_precomp'] = 1;


    return $default_settings;
}


