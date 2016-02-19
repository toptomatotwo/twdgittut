<?php global $base_url;?>
<div class="loading">
    <!-- <img class="loading-gif" src="<?php print $base_url.'/'.drupal_get_path('theme','unikue')?>/img/preloader2.gif" alt="preloader2.gif"> -->
  <div class="load">
  <div class="gear gearone">
    <svg id="blue" viewbox="0 0 100 100" fill="#645857">
      <path d="M97.6,55.7V44.3l-13.6-2.9c-0.8-3.3-2.1-6.4-3.9-9.3l7.6-11.7l-8-8L67.9,20c-2.9-1.7-6-3.1-9.3-3.9L55.7,2.4H44.3l-2.9,13.6      c-3.3,0.8-6.4,2.1-9.3,3.9l-11.7-7.6l-8,8L20,32.1c-1.7,2.9-3.1,6-3.9,9.3L2.4,44.3v11.4l13.6,2.9c0.8,3.3,2.1,6.4,3.9,9.3      l-7.6,11.7l8,8L32.1,80c2.9,1.7,6,3.1,9.3,3.9l2.9,13.6h11.4l2.9-13.6c3.3-0.8,6.4-2.1,9.3-3.9l11.7,7.6l8-8L80,67.9      c1.7-2.9,3.1-6,3.9-9.3L97.6,55.7z M50,65.6c-8.7,0-15.6-7-15.6-15.6s7-15.6,15.6-15.6s15.6,7,15.6,15.6S58.7,65.6,50,65.6z"></path>
    </svg>
  </div>
  <div class="gear geartwo">
    <svg id="pink" viewbox="0 0 100 100" fill="#00044a">
      <path d="M97.6,55.7V44.3l-13.6-2.9c-0.8-3.3-2.1-6.4-3.9-9.3l7.6-11.7l-8-8L67.9,20c-2.9-1.7-6-3.1-9.3-3.9L55.7,2.4H44.3l-2.9,13.6      c-3.3,0.8-6.4,2.1-9.3,3.9l-11.7-7.6l-8,8L20,32.1c-1.7,2.9-3.1,6-3.9,9.3L2.4,44.3v11.4l13.6,2.9c0.8,3.3,2.1,6.4,3.9,9.3      l-7.6,11.7l8,8L32.1,80c2.9,1.7,6,3.1,9.3,3.9l2.9,13.6h11.4l2.9-13.6c3.3-0.8,6.4-2.1,9.3-3.9l11.7,7.6l8-8L80,67.9      c1.7-2.9,3.1-6,3.9-9.3L97.6,55.7z M50,65.6c-8.7,0-15.6-7-15.6-15.6s7-15.6,15.6-15.6s15.6,7,15.6,15.6S58.7,65.6,50,65.6z"></path>
    </svg>
  </div>
  <div class="gear gearthree">
    <svg id="yellow" viewbox="0 0 100 100" fill="#e61c3f">
      <path d="M97.6,55.7V44.3l-13.6-2.9c-0.8-3.3-2.1-6.4-3.9-9.3l7.6-11.7l-8-8L67.9,20c-2.9-1.7-6-3.1-9.3-3.9L55.7,2.4H44.3l-2.9,13.6      c-3.3,0.8-6.4,2.1-9.3,3.9l-11.7-7.6l-8,8L20,32.1c-1.7,2.9-3.1,6-3.9,9.3L2.4,44.3v11.4l13.6,2.9c0.8,3.3,2.1,6.4,3.9,9.3      l-7.6,11.7l8,8L32.1,80c2.9,1.7,6,3.1,9.3,3.9l2.9,13.6h11.4l2.9-13.6c3.3-0.8,6.4-2.1,9.3-3.9l11.7,7.6l8-8L80,67.9      c1.7-2.9,3.1-6,3.9-9.3L97.6,55.7z M50,65.6c-8.7,0-15.6-7-15.6-15.6s7-15.6,15.6-15.6s15.6,7,15.6,15.6S58.7,65.6,50,65.6z"></path>
    </svg>
  </div>
  <div class="lil-circle"></div>
  <svg class="blur-circle">
    <filter id="blur">
      <fegaussianblur in="SourceGraphic" stddeviation="13"></fegaussianblur>
    </filter>
    <circle cx="70" cy="70" r="66" fill="transparent" stroke="white" stroke-width="40" filter="url(#blur)"></circle>
  </svg>
</div>
<div class="text">loading</div>
    
        
</div>
<!-- navigation -->
<div class="w-nav navbar" data-collapse="medium" data-animation="default" data-duration="400" data-contain="1">
    <?php if(isset($menu_social)):?>
    <div class="social-div">
        <?php print $menu_social;?>
    </div>
    <?php endif;?>
    <div class="w-container container-nav">
        <a class="w-nav-brand brand" href="<?php print $base_url;?>" data-ix="fade-down"><!-- here is the logo -->
            <!--<img class="logo" src="/sites/default/files/logos/logo-v2.png" alt="LexwebDev logo" data-ix="fade-down"> -->
            Tom Carden <span>Website Portfolio</span>
        </a>
        <!-- nav tag -->
        <?php if($is_portfolio == FALSE):?>
            <?php if($page['navigation']):?>
                <?php print render($page['navigation']);?>
            <?php endif;?>
        <?php else: ?>
            <div class="w-clearfix button-single">
                <?php if(isset($next_link)):?>
                <a class="button single" href="<?php print $next_link;?>" data-ix="fade-down-4"><?php print t('Next project');?></a>
                <?php endif;?>
                <a class="button single fa fa-th" href="<?php print $base_url.'/#project';?>" data-ix="fade-down-3"></a>
                <?php if(isset($prev_link)):?>
                <a class="button single" href="<?php print $prev_link;?>" data-ix="fade-down-2"><?php print t('previous project');?></a>
                <?php endif;?>
            </div>
        <?php endif;?>
        <div class="w-nav-button menu-button">
            <div class="w-icon-nav-menu"></div>
        </div>
    </div>
</div><!-- end navigation -->
<!-- start slider -->

<?php if($page['header']):?>
    <?php print render($page['header']);?>
<?php endif;?>

<?php if(theme_get_setting('enable_dot_navigation')):?>
    <?php if(isset($dot_navigation)):?>
        <?php print $dot_navigation;?>
    <?php endif;?>
<?php endif;?>