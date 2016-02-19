<?php
/**
 * @file
 * alter.inc
 *
 * Contains various implementations of hook_*_alter().
 */

/**
 * Implements hook_css_alter().
 */
function unikue_css_alter(&$css) {
  $theme_path = drupal_get_path('theme', 'unikue');
  // Exclude specified CSS files from theme.
  $excludes = unikue_get_theme_info(NULL, 'exclude][css');
    // Add overrides.
    $override = $theme_path . '/css/overrides.css';
    $css[$override] = array(
        'data' => $override,
        'type' => 'file',
        'every_page' => TRUE,
        'media' => 'all',
        'preprocess' => TRUE,
        'group' => CSS_THEME,
        'browsers' => array('IE' => TRUE, '!IE' => TRUE),
        'weight' => -1,
    );
  if (!empty($excludes)) {
    $css = array_diff_key($css, drupal_map_assoc($excludes));
  }
}

/**
 * Implements hook_element_info_alter().
 */
function unikue_element_info_alter(&$elements) {

}

/**
 * Implements hook_form_alter().
 */
function unikue_form_alter(array &$form, array &$form_state = array(), $form_id = NULL) {
  if ($form_id) {
    // IDs of forms that should be ignored. Make this configurable?
    // @todo is this still needed?
    $form_ids = array(
      'node_form',
      'system_site_information_settings',
      'user_profile_form',
      'node_delete_confirm',
    );
    // Only wrap in container for certain form.
    if (!in_array($form_id, $form_ids) && !isset($form['#node_edit_form']) && isset($form['actions']) && isset($form['actions']['#type']) && ($form['actions']['#type'] == 'actions')) {
      $form['actions']['#theme_wrappers'] = array();
    }

    switch ($form_id) {
      case 'system_theme_settings':
        // Include the settings form here.
        unikue_include('unikue', 'theme/settings.inc');
        _unikue_settings_form($form, $form_state);
        break;

      case 'search_form':
        // Add a clearfix class so the results don't overflow onto the form.
        $form['#attributes']['class'][] = 'clearfix';

        // Remove container-inline from the container classes.
        $form['basic']['#attributes']['class'] = array();

        // Hide the default button from display.
        $form['basic']['submit']['#attributes']['class'][] = 'element-invisible';

        // Implement a theme wrapper to add a submit button containing a search
        // icon directly after the input element.
        $form['basic']['keys']['#theme_wrappers'] = array('unikue_search_form_wrapper');
        $form['basic']['keys']['#title'] = '';
        $form['basic']['keys']['#attributes']['placeholder'] = t('Search');
        break;

      case 'search_block_form':
        $form['#attributes']['class'][] = 'form-search';

        $form['search_block_form']['#title'] = '';
        $form['search_block_form']['#attributes']['placeholder'] = t('Search');

        // Hide the default button from display and implement a theme wrapper
        // to add a submit button containing a search icon directly after the
        // input element.
        $form['actions']['submit']['#attributes']['class'][] = 'element-invisible';
        $form['search_block_form']['#theme_wrappers'] = array('unikue_search_form_wrapper');

        // Apply a clearfix so the results don't overflow onto the form.
        $form['#attributes']['class'][] = 'content-search';
        break;
        case 'user_login':
            $form['#attributes']['class'][] = 'form';
            $form['name']['#attributes']['class'][] = 'w-input text-field';
            $form['name']['#prefix'] = '<div class="input-wrapper">';
            $form['name']['#suffix'] = '</div>';
            $form['pass']['#attributes']['class'][] = 'w-input text-field';
            $form['pass']['#prefix'] = '<div class="input-wrapper">';
            $form['pass']['#suffix'] = '</div>';
            $form['actions']['submit']['#value'] = t('Login');
            $form['actions']['submit']['#attributes']['class'][] = 'w-button submit-button';
            $form['actions']['submit']['#prefix'] = '';
            $form['actions']['submit']['#suffix'] = '';
            break;
        case 'user_register_form':
            $form['#attributes']['class'][] = 'form';
            $form['account']['name']['#attributes']['class'][] = 'w-input text-field';
            $form['account']['name']['#prefix'] = '<div class="input-wrapper">';
            $form['account']['name']['#suffix'] = '</div>';
            $form['account']['mail']['#attributes']['class'][] = 'w-input text-field';
            $form['account']['mail']['#prefix'] = '<div class="input-wrapper">';
            $form['account']['mail']['#suffix'] = '</div>';
            $form['actions']['submit']['#value'] = t('Create new account');
            $form['actions']['submit']['#attributes']['class'][] = 'w-button submit-button';
            $form['actions']['submit']['#prefix'] = '';
            $form['actions']['submit']['#suffix'] = '';
            break;
        case 'user_login_block':
            $form['#attributes']['class'][] = 'form';
            $form['name']['#attributes']['class'][] = 'w-input text-field';
            $form['name']['#prefix'] = '<div class="input-wrapper">';
            $form['name']['#suffix'] = '</div>';
            $form['pass']['#attributes']['class'][] = 'w-input text-field';
            $form['pass']['#prefix'] = '<div class="input-wrapper">';
            $form['pass']['#suffix'] = '</div>';
            $form['actions']['submit']['#value'] = t('Login');
            $form['actions']['submit']['#attributes']['class'][] = 'w-button submit-button';
            $form['actions']['submit']['#prefix'] = '';
            $form['actions']['submit']['#suffix'] = '';
            break;
        case 'user_pass':
            $form['name']['#attributes']['class'][] = 'w-input text-field';
            $form['name']['#prefix'] = '<div class="input-wrapper">';
            $form['name']['#suffix'] = '</div>';
            $form['pass']['#attributes']['class'][] = 'w-input text-field';
            $form['pass']['#prefix'] = '';
            $form['pass']['#suffix'] = '';
            $form['actions']['submit']['#value'] = t('Request new password');
            $form['actions']['submit']['#attributes']['class'][] = 'w-button submit-button';
            $form['actions']['submit']['#prefix'] = '';
            $form['actions']['submit']['#suffix'] = '';
            break;
    }
    if(stristr($form_id,'webform_client_form')) {
        $form['actions']['submit']['#attributes']['class'][] = 'w-button submit-button';
    }

  }
}

/**
 * Implements hook_js_alter().
 */
function unikue_js_alter(&$js) {
  // Exclude specified JavaScript files from theme.
  $excludes = unikue_get_theme_info(NULL, 'exclude][js');

  $theme_path = drupal_get_path('theme', 'unikue');

  // Add or replace JavaScript files when matching paths are detected.
  // Replacement files must begin with '_', like '_node.js'.
  $files = file_scan_directory($theme_path . '/js', '/\.js$/');
  foreach ($files as $file) {
    $path = str_replace($theme_path . '/js/', '', $file->uri);
    // Detect if this is a replacement file.
    $replace = FALSE;
    if (preg_match('/^[_]/', $file->filename)) {
      $replace = TRUE;
      $path = dirname($path) . '/' . preg_replace('/^[_]/', '', $file->filename);
    }
    $matches = array();
    if (preg_match('/^modules\/([^\/]*)/', $path, $matches)) {
      if (!module_exists($matches[1])) {
        continue;
      }
      else {
        $path = str_replace('modules/' . $matches[1], drupal_get_path('module', $matches[1]), $path);
      }
    }
    // Path should always exist to either add or replace JavaScript file.
    if (!empty($js[$path])) {
      // Replace file.
      if ($replace) {
        $js[$file->uri] = $js[$path];
        $js[$file->uri]['data'] = $file->uri;
        unset($js[$path]);
      }
      // Add file.
      else {
        $js[$file->uri] = drupal_js_defaults($file->uri);
        $js[$file->uri]['group'] = JS_THEME;
      }
    }
  }

  if (!empty($excludes)) {
    $js = array_diff_key($js, drupal_map_assoc($excludes));
  }

}
