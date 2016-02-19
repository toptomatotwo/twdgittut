<?php
/**
 * @file
 * Panel style for the Megadrupal theme.
 */

/**
 * Implementation of hook_panels_style_info().
 */
function brt_panels_brt_panels_block_style_panels_styles() {
    return array(
        'title' => t('BRT Panel Block style'),
        'description' => t('Panel Block style for the Berathemes.'),
        'render pane' => 'brt_panels_block_style_render_pane',
        'render region' => 'brt_panels_block_style_render_region',
        'pane settings form' => 'brt_panels_block_style_settings_form',
    );
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_brt_panels_block_style_render_region($vars) {
    return implode($vars['panes']);
}

/**
 * Form callback.
 */
function brt_panels_block_style_settings_form($settings) {
    /* add js, css */
    drupal_add_css(drupal_get_path('module', 'brt_panels') . '/css/brt_panels_default_style.admin.css');
    drupal_add_js(drupal_get_path('module', 'brt_panels') . '/js/spectrum.js');
    /* Wrapper ID*/
    $form['wrapper_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Wrapper ID'),
        '#description' => t('The class to provide on the wrapper, outside the pane.'),
        '#default_value' => (isset($settings['wrapper_id'])) ? $settings['wrapper_id'] : ''
    );
    /* Wrapper Classes*/
    $form['wrapper_classes'] = array(
        '#type' => 'textfield',
        '#title' => t('Wrapper Classes'),
        '#description' => t('The class to provide on the wrapper, outside the pane.'),
        '#default_value' => (isset($settings['wrapper_classes'])) ? $settings['wrapper_classes'] : ''
    );
    /* background image */
    $form['background_image'] = array(
        '#type' => 'media',
        '#tree' => TRUE,
        '#title' => t('Background image'),
        '#input' => TRUE,
        '#media_options' => array(
            'global' => array(
                'types' => array('image'), // Example: array('image', 'audio');
                'schemes' => array('http'), // Example: array('http', 'ftp', 'flickr');
            ),
        ),
        '#default_value' => array('fid' => (isset($settings['background_image'])) ? $settings['background_image'] : ''), // Change to your default value
    );

    /* background effects */
    $form['background_effects'] = array(
        '#type' => 'item',
        '#title' => t('Background effects'),
        '#prefix' => '<div class="mdp-pane-inline">',
        '#suffix' => '</div>',
    );

    // background repeat
    $form['background_effects']['background_repeat'] = array(
        '#type' => 'select',
        '#title' => t('Repeat'),
        '#options' => array(
            'inherit' => t('Inherit'),
            'repeat' => t('Repeat'),
            'repeat-x' => t('Repeat X'),
            'repeat-y' => t('Repeat Y'),
            'no-repeat' => t('No repeat'),
        ),
        '#default_value' => (isset($settings['background_effects']['background_repeat'])) ? $settings['background_effects']['background_repeat'] : 'inherit',
    );

    // background position
    $form['background_effects']['background_position'] = array(
        '#type' => 'select',
        '#title' => t('Position'),
        '#options' => array(
            'left top' => t('Left Top'),
            'left center' => t('Left Center'),
            'left bottom' => t('Left Bottom'),
            'center center' => t('Center Center'),
            'center top' => t('Center Top'),
            'center bottom' => t('Center Bottom'),
            'right top' => t('Right Top'),
            'right center' => t('Right Center'),
            'right bottom' => t('Right Bottom'),
        ),
        '#default_value' => (isset($settings['background_effects']['background_position'])) ? $settings['background_effects']['background_position'] : 'left top',
    );

    // background attachment
    $form['background_effects']['background_attachment'] = array(
        '#type' => 'select',
        '#title' => t('Attachment'),
        '#options' => array(
            'scroll' => t('Scroll'),
            'fixed' => t('Fixed'),
        ),
        '#default_value' => (isset($settings['background_effects']['background_attachment'])) ? $settings['background_effects']['background_attachment'] : 'scroll',
    );
    return $form;
}
/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_brt_panels_block_style_render_pane($vars) {
    $content = $vars['content'];
    $pane = $vars['pane'];
    $settings = $vars['settings'];
    $display = $vars['display'];

    if (empty($content->content)) {
        return;
    }

    $block = clone($content);
    $block_load = block_load($block->module,$block->delta);

    $block_load->subject = '';
    if (!empty($block_load->title)) {
        $block_load->subject = $block_load->title;
    }

    $block_load->region = $pane->panel;
    if (!isset($block->module)) {
        $block_load->module = $block->type;
    }
    if (!isset($block->delta)) {
        $block_load->delta = $block->subtype;
    }

    $build = $block->content;

    if (isset($pane->style['style']) && $pane->style['style'] == 'brt_panels_block_style') {

        $vars['classes_array'][] = 'mdp-pane';

        // add css
        drupal_add_css(drupal_get_path('module', 'brt_panels') . '/css/brt_panels_default_style.css');

    }
    // background
    $bg_attributes = array();
    if (!empty($settings['background_color']) || !empty($settings['background_image']['fid'])) {

        // background color
        if (!empty($settings['background_color'])) {
            $bg_attributes[] = $settings['background_color'];
        }
        // background image
        if (!empty($settings['background_image']['fid']) && $settings['background_image']['fid'] != 0) {
            $file = file_load($settings['background_image']['fid']);
            $path_url = file_create_url($file->uri);
            $bg_attributes[] = 'url(' . $path_url . ')';
            $bg_attributes[] = $settings['background_effects']['background_repeat'];
            $bg_attributes[] = $settings['background_effects']['background_position'];
            $bg_attributes[] = $settings['background_effects']['background_attachment'];
        }

        $css_bg = 'background: ' . implode(" ", $bg_attributes) . '; ';
    }
    $style_bg = '';
    if(!empty($css_bg)) {
        $style_bg .= ' style="'.$css_bg.'"';
    }
    $wrapper_id = '';
    if(!empty($settings['wrapper_id'])) {
        $wrapper_id = $settings['wrapper_id'];
    }
    $wrapper_classes = '';
    if(!empty($settings['wrapper_classes'])) {
        $wrapper_classes = $settings['wrapper_classes'];
    }
    $css_class = '';
    if(!empty($pane->css['css_class'])) {
        $css_class .= $pane->css['css_class'];
    }


    if (is_string($build)) {
        $build = array('#markup' => $build);
    }

    $build['#contextual_links']['block'] = array('admin/structure/block/manage', array($block->module, $block->delta));
    $build['#block'] = $block_load;
    $build['#theme_wrappers'][] = 'block';

    $render_block = render($build);
    // If using per pane classes, $block->css_class will need to be added in your
    // preprocess or template, along with any other Panels specific field you
    // might want to utilize.
    return '<div id="'.$wrapper_id.'" class="'.$wrapper_classes.'" '.$style_bg.'><div class="'.$css_class.'">'.$render_block.'</div></div>';
}

