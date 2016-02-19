<footer class="section">
    <div class="footer" id="footer">
        <div class="w-container">
            <?php if($page['footer']):?>
                <?php print render($page['footer']);?>
            <?php endif;?>
            <?php if(isset($footer_social)):?>
            <div class="social-div in-footer">
                <!-- <?php print $footer_social;?> -->
            </div>
            <?php endif;?>
            <img class="logo_footer" src="/sites/all/themes/unikue/img/ico_57.png" alt="">
            <div class="footer_copyright"><?php print theme_get_setting('footer_text');?></div>
        </div>
    </div>
</footer><!-- end footer -->

<script type="text/javascript">

</script>