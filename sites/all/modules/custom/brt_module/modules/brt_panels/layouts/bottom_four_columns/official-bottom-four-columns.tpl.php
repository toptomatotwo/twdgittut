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

<div class="panel-display panel-bottom-3col clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
    <div class="panel-panel panel-row">
        <div class="panel-content">
            <div class="row clearfix mbs">
                <?php print $content['content']; ?>
            </div>
        </div>
    </div>
    <div class="panel-panel panel-row">
        <div class="panel-bottom grey-line">
            <div class="row clearfix">
                <div class="panel-panel panel-col-first">
                    <div class="inside"><?php print $content['bottom_col_1']; ?></div>
                </div>

                <div class="panel-panel panel-col">
                    <div class="inside"><?php print $content['bottom_col_2']; ?></div>
                </div>

                <div class="panel-panel panel-col">
                    <div class="inside"><?php print $content['bottom_col_3']; ?></div>
                </div>

                <div class="panel-panel panel-col-last">
                    <div class="inside"><?php print $content['bottom_col_4']; ?></div>
                </div>
            </div>
        </div>
    </div>

</div>
