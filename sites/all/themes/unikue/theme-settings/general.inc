<?php

/**
 * @file
 * Theme settings general.
 */

function unikue_general_settings(&$form, &$form_state) {
    global $base_url;
    $theme_path = drupal_get_path('theme','unikue');
    $form['unikue_settings']['general'] = array(
        '#type' 					=> 'fieldset',
        '#weight' 				=> -5,
        '#prefix'               => '<div id="sf-general">',
        '#suffix'               => '</div>'
    );
    /* 1.	General Settings
    --------------------------------------------------------------------------*/
    $form['unikue_settings']['general']['general_settings'] = array(
        '#type' 					=> 'fieldset',
        '#weight' 				=> -14,
        '#prefix'  				=> '<div id="general-settings" class="">',
        '#suffix'        => '</div><!-- / #general-settings -->',
    );
    $form['unikue_settings']['general']['general_settings']['general_setting_content'] = array(
        '#type' => 'fieldset',
    );
    $themes = list_themes();
    $features = $themes['unikue']->info['features'];
    // Toggle settings
    $toggles = array(
        'logo'                      => t('Logo'),
        'name'                      => t('Site name'),
        'slogan'                    => t('Site slogan'),
        'node_user_picture'         => t('User pictures in posts'),
        'comment_user_picture'      => t('User pictures in comments'),
        'comment_user_verification' => t('User verification status in comments'),
        'main_menu'                 => t('Main menu'),
        'secondary_menu'            => t('Secondary menu'),
    );

    // Some features are not always available
    $disabled = array();
    if (!variable_get('user_pictures', 0)) {
        $disabled['toggle_node_user_picture'] = TRUE;
        $disabled['toggle_comment_user_picture'] = TRUE;
    }
    if (!module_exists('comment')) {
        $disabled['toggle_comment_user_picture'] = TRUE;
        $disabled['toggle_comment_user_verification'] = TRUE;
    }

    $form['unikue_settings']['general']['general_settings']['general_setting_content']['theme_settings'] = array(
        '#type' => 'fieldset',
        '#prefix' => '      <div class="widget widget-setting">
                                <div class="title">
                                    <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                                    <h6>Toggle Display</h6>
                                </div>
                                ',
        '#suffix'       => '</div>',
    );
    foreach ($toggles as $name => $title) {
        if (in_array($name, $features)) {
            $form['unikue_settings']['general']['general_settings']['general_setting_content']['theme_settings']['toggle_' . $name] = array(
                '#type' => 'checkbox',
                '#default_value' => theme_get_setting('toggle_' . $name, 'unikue'),
                '#prefix'   =>  '<div class="formRow"><label>'.$title.'</label>',
                '#suffix'   => '</div>',
                '#field_prefix' => '<div class="formRight">',
                '#field_suffix' => '</div>',
            );
            // Disable checkboxes for features not supported in the current configuration.
            if (isset($disabled['toggle_' . $name])) {
                $form['unikue_settings']['general']['general_settings']['general_setting_content']['theme_settings']['toggle_' . $name]['#disabled'] = TRUE;
            }
        }

    }
    if(in_array('favicon', $features)) {
        $form['unikue_settings']['general']['general_settings']['general_setting_content']['theme_settings']['toggle_fvicon'] = array(
            '#type' => 'checkbox',
            '#default_value' => theme_get_setting('toggle_fvicon' , 'unikue'),
            '#prefix'   =>  '<div class="formRow"><label>Shortcut Favicon</label>',
            '#suffix'   => '</div>',
            '#field_prefix' => '<div class="formRight">',
            '#field_suffix' => '</div>',
        );
    }

    if (!element_children($form['unikue_settings']['general']['general_settings']['general_setting_content']['theme_settings'])) {
        // If there is no element in the theme settings fieldset then do not show
        // it -- but keep it in the form if another module wants to alter.
        $form['unikue_settings']['general']['general_settings']['general_setting_content']['theme_settings']['#access'] = FALSE;
    }

    /* 2.	Logo, Favicon & Webclip
    --------------------------------------------------------------------------*/
    $form['unikue_settings']['general']['logo_fav_webclip'] = array(
        '#type' 					=> 'fieldset',
        '#weight' 				=> -13,
        '#prefix'  				=> '<div id="logo-favicon-webclip" class="">',
        '#suffix'        => '</div><!-- / #general-settings -->',
    );
    /* $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_header'] = array(
        '#markup'  =>  '<div class="sf-content-header">
                             <h3 class="sf-content-title">Logo, Favicon, Webclip Settings</h3>
                             <p class="sf-content-description">You can custom path for logo, favicon and webclip</p>
                        </div><!-- /.sf-content-header -->'
    );*/
    $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content'] = array(
        '#type' => 'fieldset',

    );

    // Logo settings

    $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo'] = array(
        '#type' => 'fieldset',
        '#prefix' => '      <div class="widget">
                                <div class="title">
                                    <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                                    <h6>Logo Settings</h6>
                                </div>
                                ',
        '#suffix'       => '</div>',
        '#weight'   => 1
    );
    $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['default_logo'] = array(
        '#type' => 'checkbox',
        '#prefix'   =>  '<div class="formRow"><label>Use Default Logo</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
        '#default_value' => theme_get_setting('default_logo', 'unikue'),
        '#tree' => FALSE,
    );
    $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings'] = array(
        '#type' => 'container',
        '#states' => array(
            // Hide the logo settings when using the default logo.
            'invisible' => array(
                'input[name="default_logo"]' => array('checked' => TRUE),
            ),
        ),
    );
    $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_normal'] = array(
        '#type'     => 'container',
    );
    _build_form_upload_file($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_normal'],'logo_normal',t('Logo Normal'));
    $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_footer'] = array(
        '#type'     => 'container',
    );
    _build_form_upload_file($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['logo']['settings']['logo_footer'],'logo_footer',t('Logo Footer'));


////////////////////////////////////////// FAVICON ///////////////////////////////////////////////////////////
    if (in_array('favicon', $features)) {
        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon'] = array(
            '#type' => 'fieldset',
            '#prefix' => '      <div class="widget">
                                <div class="title">
                                    <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                                    <h6>Favicon & Webclip Settings</h6>
                                </div>
                                ',
            '#suffix'       => '</div>',
            '#weight'   => 2
        );
        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['default_favicon'] = array(
            '#type' => 'checkbox',
            '#prefix'   =>  '<div class="formRow"><label>Favicon</label>',
            '#suffix'   => '</div>',
            '#field_prefix' => '<div class="formRight">',
            '#field_suffix' => '</div>',
            '#default_value' => theme_get_setting('default_favicon', 'unikue'),
        );
        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['settings'] = array(
            '#type' => 'container',
            '#states' => array(
                // Hide the favicon settings when using the default favicon.
                'invisible' => array(
                    'input[name="default_favicon"]' => array('checked' => TRUE),
                ),
            ),
        );

        _build_form_upload_file($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon']['settings'],'favicon',t('Favicon'));

        // Inject human-friendly values for logo and favicon.
        foreach (array('logo' => 'logo.png', 'favicon' => 'favicon.ico') as $type => $default) {
            if (isset($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content'][$type]['settings'][$type . '_path'])) {
                $element = &$form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content'][$type]['settings'][$type . '_path'];

                // If path is a public:// URI, display the path relative to the files
                // directory; stream wrappers are not end-user friendly.
                $original_path = $element['#default_value'];
                $friendly_path = NULL;
                if (file_uri_scheme($original_path) == 'public') {
                    $friendly_path = file_uri_target($original_path);
                    $element['#default_value'] = $friendly_path;
                }
            }
        }


        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip'] = array(
            '#type' 					=> 'fieldset',
            '#prefix' => '      <div class="widget">
                                <div class="title">
                                    <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                                    <h6>Webclip Settings</h6>
                                </div>
                                ',
            '#suffix'       => '</div>',
            '#weight'   => 3
        );
        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_57x57'] = array(
            '#type'     => 'container'
        );
        _build_form_upload_file($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_57x57'],'ios_57x57',t('IOS 57x57'));

        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_72x72'] = array(
            '#type'     => 'container'
        );
        _build_form_upload_file($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_72x72'],'ios_72x72',t('IOS 72x72'));

        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_114x114'] = array(
            '#type'     => 'container'
        );
        _build_form_upload_file($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_114x114'],'ios_114x114',t('IOS 114x114'));

        $form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_144x144'] = array(
            '#type'     => 'container'
        );
        _build_form_upload_file($form['unikue_settings']['general']['logo_fav_webclip']['logo_fav_webclip_content']['favicon_webclip']['ios_144x144'],'ios_144x144',t('IOS 144x144'));
    }



    /* Hidden input
    --------------------------------------------------------------------------*/
    $form['unikue_settings']['general']['general_settings']['general_setting_content']['savedcolor1'] = array(
        '#type'         	=> 'hidden',
        '#default_value' 	=> theme_get_setting('savedcolor1','unikue'),
        '#attributes' => array(
            'id' => 'savedcolor1',
        ),
    );
}