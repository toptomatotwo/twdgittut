<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Sidebar Right Bottom Fullwidth'),
  'category' => t('MD Official'),
  'icon' => 'sidebar_right_bottom_fullwidth.png',
  'theme' => 'official_sidebar_right_bottom_fullwidth',
  'css' => 'sidebar_right_bottom_fullwidth.css',
  'regions' => array(
      'sidebar'           => 'Sidebar',
      'content'           => 'Content',
      'bottom'            => 'Bottom',
  )
);
