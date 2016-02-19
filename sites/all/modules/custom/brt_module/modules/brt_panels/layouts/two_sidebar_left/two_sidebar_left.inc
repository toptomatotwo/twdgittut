<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Two Sidebar Left'),
  'category' => t('MD Official'),
  'icon' => 'two_sidebar_left.png',
  'theme' => 'official_two_sidebar_left',
  'css' => 'two_sidebar_left.css',
  'regions' => array(
      'sidebar_1' => 'Sidebar 1',
      'sidebar_2' => 'Sidebar 2',
      'content' => 'Content',
  )
);
