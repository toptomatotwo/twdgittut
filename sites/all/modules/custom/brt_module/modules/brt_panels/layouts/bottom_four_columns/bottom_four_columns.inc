<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Bottom Four Columns'),
  'category' => t('Dastak'),
  'icon' => 'bottom_four_columns.png',
  'theme' => 'official_bottom_four_columns',
  'css' => 'bottom_four_columns.css',
  'regions' => array(
      'content'         => 'Content',
      'bottom_col_1'    => 'Bottom Column 1',
      'bottom_col_2'    => 'Bottom Column 2',
      'bottom_col_3'    => 'Bottom Column 3',
      'bottom_col_4'    => 'Bottom Column 4',
  )
);
