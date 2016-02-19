<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Four Columns'),
  'category' => t('MD Official'),
  'icon' => 'four_columns.png',
  'theme' => 'official_four_columns',
  'css' => 'four_columns.css',
  'regions' => array(
      'column_1'    => 'Column 1',
      'column_2'    => 'Column 2',
      'column_3'    => 'Column 3',
      'column_4'    => 'Column 4',
  )
);
