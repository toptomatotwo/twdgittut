<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Three Columns 25_50_25'),
  'category' => t('MD Official'),
  'icon' => 'three_columns_25_50_25.png',
  'theme' => 'official_three_columns_25_50_25',
  'css' => 'three_columns_25_50_25.css',
  'regions' => array(
      'column_1'    => 'Column 1',
      'column_2'    => 'Column 2',
      'column_3'    => 'Column 3',
  )
);
