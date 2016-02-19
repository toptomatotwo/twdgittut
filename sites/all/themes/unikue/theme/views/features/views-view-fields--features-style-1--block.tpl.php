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
?>
    <div class="w-row features-row">
        <div class="w-col w-col-5 col" data-ix="scroll-fade-from-left">
            <?php if(isset($fields['title'])): print $fields['title']->content; endif;?>
                <div class="hero-line left"></div>
            <?php if(isset($fields['body'])): print $fields['body']->content; endif;?>
                <?php $data = $row->field_field_features_button[0]['raw']['value'];?>
            <?php if(isset($row->field_field_features_button)):?>
                <div class="div-left"><a class="button black" href="<?php print $row->field_field_features_button[0]['rendered']['entity']['field_collection_item'][$data]['field_features_button_link'][0]['#markup'];?>"><?php print $row->field_field_features_button[0]['rendered']['entity']['field_collection_item'][$data]['field_features_button_title'][0]['#markup'];?></a>
            <?php endif;?>
            </div>
        </div>
        <div class="w-col w-col-7" data-ix="scroll-fade-from-right">
            <?php if(isset($row->field_field_features_image)):?>
            <img class="ipad" src="<?php print file_create_url($row->field_field_features_image[0]['raw']['uri']);?>" width="750">
            <?php endif;?>
        </div>
    </div>

<?php unset($fields['title']);?>
<?php unset($fields['body']);?>
<?php unset($fields['field_features_image']);?>
<?php unset($fields['field_features_button']);?>
<?php foreach ($fields as $id => $field): ?>
    <?php if (!empty($field->separator)): ?>
        <?php print $field->separator; ?>
    <?php endif; ?>
    <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
    <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>