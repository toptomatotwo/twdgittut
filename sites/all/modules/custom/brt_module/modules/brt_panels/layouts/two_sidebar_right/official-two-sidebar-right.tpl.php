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

<div class="panel-display panel-two-sidebar-right clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
    <div class="panel-panel panel-content">
        <div class="inside"><?php print $content['content']; ?></div>
    </div>
    <div class="panel-panel panel-sidebar panel-sidebar-1">
        <div class="inside"><?php print $content['sidebar_1']; ?></div>
    </div>
    <div class="panel-panel panel-sidebar panel-sidebar-2">
        <div class="inside"><?php print $content['sidebar_2']; ?></div>
    </div>
</div>
