<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Sidebar Right'),
  'category' => t('MD Official'),
  'icon' => 'sidebar_right.png',
  'theme' => 'official_sidebar_right',
  'css' => 'sidebar_right.css',
  'regions' => array(
      'content' => 'Content',
      'sidebar' => 'Sidebar'
  )
);
