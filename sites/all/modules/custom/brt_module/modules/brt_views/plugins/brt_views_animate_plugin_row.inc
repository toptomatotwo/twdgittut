<?php

class BrtViewsAnimatePluginRow extends views_plugin_row {

    public function option_definition() {
        $options = parent::option_definition();
        $options['brt_views_animate_fields'] = '';

        $options['inline'] = array('default' => array());
        $options['separator'] = array('default' => '');
        $options['hide_empty'] = array('default' => FALSE, 'bool' => TRUE);
        $options['default_field_elements'] = array('default' => TRUE, 'bool' => TRUE);
        return $options;
    }

    function options_form(&$form, &$form_state) {
        parent::options_form($form, $form_state);

        $fields = array();
        $handler = $this->display->handler;
        $get_field = $handler->get_handlers('field');
        if(!empty($get_field)) {
            $form['brt_views_animate_fields']['fields_animate'] = array(
                '#type' => 'fieldset',
                '#title' => t('Fields Animation'),
                '#collapsible' => TRUE,
                '#collapsed' => TRUE,
            );
            foreach($get_field as $field_name => $field_value) {
                $form['brt_views_animate_fields']['fields_animate'][$field_name] = array(
                    '#type' => 'fieldset',
                    '#title' => $field_value->definition['title'],
                    '#collapsible' => TRUE,
                    '#collapsed' => TRUE,
                );
                $form['brt_views_animate_fields']['fields_animate'][$field_name]['animation_type'] = array(
                    '#type' => 'select',
                    '#title' => t('Animation Type'),
                    '#options' => _brt_views_animate_get_options(),
                    '#default_value' => isset($this->options['brt_views_animate_fields']['fields_animate'][$field_name]['animation_type']) ? $this->options['brt_views_animate_fields']['fields_animate'][$field_name]['animation_type'] : '',
                );
                $form['brt_views_animate_fields']['fields_animate'][$field_name]['animation_delay'] = array(
                    '#type' => 'textfield',
                    '#title' => t('Animation Delay (ms)'),
                    '#default_value' => isset($this->options['brt_views_animate_fields']['fields_animate'][$field_name]['animation_delay']) ? $this->options['brt_views_animate_fields']['fields_animate'][$field_name]['animation_delay'] : '',
                    '#field_suffix'   => ' (ms)',
                    '#size'          => 5
                );
            }
        }
        $field_options = $this->display->handler->get_field_labels();

        if (empty($this->options['inline'])) {
            $this->options['inline'] = array();
        }

        $form['default_field_elements'] = array(
            '#type' => 'checkbox',
            '#title' => t('Provide default field wrapper elements'),
            '#default_value' => $this->options['default_field_elements'],
            '#description' => t('If not checked, fields that are not configured to customize their HTML elements will get no wrappers at all for their field, label and field + label wrappers. You can use this to quickly reduce the amount of markup the view provides by default, at the cost of making it more difficult to apply CSS.'),
        );

        $form['inline'] = array(
            '#type' => 'checkboxes',
            '#title' => t('Inline fields'),
            '#options' => $field_options,
            '#default_value' => $this->options['inline'],
            '#description' => t('Inline fields will be displayed next to each other rather than one after another. Note that some fields will ignore this if they are block elements, particularly body fields and other formatted HTML.'),
            '#dependency' => array(
                'edit-row-options-default-field-elements' => array(1),
            ),
            '#prefix' => '<div id="edit-row-options-inline-wrapper"><div>',
            '#suffix' => '</div></div>',

        );

        $form['separator'] = array(
            '#title' => t('Separator'),
            '#type' => 'textfield',
            '#size' => 10,
            '#default_value' => isset($this->options['separator']) ? $this->options['separator'] : '',
            '#description' => t('The separator may be placed between inline fields to keep them from squishing up next to each other. You can use HTML in this field.'),
            '#dependency' => array(
                'edit-row-options-default-field-elements' => array(1),
            ),
        );

        $form['hide_empty'] = array(
            '#type' => 'checkbox',
            '#title' => t('Hide empty fields'),
            '#default_value' => $this->options['hide_empty'],
            '#description' => t('Do not display fields, labels or markup for fields that are empty.'),
        );
    }
    /**
     * Perform any necessary changes to the form values prior to storage.
     * There is no need for this function to actually store the data.
     */
    function options_submit(&$form, &$form_state) {
        $form_state['values']['row_options']['inline'] = array_filter($form_state['values']['row_options']['inline']);
    }
}
/**
 * Define an animation options array
 */
function _brt_views_animate_get_options() {
    $option_animate = array(
        "" => 'None',

        "bounce" => "bounce",
        "flash" => "flash",
        "pulse" => "pulse",
        "rubberBand" => "rubberBand",
        "shake" => "shake",
        "swing" => "swing",
        "tada" => "tada",
        "wobble" => "wobble",

        "bounceInDown" => "bounceInDown",
        "bounceIn" => "bounceIn",
        "bounceInLeft" => "bounceInLeft",
        "bounceInUp" => "bounceInUp",
        "bounceInRight" => "bounceInRight",

        "fadeIn" => "fadeIn",
        "fadeInDown" => "fadeInDown",
        "fadeInDownBig" => "fadeInDownBig",
        "fadeInLeft" => "fadeInLeft",
        "fadeInLeftBig" => "fadeInLeftBig",
        "fadeInRight" => "fadeInRight",
        "fadeInRightBig" => "fadeInRightBig",
        "fadeInUp" => "fadeInUp",
        "fadeInUpBig" => "fadeInUpBig",

        "flip" => "flip",
        "flipInX" => "flipInX",
        "flipInY" => "flipInY",

        "lightSpeedIn" => "lightSpeedIn",

        "rotateIn" => "rotateIn",
        "rotateInDownLeft" => "rotateInDownLeft",
        "rotateInDownRight" => "rotateInDownRight",
        "rotateInUpLeft" => "rotateInUpLeft",
        "rotateInUpRight" => "rotateInUpRight",

        "slideInDown" => "slideInDown",
        "slideInLeft" => "slideInLeft",
        "slideInRight" => "slideInRight",

        "rollIn" => "rollIn",

    );

    return $option_animate;
}