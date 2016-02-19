<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Two Columns'),
  'category' => t('MD Official'),
  'icon' => 'two_columns.png',
  'theme' => 'official_two_columns',
  'css' => 'two_columns.css',
  'regions' => array(
      'column_1'    => 'Column 1',
      'column_2'    => 'Column 2',
  )
);
