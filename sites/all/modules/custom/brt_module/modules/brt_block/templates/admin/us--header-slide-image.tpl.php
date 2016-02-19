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
        <div class="brt-media-wrapper">
            <label class="media-title">Upload Image</label>
            <div class="preview">
                <img class="img-preview" src="<?php print $module_path.'/assets/images/no_image.png';?>" alt="">
                <p class="img-name"></p>
            </div>
            <a class="media-select-button button launcher wButton blueB brt-button" href="#">Select</a>
            <a class="media-remove-button button remove wButton redB brt-button" href="#">Remove</a>

            <input type="hidden" name="form_media_hidden" class="media-hidden-value" value=""/>
        </div>
    </div>
</div>
