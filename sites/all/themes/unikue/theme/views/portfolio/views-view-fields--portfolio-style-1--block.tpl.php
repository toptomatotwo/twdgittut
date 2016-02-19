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
$thumbnail = '';
if(isset($row->field_field_portfolio_thumbnail[0])) {
    $thumbnail = file_create_url($row->field_field_portfolio_thumbnail[0]['raw']['uri']);
}
?>
<div class="w-col w-col-4 portfolio-row">
    <a style=" background-image: url('<?php print $thumbnail;?>'); " class="w-inline-block portfolio-photo portfolio-1" href="<?php print drupal_get_path_alias('node/').$row->nid;?>">

        <div class="portfolio-photo-overlay">
            <!-- <div class="portfolio-title"><?php print $row->field_thumb_url;?></div> -->
            <div class="thumb-url"><?php if(isset($fields['field_thumb_url'])): print $fields['field_thumb_url']->content; endif;?></div>
            <?php if(isset($fields['field_portfolio_author'])): print $fields['field_portfolio_author']->content; endif;?>
        </div>
    </a>
</div>
<?php unset($fields['title']);?>
<?php unset($fields['field_portfolio_author']);?>
<?php unset($fields['field_portfolio_scroll']);?>
<?php unset($fields['field_portfolio_thumbnail']);?>
<?php unset($fields['field_thumb_url']);?>
<?php foreach ($fields as $id => $field): ?>
    <?php if (!empty($field->separator)): ?>
        <?php print $field->separator; ?>
    <?php endif; ?>
    <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
    <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>
<!-- <?php var_dump($row); ?> -->