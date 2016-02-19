<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
$number = $row->field_field_number_count;
?>
<?php foreach($number as $value):
    $data = $value['raw']['value'];
    $current_value = $value['rendered']['entity']['field_collection_item'][$data];
    ?>
    <div class="w-col w-col-2 team-column">
        <?php if(isset($current_value['field_number_count_value'])):?>
        <h3><span class="timer" data-from="0" data-to="<?php print $current_value['field_number_count_value']['#items'][0]['value'];?>" data-speed="15000"><?php print $current_value['field_number_count_value']['#items'][0]['value'];?></span>
        <?php endif;?>
            <?php if($current_value['field_number_count_type']['#items'][0]['value'] == 'percent'):?><?php print t('%');?><?php endif;?>
        </h3>
        <div class="fun-line"></div>
        <?php if(isset($current_value['field_number_count_title'])):?>
        <div class="sub-text"><?php print $current_value['field_number_count_title'][0]['#markup'];?></div>
        <?php endif;?>
    </div>
<?php endforeach;?>

<?php unset($fields['field_number_count']);?>
<?php foreach ($fields as $id => $field): ?>
    <?php if (!empty($field->separator)): ?>
        <?php print $field->separator; ?>
    <?php endif; ?>
    <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
    <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>