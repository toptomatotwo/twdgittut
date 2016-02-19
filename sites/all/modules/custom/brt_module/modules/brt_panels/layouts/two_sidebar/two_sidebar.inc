<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Two Sidebar'),
  'category' => t('MD Official'),
  'icon' => 'two_sidebar.png',
  'theme' => 'official_two_sidebar',
  'css' => 'two_sidebar.css',
  'regions' => array(
      'content' => 'Content',
      'sidebar_1' => 'Sidebar 1',
      'sidebar_2' => 'Sidebar 2',
  )
);
