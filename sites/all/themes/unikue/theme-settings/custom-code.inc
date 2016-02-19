<?php

/**
 * @file
 * Theme settings .
 */

function unikue_code_settings(&$form, &$form_state) {
    global $base_url;
    $theme_path = drupal_get_path('theme','unikue');
    $form['unikue_settings']['code'] = array(
        '#type' 					=> 'fieldset',
        '#weight' 				=> 0,
        '#prefix'  				=> '<div id="sf-code"><div class="widget">
                        <div class="title">
                            <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                            <h6>Custom Code</h6>
                        </div>',
        '#suffix'        => '</div></div><!-- / #sf-custom-code -->',
    );

    $form['unikue_settings']['code']['header_code'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#rows' => 10,
        '#default_value' => theme_get_setting('header_code','unikue'),
        '#attributes'           => array(
            'class'             => array('input-border big')
        ),
        '#prefix'   =>  '<div class="formRow"><label>The following code will be added in the &lt;head&gt; tag. Useful if you want to add additional script such as CSS or JS</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );

    $form['unikue_settings']['code']['footer_code'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#rows' => 10,
        '#default_value' => theme_get_setting('footer_code','unikue'),
        '#attributes'           => array(
            'class'             => array('input-border big')
        ),
        '#prefix'   =>  '<div class="formRow"><label>The following code will be added before the &lt;/body&gt; tag.</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );

    $form['unikue_settings']['code']['custom_css'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#rows' => 10,
        '#default_value' => theme_get_setting('custom_css','unikue'),
        '#attributes'           => array(
            'class'             => array('input-border big')
        ),
        '#prefix'   =>  '<div class="formRow"><label>Insert custom CSS code in here (without &lt;/style&gt; tag). This overrides any other stylesheets. eg: a.button{color:green}</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );
}