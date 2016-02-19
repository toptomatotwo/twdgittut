<?php

/**
 * @file
 * Theme settings .
 */

function unikue_menu_settings(&$form, &$form_state) {
    global $base_url;
    $theme_path = drupal_get_path('theme','unikue');
    $form['unikue_settings']['menu'] = array(
        '#type' 			    => 'fieldset',
        '#weight' 				=> -1,
        '#prefix'  				=> '<div id="sf-menu">',
        '#suffix'               => '</div><!-- / #sf-display -->',
    );
    $form['unikue_settings']['menu']['menu_dot'] = array(
        '#type'                 => 'fieldset',
        '#prefix' => ' <div class="widget">
                        <div class="title">
                            <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                            <h6>Dot Navigation</h6>
                        </div>
                        ',
        '#suffix'       => '</div>',
    );
    $form['unikue_settings']['menu']['menu_dot']['enable_dot_navigation'] = array(
        '#type' => 'checkbox',
        '#default_value' => theme_get_setting('enable_dot_navigation'),
        '#prefix'   =>  '<div class="formRow"><label>Enable Dot Navigation</label>',
        '#suffix'   => '</div>',
        '#field_prefix' => '<div class="formRight">',
        '#field_suffix' => '</div>',
    );
    //////////////////////////////////////////// Social ///////////////////////////////////////////////////////
    $form['unikue_settings']['menu']['menu_social'] = array(
        '#type'                 => 'fieldset',
        '#prefix' => ' <div class="widget">
                        <div class="title">
                            <img src="'.$base_url.'/'.$theme_path.'/theme-settings/img/icons/dark/preview.png" alt="" class="titleIcon">
                            <h6>Menu Social</h6>
                        </div>
                        ',
        '#suffix'       => '</div>',
    );
    $form['unikue_settings']['menu']['menu_social']['menu_social_info'] = array(
        '#type' => 'container',
    );
    $js_data_default = '
    [{"name":"form_select","value":"fa|fa-facebook-square"},{"name":"form_input","value":"http://facebook.com"}]';
    $js_data = (theme_get_setting('menu_social_array_hidden') != null) ? theme_get_setting('menu_social_array_hidden') : $js_data_default;

    $array_social = json_decode($js_data,true);
    $array_social = array_chunk($array_social,2);

    $form['unikue_settings']['menu']['menu_social']['menu_social_info']['addmore_button'] = array(
        '#markup' => '<a href="#" class="addmore-button wButton blueB ml15 m10"><span>Add More</span></a>',
    );
    $form['unikue_settings']['menu']['menu_social']['menu_social_info']['wrap_sort_open'] = array(
        '#markup' => '<ul class="wrap-sort">',
    );
    foreach ($array_social as $key => $element) {
        $options_icon = get_option_icon();
        $options_icon_html = '';
        foreach ($options_icon as $group_key => $group_value) {
            foreach ($group_value as $option_key => $option_value) {
                $select = ($option_key == $element[0]['value']) ? 'selected="selected"' : '';
                $options_icon_html .= '<option value="'.$option_key.'" '.$select.'>'.$option_value.'</option>';
            }
        }
        $form['unikue_settings']['menu']['menu_social']['menu_social_info']['menu_social_sort_list'.$key] = array(
            '#markup' => '<li class="draggable-item sortable-item medium">
                            <!-- Button remove -->
                            <a href="#" class="remove-addmore-button">X</a>
                            <!-- Select Icon -->
                            <div class="form-elements input-select">
                                <div class="formRow">
                                    <label for="edit-form-select">Icon</label>
                                    <div class="formRight">
                                        <select data-selectdiv="icon-select-'.$key.'"  name="form_select" class="form-select form-select-icon icon-select-'.$key.'">
                                            '.$options_icon_html.'
                                        </select>
                                    </div>
                                </div>
                            </div>
                            <!-- Input -->
                            <div class="form-elements input-element">
                                <div class="formRow">
                                    <label for="edit-form-input">Link </label>
                                    <div class="formRight">
                                        <input type="text" id="edit-form-input" name="form_input" value="'.$element[1]['value'].'" size="60" maxlength="128" class="form-text">
                                    </div>
                                </div>
                            </div>
                           </li>',
        );
    }
    $form['unikue_settings']['menu']['menu_social']['menu_social_info']['menu_social_wrap_sort_close'] = array(
        '#markup' => '</ul>',
    );
    $form['unikue_settings']['menu']['menu_social']['menu_social_info']['menu_social_array_hidden'] = array(
        '#type'          => 'hidden',
        '#default_value' => $js_data_default,
        '#attributes'    => array(
            'class' => array('addmore-input-hidden'),
        )
    );


}