<?php

/**
 * Implementation of template preprocess for the view.
 */
function brt_views_preprocess_views_view_brt_animate_style(&$vars) {
  $vars['animate_class'] = $vars['options']['input_animate'];
  $vars['use_animate'] = $vars['options']['use_animate'];
  $vars['animate_all'] = $vars['options']['animate_all'];
  $vars['delay_time'] = $vars['options']['delay_time'];
  $vars['delay_step'] = $vars['options']['delay_step'];
  $vars['add_class'] = $vars['options']['add_class'];

  $view = &$vars['view'];
}
/**
 * Display a view as a responsive grid style.
 */
function brt_views_preprocess_views_view_brt_responsive_grid_style(&$vars) {
    $view = $vars['view'];
    $result = $view->result;
    $options = brt_responsive_grid_style_get_options($view->style_plugin->options);
    $handler = $view->style_plugin;
    $columns  = $options['columns'];

    $vars['classes_array'] = array();
    if (!$options['default_classes']) {
        $vars['classes_array'][] = 'brt-views-responsive-grid';
        $vars['classes_array'][] = 'brt-views-responsive-grid-' . $options['alignment'];
        $vars['classes_array'][] = 'brt-views-columns-' . $columns;
    }
    $vars['classes_array'] = array_merge($vars['classes_array'], explode(' ', $options['wrapper_classes']));
    $vars['classes_array'] = array_filter($vars['classes_array']);
    // Check if there are views results to process.
    if (!empty($vars['rows'])) {
        $col_id = 0;
        $row_id = 0;
        $keys = array_keys($vars['rows']);
        // Determine style alignment.
        if ($options['alignment'] == 'horizontal') {
            $rows = array();
            $vars['row_classes'] = array();
            foreach ($vars['rows'] as $i => $row) {
                $classes = explode(' ', $options['column_classes']);
                if (!$options['default_classes']) {
                    $classes[] = 'brt-views-column-' . ($col_id + 1);
                }
                $rows[$row_id][$col_id] = array(
                    'classes' => implode(' ', $classes),
                    'content' => $vars['rows'][current($keys)],
                );
                $classes = explode(' ', $options['row_classes']);
                if (!$options['default_classes']) {
                    $classes[] = 'brt-views-row-' . ($row_id + 1);
                }
                $vars['row_classes'][$row_id] = implode(' ', $classes);

                if ($row_id == 0) {
                    $vars['row_classes'][$row_id] .= ' ' . $options['first_row_classes'];
                }
                elseif ($row_id == ceil(count($vars['rows']) / $columns) - 1) {
                    $vars['row_classes'][$row_id] .= ' ' . $options['last_row_classes'];
                }
                if ($col_id == 0) {
                    $rows[$row_id][$col_id]['classes'] .= ' ' . $options['first_column_classes'];
                    $col_id++;
                }
                elseif ($col_id == $columns - 1) {
                    $rows[$row_id][$col_id]['classes'] .= ' ' . $options['last_column_classes'];
                    $col_id = 0;
                    $row_id++;
                }
                else {
                    $col_id++;
                }
                next($keys);
            }
            $vars['rows'] = $rows;
        }
        else {
            $cols = array();
            $extra = count($vars['rows']) % $columns;
            $per_col = floor(count($vars['rows']) / $columns);
            $vars['column_classes'] = array();
            for ($i = 0; $i < $columns; $i++) {
                $classes = explode(' ', $options['column_classes']);
                if (!$options['default_classes']) {
                    $classes[] = 'brt-views-column-' . ($col_id + 1);
                }
                $vars['column_classes'][$i] = $classes;
                if ($i == 0 && !empty($options['first_column_classes'])) {
                    $vars['column_classes'][$i] = array_merge($vars['column_classes'][$i], explode(' ', $options['first_column_classes']));
                }
                elseif ($i == $columns - 1 && !empty($options['last_column_classes'])) {
                    $vars['column_classes'][$i] = array_merge($vars['column_classes'][$i], explode(' ', $options['last_column_classes']));
                }
                $vars['column_classes'][$i] = implode(' ', $vars['column_classes'][$i]);
                for ($n = 0; $n <= ($per_col - 1) + ($i < $extra ? 1 : 0); $n++) {
                    $classes = explode(' ', $options['row_classes']);
                    if (!$options['default_classes']) {
                        $classes[] = 'brt-views-row-' . ($row_id + 1);
                    }
                    $cols[$i][$n] = array(
                        'classes' => $classes,
                        'content' => $vars['rows'][current($keys)],
                    );
                    if ($n == 0 && !empty($options['first_row_classes'])) {
                        $cols[$i][$n]['classes'] = array_merge($cols[$i][$n]['classes'], explode(' ', $options['first_row_classes']));
                    }
                    elseif ($n == ($per_col - 1) + ($i < $extra ? 1 : 0)  && !empty($options['last_row_classes'])) {
                        $cols[$i][$n]['classes'] = array_merge($cols[$i][$n]['classes'], explode(' ', $options['last_row_classes']));
                    }
                    $cols[$i][$n]['classes'] = implode(' ', $cols[$i][$n]['classes']);
                    next($keys);
                    $row_id++;
                }
                $col_id++;
                $row_id = 0;
            }
            $vars['columns'] = $cols;
        }
    }
    $vars['classes'] = implode(' ', $vars['classes_array']);
}
/**
 * Preprocess theme function to print a single record from a row, with fields
 */
function template_preprocess_views_view_brt_views_animate_plugin_row(&$vars) {
    $view = $vars['view'];
    // Loop through the fields for this view.
    $previous_inline = FALSE;
    $vars['fields'] = array(); // ensure it's at least an empty array.
    $brt_options = $vars['options']['brt_views_animate_fields']['fields_animate'];
    foreach ($view->field as $id => $field) {
        // render this even if set to exclude so it can be used elsewhere.
        $field_output = $view->style_plugin->get_field($view->row_index, $id);
        $empty = $field->is_value_empty($field_output, $field->options['empty_zero']);
        if (empty($field->options['exclude']) && (!$empty || (empty($field->options['hide_empty']) && empty($vars['options']['hide_empty'])))) {
            $object = new stdClass();
            $object->handler = &$view->field[$id];
            $object->inline = !empty($vars['options']['inline'][$id]);

            $object->element_type = $object->handler->element_type(TRUE, !$vars['options']['default_field_elements'], $object->inline);
            if ($object->element_type) {
                $class = '';
                if ($object->handler->options['element_default_classes']) {
                    $class = 'field-content';
                }

                if ($classes = $object->handler->element_classes($view->row_index)) {
                    if ($class) {
                        $class .= ' ';
                    }
                    $class .=  $classes;
                }

                $pre = '<' . $object->element_type;
                if ($class) {
                    $pre .= ' class="' . $class . '"';
                }
                $field_output = $pre . '>' . $field_output . '</' . $object->element_type . '>';
            }

            // Protect ourself somewhat for backward compatibility. This will prevent
            // old templates from producing invalid HTML when no element type is selected.
            if (empty($object->element_type)) {
                $object->element_type = 'span';
            }

            $object->content = $field_output;
            if (isset($view->field[$id]->field_alias) && isset($vars['row']->{$view->field[$id]->field_alias})) {
                $object->raw = $vars['row']->{$view->field[$id]->field_alias};
            }
            else {
                $object->raw = NULL; // make sure it exists to reduce NOTICE
            }

            if (!empty($vars['options']['separator']) && $previous_inline && $object->inline && $object->content) {
                $object->separator = filter_xss_admin($vars['options']['separator']);
            }

            $object->class = drupal_clean_css_identifier($id);

            $previous_inline = $object->inline;
            $object->inline_html = $object->handler->element_wrapper_type(TRUE, TRUE);
            if ($object->inline_html === '' && $vars['options']['default_field_elements']) {
                $object->inline_html = $object->inline ? 'span' : 'div';
            }

            // Set up the wrapper HTML.
            $object->wrapper_prefix = '';
            $object->wrapper_suffix = '';

            if ($object->inline_html) {
                $class = '';
                if ($object->handler->options['element_default_classes']) {
                    $class = "views-field views-field-" . $object->class;
                }

                if ($classes = $object->handler->element_wrapper_classes($view->row_index)) {
                    if ($class) {
                        $class .= ' ';
                    }
                    $class .= $classes;
                }

                $object->wrapper_prefix = '<' . $object->inline_html;
                if ($class) {
                    $object->wrapper_prefix .= ' class="' . $class . '"';
                }
                $object->wrapper_prefix .= '>';
                $object->wrapper_suffix = '</' . $object->inline_html . '>';
            }

            // Set up the label for the value and the HTML to make it easier
            // on the template.
            $object->label = check_plain($view->field[$id]->label());
            $object->label_html = '';
            if ($object->label) {
                $object->label_html .= $object->label;
                if ($object->handler->options['element_label_colon']) {
                    $object->label_html .= ': ';
                }

                $object->element_label_type = $object->handler->element_label_type(TRUE, !$vars['options']['default_field_elements']);
                if ($object->element_label_type) {
                    $class = '';
                    if ($object->handler->options['element_default_classes']) {
                        $class = 'views-label views-label-' . $object->class;
                    }

                    $element_label_class = $object->handler->element_label_classes($view->row_index);
                    if ($element_label_class) {
                        if ($class) {
                            $class .= ' ';
                        }

                        $class .= $element_label_class;
                    }

                    $pre = '<' . $object->element_label_type;
                    if ($class) {
                        $pre .= ' class="' . $class . '"';
                    }
                    $pre .= '>';

                    $object->label_html = $pre . $object->label_html . '</' . $object->element_label_type . '>';
                }
            }
            /*$brt_field_render = '';
            if (!empty($object->separator)){
                $brt_field_render .= $object->separator;
            }

            $brt_field_render .= $object->wrapper_prefix;
            $brt_field_render .= $object->label_html;
            $brt_field_render .= $object->content;
            $brt_field_render .= $object->wrapper_suffix;

            $brt_fields[$id] = $brt_field_render;*/

            $vars['fields'][$id] = $object;
            $vars['fields'][$id]->animation_data = array(
                'animation_type'    => isset($brt_options[$id]['animation_type']) ? $brt_options[$id]['animation_type'] : '',
                'animation_delay'    => isset($brt_options[$id]['animation_delay']) ? $brt_options[$id]['animation_delay'] : 0,
            );
        }
    }

}

