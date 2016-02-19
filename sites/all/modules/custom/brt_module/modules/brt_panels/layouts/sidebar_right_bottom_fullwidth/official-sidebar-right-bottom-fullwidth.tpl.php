<?php
/**
 * @file
 * Template for a 3 column panel layout.
 *
 * This template provides a very simple "one column" panel display layout.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   $content['middle']: The only panel in the layout.
 */
?>

<div class="panel-display panel-sidebar-right-bottom-fullwidth clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
    <div class="panel-panel panel-row">
        <div class="row clearfix mbs">
            <div class="panel-panel panel-content">
                <?php print $content['content']; ?>
            </div>
            <div class="panel-panel panel-sidebar">
                <?php print $content['sidebar']; ?>
            </div>
        </div>
    </div>
    <div class="panel-panel panel-row">
        <div class="panel-bottom">
            <?php print $content['bottom']; ?>
        </div>
    </div>
</div>
