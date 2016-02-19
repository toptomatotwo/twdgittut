<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('One Column'),
  'category' => t('Dastak'),
  'icon' => 'one_column.png',
  'theme' => 'dastak_one_column',
  'css' => 'one_column.css',
  'regions' => array(
      'content'    => 'Content',
  )
);
