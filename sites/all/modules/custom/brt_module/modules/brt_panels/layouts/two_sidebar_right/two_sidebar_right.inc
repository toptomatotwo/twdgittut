<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Two Sidebar Right'),
  'category' => t('MD Official'),
  'icon' => 'two_sidebar_right.png',
  'theme' => 'official_two_sidebar_right',
  'css' => 'two_sidebar_right.css',
  'regions' => array(
      'content' => 'Content',
      'sidebar_1' => 'Sidebar 1',
      'sidebar_2' => 'Sidebar 2',
  )
);
