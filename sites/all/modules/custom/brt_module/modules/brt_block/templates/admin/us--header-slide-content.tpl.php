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
        <label>Content text</label>
        <textarea style="border:1px solid #ccc" type="text" rows="5" name="form_content_text" class="form-text full" value=""></textarea>

    </div>
</div>
