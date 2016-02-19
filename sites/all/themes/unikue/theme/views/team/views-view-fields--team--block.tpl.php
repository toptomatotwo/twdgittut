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
    <div class="w-col w-col-3 team-column">
        <a class="w-inline-block" href="#">
            <?php if(isset($fields['field_team_avatar'])): print $fields['field_team_avatar']->content; endif;?>
        </a>
        <?php if(isset($fields['title'])): print $fields['title']->content; endif;?>
        <?php if(isset($fields['field_team_job'])): print $fields['field_team_job']->content; endif;?>
        <div class="team-line orange"></div>
        <?php if(isset($fields['body'])): print $fields['body']->content; endif;?>
        <div class="social-icon">
            <?php if(isset($row->field_field_team_socials)):?>
                <?php foreach($row->field_field_team_socials as $key => $value):
                    $data = $value['raw']['value'];?>
                    <a href="<?php print $value['rendered']['entity']['field_collection_item'][$data]['field_team_socials_link']['#items'][0]['value'];?>"><?php print $value['rendered']['entity']['field_collection_item'][$data]['field_team_socials_title']['#items'][0]['value'];?></a>
                <?php endforeach;?>
            <?php endif;?>
        </div>
    </div>
<?php unset($fields['title']);?>
<?php unset($fields['body']);?>
<?php unset($fields['field_team_job']);?>
<?php unset($fields['field_team_avatar']);?>
<?php unset($fields['field_team_socials']);?>
<?php unset($fields['field_team_data']);?>
<?php unset($fields['field_team_scroll']);?>
<?php foreach ($fields as $id => $field): ?>
    <?php if (!empty($field->separator)): ?>
        <?php print $field->separator; ?>
    <?php endif; ?>
    <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
    <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>