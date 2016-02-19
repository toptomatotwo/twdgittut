<?php
/**
 * @file views-bootstrap-thumbnail-plugin-style.tpl.php
 * Default simple view template to display Bootstrap Thumbnails.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 * - $column_type contains a number (default Bootstrap grid system column type).
 *
 * @ingroup views_templates
 */
 $animate_class = explode('|',$animate_class);
 $animate_class = array_filter($animate_class);

 $random =($animate_class) ? array_rand($animate_class) : 'fade';
?>
<?php if($use_animate == 1 && count($rows) > 1):?>
    <?php if($animate_all == 0): ?>
      <?php if(count($animate_class)<count($rows)): ?>
        <?php foreach ($outputArr as $id => $group): ?>
            <div class="clearfix">
                <?php foreach($group as $key => $row):?>.
                    <div class="<?php print $add_class; ?> wow <?php print $animate_class[$key%count($animate_class)]?>" data-wow-delay="<?php print ($delay_time+($key*$delay_step));?>s">
                        <?php print $row ?>
                    </div>
                <?php endforeach;?>
            </div>
        <?php endforeach ?>
      <?php else: ?>
        <?php foreach ($outputArr as $id => $group): ?>
            <div class="clearfix">
                <?php foreach ($group as $key => $row): ?>
                    <div class="<?php print $add_class; ?>  wow <?php print $animate_class[$key];?>" data-wow-delay="<?php print ($delay_time+($key*$delay_step));?>s">
                        <?php print $row ?>
                    </div>
                <?php endforeach ?>
            </div>
        <?php endforeach ?>
      <?php endif; ?>
    <?php else: ?>
        <?php foreach ($outputArr as $id => $group): ?>
            <div class="clearfix">
              <?php foreach ($rows as $key => $row): ?>
                <div class="<?php print $add_class; ?>  wow <?php print $animate_class[$random];?>" data-wow-delay="<?php print ($delay_time+($key*$delay_step));?>s">
                    <?php print $row ?>
                </div>
              <?php endforeach ?>
            </div>
        <?php endforeach ?>
    <?php endif; ?>
<?php else: ?>
    <?php foreach ($rows as $id => $row): ?>
        <div class="<?php print $add_class; ?>  wow <?php print $animate_class[$random];?>" data-wow-delay="<?php print ($delay_time+($key*$delay_step));?>s"">
            <?php print $row; ?>
        </div>
    <?php endforeach; ?>
<?php endif;?>