<?php
/**
 * @file
 * Provide views data and handlers.
 */

/**
 * Implements hook_views_plugins().
 */
function brt_views_views_plugins()
{
    $module_path = drupal_get_path('module', 'brt_views');
    return array(
        'style' => array(
            'brt_animate_style' => array(
                'title' => t('Brt Views Animate'),
                'help' => t('Brt Views Animate'),
                'path' => $module_path . '/plugins',
                'handler' => 'BrtViewsAnimateStyle',
                'theme' => 'views_view_brt_animate_style',
                'theme path' => $module_path . '/templates',
                'theme file' => 'theme.inc',
                'uses row plugin' => TRUE,
                'uses row class' => TRUE,
                'uses grouping' => TRUE,
                'uses options' => TRUE,
                'type' => 'normal',
            ),
            'brt_responsive_grid_style' => array(
                'title' => t('Brt Responsive grid'),
                'help' => t('Display content in a responsive grid.'),
                'path' => $module_path . '/plugins',
                'handler' => 'BrtViewsResponsiveGridStyle',
                'theme' => 'views_view_brt_responsive_grid_style',
                'theme path' => $module_path . '/templates',
                'theme file' => 'theme.inc',
                'uses row plugin' => TRUE,
                'uses row class' => TRUE,
                'uses options' => TRUE,
                'uses grouping' => TRUE,
                'type' => 'normal',
            ),
        ),
        'row' => array(
            'brt_views_animate_plugin_row' => array(
                'title' => t('BRT - Fields with Animation'),
                'path' => $module_path . '/plugins',
                'handler' => 'BrtViewsAnimatePluginRow',
                'theme' => 'views_view_brt_views_animate_plugin_row',
                'theme path' => $module_path . '/templates',
                'theme file' => 'theme.inc',
                'uses fields' => TRUE,
                'uses options' => TRUE,
                'type' => 'normal',
            ),
        ),
        'pager' => array(
            'brt_views_blog_pager' => array(
                'title' => t('Brt Views Blog Pager'),
                'handler' => 'brt_views_plugin_blog_pager',
                'uses options' => TRUE,
                'parent' => 'full',
            ),
        ),
/*        'row' => array(
            'brt_fields' => array(
                'title' => t('Fields with Animation'),
                'help' => t('Displays the fields with an optional template.'),
                'handler' => 'views_plugin_row_brt_fields',
                'path' => $module_path . '/plugins',
                'theme' => 'views_view_brt_fields',
                'theme path' => $module_path . '/templates',
                'theme file' => 'theme.inc',
                'uses fields' => TRUE,
                'uses options' => TRUE,
                'type' => 'normal',
                'help topic' => 'style-row-fields',
            ),
        ),*/
    );
}
