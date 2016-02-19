<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Two Columns 70_30'),
  'category' => t('MD Official'),
  'icon' => 'two_columns_70_30.png',
  'theme' => 'official_two_columns_70_30',
  'css' => 'two_columns_70_30.css',
  'regions' => array(
      'column_1'    => 'Column 1',
      'column_2'    => 'Column 2',
  )
);
