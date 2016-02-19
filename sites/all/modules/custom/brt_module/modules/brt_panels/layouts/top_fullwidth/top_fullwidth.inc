<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Top Fullwidth'),
  'category' => t('MD Official'),
  'icon' => 'top_fullwidth.png',
  'theme' => 'panels_top_fullwidth',
  'css' => 'top_fullwidth.css',
  'regions' => array(
      'top'    => 'Main Content',
      'sidebar' => 'Sidebar',
      'content' => 'Content'
  )
);
