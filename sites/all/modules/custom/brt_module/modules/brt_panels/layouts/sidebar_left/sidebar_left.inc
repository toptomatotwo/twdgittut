<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Sidebar Left'),
  'category' => t('MD Official'),
  'icon' => 'sidebar_left.png',
  'theme' => 'official_sidebar_left',
  'css' => 'sidebar_left.css',
  'regions' => array(
      'content' => 'Content',
      'sidebar' => 'Sidebar'
  )
);
