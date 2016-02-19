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
<div class="w-row row form">
    <div class="w-col w-col-8" data-ix="scroll-fade-from-left">
        <?php if (isset($fields['webform_form_body'])): print $fields['webform_form_body']->content; endif; ?>
    </div>
    <div class="w-col w-col-4 column-work" data-ix="scroll-fade-from-right">
        <?php if($fields['title']):?>
        <div class="small-tittle"><?php print $fields['title']->content; ?></div>
        <?php endif;?>
        <p class="left">
            <?php if (isset($row->field_field_webform_phone)): ?>
                <span class="darker"><?php print t('Phone');?>:</span><?php print $row->field_field_webform_phone[0]['raw']['value']; ?>
            <?php endif; ?>
            <?php if (isset($row->field_field_webform_fax)): ?>
                <br><span class="darker"><?php print t('Fax');?>:&nbsp;</span><?php print $row->field_field_webform_fax[0]['raw']['value']; ?>
            <?php endif; ?>
            <?php if (isset($row->field_field_webform_email)): ?>
                <br><span class="darker"><?php print t('Email');?>:</span>&nbsp;<?php print $row->field_field_webform_email[0]['raw']['value']; ?>
            <?php endif; ?>
            <?php if (isset($row->field_field_webform_adress)): ?>
                <br><span class="darker"><?php print t('Address');?>:</span><?php print $row->field_field_webform_adress[0]['raw']['value']; ?>
            <?php endif; ?>
            
        </p>
    </div>
</div>
<?php unset($fields['title']); ?>
<?php unset($fields['field_webform_phone']); ?>
<?php unset($fields['field_webform_fax']); ?>
<?php unset($fields['field_webform_email']); ?>
<?php unset($fields['field_webform_adress']); ?>
<?php unset($fields['webform_form_body']); ?>
<?php unset($fields['field_webform_work_hours']); ?>

<?php foreach ($fields as $id => $field): ?>
    <?php if (!empty($field->separator)): ?>
        <?php print $field->separator; ?>
    <?php endif; ?>
    <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
    <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>