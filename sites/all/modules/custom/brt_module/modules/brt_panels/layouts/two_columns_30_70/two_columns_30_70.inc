<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Two Columns 30_70'),
  'category' => t('MD Official'),
  'icon' => 'two_columns_30_70.png',
  'theme' => 'official_two_columns_30_70',
  'css' => 'two_columns_30_70.css',
  'regions' => array(
      'column_1'    => 'Column 1',
      'column_2'    => 'Column 2',
  )
);
