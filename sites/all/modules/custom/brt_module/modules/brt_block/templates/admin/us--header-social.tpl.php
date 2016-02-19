<?php
/*
Caution:
Using media upload input must have name="form_media_hidden"

*/
global $base_url;
$module_path = $base_url. '/' .drupal_get_path('module','brt_block');

?>

<div class="wrap-sortable">
    <div class="sortable-item small" data-index="">
        <a href="#" class="us-remove-button">X</a>
        <label>Icon</label>
        <label>Link</label>
        <input type="text" name="form_social_link" class="form-text full" value=""/>
    </div>
</div>