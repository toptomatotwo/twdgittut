<?php
/**
 * Override or insert vars into the page template.
 */
function unikue_process_page(&$vars) {

    // Hook into color.module.
    if (module_exists('color')) {
        _color_page_alter($vars);
    }
    $one_page = FALSE;
    foreach($vars['theme_hook_suggestions'] as $key => $value) {
        if($value == 'page__front') {
            $one_page = TRUE;
        }
    }
    $vars['one_page'] = $one_page;
    drupal_add_js(array('onePage' => $one_page),'setting');
    $status = drupal_get_http_header("status");
    if($status == "404 Not Found") {

    }

    $vars['social_links'] = 0;

    // Always print the site name and slogan, but if they are toggled off, we'll
    // just hide them visually.
    $vars['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
    $vars['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
    if ($vars['hide_site_name']) {
        // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
        $vars['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
    }
    if ($vars['hide_site_slogan']) {
        // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
        $vars['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
    }
    // Since the title and the shortcut link are both block level elements,
    // positioning them next to each other is much simpler with a wrapper div.
    if (!empty($vars['title_suffix']['add_or_remove_shortcut']) && $vars['title']) {
        // Add a wrapper div using the title_prefix and title_suffix render elements.
        $vars['title_prefix']['shortcut_wrapper'] = array(
            '#markup' => '<div class="shortcut-wrapper clearfix">',
            '#weight' => 100,
        );
        $vars['title_suffix']['shortcut_wrapper'] = array(
            '#markup' => '</div>',
            '#weight' => -99,
        );
        // Make sure the shortcut link is the first item in title_suffix.
        $vars['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
    }
    // Menu Social
    $info = '';
    $top_menu_social = theme_get_setting('menu_social_array_hidden');

    if($top_menu_social != null) {
        $top_social = json_decode($top_menu_social,true);
        $top_social = array_chunk($top_social,2);
        if(is_array($top_social)) {
            $i = 9;
            foreach ($top_social as $group_key => $group_value) {
                $icon_value = explode("|",$group_value[0]['value']);
                $link = $group_value[1]['value'];
                $info .= '<a href="'.$link.'" class="w-inline-block social '.$icon_value[0].' '.$icon_value[1].'" data-ix="fade-down-9">';
                $info .= '</a>';
                $i++;
            }
        }
    }
    $vars['menu_social'] = $info;
    // Footer Social
    $ft_social = '';
    $footer_social = theme_get_setting('social_array_hidden');

    if($footer_social != null) {
        $fter_social = json_decode($footer_social,true);
        $fter_social = array_chunk($fter_social,2);
        if(is_array($fter_social)) {
            foreach ($fter_social as $group_key => $group_value) {
                $icon_value = explode("|",$group_value[0]['value']);
                $link = $group_value[1]['value'];
                $ft_social .= '<a href="'.$link.'" class="w-inline-block social '.$icon_value[0].' '.$icon_value[1].'">';
                $ft_social .= '</a>';
            }
        }
    }
    $vars['footer_social'] = $ft_social;
}

/**
 * Implements hook_preprocess_page().
 */
function unikue_preprocess_page(&$vars) {
    global $base_url;
    $themepath = drupal_get_path('theme','unikue');
    // check enable module panels
    if (module_exists('panels')) {
        // check page use panel
        $panel = panels_get_current_page_display();
        if (isset($panel) && !empty($panel->layout)) {
            $vars['theme_hook_suggestions'][] = 'page__panel';
        }
    }
    $vars['is_portfolio'] = FALSE;
    if(isset($vars['node'])) {
    	$vars['theme_hook_suggestions'][] = 'page__node__'.$vars['node']->type;
        if($vars['node']->type == 'portfolio') {
            $node_view = node_view(node_load($vars['node']->nid));
            if(isset($node_view['flippy_pager'])) {
                if(isset($node_view['flippy_pager']['#list']['prev'])  && $node_view['flippy_pager']['#list']['prev'] != FALSE) {
                    $vars['prev_link'] = url('node/'.$node_view['flippy_pager']['#list']['prev']['nid']);
                }
                if(isset($node_view['flippy_pager']['#list']['next']) && $node_view['flippy_pager']['#list']['next'] != FALSE) {
                    $vars['next_link'] = url('node/'.$node_view['flippy_pager']['#list']['next']['nid']);
                }
            }
            $vars['is_portfolio'] = TRUE;
            
        }
    }
    // LOGO SETTINGS
    $vars['logo'] = $base_url.'/'.$themepath.'/logo.png';
    if(theme_get_setting('default_logo') == 0) {
        if(module_exists('media')) {
            if($file_upload = theme_get_setting('logo_normal_media_file')) {
                if(!empty($file_upload)) {
                    $file_decode = json_decode($file_upload);
                    if(isset($file_decode->fid) && $file_decode->fid != 0) {
                        $file = file_load($file_decode->fid);
                        if($file) {
                            $vars['logo'] = file_create_url($file->uri);
                        }
                    }
                }
            }
        } else {
            if ($logo_file = theme_get_setting('logo_normal_form_file')) {
                $vars['logo'] =  file_create_url(file_build_uri($logo_file));
            }
        }
    }

    $vars['logo_footer'] = $base_url.'/'.$themepath.'/logo_footer.png';
    if(module_exists('media')) {
        if($file_upload = theme_get_setting('logo_footer_media_file')) {
            if(!empty($file_upload)) {
                $file_decode = json_decode($file_upload);
                if(isset($file_decode->fid) && $file_decode->fid != 0) {
                    $file = file_load($file_decode->fid);
                    if($file) {
                        $vars['logo_footer'] = file_create_url($file->uri);
                    }
                }
            }
        }
    } else {
        if ($logo_file = theme_get_setting('logo_footer_form_file')) {
            $vars['logo_footer'] =  file_create_url(file_build_uri($logo_file));
        }
    }


    // Page title in node page

    if(isset($vars['node'])) {
        $node = $vars['node'];
        $vars['page_title'] = $vars['node']->type;
        if($node->type == 'portfolio') {

        }
    }
    if(theme_get_setting('footer_text')){
        $vars['footer_text'] = theme_get_setting('footer_text');
    }
    if(strpos(current_path(),'portfolio_popup') !== false) {

    }

    /* layout */
    // Add information about the number of sidebars.
    if (!empty($vars['page']['sidebar_first']) && !empty($vars['page']['sidebar_second'])) {
        $vars['content_column_class'] = 'col-md-6';
    }
    elseif (!empty($vars['page']['sidebar_first']) || !empty($vars['page']['sidebar_second'])) {
        $vars['content_column_class'] = 'col-md-9';
    }
    else {
        $vars['content_column_class'] = '';
    }
    // Prepare dot navigation
    $tree = menu_tree_all_data('main-menu');
    $menu_tree_output = menu_tree_output($tree);
    $vars['dot_navigation'] = '';
    if(!empty($menu_tree_output)) {
        $vars['dot_navigation'] .= '<div class="w-hidden-medium w-hidden-small w-hidden-tiny dot-container" id="hide">';
    }
    foreach ($menu_tree_output as $menu_id => $value) {
        if(isset($value['#href']) && $value['#href'] == '<front>' && isset($value['#localized_options']['fragment']) && !empty($value['#localized_options']['fragment'])) {
            $vars['dot_navigation'] .= '<a class="w-inline-block dot-link" href="#'.$value['#localized_options']['fragment'].'"></a>';
        }
    }
    if(!empty($menu_tree_output)) {
        $vars['dot_navigation'] .= '</div>';
    }
}
/**
 * Implements hook_preprocess_maintenance_page().
 */
function unikue_preprocess_maintenance_page(&$vars) {
    $theme_path = drupal_get_path('theme','unikue');

    if (!$vars['db_is_active']) {
        unset($vars['site_name']);
    }
    // Always print the site name and slogan, but if they are toggled off, we'll
    // just hide them visually.
    $vars['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
    $vars['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
    if ($vars['hide_site_name']) {
        // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
        $vars['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
    }
    if ($vars['hide_site_slogan']) {
        // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
        $vars['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
    }
}
