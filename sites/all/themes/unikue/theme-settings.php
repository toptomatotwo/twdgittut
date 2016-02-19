<?php
/**
 * @file
 * theme-settings.php
 *
 * Provides theme settings for Bootstrap based themes when admin theme is not.
 *
 * @see theme/settings.inc
 */

/**
 * Include common unikue functions.
 */
include_once dirname(__FILE__) . '/theme/common.inc';
unikue_include('unikue','theme/ultis.inc');
/**
 * Implements hook_form_FORM_ID_alter().
 */
function unikue_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  if (isset($form_id)) {
    return;
  }
  // Include theme settings file.
  unikue_include('unikue', 'theme/settings.inc');
  // Alter theme settings form.
  _unikue_settings_form($form, $form_state);
}
