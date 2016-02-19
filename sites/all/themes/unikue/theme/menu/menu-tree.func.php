<?php
/**
 * @file
 * menu-tree.func.php
 */

/**
 * Overrides theme_menu_tree().
 */
function unikue_menu_tree(&$variables) {
  return '<ul class="w-nav-menu nav menu" role="navigation">' . $variables['tree'] . '</ul>';
}

/**
 * Bootstrap theme wrapper function for the primary menu links.
 */
function unikue_menu_tree__primary(&$variables) {
  return '<ul class="w-nav-menu nav menu">' . $variables['tree'] . '</ul>';
}


